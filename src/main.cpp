#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include <sstream>
#include "sorting.hpp"

// pass in function to sort that gets called for every iteration

int numbers[79]; 
int yMax, xMax;
int size;

void fill(int numbers[], int size)
{
	for (int i = 0; i < size; i++)
	{
		numbers[i] = rand() % size;
	}
}

void printbars()
{
	clear();
	int width = xMax/size;	

	for (int i = 0; i < xMax; i=i+width)
	{
		int current = i/width;
		float height = (numbers[current]/float(numbers[sort::find_max(numbers,size)]))*yMax;
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				mvprintw(yMax-y,x+i,"b");
			}
		}
	}

	std::stringstream ss;
	ss << "Swaps: " << sort::swaps << "\nComparisons: " << sort::comparisons;
	std::string data = ss.str();

	mvprintw(0, 0, data.c_str());
	getch();
}

int main()
{
	initscr();
	noecho();
	curs_set(0);
	setlocale(LC_ALL, "");
	getmaxyx(stdscr, yMax, xMax);

	refresh();

	// init all colors
	start_color();
	for (int i = 0; i < 16; i++)
	{
		init_pair(i, i, COLOR_BLACK);
	}

	size = sizeof(numbers)/sizeof(numbers[0]);
	fill(numbers,size);

	printbars();
	getch();

	sort::bubble(numbers,size,printbars);
		
	getch();
	endwin();
	return 0;
}
