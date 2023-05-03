#include "dumpling.h"

#include <iostream>
using namespace std;

int S, ns;

void init(int s) {
    cerr << "init " << s << "\n";
    S = s;
}

void step(int event) {
    if (ns == 0) {
        for (int i = 0; i < 5; i++) serve();
    }
    ns++;
    cerr << "step " << event << "\n";
    if (event != -1) {
        cerr << "serve\n";
        serve();
    }
}
