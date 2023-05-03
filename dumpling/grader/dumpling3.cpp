#include <bits/stdc++.h>
#include "dumpling.h"
 
int S;
 
void init(int s) {
    S = s;
    srand(time(0));
}
 
bool first = true;
void step(int event) {
  if(first) {
    for(int i = 0; i < 20; i++) serve();
    first = false;
  } else {
    if(rand() % 800 == 0 || event != -1) serve();
  }
}
