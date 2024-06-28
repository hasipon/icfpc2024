#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
    vector<string> input;

    if (argc <= 1) {
        cerr << "need problem file path" << endl;
        exit(1);
    }

    {
        ifstream ifs(argv[1]);
        string s;
        while (std::getline(ifs, s)) {
            input.push_back(s);
        }
    }

    cerr << "input:" << endl;
    for (auto& s: input) {
        cerr << s << endl;
    }

    int lx = -1;
    int ly = -1;
    int dot_count = 0;
    for (int y = 0; y < input.size(); y++) {
        for (int x = 0; x < input[y].size(); x++) {
            if (input[y][x] == '.') {
                dot_count++;
            }
            if (input[y][x] == 'L') {
                lx = x;
                ly = y;
            }
        }
    }

    if (lx == -1 || ly == -1) {
        cerr << "L" << endl;
        exit(0);
    }

    string dirs = "URDL";
    const int H = input.size();
    const int W = input[0].size();
    const int dx[] = {0, 1, 0, -1};
    const int dy[] = {-1, 0, 1, 0};
    string solution;

    for (int t = 0; t < dot_count; t++) {
        vector visit(H, vector<int>(W));
        stack<tuple<int, int, string> > stk;
        cerr << "lambda (x, y) = " << lx << " " << ly << " " << solution << endl;
        stk.emplace(lx, ly, "");

        while (!stk.empty()) {
            auto [px, py, ans] = stk.top();
            stk.pop();
            bool found = false;

            for (int r = 0; r < 4; r++) {
                const int nx = px + dx[r];
                const int ny = py + dy[r];
                if (0 <= nx && nx < W && 0 <= ny && ny < H) {
                    if (input[ny][nx] == '.') {
                        lx = nx;
                        ly = ny;
                        solution += ans + dirs[r];
                        input[ny][nx] = ' ';
                        found = true;
                        break;
                    }

                    if (input[ny][nx] != '#') {
                        if (!visit[ny][nx]) {
                            visit[ny][nx] = 1;
                            stk.emplace(nx, ny, ans + dirs[r]);
                        }
                    }
                }
            }

            if (found) break;
        }

        // for (auto &s: input) { cerr << s << endl; }
    }

    cerr << solution.size() << endl;
    cout << solution << endl;
}
