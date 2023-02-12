#include <cstdio>
using namespace std;

int main() {
    int N,M;
    scanf("%d%d",&N,&M);
    char words[5002][102];
    for (int i = 0; i < N; ++i)
	scanf("%s",words[i]);
    for (int i = 0; i < M; ++i) {
	char plate[4];
	scanf("%s",plate);
	for (int i = 0; i<3; ++i) plate[i] -= 'A'-'a';
	bool success = false;
	for (int j = 0; j < N; ++j) {
	    int a = 0;
	    for (int k = 0; a < 3 && words[j][k]; ++k)
		a += plate[a]==words[j][k];
	    if (a==3) {
		success = true;
		puts(words[j]);
		break;
	    }
	}
	if (!success)
	    puts("No valid word");
    }
}



