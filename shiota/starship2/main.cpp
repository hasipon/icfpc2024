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

class State{
public:
    Int vx, vy, px, py;
    vector<pair<int, int> > target;
    bool found;
    vector<int> history;
    pair<int, int> gv, gp;
    int step;
    bool operator < (const State &rhs) const {
        if(vx != rhs.vx) return vx < rhs.vx;
        if(vy != rhs.vy) return vy < rhs.vy;
        if(px != rhs.px) return px < rhs.px;
        if(py < rhs.py)return py < rhs.py;
        return target < rhs.target;
    }
};

Int gcd(Int a, Int b){
    if(b == 0) return a;
    return gcd(b, a % b);
}

/*
vector<int> genHistory(map<State, Int> &ope, State next,  pair<int, int> s, pair<int, int> g, const set<pair<int, int>> &tg){
    cerr << "genHistory" <<' ' << g.first << ' ' << g.second << endl;
    cerr << "next" <<' ' << next.px << ' '<<next.py <<endl;
    vector<int> history;
    bool found = false;
    // usokamo
    while(next.px != s.first || next.py != s.second || tg != next.target){
        int cope = ope[next]-1;
        if(cope == -1){
            cerr << "error" << endl;
            cerr << next.px << ' ' << next.py << ' ' << next.vx << ' ' << next.vy << endl;
            assert(false);
        }
        if(next.px == g.first && next.py == g.second){
            found = true;
        }
        if(found){
            history.push_back(cope+1);
        }
        cerr << next.px  << ' '<< next.py <<endl;
        if(next.target.count(make_pair(next.px, next.py))){
            next.target.insert(make_pair(next.px, next.py));
        }
        next.px -= next.vx;
        next.py -= next.vy;
        next.vx -= dx[cope];
        next.vy -= dy[cope];
    }
    reverse(history.begin(), history.end());
    return history;
}
 */

pair<int, State> greedy(const State &st){
    const int X_LIMIT = abs(st.px - st.target[0].first) / 2;
    const int Y_LIMIT = abs(st.py - st.target[0].second) / 2;
    pair<int, int> p = make_pair(st.px, st.py);
    pair<int, int> g = st.target[0];
    int vx = st.vx, vy = st.vy;
    vector<int> ret = st.history;
    bool found = false;
    while(p != g && ret.size()  - st.history.size()< 100){
        int dx = g.first - p.first;
        int dy = g.second - p.second;
        if( max(abs(dx), abs(dy) )< 5){
            State retState = st;
            retState.vx = vx;
            retState.vy = vy;
            retState.px = p.first;
            retState.py = p.second;
            retState.history = ret;
            if(found){
                cerr << "greedy res: " << dx <<' ' << dy <<endl;
            }
            return make_pair(0, retState);
        }
        found = true;
        int moveX = 0, moveY = 0;

        // X
        if(dx >0){
            moveX = 1;
        } else if(dx < 0){
            moveX = -1;
        }
        if(vx > X_LIMIT){
            moveX = -1;
        }
        else if(vx < -X_LIMIT){
            moveX = 1;
        }

        // Y
        if(dy >0){
            moveY = 1;
        } else if(dy < 0){
            moveY = -1;
        }
        if(vy > Y_LIMIT){
            moveY = -1;
        }
        else if(vy < -Y_LIMIT){
            moveY = 1;
        }
        vx += moveX;
        vy += moveY;
        p.first += vx;
        p.second += vy;
        if(moveX == 0 && moveY == 0){
            ret.push_back(5);
        }else if(moveX == 1 && moveY == 1){
            ret.push_back(9);
        }else if(moveX == 1 && moveY == -1){
            ret.push_back(3);
        }else if(moveX == -1 && moveY == 1){
            ret.push_back(7);
        }else if(moveX == -1 && moveY == -1){
            ret.push_back(1);
        }else if(moveX == 1){
            ret.push_back(6);
        } else if(moveX == -1){
            ret.push_back(4);
        } else if(moveY == 1){
            ret.push_back(8);
        } else if(moveY == -1){
            ret.push_back(2);
        }
    }
    cerr << "fail" <<endl;
    return make_pair(-1, State());

}
pair<State, vector<int>> dijkstra(int _sx, int _sy, int _vx, int _vy, int nowBest, const vector<pair<int, int>> &tg, pair<int, int> g){
//    cerr << _sx << ' ' << _sy << ' ' << _vx << ' ' << _vy << ' ' << nowBest << ' ' << tg.size() << ' ' << g.first << ' ' << g.second <<endl;

    map<State, Int> minCost;
    map<State, Int>  ope;
    priority_queue<pair<Int, State>> Q;

    {
        State start;
        start.px = _sx;
        start.py = _sy;
        start.vx = _vx;
        start.vy = _vy;
        start.target = tg;
        start.found = false;
        start.step = 0;
        /*
        auto gres = greedy(start);
        if(gres.first == -1){
            return make_pair(State(), vector<int>(1, -1));
        }*/
        // start = gres.second;

        Q.push(make_pair(0, start));
    }

    State best;
    best.found = false;
    while(!Q.empty()){
        Int cost = -Q.top().first;

        if(cost > nowBest){
 //           cerr << endl << "RET"<< __LINE__ <<endl;
            return make_pair(State(), vector<int>(1, -1));
        }
        State cur = Q.top().second;
        // cerr << cur.px << ' ' << cur.py <<endl;
                Q.pop();
        if(best.found){
            if(best.target.size() < cur.target.size()){
                continue;
            }
            if(cur.found){
                if(best.target.size() > cur.target.size()){
                    best = cur;
                }
            }
        }
        if(cur.step > 20){
            continue;
        }

        for(Int i = 0; i < 9; i++){
            State next = cur;
            const int vx = next.vx = cur.vx + dx[i];
            const int vy = next.vy = cur.vy + dy[i];

            const int px = next.px = cur.px + vx;
            const int py = next.py = cur.py + vy;
            Int nextCost = cost + 1;
            next.step++;
            if(!next.found){
                next.history.push_back(i+1);
            }


            /*
            if(vx != 0 || vy != 0){
                Int div =1;
                if(vx != 0 && vy != 0){
                    div = gcd(abs(vx), abs(vy));
                }
                for(Int j = 1; j<div; j++){
                    Int dpx = cur.px + (vx / div) * j;
                    Int dpy = cur.py + (vy / div) * j;
                    auto dp = make_pair(dpx, dpy);
                    if(!next.target.empty() && next.target[0] == dp){
                        next.target.erase(next.target.begin());
                    }
                    if(dp == g){
                        next.found = true;
                        next.gv = make_pair(vx, vy);
                        next.gp = make_pair(px, py);
                    }
                }
            }
             */
            if(!next.target.empty() && next.target[0] == make_pair(next.px, next.py)){
                next.target.erase(next.target.begin());
                /*
                if(!next.target.empty()){
                    auto gres = greedy(next);
                    if(gres.first == -1){
                        return make_pair(State(), vector<int>(1, -1));
                    }
                    next = gres.second;
                    nextCost = next.history.size();
                }*/
            }
            if( next.py == g.second && next.px == g.first){
                next.found = true;
                next.gv = make_pair(vx, vy);
                next.gp = make_pair(px, py);
            }

            if(minCost.find(next) == minCost.end() || minCost[next] > nextCost){
                minCost[next] = nextCost;
                ope[next] = i+1;

                if(next.target.empty()){
//                    cerr << endl << "RET" <<  __LINE__ <<endl;
                    return make_pair(next, next.history);
                }
                Q.push(make_pair(-nextCost, next));
            }
        }
    }
    if(best.found){
 //       cerr << endl << "RET" << __LINE__ <<endl;
        return make_pair(best, best.history);
    }else{
        return make_pair(State(), vector<int>(1, -1));

    }
    assert(false);
}


