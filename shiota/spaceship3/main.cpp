#include <iostream>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <set>

using namespace std;


using Int = long long;
const Int dx[] = {-1, 0,  1, -1, 0, 1, -1, 0, 1};
const Int dy[] = {-1, -1,  -1, 0, 0, 0, 1, 1, 1};

class OneDState{
public:
    int p, v;
    vector<int> history;
    bool operator<(const OneDState &rhs) const {
        if(p != rhs.p) return p < rhs.p;
         return v < rhs.v;
    }
};

class TwoDState{
public:
    pair<int, int> p;
    pair<int, int> v;
    vector<int> history;
};


// TODO:
// 到達速度ごとに最小のコストを出しているけど、同じ速度でコストが高い方が良い場合も有るかもしれない？ので、嘘を含む
// 経路をもつのでなく、復元する
// 正負まとめる
map<int, vector<OneDState>> solve1D(const int _v, const int _dist,  map<int, int> comm){
    const int vLimit = max(sqrt(abs(_dist)), 100.);
    const int pLimit = max(abs(_dist)*2 + _v*_v, 100);

    map<OneDState, int> minCost;
    priority_queue<pair<int, OneDState>> Q;
    {
        auto start = OneDState({
                                       0, _v, vector<int>()
                               });
        Q.push(make_pair(0, start));
        if(_v == 0){
            for(int i = 0; i < pLimit; i++){
                start.history.push_back(5);
                Q.push(make_pair(-start.history.size(), start));
            }
        }

    }
    auto ret = map<int, vector<OneDState>>();
    while(!Q.empty()){
        int cost = -Q.top().first;
        OneDState cur = Q.top().second;
        Q.pop();
        // if(minCost[cur] < cost) continue;
        if(cur.p == _dist){
            ret[cost].push_back(cur);
            if(cur.v == 0){
                for(int i = 0; i < pLimit; i++){
                    cur.history.push_back(5);
                    cost++;
                    ret[cost].push_back(cur);
                }
            }
        }
        for(int i = -1; i<=1; i++){
            OneDState next = cur;
            next.v += i;
            next.p += next.v;
            if(next.v > vLimit || next.v < -vLimit || next.p > pLimit || next.p < -pLimit)continue;

            int nextCost = cost + 1;
            if(minCost.find(next) == minCost.end() || minCost[next] > nextCost){
                minCost[next] = nextCost;
                next.history.push_back(comm[i]);
                Q.push(make_pair(-nextCost, next));
            }
        }
    }
    return ret;
}


vector<int> solveDijskstra(const vector<pair<int, int> > &vg, const int nowBest){
    cerr << "nowBest " << nowBest <<endl;
    const int beam = 100;

    auto nowState = vector<TwoDState>(1, {{0, 0}, {0, 0}, vector<int>()});
    for(int posi = 0; posi<vg.size(); posi++) {
        auto nextPos = vg[posi];
        vector<TwoDState> nextState = vector<TwoDState>();
        for (int si = 0; si < nowState.size(); si++) {
            auto s = nowState[si].p;
            auto v = nowState[si].v;
            if (nextPos == s) continue;
            // x
            map<int, vector<OneDState>> xResult;
            {
                map<int, int> comm;
                comm[-1] = 4;
                comm[0] = 5;
                comm[1] = 6;
                xResult = solve1D(v.first, nextPos.first - s.first, comm);
            }
            // y
            map<int, vector<OneDState>> yResult;
            {
                map<int, int> comm;
                comm[-1] = 2;
                comm[0] = 5;
                comm[1] = 8;
                yResult = solve1D(v.second, nextPos.second - s.second, comm);
            }
            // for (auto c: xResult) {
            //     cerr << "xcost = " << c.first <<" size "<< c.second.size() << endl;
            // }
            // for (auto c: yResult) {
            //     cerr << "ycost = " << c.first <<" size "<< c.second.size() << endl;
            // }
            for (auto c: xResult) {
                int cost = c.first;
                //cerr << xResult[cost].size() << ' ' << yResult[cost].size() << endl;
                for (auto x: xResult[cost]) {
                    for (auto y: yResult[cost]) {
                        auto histX = x.history;
                        auto histY = y.history;
                        auto hist = nowState[si].history;
                        for (int i = 0; i < histX.size() && i < histY.size(); i++) {
                            if (histX[i] == 5) {
                                hist.push_back(histY[i]);
                            } else if (histY[i] == 5) {
                                hist.push_back(histX[i]);
                            } else if (histX[i] == 6 && histY[i] == 8) {
                                hist.push_back(9);
                            } else if (histX[i] == 6 && histY[i] == 2) {
                                hist.push_back(3);
                            } else if (histX[i] == 4 && histY[i] == 8) {
                                hist.push_back(7);
                            } else if (histX[i] == 4 && histY[i] == 2) {
                                hist.push_back(1);
                            } else {
                                cerr << histX[i] << ' ' << histY[i] << endl;
                                assert(false);
                            }
                        }
                        nextState.push_back({nextPos, {x.v, y.v}, hist});
                    }
                }
            }
        }
        nowState.clear();
        sort(nextState.begin(), nextState.end(), [&](const TwoDState &lhs, const TwoDState &rhs){
            return lhs.history.size() < rhs.history.size();
        });
        for(int i = 0; i<min(beam, int(nextState.size())); i++){
            if(nextState[i].history.size() < nowBest){
                nowState.push_back(nextState[i]);
            }
        }
        cerr << "step == " << posi  << " nowState.size() " << nowState.size() << endl;
    }
    return nowState[0].history;
}


