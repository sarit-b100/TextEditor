#include "page.h"
#include "line.h"

void init_page(PAGE& p, char* fname)
{
	p.filename = new char[DFLT_FILENAME_SIZE];
	strcpy(p.filename, fname);
	LINE li;
	init_line(li);
	p.lines.push_back(li);
	p.numlines = 0;
}

/*void init_page(PAGE* p, char* fname, int size)
{
	p = new PAGE;
	strcpy(p->filename, fname);
	p->size = size;
	p->lines = new LINE[p->size];
	p->filename = 0;
}*/

void del_page(PAGE& p)
{
	p.lines.clear();
	p.numlines = 0;
}

void insert_blankline(PAGE& p, char str[], int pos)
{
	LINE li;
	init_line(li);
	//li.line = str;

	for(int i = 0; i < strlen(str); i++)
		append_char(li, str[i]);

	p.lines.insert(p.lines.begin() + pos, li);
	p.numlines++;
}

void insert_blankline(PAGE& p)
{
	LINE li;
	init_line(li);
	p.lines.push_back(li);
	p.numlines++;
}

/*void append_char(PAGE& p, char c)
{
	int np = p.numlines; // this represents the vector index of the current line in the given page
	append_char(p.lines[np], c); // appends the character at the end of the current line
}*/

void insert_char(PAGE& p, char c, int y, int x)
{
	insert_char(p.lines[y], c, x); // appends the character at index x of the yth line
}

void del_line(PAGE& p, int pos)
{
	p.lines.erase(p.lines.begin() + pos);
	p.numlines--;
}