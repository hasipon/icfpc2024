#include <iostream>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
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
    int nextCost;
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
    int nextCost;
};
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

void solveMoveAndStop(TwoDState &st, pair<int, int> g){
    int xs = st.p.first, ys = st.p.second;
    int cnt = 0;
    vector<Int> histX, histY;
    {
        Int xg = g.first;
        Int posi = 6, nega = 4;
        if (xs > xg) {
            swap(posi, nega);
        }
        histX = trip_hist_by_dist(abs(xg - xs), posi, nega);
        xs = xg;
    }
    {
        Int yg = g.second;
        Int posi = 8, nega = 2;
        if (ys > yg) {
            swap(posi, nega);
        }
        histY = trip_hist_by_dist(abs(yg - ys), posi, nega);
        ys = yg;
    }
    for(int i = 0; i<histX.size() && i < histY.size(); i++){
        if(histX[i] == 5){
            st.history.push_back(histY[i]);
        }else if(histY[i] == 5) {
            st.history.push_back(histX[i]);
        }else if(histX[i]==6 && histY[i] == 8){
            st.history.push_back(9);
        }else if(histX[i]==6 && histY[i] == 2) {
            st.history.push_back(3);
        }else if(histX[i]==4 && histY[i] == 8) {
            st.history.push_back(7);
        }else if(histX[i]==4 && histY[i] == 2) {
            st.history.push_back(1);
        } else{
            assert(false);
        }
        cnt++;
    }
    if(histX.size() > cnt){
        for(int i = cnt; i<histX.size(); i++){
            st.history.push_back(histX[i]);
            cnt++;
        }
    } else {
        for(int i = cnt; i<histY.size(); i++){
            st.history.push_back(histY[i]);
            cnt++;
        }
    }
    st.p = g;
    st.v = make_pair(0, 0);
    st.nextCost = 0;
}


map<pair<int, int>, int> solve1DMemo;

