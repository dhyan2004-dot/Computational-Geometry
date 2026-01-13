#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <numeric> 
#include <random>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>

using namespace std;
using Clock=chrono::steady_clock;
// data points struct
struct Pt{double x,y;};
// cross product of AB and AC (Positive if C lies to the left of AB, negative if to the right)
inline double cross(const Pt& a,const Pt& b,const Pt& c){
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}
// if given point is inside triangle
inline bool if_point_in_triangle(const Pt& p,const Pt& a,const Pt& b,const Pt& c){
    double A=fabs(cross(a,b,c));
    double A1=fabs(cross(p,b,c)),A2=fabs(cross(a,p,c)),A3=fabs(cross(a,b,p));
    return fabs(A-(A1+A2+A3))<1e-12 && A1>1e-12 && A2>1e-12 && A3>1e-12;
}
// read generated polygons from csv files
vector<Pt> read_polygon(const string&fname) {
    ifstream ifs(fname);string line;getline(ifs,line);
    vector<Pt> poly;double x,y;char comma;
    while(ifs>>x>>comma>>y){poly.push_back({x,y});}
    return poly;
}
// Recursive(naive) triangulation
vector<array<int,3>> naive_triangulate_recursive(vector<int> idx,const vector<Pt>& poly){
    vector<array<int,3>> tris;
    // Base case
    if(idx.size()==3){
        tris.push_back({idx[0],idx[1],idx[2]});
        return tris;
    }
    int m=idx.size();
    for(int i=0;i<m;++i){
        int prev=idx[(i-1+m)%m];
        int cur=idx[i];
        int next=idx[(i+1)%m];
        // check convexity
        if(cross(poly[prev],poly[cur],poly[next])<=0) continue;
        // check no other point inside triangle
        bool ok=true;
        for(int j:idx){
            if(j==prev||j==cur||j==next) continue;
            if(if_point_in_triangle(poly[j],poly[prev],poly[cur],poly[next])){
                ok=false;
                break;
            }
        }
        if(ok){
            // found an ear
            tris.push_back({prev,cur,next});
            // remove this ear vertex
            vector<int>new_idx=idx;
            new_idx.erase(new_idx.begin()+i);
            // recurse on smaller polygon
            auto rest=naive_triangulate_recursive(new_idx,poly);
            tris.insert(tris.end(), rest.begin(), rest.end());
            return tris; // return after first ear found
        }
    }
    // no ear found (not possible if polygon is simple & CCW)
    return tris;
}
vector<array<int,3>> naive_triangulate(const vector<Pt>& poly){
    vector<int> idx(poly.size());
    iota(idx.begin(),idx.end(),0);
    return naive_triangulate_recursive(idx,poly);
}
// optimal ear clipping
vector<array<int,3>> opt_triangulate(const vector<Pt>& poly){
    int n=poly.size();vector<int>prev(n),next(n);vector<char>alive(n,1);
    // initialize doubly-linked structure
    for(int i=0;i<n;++i){prev[i]=(i-1+n)%n;next[i]=(i+1)%n;}
    // convexity check
    auto is_convex=[&](int i){return cross(poly[prev[i]],poly[i],poly[next[i]])>1e-12;};
    // ear validity
    auto ear=[&](int i){
        if(!is_convex(i)) return false;
        Pt a=poly[prev[i]],b=poly[i],c=poly[next[i]];
        int j=next[next[i]];while(j!=prev[i]){
            if(alive[j] && if_point_in_triangle(poly[j],a,b,c)) return false;
            j=next[j];
        }return true;
        };
    // ear flags
    vector<char>is_ear(n,0);for(int i=0;i<n;++i) is_ear[i]=ear(i);
    int rem=n;vector<array<int,3>>tris;int i=0;
    // until only 3 vertices remain
    while(rem>3) {
        // Find next ear
        while((!alive[i]||!is_ear[i]))i=next[i];
        int a=prev[i],b=i,c=next[i];
        tris.push_back({a,b,c});
        // Remove vertex b
        alive[b]=0;next[a]=c;prev[c]=a;
        // Update ear status for neighbors
        is_ear[a]=ear(a);is_ear[c]=ear(c);rem--;
        i=c;
    }
    // Add the final triangle
    vector<int>R;for(int k=0;k<n;++k)if(alive[k])R.push_back(k);
    if(R.size()==3) tris.push_back({R[0],R[1],R[2]});
    return tris;
}
// CGAL-delaunay triangulation
using K=CGAL::Exact_predicates_inexact_constructions_kernel;
using CDT=CGAL::Constrained_Delaunay_triangulation_2<K>;
using Point=K::Point_2;
vector<array<int,3>> cgal_triangulate(const vector<Pt>& poly,vector<Pt>& out) {
    CDT cdt; vector<CDT::Vertex_handle> vh;
    // Insert vertices
    for(auto& p:poly) vh.push_back(cdt.insert(Point(p.x,p.y)));
    // Insert polygon edges as constraints
    for(size_t i=0;i<poly.size();++i) cdt.insert_constraint(vh[i],vh[(i+1)%poly.size()]);
    // Map vertex coordinates to indices
    map<pair<double, double>,int> id;out.clear();int idx=0;
    for(auto vit=cdt.finite_vertices_begin();vit!=cdt.finite_vertices_end();++vit){
        double x=vit->point().x(),y=vit->point().y();id[{x,y}]=idx++;out.push_back({x,y});
    }
    // Collect triangle faces
    vector<array<int,3>> tris;
    for(auto fit=cdt.finite_faces_begin();fit!=cdt.finite_faces_end();++fit){
        if(cdt.is_infinite(fit)) continue;
        auto v0=fit->vertex(0)->point(),v1=fit->vertex(1)->point(),v2=fit->vertex(2)->point();
        tris.push_back({id[{v0.x(),v0.y()}],id[{v1.x(),v1.y()}],id[{v2.x(),v2.y()}]});
    } return tris;
}
// writing csv for visualization
void write_tris(const string& fname,const vector<array<int,3>>& tris,const vector<Pt>& pts){
    ofstream ofs(fname);ofs<< "x1,y1,x2,y2,x3,y3\n";
    for (auto& t:tris){
        ofs<<pts[t[0]].x<<","<<pts[t[0]].y<<","
           <<pts[t[1]].x<<","<<pts[t[1]].y<<","
           <<pts[t[2]].x<<","<<pts[t[2]].y<<"\n";
    }
}
int main(){
    // Different polygon sizes to test
    vector<int> ns={30,60,100,200,500};
    ofstream csv("timings.csv");csv<<"n,naive,opt,cgal\n";csv.close();
    for(int n:ns){
        string fname="polygon_n"+to_string(n)+".csv";
        auto poly=read_polygon(fname);
        auto t0=Clock::now();auto nt=naive_triangulate(poly);auto t1=Clock::now();
        double naive=chrono::duration<double>(t1-t0).count();
        t0=Clock::now();auto ot=opt_triangulate(poly);t1=Clock::now();
        double opt=chrono::duration<double>(t1-t0).count();
        vector<Pt>cgalpts;t0=Clock::now();auto ct=cgal_triangulate(poly,cgalpts);t1=Clock::now();
        double cgal=chrono::duration<double>(t1-t0).count();
        ofstream csv("timings.csv",ios::app);csv<<n<<","<<naive<<","<<opt<<","<<cgal<<"\n";csv.close();
        write_tris("triang_naive_n"+to_string(n)+".csv",nt,poly);
        write_tris("triang_opt_n"+to_string(n)+".csv",ot,poly);
        write_tris("triang_cgal_n"+to_string(n)+".csv",ct,cgalpts);
        cerr<<"n="<<n<<" naive="<<naive<<" opt="<<opt<<" cgal="<<cgal<<"\n";
    }
}
