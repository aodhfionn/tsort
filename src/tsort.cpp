#include <iostream>
#include <unistd.h>
#include <ncurses.h>
#include <sstream>
#include "sorting.hpp"

int yMax, xMax;

struct config
{
	int amount;
	int delay;
	std::string type;
} conf;	

void fill(int numbers[], int size)
{
	for (int i = 0; i < size; i++)
	{
		numbers[i] = rand()%size;
	}
}

int quit(struct config *cf, int code, std::string msg)
{
	clear();
	refresh();
	endwin();

	std::cout << msg << std::endl;

	free(cf);
	exit(code);
}

void printdebug(struct config *cf, int numbers[], int size)
{
	std::stringstream ss;
	std::string type = cf->type;

	/*
	int c = int(type[0]);
	if (c > 140 && c < 173)
	{
		c += 32;
	}
	type[0] = char(c);
	*/

	type[0] = toupper(type[0]);

	ss << type << " Sort\n";
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
	
	printdebug(&conf, numbers, size);

	refresh();
	usleep(1000*conf.delay);
}

int start()
{
	int n = conf.amount;
	int numbers[n]; // this, for some reason, doesnt work
	int size = sizeof(numbers)/sizeof(numbers[0]);

	fill(numbers,size);

	printbars(numbers,size);
	getch();
 
	if (conf.type == "bubble")
	{
		sort::bubble(numbers, size, printbars);
	}else if (conf.type == "quick")
	{
		sort::quick(numbers, size, 0, size-1, printbars);
	}else if (conf.type == "bogo")
	{
		sort::bogo(numbers, size, printbars);
	}else if (conf.type == "insertion")
	{
		sort::insertion(numbers, size, printbars);
	}else if (conf.type == "cocktail")
	{
		sort::cocktail(numbers, size, printbars);
	}else if (conf.type == "gnome")
	{
		sort::gnome(numbers, size, printbars);
	}
	else
	{
		endwin();
		std::cout << "Sort type " << "\""<< conf.type << "\"" << " not found" << std::endl;
		quit(&conf, 1, "");
	}

	getch();
	endwin();
	return 0;
}

void parse(int argc, char* argv[])
{
	for (int i = 0; i < argc; i++)
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
					if (n > xMax)
					{
						quit(&conf, 1, "Amount of numbers too large");					
					}else if (n < 1)
					{
						quit(&conf, 1, "Amount of numbers must be greater than 0");
					}
					conf.amount = n;
					break;
				}
				case 'd':
				{
					int d = std::stoi(arg);
					if (d < 0)
					{
						quit(&conf, 1, "Delay cannot be less than 0 milliseconds");
					}
					conf.delay = d;
					break;
				}
				case 't':
				{
					conf.type = arg;
					break;
				}
				default:
				{
					break;
				}	
			}	
		}	
	}	
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");
	initscr();
	noecho();
	curs_set(0);
	getmaxyx(stdscr, yMax, xMax);

	conf.amount = xMax;
	conf.delay = 12;
	conf.type = "cocktail";
	
	parse(argc, argv); //parsing type doesnt work

	refresh();

	if (has_colors())
	{	
		start_color();
		init_pair(1, COLOR_WHITE, COLOR_WHITE);
		init_pair(2, COLOR_RED, COLOR_RED);
		init_pair(3, COLOR_GREEN, COLOR_GREEN);
		
		start();
	}else
	{
		quit(&conf, 1, "Your terminal is not supported");
	}

	return 0;
}
