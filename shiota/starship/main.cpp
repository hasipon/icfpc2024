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
        history.push_back(cope+1);
        next.px -= next.vx;
        next.py -= next.vy;
        next.vx -= dx[cope];
        next.vy -= dy[cope];
    }
    reverse(history.begin(), history.end());
    return history;
}

pair<State, vector<int>> dijkstra(int _sx, int _sy, int gx, int gy, int _vx, int _vy){
    map<State, Int> minCost;
    map<State, Int>  ope;
    priority_queue<pair<Int, State>> Q;

    minCost[State{_vx, _vy, _sx, _sy}] = 0;
    Q.push(make_pair(0, State{_vx, _vy, _sx, _sy}));
    if(_sx == gx && _sy == gy) return make_pair(Q.top().second, vector<int>());

    while(!Q.empty()){
        Int cost = -Q.top().first;
        const State cur = Q.top().second;
        Q.pop();

        for(Int i = 0; i < 9; i++){
            Int vx = cur.vx + dx[i];
            Int vy = cur.vy + dy[i];

            if(abs(cur.px + cur.vx - gx) + abs(cur.py + cur.vy - gy) <
                abs(cur.px + vx     - gx) + abs(cur.py + vy     - gy)){
                continue;
            }

            Int px = cur.px + vx;
            Int py = cur.py + vy;
            State next{vx, vy, px, py};
            Int nextCost = cost + 1;

            Int div = gcd(fabs(cur.vx), fabs(cur.vy));
            if(vx != 0 && vy != 0){
                for(Int j = 1; j<div; j++){
                    Int px = cur.px + (cur.vx / div) * j;
                    Int py = cur.py + (cur.vy / div) * j;
                    if(px == gx && py == gy){
                        return make_pair(next, genHistory(ope, next, _sx, _sy, _vx, _vy));
                    }
                }
            }

            if(minCost.find(next) == minCost.end() || minCost[next] > nextCost){
                if(max(fabs(next.vx), fabs(next.vy)) > 12) continue;
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

vector<pair<int, int>> input(){
    vector<pair<int, int> > vg;
    int x, y;
    while(cin >> x >> y){
        vg.push_back(make_pair(x, y));
    }
    return vg;
}

int main() {
    auto vg = input();
    // sort(vg.begin(), vg.end());
    Int sx, sy;
    Int vx, vy;
    vx = vy = sx = sy = 0;
    for(Int i = 0; i < vg.size(); i++){
        pair<State, vector<int>> result = dijkstra(sx, sy, vg[i].first, vg[i].second, vx, vy);
        vector<int> history = result.second;
        for(Int j = 0; j < history.size(); j++){
            cout << history[j];
        }
        vx = result.first.vx;
        vy = result.first.vy;
        sx = result.first.px;
        sy = result.first.py;
    }

    return 0;
}
