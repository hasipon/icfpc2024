#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <queue>

using namespace std;

using Int = __int128;

const Int dx[] = {-1, 0,  1, -1, 0, 1, -1, 0, 1};
const Int dy[] = {-1, -1,  -1, -0, 0, 0, 1, 1, 1};

class State{
public:
    Int vx, vy, px, py;
    bool operator < (const State &rhs) const {
        if(vx != rhs.vx) return vx < rhs.vx;
        if(vy != rhs.vy) return vy < rhs.vy;
        if(px != rhs.px) return px < rhs.px;
        return py < rhs.py;
    }
    vector<int> history;
};

Int gcd(Int a, Int b){
    if(b == 0) return a;
    return gcd(b, a % b);
}

State dijkstra(int _sx, int _sy, int gx, int gy, int _vx, int _vy){
    map<State, Int> minCost;
    priority_queue<pair<Int, State>> Q;

    minCost[State{_vx, _vy, _sx, _sy}] = 0;
    Q.push(make_pair(0, State{_vx, _vy, _sx, _sy}));

    while(!Q.empty()){
        Int cost = -Q.top().first;
        State cur = Q.top().second;
        Q.pop();

        for(Int i = 0; i < 9; i++){
            Int vx = cur.vx + dx[i];
            Int vy = cur.vy + dy[i];

            Int px = cur.px + vx;
            Int py = cur.py + vy;
            State next{vx, vy, px, py};
            Int nextCost = cost + 1;
            next.history = cur.history;
            next.history.push_back(i);

            /*
            Int div = gcd(fabs(cur.vx), fabs(cur.vy));
            if(vx != 0 && vy != 0){
                for(Int j = 1; j<div; j++){
                    Int px = cur.px + (cur.vx / div) * j;
                    Int py = cur.py + (cur.vy / div) * j;
                    if(px == gx && py == gy){
                       return next;
                    }
                }
            }*/

            if(minCost.find(next) == minCost.end() || minCost[next] > nextCost){
                minCost[next] = nextCost;
                if(max(fabs(next.vx), fabs(next.vy)) > 2) continue;
                if(next.px == gx && next.py == gy) return next;
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
    sort(vg.begin(), vg.end());
    Int sx, sy;
    Int vx, vy;
    vx = vy = sx = sy = 0;
    for(Int i = 0; i < vg.size(); i++){
        State result = dijkstra(sx, sy, vg[i].first, vg[i].second, vx, vy);
        for(Int i = 0; i < result.history.size(); i++){
            cout << result.history[i] + 1;
        }
        vx = result.vx;
        vy = result.vy;
        sx = result.px;
        sy = result.py;
    }

    return 0;
}
