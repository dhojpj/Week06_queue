#ifndef DRIVER_H
#define DRIVER_H

#include <cstdlib>
#include <iostream>
#include "queue.h"
//#include <string>
#include <fstream>
#include <cstring>


using namespace std;

char menu(string title[]);
void perform(char ans, int &list, queue<char> &one, queue<char> &two);
void loadfile(queue<char> &one,char *filename);
void help();
void checkArgs(int argc, char *argv[],queue<char> &one,queue<char> &two, int &list);



#endif // DRIVER_H
