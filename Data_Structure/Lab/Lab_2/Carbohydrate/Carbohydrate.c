#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef 
	struct {
		void * buffer ;
		int unit ;
		int capacity ;
		int top ;
	}
	stack ;

stack * 
create_stack (int capacity, int unit) 
{
	stack * st = malloc(sizeof(stack)) ;
	st->capacity = capacity ;
	st->unit = unit ;
	st->top = 0 ;
	st->buffer = calloc(capacity, unit) ;
	return st ;
}

void
delete_stack (stack * st) 
{
	if (st->buffer != 0x0)
		free(st->buffer) ;
	free(st) ;
}

int 
is_empty (stack * st) 
{
	return (st->top == 0) ;
}

int 
is_full (stack * st) 
{
	return (st->top == st->capacity) ;
}

int 
push (stack * st, void * elem)
{
	if (is_full(st))
		return 1 ;

	memcpy(st->buffer + ((st->top) * (st->unit)), elem, st->unit) ;
	st->top += 1 ;

	return 0 ;
}

int
pop (stack * st, void * elem)
{
	if (is_empty(st)) 
		return 1 ;
	
	memcpy(elem, st->buffer + (st->top - 1) * st->unit, st->unit) ;
	st->top -= 1 ;
	return 0;
}

int
get_size (stack * st) 
{
	return st->top ;
}

int
get_element (stack * st, int index, void * elem)
{
	if (st->top <= index)
		return 1 ;

	memcpy(elem, st->buffer + index * st->unit, st->unit) ;
	return 0 ;
}

void
print_stack (stack * st)
{
	int i ;
	for (i = 0 ; i < get_size(st) ; i++) {
		int num ;
		get_element(st, i, &num) ;
		printf("[%d]", num) ;
	}
	printf(".\n") ;
}

int main()
{
    int i=0, H=1, C=12, O=16;
    int molecule=0;
    int open=0;

    stack * st;
    st=create_stack(100,sizeof(int));

	push(st, &open) ;

    char input[100];
    scanf("%s", input);

    do{
        if(input[i]=='('){
            push(st, &open) ;
        }
        else if(isalpha(input[i])){
            if(input[i]=='H'){
                push(st, &H) ;
            }
            else if(input[i]=='C'){
                push(st, &C);
            }
            else{
                push(st, &O);
            }
        }
        else if(input[i]==')' || input[i]=='\0'){
            int temp1, temp2, top, res, temp3;
            do{
                pop(st, &temp2);
                pop(st, &temp1);
                res=temp2+temp1;
                pop(st, &top);
                if(top!=open){
                    push(st, &top);
                }
                push(st, &res);
            }while(top!=open);
        }
        else if(isdigit(input[i])){
            int temp;
            pop(st, &temp);
            temp*=atoi(&input[i]);
            push(st, &temp);
        }
        i++;
    }while(input[i-1] != '\0');

    pop(st, &molecule);
    printf("%d\n", molecule);
    delete_stack(st);
    return 0;
}