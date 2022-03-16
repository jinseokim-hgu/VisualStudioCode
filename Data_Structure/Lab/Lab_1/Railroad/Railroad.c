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
    int N,C;
    
    scanf("%d %d", &N, &C);

    int seq[1000];
    int dest[1000];
    int car=1;
    int suc=0;

    for(int i=0;i<N;i++){
        scanf("%d", &seq[i]);
    }

    stack * st=create_stack(C,sizeof(int));

    for(int i=0;i<N;i++){
        while(!(seq[i]==dest[i])){
            if(seq[i]==car){
                dest[i]=car;
                car+=1;
            }
            else if(seq[i]>car){
                if(push(st, &car)){
                    suc=1;
                    break;
                }
                car+=1;
            }
            else{
                pop(st, &dest[i]);
                if(dest[i]!=seq[i]){
                    suc=1;
                    break;
                }
            }
        }
        if(suc==1){
            break;
        }
    }
    if(suc==1){
        printf("false");
    }
    else{
        printf("true");
    }
}