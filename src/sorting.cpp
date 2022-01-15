#include <iostream>
#include "sorting.hpp"

int sort::swaps = 0;
int sort::comparisons = 0;
int sort::selected;

int sort::find_max(int numbers[], int size)
{
	int max = 0;
	
	for (int i = 0; i < size; i++)
	{
		if (numbers[i] > numbers[max])
		{
			max = i;
		}	
	}

	return max;
}	

void swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
	
	sort::swaps++;
}

void sort::bubble(int numbers[], int size, void(*func)())
{
	bool swapped;
	for (int i = 0; i < size-1; i++)
	{
		swapped = false;
		for (int j = 0; j < size-i-1; j++)
		{
			sort::selected = j;
			sort::comparisons++;
			if (numbers[j] > numbers[j+1])
			{
				swap(&numbers[j],&numbers[j+1]);
				swapped = true;
			}
			func();
		}
		if (swapped = false)
			break;
	}
}
