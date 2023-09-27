#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <locale>
#include <sys/stat.h>
#include <malloc.h>
#include <string.h>

typedef int Elem_t;

struct stack
{
	Elem_t* data;
	long long size;
	long long capacity;
	size_t status;

	size_t line;
	char* file;
	char* func;
};

//stack functions

struct stack* stackCtor(long long capacity, size_t line, const char* file, const char* func);

size_t stackPush(struct stack* stk, Elem_t value);

Elem_t stackPop(struct stack* stk);


#endif //STACK_H


