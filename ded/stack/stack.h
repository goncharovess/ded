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

#define STACK_CTOR(capacity) stackCtor((capacity), __LINE__, __FILE__, __PRETTY_FUNCTION__);
#define STACK_DUMP(stk) stackDump((stk), #stk, __LINE__, __FILE__, __PRETTY_FUNCTION__ );

typedef struct
{
	Elem_t* data;
	long long size;
	long long capacity;
	int status;

	size_t line;
	const char* file;
	const char* func;
}Stack;

//stack functions

Stack* stackCtor (long long capacity, size_t line, const char* file, const char* func);

int stack_OK (Stack* stk);

void stackDump(Stack* stk, const char* name, size_t line, const char* file, const char* func);

void print_stack_status (Stack* stk);

int stackPush (Stack* stk, Elem_t value);

Elem_t stackPop (Stack* stk);

int stackDtor (Stack* stk);

#endif //STACK_H



