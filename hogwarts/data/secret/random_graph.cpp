#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

#define rep(i,a,b) for(int i=a;i<b;++i)

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

int n, n_e;

int main(int argc, char **argv) {
	srand(time(0));
	if(argc > 2)
		n = atoi(argv[1]), n_e = atoi(argv[2]);
	else
		n = 3, n_e = 2;
	if(n*(n-1)/2 < n_e) return 0;	
	vvi adj(n, vi(n, 0));
	//cout << n << " " << n_e << endl;
	rep(t,0,n_e) {
		int i,j;
		do {
			i = rand() % n;
			j = (i + 1 + rand()%(n-1))%n;	
		} while(adj[i][j]);
		adj[i][j] = adj[j][i] = true;
		int I = min(i,j), J = max(i,j);
		cout << (I) << " " << (J) << endl;
	}
	
	return 0;
}
