#include "stack.h"

const Elem_t TRASH_ELEM = 0xDEAD;

enum stack_status
{
	ALL_IS_OK = 0,
	NEGATIVE_SIZE = 1 << 0,
	NULL_DATA = 1 << 1,
	NEGATIVE_CAPACITY = 1 << 2,
	SIZE_BIGGER_CAPACITY = 1 << 3,
	NEXT_ELEM_NOT_TRASH = 1 << 4
};

static const char* errors[5] = {"The stack has a negative size\n",
		         	"Pointer to data is NULL\n", 
			 	"The stack has a negative capacity\n",
			 	"Size of stack is bigger than it's capacity\n",
			 	"Empty cells are not filled with TRASH_ELEM\n"};

Stack* stackCtor (long long capacity, size_t line, const char* file, const char* func) 
{
	Stack* stk = (Stack*) malloc(sizeof(Stack));	
	
	stk->data = (Elem_t*) calloc((size_t) capacity, sizeof(Elem_t));
	stk->capacity = capacity;
	stk->size = 0;
	stk->line = line;
	stk->file = file;
	stk->func = func;
	stk->status = stack_OK(stk);
	
	for (long long data_iter = stk->size; data_iter < stk->capacity; data_iter++)
	{
		*(stk->data + data_iter) = TRASH_ELEM;
	}

	return stk;
}

int stack_OK (Stack* stk)
{
	int error = 0;

	if (stk->size < 0) error |= NEGATIVE_SIZE;
	if (stk->data == NULL) error |= NULL_DATA;
	if (stk->capacity < 0) error |= NEGATIVE_CAPACITY;
	if (stk->size > stk->capacity) error |= SIZE_BIGGER_CAPACITY;
	
	for (long long data_iter = stk->size; data_iter < stk->capacity; data_iter++)
	{
		if (*(stk->data + data_iter) != TRASH_ELEM)
		{
			error |= NEXT_ELEM_NOT_TRASH;
			return error;
		}
	}
	return error;
}	

void print_stack_status (Stack* stk)
{
	int error = stk->status;
	
	printf("Stack status:\n");

	if (error == 0) printf("The stack is OK\n"); 
	
	for (size_t error_iter = 0; error_iter < 5; error_iter++)
	{
		if ( (error & (1 << error_iter)) > 0 ) puts(errors[error_iter]);
	}
}

void stackDump (Stack* stk, const char* name, size_t line, const char* file, const char* func)
{
	printf("Name of stack: %s\n", name);
	printf("Stack adress: %p\n\n", stk);
	
	printf("The stack has been created..\n");
	printf("in function %s\n", stk->func);
	printf("from file %s\n", stk->file);
	printf("on the line %lu\n\n", stk->line);

	printf("Dump is called..\n");
	printf("in function %s\n", func);
	printf("from file %s\n", file);
	printf("on the line %lu\n\n", line);

	printf("Size of stack: %lld\n", stk->size);
	printf("Capacity of stack: %lld\n\n", stk->capacity);
	
	printf("data[%lld]\n", stk->capacity);
	printf("{\n");
	for (long long data_iter = 0; data_iter < stk->capacity; data_iter++)
	{
		if (data_iter < stk->size)
		{
			printf("\t*[%lld] = %d\n", data_iter, *(stk->data + data_iter));
		}
		else
		{
			printf("\t [%lld] = %d\n", data_iter, *(stk->data + data_iter));
		}
	}
	printf("}\n");
}

int stackPush (Stack* stk, Elem_t value)
{
	stk->status = stack_OK(stk);
	if (stk->status) return stk->status;

	if (stk->size == stk->capacity)
	{
		stk->capacity *= 2;
		stk->data = (Elem_t*) realloc(stk->data, sizeof(Elem_t) * (size_t) stk->capacity);
		
		for (long long stk_iter = stk->size; stk_iter < stk->capacity; stk_iter++)
		{
			*(stk->data + stk_iter) = TRASH_ELEM;
		}
	}
	
	*(stk->data + stk->size) = value;
	(stk->size)++;

	stk->status = stack_OK(stk);

	return stk->status;
}

Elem_t stackPop (Stack* stk)
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

int stackDtor (Stack* stk) 
{
	for (long long stk_iter = 0; stk_iter < stk->size; stk_iter++)
	{
		*(stk->data + stk_iter) = TRASH_ELEM;
	}

	free(stk->data);

	stk->size = -5;
	stk->capacity = -3;

	free(stk);

	return 0;
}

