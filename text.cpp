#include "text.h"

int main(int argc, char* argv[])
{
	PAGE page1;
	int ch;
	int flag = 0;
	int cur_y, cur_x; // cursor position
	int bound_y, bound_x; // screen measurements
	int index; // index to delete

	if(argc > 1)
	{
		init_page(page1, argv[1]);

		if(fileExists(argv[1])) // if a file with the given name is found, it is opened
		{
			cout << "Opening file...\n";
			loadfile(page1, argv[1]);
		}
		else // otherwise a new file with the given name is created
		{
			cout << "Creating file...\n";
		}
	}
	else
	{
		cout << "Provide a filename to continue\n";
		exit(0);
	}


	initscr(); // using NCURSES to initialize the standard screen
	keypad(stdscr, TRUE);
	noecho();
	getyx(stdscr, cur_y, cur_x);
	getmaxyx(stdscr, bound_y, bound_x);
	//nodelay(stdscr, TRUE);

	refresh_screen(page1);

	while(!flag)
	{
		if(cur_x == bound_x - 2) // if the entered text reaches the right screen boundary, a newline is added automatically
			ch = '\n';
		else
			ch = getch();

		switch(ch)
		{
			case KEY_F(4): // Press F4 to quit
			flag = 1;
			break;

			case KEY_F(6): // Press F6 to save the file
			savefile(page1);
			//printfile(page1);
			break;

			case KEY_LEFT:
			getyx(stdscr, cur_y, cur_x);
			if(cur_x > 0)
			{
				cur_x--;
				move(cur_y, cur_x);
			}
			break;

			case KEY_RIGHT:
			getyx(stdscr, cur_y, cur_x);
			if(cur_x < bound_x - 2)
			{
				cur_x++;
				move(cur_y, cur_x);
			}
			break;

			case KEY_UP:
			getyx(stdscr, cur_y, cur_x);
			if(cur_y > 0)
			{
				cur_y--;
				move(cur_y, cur_x);
			}
			break;

			case KEY_DOWN:
			getyx(stdscr, cur_y, cur_x);
			if(cur_y < bound_y - 2)
			{
				cur_y++;
				move(cur_y, cur_x);
			}
			break;

			case KEY_BACKSPACE:
			getyx(stdscr, cur_y, cur_x);
			if(cur_x > 0)
			{
				move(cur_y, cur_x - 1);
				delch();
				delete_char(page1.lines[cur_y], cur_x - 1);	
			}
			break;

			case '\n':
			getyx(stdscr, cur_y, cur_x);
			cur_y++;
			cur_x = 0;
			move(cur_y, cur_x);
			insert_blankline(page1, (char*)"", cur_y);
			break;

			default: // all other characters which are treated as text input
			if(isprint(ch))
			{
				getyx(stdscr, cur_y, cur_x);
				//append_char(page1, (char)ch);
				insert_char(page1, (char)ch, cur_y, cur_x);
				move(cur_y, cur_x + 1);
			}
		}
		refresh_screen(page1);
	}

	endwin();
	printfile(page1);
	del_page(page1);
	return 0;
}

void printfile(PAGE& p)
{
	for(int i = 0; i <= p.numlines; i++)
	{
		char* st = p.lines[i].line;
		printf("%s\n", st);
	}
}

void refresh_screen(PAGE& p) // refreshes the standard screen with the updated contents of the page
{
	int cur_y, cur_x;
	getyx(stdscr, cur_y, cur_x);
	clear();
	int nl = p.numlines;

	for(int i = 0; i <= nl; i++)
	{
		addstr(p.lines[i].line);
		if(i != nl) addch('\n');
	}
	move(cur_y, cur_x);
	refresh();
}

void loadfile(PAGE& p, char* fname)
{
	FILE* file = fopen(fname, "r");
	char ch = '\0';

	while(TRUE)
	{
		ch = fgetc(file);
		while(ch != '\n' && ch != EOF)
		{
			append_char(p.lines[p.numlines], ch);
			ch = fgetc(file);
		}
		if(ch == EOF)
			break;
		insert_blankline(p);
	}
	fclose(file);
}

void savefile(PAGE& p)
{
	FILE* file = fopen(p.filename, "w");

	for(int i = 0; i <= p.numlines; i++)
	{
		fprintf(file, "%s", p.lines[i].line);
		fputc('\n', file);
	}

	fclose(file);
}

int fileExists(char* fname)
{
	FILE* file = fopen(fname, "r");

	if(file != NULL)
	{
		fclose(file);
		return 1;
	}
	return 0;
}