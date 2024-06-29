#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <queue>

using namespace std;


using Int = long long;
const Int dx[] = {-1, 0,  1, -1, 0, 1, -1, 0, 1};
const Int dy[] = {-1, -1,  -1, 0, 0, 0, 1, 1, 1};

class State{
public:
    Int vx, vy, px, py;
    bool operator < (const State &rhs) const {
        if(vx != rhs.vx) return vx < rhs.vx;
        if(vy != rhs.vy) return vy < rhs.vy;
        if(px != rhs.px) return px < rhs.px;
        return py < rhs.py;
    }
};

Int gcd(Int a, Int b){
    if(b == 0) return a;
    return gcd(b, a % b);
}

vector<int> genHistory(map<State, Int> &ope, State next, Int _sx, Int _sy, Int _vx, Int _vy){
    vector<int> history;
    while(next.px != _sx || next.py != _sy || next.vx != _vx || next.vy != _vy){
        int cope = ope[next]-1;
        if(cope == -1){
            cerr << "error" << endl;
            cerr << next.px << ' ' << next.py << ' ' << next.vx << ' ' << next.vy << endl;
            cerr << _sx << ' ' << _sy << ' ' << _vx << ' ' << _vy << endl;
            assert(false);
        }
        history.push_back(cope+1);
        next.px -= next.vx;
        next.py -= next.vy;
        next.vx -= dx[cope];
        next.vy -= dy[cope];
    }
    reverse(history.begin(), history.end());
    return history;
}
pair<State, vector<int>> dijkstra(int _sx, int _sy, int gx, int gy, int _vx, int _vy, int nowBest){
    map<State, Int> minCost;
    map<State, Int>  ope;
    priority_queue<pair<Int, State>> Q;

    minCost[State{_vx, _vy, _sx, _sy}] = 0;
    Q.push(make_pair(0, State{_vx, _vy, _sx, _sy}));
    if(_sx == gx && _sy == gy) return make_pair(Q.top().second, vector<int>());

    while(!Q.empty()){
        Int cost = -Q.top().first;
        if(cost > 1000 || cost > nowBest){
            return make_pair(State(), vector<int>(1, -1));
        }
        const State cur = Q.top().second;
        Q.pop();

        for(Int i = 0; i < 9; i++){
            Int vx = cur.vx + dx[i];
            Int vy = cur.vy + dy[i];

            // 嘘かも。高速化
            if(abs(cur.px + cur.vx - gx) + abs(cur.py + cur.vy - gy) <
               abs(cur.px + vx     - gx) + abs(cur.py + vy     - gy)){
               continue;
            }//*/

            Int px = cur.px + vx;
            Int py = cur.py + vy;
            State next{vx, vy, px, py};
            Int nextCost = cost + 1;

            /*
            Int div = gcd(fabs(cur.vx), fabs(cur.vy));
            if(vx != 0 && vy != 0){
                for(Int j = 1; j<div; j++){
                    Int px = cur.px + (cur.vx / div) * j;
                    Int py = cur.py + (cur.vy / div) * j;
                    if(px == gx && py == gy){
                        minCost[next] = nextCost;
                        ope[next] = i+1;
                        return make_pair(next, genHistory(ope, next, _sx, _sy, _vx, _vy));
                    }
                }
            }*/

            if(minCost.find(next) == minCost.end() || minCost[next] > nextCost){
                if(max(fabs(next.vx), fabs(next.vy)) > 4) continue;
                minCost[next] = nextCost;
                ope[next] = i+1;
                if(next.px == gx && next.py == gy){
                    return make_pair(next, genHistory(ope, next, _sx, _sy, _vx, _vy));
                }
                Q.push(make_pair(-nextCost, next));
            }
        }
    }
    cout << endl << _sx << ' ' << _sy << ' ' << gx << ' ' << gy <<' ' << _vx <<' ' << _vy <<endl;
    assert(false);
}


vector<Int> solveDijskstra(vector<pair<int, int> > &vg, int nowBest){
    cerr << "nowBest " << nowBest <<endl;

    Int sx = 0, sy = 0;
    Int vx = 0, vy = 0;
    vector<Int> ret;
    for(int i = 0; i<vg.size(); i++){
        pair<State, vector<int>> result = dijkstra(sx, sy, vg[i].first, vg[i].second, vx, vy, nowBest-ret.size());
        vector<int> history = result.second;
        for(Int j = 0; j < history.size(); j++){
            if(history[j] == -1) {
                ret.clear();
                goto END;
            }
            ret.push_back(history[j]);
        }
        if(ret.size() > nowBest){
            ret.clear();
            break;
        }
        vx = result.first.vx;
        vy = result.first.vy;
        sx = result.first.px;
        sy = result.first.py;
    }
    END:
    cerr << "solve dijkstra " << ret.size() <<endl;
    return ret;
}

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

