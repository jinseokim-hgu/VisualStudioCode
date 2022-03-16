#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main()
{
    char bracket[100];
    int depth=0;
    char element;
    stack * st;

    scanf("%s", bracket);

    st=create_stack(strlen(bracket),sizeof(char));

    for(int i=0;i<strlen(bracket);i++){
        if(bracket[i]=='(' || bracket[i]=='{' || bracket[i]=='<' || bracket[i]=='['){
            push(st,&bracket[i]);
            if(depth<st->top){
                depth=st->top;
            }
        }
        else if(bracket[i]==')'){
            get_element(st,st->top-1,&element);
            if(element=='('){
                pop(st,&element);
            }
            else{
                break;
            }
        }
        else if(bracket[i]=='}'){
            get_element(st,st->top-1,&element);
            if(element=='{'){
                pop(st,&element);
            }
            else{
                break;
            }
        }
        else if(bracket[i]=='>'){
            get_element(st,st->top-1,&element);
            if(element=='<'){
                pop(st,&element);
            }
            else{
                break;
            }
        }
        else if(bracket[i]==']'){
            get_element(st,st->top-1,&element);
            if(element=='['){
                pop(st,&element);
            }
            else{
                break;
            }
        }
    }
    if(!is_empty(st)){
        printf("invalid");
    }
    else{
        printf("%d", depth);
    }
}