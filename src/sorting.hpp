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

void bubble(int numbers[], int size, void(*func)(int num[], int));
void quick(int numbers[], int size, int a, int b, void(*func)(int num[], int));
void bogo(int numbers[], int size, void(*func)(int num[], int));
void insertion(int numbers[], int size, void(*func)(int num[], int));
void cocktail(int numbers[], int size, void(*func)(int num[], int));
void gnome(int numbers[], int size, void(*func)(int num[], int));

}

#endif // SORTING_H
