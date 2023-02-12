#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef vector<int> vi;
typedef vector<pair<int,int> > vpi;

const int N_NODES = 5;
const int S = 6;

const int MAX_D = 3;

const int PERCENT_LAMPS = 80;

struct Edge {
    int from, to, dist;
};

int main() {

    // decide where lamps are already placed
    vi lamps;
    for (int i = 0; i < N_NODES; ++i) {
        if ((rand()%100+1)<=PERCENT_LAMPS) {
            lamps.push_back(i);
        }
    }

    srand(time(0));

    vi inside;
    inside.push_back(0);

    vi outside;
    for (int i = 1; i < N_NODES; ++i) outside.push_back(i);
    
    vector<Edge> edges;

    // add edges for random pairs of (inside, outside)
    for (int i = 1; i < N_NODES; ++i) {
        size_t from = rand()%inside.size();
        size_t to = rand()%outside.size();

        Edge e;
        e.from = inside[from]; 
        e.to = outside[to]; 
        e.dist = rand()%MAX_D + 1;
   
        edges.push_back(e);

        inside.push_back(outside[to]);
        outside.erase(outside.begin()+to);
    }

    random_shuffle(edges.begin(),edges.end());
    cout << N_NODES << " " << S << endl;
    for (int i = 0; i < edges.size(); ++i) {
        cout << edges[i].from+1 << " ";
        cout << edges[i].to+1 << " ";
        cout << edges[i].dist << endl;
    }

    cout << lamps.size() << endl;
    random_shuffle(lamps.begin(),lamps.end());
    for (int i = 0; i < lamps.size(); ++i) {
        cout << lamps[i]+1;
        if (i != lamps.size()-1)  cout << " ";
    }
    cout << endl;
}
