#include <utility>
#include <string>
#include <cassert>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#include "streamcorr.h"

#include <sstream>
using namespace std;

typedef vector<vector<int> > vvi;

bool author_messages = false;

/* Wrapper for author message printing so that they are only printed in
 * case the author_messages option was given.  If the validator should
 * always print author messages, you can just call
 * report_feedback(authormessage, ...) directly.
 */
void author_message(const char *s) {
    if (author_messages) {
        report_feedback(authormessage, s);
    }
}

/* Presses the (sign?red:green) button on floor k (0-indexed), when
 * the state is stored in adj.
 */
void shift(int k, bool sign, vvi& adj) {
    int n = adj.size();
    vector<int> row(adj[k]);
    row.erase(row.begin() + k);
    if (sign)
        rotate(row.begin(), row.begin() + (n - 2), row.end());
    else
        rotate(row.begin(), row.begin() + 1, row.end());
    for(int l = 0; l < n - 1; ++l)
    {
        int rl = l + (l >= k);
        adj[k][rl] = adj[rl][k] = row[l];
    }
}

/* Check one test case.  Returns false if there were no more test
 * cases to check. */
bool check_case() {
    int n, e;
    judge_in >> n >> e;
    vector<vector<int> > adj(n, vector<int>(n, 0));
    for(int k = 0; k < e; ++k) {
        int x,y;
        judge_in >> x >> y;
        adj[x][y] = adj[y][x] = true;
    }

    int q;
    if(!(author_out >> q))
        report_error("Bad output format");
    if (q < 0 || q > 250000)
        report_error("Wrong number of operations, q = %d", q);

    for(int t = 0; t < q; ++t) {
        char c;
        int k;
        if(!(author_out >> c >> k) || (c != 'R' && c != 'G') || (k < 0 || k >= n)) {
            report_error("Bad output, c = %c, k = %d", c, k);
        }
        shift(k, c == 'R', adj);
    }
    for(int k = 0; k < e; ++k) {
        int x,y;
        judge_in >> x >> y;
        if(!adj[x][y]) {
            report_error("%d %d not connected", x, y);
        }
    }
    return true;
}

int main(int argc, char **argv) {
    init_io(argc, argv);
    /* Check if the author_messages option is given. */
    for (int i = 4; i < argc; ++i)
        if (!strcmp(argv[i], "author_messages"))
            author_messages = true;

    check_case();

    /* Check for trailing output in author file. */
    string trash;
    if (author_out >> trash) {
        author_message("Trailing output after last test case");
        report_error("Trailing output");
    }

    /* Yay! */
    author_message("Thank you for your great code. It was fantastic.");
    accept();
}