vector<Int> solve(vector<pair<int, int> > &vg, int nowBest){
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
        if(ret.size() > nowBest){
            ret.clear();
            break;
        }
    }
    cerr << "solve " << ret.size() <<endl;
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
    int lastId = -1;
    for(int i =0 ; i<vg.size(); i++){
        int minDist = 1e9;
        int select = -1;
        int cnt =0;
        for(int j = max(i-500, 0); j<vg.size(); j++){
            cnt++;
            if(lastId != -1 && cnt > 1000) break;
            if(used[j]) continue;
            // int dist = trip_hist_by_dist(abs(vg[j].first - xs), 0,0).size() +
            // trip_hist_by_dist(abs(vg[j].second - ys), 0, 0).size();
            int dist = abs(vg[j].first - xs) +
                       abs(vg[j].second - ys );
            if(dist < minDist){
                minDist = dist;
                select = j;
            }
        }
        ret.push_back(vg[select]);
        used[select] = true;
        lastId = select;
        xs = vg[select].first;
        ys = vg[select].second;
    }
    for(int i = 0; i<vg.size(); i++){
        if(!used[i])return vector<pair<int, int> >();
    }
    return ret;
}

int main() {
    for(Int i = 1; i<1000; i++){
        distAndAccel.push_back(make_pair(i*i, i));
    }
    vector<vector<Int>> anss;
    int nowBest = 1000001;
    auto vg = (input());
    {
        vector<pair<int, int> > xo = vg;
        sort(xo.begin(), xo.end());
        anss.push_back(solve(xo, nowBest));
        if(!anss.back().empty()){
            nowBest = min(nowBest, (int)anss.back().size());
        }
        anss.push_back(solveDijskstra(xo, nowBest));
        if(!anss.back().empty()){
            nowBest = min(nowBest, (int)anss.back().size());
        }
        {
            vector<pair<int, int> > no = nearOrder(xo);
            if(!no.empty()){
                anss.push_back(solve(no, nowBest));
                if(!anss.back().empty()){
                    nowBest = min(nowBest, (int)anss.back().size());
                }
                anss.push_back(solveDijskstra(no, nowBest));
                if(!anss.back().empty()){
                    nowBest = min(nowBest, (int)anss.back().size());
                }
            }
        }
        reverse(xo.begin(), xo.end());
        anss.push_back(solve(xo, nowBest));
        if(!anss.back().empty()){
            nowBest = min(nowBest, (int)anss.back().size());
        }
        anss.push_back(solveDijskstra(xo, nowBest));
        if(!anss.back().empty()){
            nowBest = min(nowBest, (int)anss.back().size());
        }
        {
            vector<pair<int, int> > no = nearOrder(xo);
            if(!no.empty()) {
                anss.push_back(solve(no, nowBest));
                if(!anss.back().empty()){
                    nowBest = min(nowBest, (int)anss.back().size());
                }
                anss.push_back(solveDijskstra(no, nowBest));
                if(!anss.back().empty()){
                    nowBest = min(nowBest, (int)anss.back().size());
                }
            }
        }
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
        anss.push_back(solve(yo, nowBest));
        if(!anss.back().empty()){
            nowBest = min(nowBest, (int)anss.back().size());
        }
        anss.push_back(solveDijskstra(yo, nowBest));
        if(!anss.back().empty()){
            nowBest = min(nowBest, (int)anss.back().size());
        }
        {
            vector<pair<int, int> > no = nearOrder(yo);
            if(!no.empty()) {
                anss.push_back(solve(no, nowBest));
                if(!anss.back().empty()){
                    nowBest = min(nowBest, (int)anss.back().size());
                }
                anss.push_back(solveDijskstra(no, nowBest));
                if(!anss.back().empty()){
                    nowBest = min(nowBest, (int)anss.back().size());
                }
            }
        }
        reverse(yo.begin(), yo.end());
        anss.push_back(solve(yo,nowBest));
        if(!anss.back().empty()){
            nowBest = min(nowBest, (int)anss.back().size());
        }
        anss.push_back(solveDijskstra(yo, nowBest));
        if(!anss.back().empty()){
            nowBest = min(nowBest, (int)anss.back().size());
        }
        {
            vector<pair<int, int> > no = nearOrder(yo);
            if(!no.empty()) {
                anss.push_back(solve(no, nowBest));
                if(!anss.back().empty()){
                    nowBest = min(nowBest, (int)anss.back().size());
                }
                anss.push_back(solveDijskstra(no, nowBest));
                if(!anss.back().empty()){
                    nowBest = min(nowBest, (int)anss.back().size());
                }
            }
        }
    }
    Int miniAns = 1e9;
    vector<Int> ans;
    int id = 0;
    for(vector<Int> v : anss){
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
