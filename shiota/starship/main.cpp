#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

const int dx[] = {-1, 0,  1, -1, 0, 1, -1, 0, 1};
const int dy[] = {-1, -1,  -1, -0, 0, 0, 1, 1, 1};

class State{
public:
    int vx, vy, px, py;
    bool operator < (const State &rhs) const {
        if(vx != rhs.vx) return vx < rhs.vx;
        if(vy != rhs.vy) return vy < rhs.vy;
        if(px != rhs.px) return px < rhs.px;
        return py < rhs.py;
    }
    vector<int> history;
};

State dijkstra(int sx, int sy, int gx, int gy, int vx, int vy){
    map<State, int> minCost;
    minCost[State{vx, vy, sx, sy}] = 0;
    priority_queue<pair<int, State>> Q;

    Q.push(make_pair(0, State{vx, vy, sx, sy}));

    while(!Q.empty()){
        int cost = -Q.top().first;
        State cur = Q.top().second;
        Q.pop();


        for(int i = 0; i < 9; i++){
            int vx = cur.vx + dx[i];
            int vy = cur.vy + dy[i];
            int px = cur.px + vx;
            int py = cur.py + vy;

            State next{vx, vy, px, py};
            int nextCost = cost + 1;
            if(minCost.find(next) == minCost.end() || minCost[next] > nextCost){
                minCost[next] = nextCost;
                next.history = cur.history;
                next.history.push_back(i);
                if(next.px == gx && next.py == gy) return next;
                Q.push(make_pair(-nextCost, next));
            }
        }
    }
    return State();
}

int main() {
    int sx, sy, gx, gy;
    int vx, vy;
    vx = vy = sx = sy = 0;
    while(cin >> gx >> gy){
        State result = dijkstra(sx, sy, gx, gy, vx, vy);
        for(int i = 0; i < result.history.size(); i++){
            cout << result.history[i] + 1;
        }
        vx = result.vx;
        vy = result.vy;
        sx = result.px;
        sy = result.py;
    }
    return 0;
}
