#include "stack.h"

const Elem_t TRASH_ELEM = 0xDEAD;

#define STACK_CTOR(capacity) stackCtor((capacity), __LINE__, __FILE__, __PRETTY_FUNCTION__);

struct stack* stackCtor (long long capacity, int line, const char* file, const char* func)
{
	struct stack stk;	
	
	stk->data = (Elem_t*) calloc(capacity, sizeof(Elem_t));
	stk->capacity = capacity;
	stk->size = 0;
	stk->line = line;
	stk->file = strdup(file);
	stk->func = strdup(func);

	return stk;
}

int stackPush (struct stack* stk, Elem_t value)
{
	assert(stk != NULL);
	assert(stk->data != NULL);

	if (stk->size == stk->capacity)
	{
		stk->capacity *= 2;
		stk->data = (Elem_t*) realloc(stk->data, sizeof(Elem_t) * (size_t) stk->capacity);
		*(stk->data + stk->size) = value;
		(stk->size)++;	
	}

	return stk->status;
}

Elem_t stackPop (struct stack* stk)
{
	assert(stk != NULL);
	assert(stk->data != NULL);

	if (stk->capacity > 2 * stk->size)
	{
		stk->capacity /= 2;
	}
	
	if (stk->size == 0)
	{
		puts("You can't pop from an empty stack\n");
	}
	
	Elem_t removed_elem = *(stk->data + stk->size);
	*(stk->data + stk->size) = TRASH_ELEM;
	(stk->size)--;

	return removed_elem;
}



