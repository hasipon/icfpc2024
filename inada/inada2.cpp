#include <iostream>
#include <set>
#include <fstream>
#include <stack>
#include <queue>
#include <string>
#include <vector>

using namespace std;

const string dirs = "URDL";
const int dx[] = {0, 1, 0, -1};
const int dy[] = {-1, 0, 1, 0};

class Solver {
public:
    int W{}, H{};
    vector<string> input;

    bool inside(int x, int y) const {
        return 0 <= x && x < W && 0 <= y && y < H;
    }

    string solve2() {
        auto [lx, ly, dot_count] = preprocess(input);
        vector got(H, vector<bool>(W));
        string ans;

        while (dot_count) {
            int best_r = 0;
            int best_len = 1 << 30;
            for (int r = 0; r < 4; r++) {
                const int nx = lx + dx[r];
                const int ny = ly + dy[r];
                if (inside(nx, ny) && input[ny][nx] != '#') {
                    const int len = playout(nx, ny, dot_count, got);
                    if (len < best_len) {
                        best_r = r;
                        best_len = len;
                    }
                }
            }

            ans += dirs[best_r];
            lx += dx[best_r];
            ly += dy[best_r];
            if (input[ly][lx] == '.' && !got[ly][lx]) {
                got[ly][lx] = true;
                dot_count--;
            }
            cerr << "lambda (x, y) = " << lx << " " << ly << " " << " dot=" << dot_count << " " << ans << endl;
        }

        return ans;
    }

    int playout(int lx, int ly, int dot_count, vector<vector<bool>> got) {
        int ans_len = 0;
        if (input[ly][lx] == '.' && !got[ly][lx]) {
            dot_count--;
            got[ly][lx] = true;
        }
        while (dot_count) {
            set<tuple<int, int> > mark;
            queue<tuple<int, int, int> > Q;
            Q.emplace(lx, ly, 0);
            bool found = false;
            while (!Q.empty()) {
                auto [px, py, depth] = Q.front();
                Q.pop();

                for (int r = 0; r < 4; r++) {
                    const int nx = px + dx[r];
                    const int ny = py + dy[r];
                    if (inside(nx, ny)) {
                        if (input[ny][nx] == '.' && !got[ny][nx]) {
                            lx = nx;
                            ly = ny;
                            got[ny][nx] = true;
                            ans_len += depth + 1;
                            dot_count--;
                            found = true;
                            break;
                        }

                        if (input[ny][nx] != '#') {
                            if (mark.find({nx,ny}) == mark.end()) {
                                mark.emplace(nx, ny);
                                Q.emplace(nx, ny, depth + 1);
                            }
                        }
                    }
                }

                if (found) break;
            }
        }

        return ans_len;
    }

    tuple<int, int, int> preprocess(const vector<string> &input) {
        H = input.size();
        W = input[0].size();
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
        return {lx, ly, dot_count};
    }
};

vector<string> read_input(const string& path) {
    ifstream ifs(path);
    vector<string> input;
    string s;
    while (std::getline(ifs, s)) {
        input.push_back(s);
    }
    return input;
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        cerr << "need problem file path" << endl;
        exit(1);
    }

    Solver solver;
    solver.input = read_input(argv[1]);
    auto ans = solver.solve2();

    cerr << ans.size() << endl;
    cout << ans << endl;
}
