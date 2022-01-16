#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include <sstream>
#include "sorting.hpp"

// pass in function to sort that gets called for every iteration

int numbers[79]; 
int yMax, xMax;
int size;

const int delay = 25; // delay in milliseconds

void fill(int numbers[], int size)
{
	for (int i = 0; i < size; i++)
	{
		numbers[i] = rand() % size;
	}
}

void printdebug()
{
	std::stringstream ss;

	ss << "Bubble Sort\n";
	ss << size << " Numbers\n";
	ss << "\nSwaps: " << sort::swaps;
	ss << "\nComparisons: " << sort::comparisons;
	ss << "\nDelay: " << delay << "ms";
	std::string data = ss.str();
	
	mvprintw(0,0,data.c_str());
}	

void printbars()
{
	clear();
	int width = xMax/size;	

	for (int i = 0; i < xMax; i=i+width)
	{
		int current = i/width;
		float height = (numbers[current]/float(numbers[sort::find_max(numbers,size)]))*yMax;
	
		/*
		std::stringstream ss;
		ss << current << " " << sort::selected;
		std::string dat = ss.str();
		mvprintw(6,0,dat.c_str());
		*/

		if (current == sort::selected)
		{
			attron(COLOR_PAIR(2));
		}else
		{
			attron(COLOR_PAIR(1));
		}	

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				mvprintw(yMax-y,x+i,"b");
			}
		}
		attroff(COLOR_PAIR(1));
		attroff(COLOR_PAIR(2));
	}
	
	printdebug();

	refresh();
	usleep(1000*delay);
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
	init_pair(1, COLOR_WHITE, COLOR_WHITE);
	init_pair(2, COLOR_RED, COLOR_RED);

	size = sizeof(numbers)/sizeof(numbers[0]);
	fill(numbers,size);

	printbars();
	getch();

	sort::bubble(numbers,size,printbars);
		
	getch();
	endwin();
	return 0;
}
