#include <iomanip>
#include <unistd.h>
#include <sys/types.h>
#include <string>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

void compil( char * root, char * progName);
void FinalLogWrite( ofstream & fout, int numPassed, int numTest);
void LogWrite( ofstream & fout, int testNum, std::string result);

