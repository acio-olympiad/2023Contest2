#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;


class Checker {
public:

    Checker() {};
    const int MIN_N = 1,      MAX_N = 100000;
    const int MIN_Q = 1,      MAX_Q = 100000;
    const int MIN_A = -10000, MAX_A = 10000;
    const int MIN_K = 1;

    void validate() {
        registerValidation();

        int N = inf.readInt(MIN_N, MAX_N);
        inf.readSpace();
        int Q = inf.readInt(MIN_Q, MAX_Q);
        inf.readEoln();

        vector<int> a, k;
        int maxk = 0;
        for (int i = 0; i < N; i++) {
            a.push_back(inf.readInt(MIN_A, MAX_A));
            if (i < N-1) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
        for (int i = 0; i < Q; i++) {
            k.push_back(inf.readInt(MIN_K, N));
            maxk = max(maxk, k.back());
            if (i < Q-1) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }

        #ifdef SUB1
        ensuref(Q == 1, "Q = 1");
        ensuref(maxk == 1, "K = 1");
        #endif

        #ifdef SUB2
        ensuref(Q == 1, "Q = 1");
        ensuref(maxk <= 2, "K <= 2");
        #endif

        #ifdef SUB3
        ensuref(Q == 1, "Q = 1");
        ensuref(maxk <= 50, "K <= 50");
        #endif

        #ifdef SUB4
        ensuref(Q == 1, "Q = 1");
        #endif

        for (int i = 0; i + 1 < k.size(); i++) {
            ensuref(k[i+1] > k[i], "All k[i] are unique and in ascending order");
        }

        //-------

        
        inf.readEof();
    }
};

int main() {
    Checker c;
    c.validate();
}
