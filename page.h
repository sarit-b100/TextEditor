#ifndef PAGE_H
#define PAGE_H

#define DFLT_PAGE_SIZE 100
#define DFLT_FILENAME_SIZE 128
#include <ncurses.h>
#include "line.h"

struct PAGE
{
	char* filename;//[DFLT_FILENAME_SIZE];
	vector<LINE> lines;
	int numlines;
	//int size;
};

typedef struct PAGE PAGE;

void init_page(PAGE& p, char* fname);
//void init_page(PAGE* p, char* fname, int size)
void del_page(PAGE& p);
void insert_blankline(PAGE& p, char str[], int pos);
void insert_blankline(PAGE& p);
//void append_char(PAGE& p, char c);
void insert_char(PAGE& p, char c, int y, int x);
void del_line(PAGE& p, int pos);

#endif