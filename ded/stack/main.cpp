#include "stack.h"

int main()
{
	Stack* stk = STACK_CTOR(15);	
	STACK_DUMP(stk);
	stackDtor(stk);
}
