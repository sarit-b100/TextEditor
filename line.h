#ifndef LINE_H
#define LINE_H

#include <iostream>
#include <string.h>
//#include <cstring.h>
#include <vector>
#include <ctype.h>
#define DFLT_LINE_SIZE 256 // default number of max characters in a line

using namespace std;

struct LINE
{
	int size;
	char line[DFLT_LINE_SIZE] = "";
};

typedef struct LINE LINE;

void init_line(LINE& l);
void init_line(LINE& l, int s);
void insert_char(LINE& l, char c, int index);
void delete_char(LINE& l, int index);
void append_char(LINE& l, char c);

#endif