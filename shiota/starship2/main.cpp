#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <queue>

using namespace std;

using Int = long long;

const Int dx[] = {-1, 0,  1, -1, 0, 1, -1, 0, 1};
const Int dy[] = {-1, -1,  -1, 0, 0, 0, 1, 1, 1};

vector<pair<int, int>> input(){
    vector<pair<int, int> > vg;
    int x, y;
    while(cin >> x >> y){
        vg.push_back(make_pair(x, y));
    }
    return vg;
}

vector<pair<Int, Int> > distAndAccel;

vector<Int> trip_hist_by_dist(Int _dist, Int posi, Int nega){
    vector<Int> hist;
    Int accelCnt = 0;
    Int dist = _dist;
    for(int i = distAndAccel.size() -1; i>=0; i--){
        if(dist >= distAndAccel[i].first){
            dist -= distAndAccel[i].first;
            accelCnt = distAndAccel[i].second;
            break;
        }
    }
    map<Int, Int> idle;
    for(Int i = accelCnt; i>0; i--){
        while(dist - i >= 0){
            idle[i]++;
            dist -= i;
        }
    }
    for(Int i = 1; i<=accelCnt; i++){
        hist.push_back(posi);
        for(Int j = 0; j<idle[i]; j++){
          hist.push_back(5);
        }
    }
    for(Int i = 1; i<=accelCnt; i++){
        hist.push_back(nega);
    }
    return hist;
}

vector<Int> solve(vector<pair<int, int> > &vg){
    Int xs =0, ys = 0;
    vector<Int> ret;
    for(int i = 0; i<vg.size(); i++) {
        int cnt = 0;
        vector<Int> histX, histY;
        {
            Int xg = vg[i].first;
            Int posi = 6, nega = 4;
            if (xs > xg) {
                swap(posi, nega);
            }
            histX = trip_hist_by_dist(abs(xg - xs), posi, nega);
            xs = xg;
        }
        {
            Int yg = vg[i].second;
            Int posi = 8, nega = 2;
            if (ys > yg) {
                swap(posi, nega);
            }
            histY = trip_hist_by_dist(abs(yg - ys), posi, nega);
            ys = yg;
        }
        for(int i = 0; i<histX.size() && i < histY.size(); i++){
            if(histX[i] == 5){
                ret.push_back(histY[i]);
            }else if(histY[i] == 5) {
                ret.push_back(histX[i]);
            }else if(histX[i]==6 && histY[i] == 8){
                ret.push_back(9);
            }else if(histX[i]==6 && histY[i] == 2) {
                ret.push_back(3);
            }else if(histX[i]==4 && histY[i] == 8) {
                ret.push_back(7);
            }else if(histX[i]==4 && histY[i] == 2) {
                ret.push_back(1);
            } else{
                assert(false);
            }
            cnt++;
        }
        if(histX.size() > cnt){
            for(int i = cnt; i<histX.size(); i++){
                ret.push_back(histX[i]);
                cnt++;
            }
        } else {
            for(int i = cnt; i<histY.size(); i++){
                ret.push_back(histY[i]);
                cnt++;
            }
        }
    }
    return ret;
}

vector<pair<int, int> > nearOrder(const vector<pair<int, int> > &vg){
    int xs, ys;
    xs = ys = 0;

    vector<pair<int, int> > ret;
    bool used[vg.size()];
    for(int i = 0; i<vg.size(); i++){
        used[i] = false;
    }
    for(int i =0 ; i<vg.size(); i++){
        int minDist = 1e9;
        int select = -1;
        for(int j = 0; j<vg.size(); j++){
            if(used[j]) continue;
            int dist = max(trip_hist_by_dist(vg[j].first - xs, 0,0).size(),
                        trip_hist_by_dist(vg[j].second - ys, 0, 0).size());
            if(dist < minDist){
                minDist = dist;
                select = j;
            }
        }
        ret.push_back(vg[select]);
        used[select] = true;
    }
    return ret;
}

int main() {
    for(Int i = 1; i<100000; i++){
        distAndAccel.push_back(make_pair(i*i, i));
    }
    vector<vector<Int>> anss;
    auto vg = (input());
    if(vg.size() <= 5000){
        vector<pair<int, int> > no = nearOrder(vg);
        anss.push_back(solve(no));
    }
    {
        vector<pair<int, int> > xo = vg;
        sort(xo.begin(), xo.end());
        anss.push_back(solve(xo));
        reverse(xo.begin(), xo.end());
        anss.push_back(solve(xo));
    }
    {
        vector<pair<int, int> > yo = vg;
        for(int i = 0; i<yo.size(); i++){
            swap(yo[i].first, yo[i].second);
        }
        sort(yo.begin(), yo.end());
        for(int i = 0; i<yo.size(); i++){
            swap(yo[i].first, yo[i].second);
        }
        anss.push_back(solve(yo));
        reverse(yo.begin(), yo.end());
        anss.push_back(solve(yo));
    }
    Int miniAns = 1e9;
    vector<Int> ans;
    for(vector<Int> v : anss){
        if(v.size() < miniAns){
            miniAns = v.size();
            ans = v;
        }
    }
    for(Int i = 0; i<ans.size(); i++){
        cout << ans[i];
    }
    cout <<endl;
    return 0;
}
