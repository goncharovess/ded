#include "stack.h"

int main()
{
	struct stack* stk = STACK_CTOR(15);	
	STACK_DUMP(stk);
	stackDtor(stk);
}
