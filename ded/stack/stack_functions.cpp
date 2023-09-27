#include "stack.h"

const Elem_t TRASH_ELEM = 0xDEAD;

#define STACK_CTOR(capacity) stackCtor((capacity), __LINE__, __FILE__, __PRETTY_FUNCTION__);

enum stack_status //каждая ошибка соответствует определенному биту в целом числе
{
	ALL_IS_OK = 0,
	NEGATIVE_SIZE = 1 << 0, //представление степеней двойки при помощи побитового сдвига
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

struct stack* stackCtor (long long capacity, size_t line, const char* file, const char* func) //конструктор
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

size_t stack_OK (struct stack* stk) //возвращает целое число, в двоичном представлении которого каждая единица свидетельствует о наличии конкретной ошибки
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
	
	printf("\nStack status:\n");

	if (error == 0) printf("The stack is OK\n"); 
	
	for (size_t error_iter = 0; error_iter < 5; error_iter++)
	{
		if ( (error & (1 << error_iter)) > 0 ) puts(errors[error_iter]);
	}
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

size_t stackDtor (struct stack* stk) //деструктор
{
	for (size_t stk_iter = 0; stk_iter < (size_t) stk->size; stk_iter++)
	{
		*(stk->data + stk_iter) = TRASH_ELEM;
	}

	free(stk->data);

	stk->size = -5;
	stk->capacity = -3;
	stk->status = stack_OK(stk);

	return stk->status;
}