vector<Int> solveDijskstra(vector<pair<int, int> > &vg, int nowBest){
    cerr << "nowBest " << nowBest <<endl;

    Int sx = 0, sy = 0;
    Int vx = 0, vy = 0;
    vector<Int> ret;
    for(int i = 0; i<vg.size(); i++){
        if(vg[i] == make_pair(sx, sy)) continue;

        /*
        {
            State start;
            start.px = sx;
            start.py = sy;
            start.vx = vx;
            start.vy = vy;
            start.target.push_back(vg[i]);
            start.found = false;
            start.step = 0;
            auto gres = greedy(start);
                cerr <<  "greedy from" << sx << ' ' << sy <<endl;
                for(Int j = 0; j<gres.second.history.size(); j++){
                    cerr << gres.second.history[j];
                }
                cerr <<endl;
        }
         */

        vector<pair<int, int>> target;
        target.push_back(vg[i]);
        if(i < vg.size() - 1){
           target.push_back( vg[i+1]);
        }
        if(i < vg.size() - 2){
            target.push_back( vg[i+2]);
        }
        if(i < vg.size() - 3){
        //      target.push_back( vg[i+3]);
        }
        auto result = dijkstra(sx, sy, vx, vy, int(nowBest - ret.size()), target, vg[i]);
        vector<int> history = result.second;
        cerr << "res" << endl;
        for(Int j = 0; j < history.size(); j++){
            if(history[j] == -1) {
                ret.clear();
                goto END;
            }
            ret.push_back(history[j]);
        }
        for(int j=0; j<ret.size();j++){
            cerr << ret[j];
        }
        cerr << endl;
        if(ret.size() > nowBest){
            ret.clear();
            break;
        }
        vx = result.first.gv.first;
        vy = result.first.gv.second;
        sx = result.first.gp.first;
        sy = result.first.gp.second;
    }
    END:
    cerr << endl << "solve dijkstra " << ret.size() <<endl;
    return ret;
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

int smartDist(int v, int diff){
    int base = 0;
    // 逆の場合
    if(v * diff <0 ){
        base = abs(v) + abs(v)*(abs(v)-1);
        v = 1;
    }
    if(v == 0)v++;
    return base + abs(diff /v);
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
        // /*
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
        // int select = beam[0].second;
        ret.push_back(vg[select]);
        used[select] = true;
        xs = vg[select].first;
        ys = vg[select].second;
        xv = miniRes.vx;
        yv = miniRes.vy;
    }
    for(int i = 0; i<vg.size(); i++){
        if(!used[i])return vector<pair<int, int> >();
         // cout << ret[i].first << ' ' << ret[i].second << endl;
    }
    assert(vg.size() == ret.size());
    return ret;
}

void updateAnss(vector<vector<Int>> &anss, const vector<Int> &ans, int &nowBest){
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
    for(Int i = 1; i<1000; i++){
        distAndAccel.push_back(make_pair(i*i, i));
    }
    vector<vector<Int>> anss;
    int nowBest = 1000001;
    auto vg = (input());
    updateAnss(anss, solveDijskstra(vg, nowBest), nowBest);
    return 0;

    // x_order
    {
        vector<pair<int, int> > xo = vg;
        sort(xo.begin(), xo.end());
        {
            vector<pair<int, int> > no = nearOrder(xo);
            if(!no.empty()){
                //updateAnss(anss, solve(no, nowBest), nowBest);
//                updateAnss(anss, solveDijskstra(no, nowBest), nowBest);
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
