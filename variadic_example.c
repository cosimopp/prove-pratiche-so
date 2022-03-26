#include <stdio.h>
#include <stdarg.h>

void printEachInt(int n, ...){ //always put mandatory arguments first, followed by "..."
	va_list args;
	//init
	va_start(args, n); //n = last mandatory argument
	for (int i = 0; i < n; i++){
		//applicabile solo per self promoting type variable
		int value = va_arg(args,int); //next call returns the next argument
		//we told va_arg what type the current argument is so it knows how big it is
		printf("%d\n", value);
	}
	va_end(args); //clean up
}

void main(){
	printEachInt(3, 1, 4, 6);
}