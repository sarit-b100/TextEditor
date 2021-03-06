#ifndef TEXT_H
#define TEXT_H

#include "page.h"
#define FULLSTOP 46

void printfile(PAGE& p);
void refresh_screen(PAGE& p);
void loadfile(PAGE& p, char* fname);
void savefile(PAGE& p);
int fileExists(char* fname);

#endif