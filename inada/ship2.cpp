#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <string>
#include <map>
#include <queue>
#include <set>
#include <thread>
#include <vector>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

using Int = long long;
const Int dx[] = {-1, 0,  1, -1, 0, 1, -1, 0, 1};
const Int dy[] = {-1, -1,  -1, 0, 0, 0, 1, 1, 1};
using StageData = vector<pair<Int, Int>>;

StageData input(istream& is){
	StageData vg;
    int x, y;
	string s;
	while(getline(is, s)) {
		if (s[0] == '#') continue;
		stringstream ss(s);
		ss >> x >> y;
        vg.push_back(make_pair(x, y));
	}
    return vg;
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        cerr << "need problem file path" << endl;
        exit(1);
    }

    ifstream ifs(argv[1]);
    auto vg = input(ifs);
    ifs.close();

	cout << "# distance=9999999999999999" << endl;
	int n = vg.size();
    Int px = 0;
    Int py = 0;
	for (int i = 0; i < n; i++) {
		auto index = (int) std::distance(
			vg.begin(),
			std::min_element(vg.begin(), vg.end(),
			                 [&](const auto &a, const auto &b) {
				                 return max<Int>(abs(px - a.first), abs(py - a.second)) < max<Int>(abs(px - b.first), abs(py - b.second));
			                 }));
		px = vg[index].first;
		py = vg[index].second;
		cout << px << " " << py << endl;
		vg[index] = vg.back();
		vg.pop_back();
	}
}