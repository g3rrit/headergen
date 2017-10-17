#ifndef MAIN_H
#define MAIN_H

#include"stdbool.h"

FILE* headf;
FILE* sourcef;

bool debug;

bool createOutput(char *outdir, char *file, char *ext);
bool closeFiles();
void processFile(char *fname, char *outdir);

#endif
