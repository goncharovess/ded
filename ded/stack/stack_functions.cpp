#include "stack.h"

const Elem_t TRASH_ELEM = 0xDEAD;

#define STACK_CTOR(capacity) stackCtor((capacity), __LINE__, __FILE__, __PRETTY_FUNCTION__);
#define STACK_DUMP(stk) stackDump((stk), #stk, __LINE__, __FILE__, __PRETTY_FUNCTION__ );

enum stack_status
{
	ALL_IS_OK = 0,
	NEGATIVE_SIZE = 1 << 0,
	NEGATIVE_ITER = 1 << 1,
	NEGATIVE_CAPACITY = 1 << 2,
	SIZE_BIGGER_CAPACITY = 1 << 3,
	NEXT_ELEM_NOT_TRASH = 1 << 4
};

const char* errors[5] = {"The stack has a negative size\n",
		         "The stack has a negative iter\n", 
			 "The stack has a negative capacity\n",
			 "Size of stack is bigger than it's capacity\n",
			 "Empty cells are not filled with TRASH_ELEM\n"};

struct stack* stackCtor (long long capacity, size_t line, const char* file, const char* func) 
{
	struct stack* stk = (struct stack*) malloc(sizeof(struct stack));	
	
	stk->data = (Elem_t*) calloc(capacity, sizeof(Elem_t));
	stk->capacity = capacity;
	stk->size = 0;
	stk->line = line;
	stk->file = file;
	stk->func = func;
	stk->status = stack_OK(stk);

	return stk;
}

size_t stack_OK (struct stack* stk)
{
	size_t error = 0;

	if (stk->size < 0) error |= NEGATIVE_SIZE;
	if (stk->data == NULL) error |= NEGATIVE_ITER;
	if (stk->capacity < 0) error |= NEGATIVE_CAPACITY;
	if (stk->size > stk->capacity) error |= SIZE_BIGGER_CAPACITY;
	
	for (size_t data_iter = stk->size; data_iter < (size_t) stk->capacity; data_iter++)
	{
		if (*(stk->data + data_iter) != TRASH_ELEM)
		{
			error |= NEXT_ELEM_NOT_TRASH;
			return error;
		}
	}
	return error;
}	

void print_stack_status (struct stack* stk)
{
	size_t error = stk->status;
	
	printf("Stack status:\n");

	if (error == 0) printf("The stack is OK\n"); 
	
	for (size_t error_iter = 0; error_iter < 5; error_iter++)
	{
		if ( (error & (1 << error_iter)) > 0 ) puts(errors[error_iter]);
	}
}

void stackDump (struct stack* stk, const char* name, size_t line, const char* file, const char* func)
{
	printf("Name of stack: %s\n", name);
	printf("Stack adress: %p\n\n", stk);
	
	printf("The stack has been created..\n");
	printf("in function %s\n", stk->func);
	printf("from file %s\n", stk->file);
	printf("on the line %d\n\n", stk->line);

	printf("Dump is called..\n");
	printf("in function %s\n", func);
	printf("from file %s\n", file);
	printf("on the line %d\n\n", line);

	printf("Size of stack: %lld\n", stk->size);
	printf("Capacity of stack: %lld\n\n", stk->capacity);
	
	printf("data[%lld]\n", stk->capacity);
	printf("{\n");
	for (size_t data_iter = 0; data_iter < (size_t) stk->capacity; data_iter++)
	{
		if (data_iter < (size_t) stk->size)
		{
			printf("\t*[%d] = %d\n", data_iter, *(stk->data + data_iter));
		}
		else
		{
			printf("\t [%d] = %d\n", data_iter, *(stk->data + data_iter));
		}
	}
	printf("}");
}

size_t stackPush (struct stack* stk, Elem_t value)
{
	stk->status = stack_OK(stk);
	if (stk->status) return stk->status;

	if (stk->size == stk->capacity)
	{
		stk->capacity *= 2;
		stk->data = (Elem_t*) realloc(stk->data, sizeof(Elem_t) * (size_t) stk->capacity);
		
		for (size_t stk_iter = stk->size; stk_iter < (size_t) stk->capacity; stk->iter++)
		{
			*(stk->data + stk->iter) = TRASH_ELEM;
		}
	}
	
	*(stk->data + stk->size) = value;
	(stk->size)++;

	stk->status = stack_OK(stk);

	return stk->status;
}

Elem_t stackPop (struct stack* stk)
{
	stk->status = stack_OK(stk);
	if (stk->status) return stk->status;

	if (stk->capacity > 2 * stk->size)
	{
		stk->capacity /= 2;
	}
	
	if (stk->size == 0)
	{
		printf("Stack is already empty\n");
		return TRASH_ELEM;
	}
	
	(stk->size)--;
	Elem_t removed_elem = *(stk->data + stk->size);
	*(stk->data + stk->size) = TRASH_ELEM;

	return removed_elem;
}

size_t stackDtor (struct stack* stk) 
{
	for (size_t stk_iter = 0; stk_iter < (size_t) stk->size; stk_iter++)
	{
		*(stk->data + stk_iter) = TRASH_ELEM;
	}

	free(stk->data);

	stk->size = -5;
	stk->capacity = -3;
	
	size_t status = stack_OK(stk);

	free(stk);

	return status;
}

