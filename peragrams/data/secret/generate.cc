#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    int size;
    srand(time(NULL)+size);
    cin >> size;
    for (int i = 0; i < size; ++i) {
        cout << char('a'+rand()%26);
    }
    cout << endl;
}
