#ifndef KROWA_H_INCLUDED
#define KROWA_H_INCLUDED

int irandom(int, int);
// returns random int from int to int (inclusive)

double drandom(double, double);

float frandom(float, float);

//--------------------------------------------------------FIX THIS----------------------------------------------
void read_variable(char *, int *, char *);
//pointer to prompt string, pointer to variable to fill, pointer to format string
//ensures the read variable is in proper type
//--------------------------------------------------------FIX THIS----------------------------------------------

void merge1(int *, int, int ,int);
////merge one table with 2 sorted sequences


int * merge2(int *, int, int *, int);
//merge two tables with sorted sequences
//1,2: table 1 i and its size,
//3,4: table 2 i and its size

void mergesort(int [], int , int);
//pointer to table, start index, end index

int float_check(const char *, int);
//pointer to string, length of string
//if using with main() function arguments add 1 to length
//returns 1 if pointer points at number, returns 0 otherwise

int bin_search(const int *, const int, const int, const int);
//pointer to sorted sequence, value to find, index of sequence start, index of sequence end
// returns index to given value, if none is find returns -1



#endif // KROWA_H_INCLUDED
