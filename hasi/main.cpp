#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;

string solve(const vector<string> &field, int pi, int pj, int ni, int nj) {
    vector<vector<int>> dist(field.size(), vector<int>(field[0].size(), 1e9));
    if (pi == ni && pj == nj) return "";
    dist[pi][pj] = 0;
    queue<pair<int,int>> q;
    q.emplace(pi, pj);
    while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop();
        if (i == ni && j == nj) break;
        if (i > 0 && field[i-1][j] != '#' && dist[i-1][j] == 1e9) {
            dist[i-1][j] = dist[i][j] + 1;
            q.emplace(i-1, j);
        }
        if (i < field.size()-1 && field[i+1][j] != '#' && dist[i+1][j] == 1e9) {
            dist[i+1][j] = dist[i][j] + 1;
            q.emplace(i+1, j);
        }
        if (j > 0 && field[i][j-1] != '#' && dist[i][j-1] == 1e9) {
            dist[i][j-1] = dist[i][j] + 1;
            q.emplace(i, j-1);
        }
        if (j < field[0].size()-1 && field[i][j+1] != '#' && dist[i][j+1] == 1e9) {
            dist[i][j+1] = dist[i][j] + 1;
            q.emplace(i, j+1);
        }
    }
    string res;
    while (pi != ni || pj != nj) {
        if (ni > 0 && dist[ni - 1][nj] == dist[ni][nj] - 1) {
            ni--;
            res += 'D';
            continue;
        }
        if (ni < field.size() - 1 && dist[ni + 1][nj] == dist[ni][nj] - 1) {
            ni++;
            res += 'U';
            continue;
        }
        if (nj > 0 && dist[ni][nj - 1] == dist[ni][nj] - 1) {
            nj--;
            res += 'R';
            continue;
        }
        if (nj < field[0].size() - 1 && dist[ni][nj + 1] == dist[ni][nj] - 1) {
            nj++;
            res += 'L';
            continue;
        }
    }
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    vector<string> field;
    string buf;
    while (cin >> buf) field.push_back(buf);
    int pi, pj;
    set<pair<int,int>> pills;
    for (int i = 0; i < field.size(); i++) {
        for (int j = 0; j < field[i].size(); j++) {
            if (field[i][j] == 'L') {
                pi = i;
                pj = j;
            } else if (field[i][j] == '.') {
                pills.insert({i, j});
            }
        }
    }
    while (!pills.empty()) {
        int min_dist = 1e9;
        pair<int,int> min_pill;
        for (auto pill : pills) {
            int dist = abs(pi - pill.first) + abs(pj - pill.second);
            if (dist < min_dist) {
                min_dist = dist;
                min_pill = pill;
            }
        }
        cout << solve(field, pi, pj, min_pill.first, min_pill.second);
        pills.erase(min_pill);
        pi = min_pill.first;
        pj = min_pill.second;
    }
    cout << endl;
}
