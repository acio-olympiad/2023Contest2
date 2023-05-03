#include <algorithm>
#include <iostream>
#include <cmath>
#include "dumpling.h"

using namespace std;
 
int S;
int lastout;
int nextin;

double cwnd;
double thresh;
 
void init(int s) {
    S = s;
    cwnd = 10;
}
 
bool first = true;
void step(int event) {
    //cerr << "step " << event << "\n";
    if(first) {
        for(int i = 0; i < 1; i++) lastout = serve();
        first = false;
    } else {
        if (event != -1) {
            if (event <= nextin) {
                // No loss
                if (event == nextin && cwnd < thresh) {
                    cwnd = cwnd + 1;
                } else {
                    cwnd = cwnd + 1/cwnd;
                }
            } else if (event > nextin) {
                // Loss!!!
                thresh = cwnd * 0.5;
                cwnd = 1;
                nextin = lastout - ceil(cwnd);
            }
            nextin = max(nextin, event + 1);
            while (lastout - nextin < cwnd) {
                lastout = serve();
                if (lastout == -1) return;
            }
        }
    }
}
