#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main() {
    int L = 10000;
    int N[14] = {50, 50, 100, 100, 200, 200, 500, 500, 1000, 1000, 2000, 2000, 2000, 2000};
    ofstream out;
    for (int i = 0; i < 14; ++i) {
	char file[100];
	sprintf(file,"%02d.in",i+5);
	out.open(file);
	out << rand()%L+1 << " " << rand()%L+1 << " " << N[i] << endl;
	for (int j = 0; j < N[i]; ++j)
	    out << rand()%L+1 << endl;
	out.close();
    }
    out.open("19.in");
    out << "100 200 2000" << endl;
    out << "50" << endl << "60" << endl;
    for (int i = 0; i < 2000-2; ++i)
	out << rand()%(L-60)+55 << endl;
    out.close();

    out.open("20.in");
    out << "100 140 2000" << endl;
    for (int i = 0; i < 2000-5; ++i)
	out << rand()%(L-160)+155 << endl;
    out << 50 << endl << 90 << endl << 50 << endl << 8 << endl << 87 << endl;
    out.close();

}

