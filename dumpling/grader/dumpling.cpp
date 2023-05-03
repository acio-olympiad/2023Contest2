#include "dumpling.h"

int S;
int ste;
void init(int s) {
    S = s;
}

void step(int event) {
    if (!(ste++)) {
        for (int i = 0; i < 20; i++) serve();
    }
    if (event != -1) serve();
}
