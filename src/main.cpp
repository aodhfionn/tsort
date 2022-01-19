#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include <sstream>
#include <getopt.h>
#include "sorting.hpp"

int yMax, xMax;

struct config
{
	int amount;
	int delay;
	const char* type;
} conf;	


void fill(int numbers[], int size)
{
	for (int i = 0; i < size; i++)
	{
		numbers[i] = rand()%size;
	}
}

void printdebug(int numbers[], int size)
{
	std::stringstream ss;

	ss << "Bubble Sort\n";
	ss << size << " Numbers\n";
	ss << "\nSwaps: " << sort::swaps;
	ss << "\nComparisons: " << sort::comparisons;
	ss << "\nDelay: " << conf.delay << "ms";
	std::string data = ss.str();
	
	mvprintw(0,0,data.c_str());
}

void printbars(int numbers[], int size)
{
	clear();
	int width = xMax/size;	

	for (int i = 0; i < xMax; i=i+width)
	{
		int current = i/width;
		float height = (numbers[current]/float(numbers[sort::find_max(numbers,size)]))*(yMax-6);
	
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
	
	printdebug(numbers, size);

	refresh();
	usleep(1000*conf.delay);
}

int start()
{
	int numbers[conf.amount]; // this, for some reason, doesnt work
	int size = sizeof(numbers)/sizeof(numbers[0]);

	fill(numbers,size);

	printbars(numbers,size);
	getch(); 

	if (conf.type == "bubble")
	{
		sort::bubble(numbers,size,printbars);
	}else if (conf.type == "quick")
	{
		sort::quick(numbers,size,0,size-1,printbars);
	}else if (conf.type == "bogo")
	{
		sort::bogo(numbers,size,printbars);
	}else
	{
		endwin();
		std::cout << "Sort type not found" << std::endl;
		return 1;
	}	

	getch();
	endwin();
	return 0;
}

void parse(int argc, char* argv[])
{
	for (int i = 1; i < argc; i++)
	{
		std::string s(argv[i]);

		if (s[0] == '-')
		{
			std::string arg(argv[i+1]);

			switch (s[1])
			{
				case 'n':
				{
					int n = std::stoi(arg);
					conf.amount = n;
					break;
				}
				case 'd':
				{
					int d = std::stoi(arg);
					conf.delay = d;
					break;
				}
				case 't':
				{
					conf.type = arg.c_str();
					break;
				}
				default:
				{
					endwin();
					std::cout << "ERROR" << std::endl;
					break;
				}	
			}	
		}	
	}	
}	

int main(int argc, char* argv[])
{
	/*
	struct config conf = {
		int amount = yMax/2;
		int delay = 25;
		const char* type;
	};
	*/

	setlocale(LC_ALL, "");
	initscr();
	noecho();
	curs_set(0);
	getmaxyx(stdscr, yMax, xMax);

	conf.amount = xMax/2;
	conf.delay = 25;
	conf.type = "quick";
	
	parse(argc, argv); //parsing type doesnt work
/*
	int index = 0;
	int c;
	while ((c = getopt(argc, argv, "ndt:")) != -1)
	{
		switch (c)
		{
			case 'n':
			{
				int n = std::atoi(optarg);
				if (n > xMax || n < 1)
				{
					std::cout << "Amount must be in the range of 1 to " << xMax << std::endl;
					return 1;
				}
				conf.amount = n;
				break;
			}
			case 'd':
			{
				int d = std::atoi(optarg);
				if (d < 0)
				{
					std::cout << "Delay can not be less than 0 milliseconds" << std::endl;
					return 1;
				}
				conf.delay = d;
				break;
			}
			case 't':
			{
				if (optarg == NULL)
				{
					std::cout << "Sort type can not be null" << std::endl;
					return 1;
				}	
				conf.type = optarg;
				break;
			}
		}	
	}
	*/

	refresh();

	if (has_colors())
	{	
		start_color();
		init_pair(1, COLOR_WHITE, COLOR_WHITE);
		init_pair(2, COLOR_RED, COLOR_RED);
		init_pair(3, COLOR_GREEN, COLOR_GREEN);
	}	
	
	start();

	return 0;
}
