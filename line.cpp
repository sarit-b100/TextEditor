#include "line.h"

void init_line(LINE& l, int s)
{
	l.size = s;
}

void init_line(LINE& l)
{
	l.size = DFLT_LINE_SIZE;
}

void insert_char(LINE& l, char c, int index)
{
	int len = strlen(l.line);

	for(int i = len; i > index; i--)
		l.line[i] = l.line[i-1];

	l.line[index] = c;
}

void delete_char(LINE& l, int index)
{
	int len = strlen(l.line);

	for(int i = index; i < len; i++)
		l.line[i] = l.line[i+1];
}

void append_char(LINE& l, char c)
{
	int len = strlen(l.line);

	insert_char(l, c, len);
	insert_char(l, '\0', len+1);
}

