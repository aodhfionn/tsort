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

bool sort::is_sorted(int numbers[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (numbers[i] > numbers[i+1])
			return false;	
	}
	return true;
}	

void sort::bubble(int numbers[], int size, void(*func)(int num[], int))
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
			func(numbers, size);
		}
		if (swapped = false)
			break;
	}
}

void sort::quick(int numbers[], int size, int a, int b, void(*func)(int num[], int))
{
	if (a < b)
	{
		int pivot = numbers[b];
		int i = (a-1);

		for (int j = a; j <= b-1; j++)
		{
			sort::selected = j;
			sort::comparisons++;
			if (numbers[j] < pivot)
			{
				i++;
				swap(&numbers[i], &numbers[j]);
			}
			func(numbers, size);
		}
		swap(&numbers[i+1], &numbers[b]);

		sort::quick(numbers, size, a, i, func);
		sort::quick(numbers, size, i+2, b, func);
	}
}

void sort::bogo(int numbers[], int size, void(*func)(int num[], int))
{
	while (!sort::is_sorted(numbers,size))
	{
		for (int i = 0; i < size; i++)
		{
			sort::selected = i;
			swap(&numbers[i], &numbers[rand()%size]);
			func(numbers, size);
		}
	}
}
