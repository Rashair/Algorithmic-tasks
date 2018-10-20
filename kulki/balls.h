#ifndef BALLS_H_INCLUDED
#define BALLS_H_INCLUDED

void balls();
inline int skip(int);
void possib(int k, int level=0);
bool sequence(int k, bool swaped);
bool sequence();
void activate_sequence(register int k,bool way_of_swap);
void activate_sequence();
void drop(int j,int k);
void complex_drop(int j,int mode);
void go_down();
bool clean();

#endif // BALLS_H_INCLUDED
