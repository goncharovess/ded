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

struct stack
{
	Elem_t* data;
	long long size;
	long long capacity;
	int status;

	size_t line;
	const char* file;
	const char* func;
};

//stack functions

struct stack* stackCtor (long long capacity, size_t line, const char* file, const char* func);

int stack_OK (struct stack* stk);

void stackDump(struct stack* stk, const char* name, size_t line, const char* file, const char* func);

void print_stack_status (struct stack* stk);

int stackPush (struct stack* stk, Elem_t value);

Elem_t stackPop (struct stack* stk);

int stackDtor (struct stack* stk);

#endif //STACK_H



