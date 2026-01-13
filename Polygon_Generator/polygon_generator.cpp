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

using namespace std;
// data points struct
struct Pt { double x,y; };
// cross product of AB and AC(Positive if C lies to the left of AB, negative if to the right)
inline double cross(const Pt& a,const Pt& b,const Pt& c){
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}
// Twice the signed area of polygon P (Positive if CCW, negative if CW)
inline double area2(const vector<Pt>& P){
    double A=0;
    for (size_t i=0;i<P.size();++i){
        size_t j=(i+1)%P.size();
        A+=P[i].x*P[j].y-P[j].x*P[i].y;
    }
    return A;
}
// check orientation
inline bool is_ccw(const vector<Pt>& P){ return area2(P) > 0; }
// generate random simple polygon
vector<Pt> random_simple_polygon(int n,mt19937& rng,double scale){
    uniform_real_distribution<double> dist(-scale,scale);
    // generate random points in bounding square
    vector<Pt> pts(n);
    for (int i=0;i<n;++i){ pts[i].x=dist(rng);pts[i].y=dist(rng); }
    // compute centroid of points
    double cx=0,cy=0;
    for (auto& p : pts){ cx+=p.x;cy+=p.y; }
    cx /= n;cy /= n;
    // sort points by angle around centroid
    sort(pts.begin(),pts.end(),[&](const Pt& a,const Pt& b){
        return atan2(a.y-cy,a.x-cx)<atan2(b.y-cy,b.x-cx);
        });
    // ensure CCW orientation
    if (!is_ccw(pts))reverse(pts.begin(),pts.end());
    return pts;
}
// Write polygon vertices to a CSV file
void write_polygon_csv(const string& fname,const vector<Pt>& poly){
    ofstream ofs(fname);
    ofs<<"x,y\n";
    ofs<<fixed<<setprecision(9);
    for (auto& p : poly)ofs<<p.x<<","<<p.y<<"\n";
    ofs.close();
}
int main(){
    vector<int> ns={ 30,60,100,200,500 };
    random_device rd;mt19937 rng(rd());
    for (int n : ns){
        auto poly=random_simple_polygon(n,rng,100);
        string fname="polygon_n"+to_string(n)+".csv";
        write_polygon_csv(fname,poly);
    }
    return 0;
}