vector<pair<int, int>> input(){
    vector<pair<int, int> > vg;
    int x, y;
    set<pair<int, int>> used;
    used.insert(make_pair(0, 0));
    while(cin >> x >> y){
        if(used.count(make_pair(x, y))) continue;
        vg.push_back(make_pair(x, y));
        used.insert(make_pair(x, y));
    }
    return vg;
}

vector<pair<int, int> > nearOrder(const vector<pair<int, int> > &vg){
    int xs, ys, xv, yv;
    xs = ys = xv = yv = 0;

    vector<pair<int, int> > ret;
    bool used[vg.size()];
    map<int, int> xmap;
    bool foundPosi=false;
    for(int i = 0; i<vg.size(); i++){
        used[i] = false;
        if(vg[i].first > 0 && !foundPosi){
            xmap[0] = i;
            foundPosi = true;
        }
        xmap[vg[i].first] = i;
    }

    for(int i =0 ; i<vg.size(); i++){
        vector<pair<int, int> > beam;
        int id= xmap[xs];
        cerr << i << endl;
        while(id > 0 && vg[id].first >= xs - 800){
            id--;
        }
        cerr << "begin: " << id << endl;
        while(id < vg.size() && vg[id].first <= xs + 800){
            if(used[id]) {
                id++;
                continue;
            }
            if(xs == -165 && ys == -173){
                if(vg[id].first != -168 || vg[id].second != 175){
                    id++;
                    continue;
                }
            }
            // int dist = max(trip_hist_by_dist(abs(vg[j].first - xs), 0,0).size() ,
            // trip_hist_by_dist(abs(vg[j].second - ys), 0, 0).size());

            // int dist = max(abs(vg[j].first - xs), abs(vg[j].second - ys ));
            int dist = abs(vg[id].first - xs) + abs(vg[id].second - ys );
            // int dist = max(smartDist(xv-1, vg[j].first - xs), smartDist(yv-1, vg[j].second - ys));
            beam.push_back(make_pair(dist, id));
            id++;
        }
        cerr << "end: " << id << endl;

        sort(beam.begin(), beam.end());
        /*
        int mini = 1e9, select = 0;
        State miniRes;
        for(int j = 0; j<min(int(beam.size()), 3); j++){
            if(beam[j].first - beam[0].first > 1)continue;
            int now = beam[j].second;
            vector<pair<int, int> > target;
            target.push_back(vg[now]);
            auto res = dijkstra(xs, ys, xv, yv,  1e9, target, vg[now]);
            if(res.second.size() <0){
                continue;
            }
            if(res.second.size() < mini){
                mini = res.second.size();
                select = now;
                miniRes = res.first;
            }
        }//*/
         int select = beam[0].second;
        ret.push_back(vg[select]);
        used[select] = true;
        xs = vg[select].first;
        ys = vg[select].second;
        // xv = miniRes.vx;
        // yv = miniRes.vy;
    }
    for(int i = 0; i<vg.size(); i++){
        if(!used[i])return vector<pair<int, int> >();
         // cout << ret[i].first << ' ' << ret[i].second << endl;
    }
    assert(vg.size() == ret.size());
    return ret;
}

void updateAnss(vector<vector<int>> &anss, const vector<int> &ans, int &nowBest){
    if(ans.empty()) return;
    if(ans.size() < nowBest){
        anss.push_back(ans);
        nowBest = ans.size();
        for(Int i = 0; i<ans.size(); i++){
            cerr << ans[i];
        }
        cerr << endl;
    }
}

int main() {
    vector<vector<int>> anss;
    int nowBest = 1000001;
    auto vg = (input());

    // x_order
    {
        vector<pair<int, int> > xo = vg;
        sort(xo.begin(), xo.end());
        {
            vector<pair<int, int> > no = nearOrder(xo);
            if(!no.empty()){
                //updateAnss(anss, solve(no, nowBest), nowBest);
                updateAnss(anss, solveDijskstra(no, nowBest), nowBest);
            }
        }
        //reverse(xo.begin(), xo.end());
        //{
        //    vector<pair<int, int> > no = nearOrder(xo);
        //    if(!no.empty()) {
        //        //updateAnss(anss, solve(no, nowBest), nowBest);
        //        updateAnss(anss, solveDijskstra(no, nowBest), nowBest);
        //    }
        //}
    }
    /*
    {
        vector<pair<int, int> > yo = vg;
        for(int i = 0; i<yo.size(); i++){
            swap(yo[i].first, yo[i].second);
        }
        sort(yo.begin(), yo.end());
        for(int i = 0; i<yo.size(); i++){
            swap(yo[i].first, yo[i].second);
        }
        {
            vector<pair<int, int> > no = nearOrder(yo);
            if(!no.empty()) {
                // updateAnss(anss, solve(no, nowBest), nowBest);
                updateAnss(anss, solveDijskstra(no, nowBest), nowBest);
            }
        }
        reverse(yo.begin(), yo.end());
        {
            vector<pair<int, int> > no = nearOrder(yo);
            if(!no.empty()) {
                // updateAnss(anss, solve(no, nowBest), nowBest);
                updateAnss(anss, solveDijskstra(no, nowBest), nowBest);
            }
        }
    }
     */
    Int miniAns = 1e9;
    vector<int> ans;
    int id = 0;
    for(vector<int> v : anss){
        cerr << "id: " << id << " size: " << v.size() << endl;
        id++;
        if(v.empty()) continue;
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
