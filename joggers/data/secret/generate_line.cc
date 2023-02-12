#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {

    srand(time(NULL));

    int N = 50;
    int S = 98;
    vector<int> lamps;
    for (int i = 1; i <= N; ++i) {
        if (rand()%4 == 0) lamps.push_back(i);
    }
    cout << N << " " << S << endl;
    for (int i = 0; i < N-1; ++i) {
        cout << i+1 << " " << i+2 << " " << 1 << endl;
    }
    cout << lamps.size() << endl;
    for (int i = 0; i < lamps.size(); ++i) {
        cout << lamps[i];
        if (i != lamps.size()-1) cout << " ";
    }
    cout << endl;
}
