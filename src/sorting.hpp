#include <iostream>
#ifndef SORTING_H
#define SORTING_H

namespace sort
{

extern int swaps;
extern int comparisons;
extern int selected;

int find_max(int numbers[], int size);
bool is_sorted(int numbers[], int size);

void bubble(int numbers[], int size, void(*func)());
void quick(int numbers[], int a, int b, void(*func)());
void bogo(int numbers[], int size, void(*func)());

}

#endif // SORTING_H