// TODO:
// 到達速度ごとに最小のコストを出しているけど、同じ速度でコストが高い方が良い場合も有るかもしれない？ので、嘘を含む
// 経路をもつのでなく、復元する
// 正負まとめる
map<int, vector<OneDState>> solve1D(const int _v, const int _dist,  map<int, int> comm, int beam, int nextDist){
    const int vLimit = max(max(int(sqrt(abs(_dist))), abs(_v)), 20);
    const int pLimit = max(max(abs(_dist), (_v*_v)/2), 20);
    // cerr << vLimit << ' ' << pLimit <<endl;

    auto ret = map<int, vector<OneDState>>();
    map<OneDState, int> minCost;
    priority_queue<pair<int, OneDState>> Q;
    {
        auto start = OneDState({
                                       0, _v, vector<int>()
                               });
        Q.push(make_pair(0, start));
        if(_v == 0 && _dist == 0){
            for(int i = 0; i < pLimit; i++){
                start.history.push_back(5);
                Q.push(make_pair(-start.history.size(), start));
                ret[start.history.size()].push_back(start);
            }
        }

    }
    set<OneDState> visited;
    while(!Q.empty()){
        int cost = -Q.top().first;
        OneDState cur = Q.top().second;
        Q.pop();
        if(minCost[cur] < cost) continue;
        if(visited.count(cur)) continue;
        visited.insert(cur);
        if(cur.p == _dist){
            {
                auto memoP = make_pair(_v, _dist);
                if(solve1DMemo.count(memoP) == 0)solve1DMemo[memoP] = cost;
                else {
                    solve1DMemo[memoP] = min(solve1DMemo[memoP], cost);
                }
                if(nextDist != 1e9){
                    if(solve1DMemo.count(memoP) > 0){
                        cur.nextCost = solve1DMemo[memoP];
                    }else {
                        auto nextRes = solve1D(cur.v, nextDist, comm, 1, 1e9);
                        cur.nextCost = nextRes.begin()->first;
                    }
                }
            }

            ret[cost].push_back(cur);
            if(ret.size() >= beam){
                return ret;
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

void forceStop(TwoDState &st){
    while(st.v.first>0 && st.v.second > 0){
        st.v.first--;
        st.v.second--;
        st.history.push_back(1);
        st.p.first += st.v.first;
        st.p.second += st.v.second;
    }
    while(st.v.first>0 && st.v.second<0){
        st.v.first--;
        st.v.second++;
        st.history.push_back(7);
        st.p.first += st.v.first;
        st.p.second += st.v.second;
    }
    while(st.v.first<0 && st.v.second>0){
        st.v.first++;
        st.v.second--;
        st.history.push_back(3);
        st.p.first += st.v.first;
        st.p.second += st.v.second;
    }
    while(st.v.first<0 && st.v.second<0){
        st.v.first++;
        st.v.second++;
        st.history.push_back(9);
        st.p.first += st.v.first;
        st.p.second += st.v.second;
    }
    while(st.v.first<0){
        st.v.first++;
        st.history.push_back(6);
        st.p.first += st.v.first;
        st.p.second += st.v.second;
    }
    while(st.v.first>0){
        st.v.first--;
        st.history.push_back(4);
        st.p.first += st.v.first;
        st.p.second += st.v.second;
    }
    while(st.v.second<0){
        st.v.second++;
        st.history.push_back(8);
        st.p.first += st.v.first;
        st.p.second += st.v.second;
    }
    while(st.v.second>0){
        st.v.second--;
        st.history.push_back(2);
        st.p.first += st.v.first;
        st.p.second += st.v.second;
    }
    assert(st.v.first == 0 && st.v.second == 0);
}


vector<int> solveDijskstra(const vector<pair<int, int> > &vg, const int nowBest, const int beam, const int pid){
    cerr << "vg size " << vg.size() <<endl;
    cerr << "nowBest " << nowBest <<endl;

    TwoDState last;
    auto nowState = vector<TwoDState>(1, {{0, 0}, {0, 0}, vector<int>()});
    for(int posi = 0; posi<vg.size(); posi++) {
        auto nextPos = vg[posi];
        cerr << "(" << nowState[0].p.first << "," << nowState[0].p.second << ") => (" << nextPos.first << "," << nextPos.second<< ")" << endl;
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
                int nextDist = 1e9;
                if(posi +1 <vg.size()){
                    nextDist = vg[posi+1].first - nextPos.first;
                }
                xResult = solve1D(v.first, nextPos.first - s.first, comm, beam, nextDist);
            }
            // y
            map<int, vector<OneDState>> yResult;
            {
                map<int, int> comm;
                comm[-1] = 2;
                comm[0] = 5;
                comm[1] = 8;
                int nextDist = 1e9;
                if(posi +1 <vg.size()){
                    nextDist = vg[posi+1].first - nextPos.first;
                }
                yResult = solve1D(v.second, nextPos.second - s.second, comm,beam, nextDist);
            }
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
                        nextState.push_back({nextPos, {x.v, y.v}, hist, max(x.nextCost, y.nextCost)});
                    }
                }
            }

            TwoDState toStop = nowState[si];
            forceStop(toStop);
            solveMoveAndStop(toStop, nextPos);
            // nextState.push_back(toStop);
        }

        nowState.clear();
        sort(nextState.begin(), nextState.end(), [&](const TwoDState &lhs, const TwoDState &rhs){
            return lhs.history.size() + lhs.nextCost < rhs.history.size() + rhs.nextCost;
        });
        for(int i = 0; i<min(beam, int(nextState.size())); i++){
            if(nextState[i].history.size() < nowBest){
                nowState.push_back(nextState[i]);
            }
        }
        if(!nowState.empty()){
            last = nowState[0];
        }else {
            break;
        }
        cerr << "problem id = " << pid << " step == " << posi  << " cost = " << nowState[0].history.size() << " nowState.size() " << nowState.size() << endl;
    }
    if(nowState.empty()){
        cerr << "failed "<<endl;
        for(int i = 0; i < last.history.size(); i++){
            cerr << last.history[i];
        }
        cerr << endl;
        return last.history;
    }
    return nowState[0].history;
}


vector<pair<int, int>> input(){
    vector<pair<int, int> > vg;
    int x, y;
    set<pair<int, int>> used;
    used.insert(make_pair(0, 0));
    string hoge;
    getline(cin, hoge);
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

map<int, int> beamMap;
void buildBeamMap(){
    for(int i = 0; i<30;i++)beamMap[i] = 100;
    beamMap[11] = 1;
    beamMap[13] = 100;
    beamMap[14] = 100;
}


int main(int argc, char **argv) {
    for(Int i = 1; i<1000; i++){
        distAndAccel.push_back(make_pair(i*i, i));
    }
    buildBeamMap();
    int pid = atoi(argv[1]);
    cerr << "PID = " << pid << endl;
    int beam =beamMap[pid];
    vector<vector<int>> anss;
    int nowBest = 1000001;
    auto vg = (input());
    updateAnss(anss, solveDijskstra(vg, nowBest, beam, pid), nowBest);

    /*
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
    for(vector<int> v : anss){
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
    cerr << "problem = " << pid << " ans.size() = " << ans.size() << endl;
    return 0;
}
