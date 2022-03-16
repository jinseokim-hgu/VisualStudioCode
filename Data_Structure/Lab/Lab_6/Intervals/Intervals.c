#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct arraylist {
	int capacity ;
	int length ;
	int unit ;
	void * elements ;
} ;

typedef struct interval {
    float value;
    char type;
} interval_i ;

typedef struct arraylist arraylist_t ;

arraylist_t * 
arraylist_alloc (int unit) 
{
	arraylist_t * l ;

	l = (arraylist_t *) malloc(sizeof(arraylist_t)) ;
	l->capacity = 10 ;
	l->length = 0 ;
	l->unit = unit ;
	l->elements = (int *) calloc(l->capacity, l->unit) ;
	return l ;
}

void
arraylist_free (arraylist_t * l, void (* free_element)(void * e)) 
{
	if (free_element != 0x0) {
		int i ;
		for (i = 0 ; i < l->length ; i++) {
			void * elem = l->elements + l->unit * i ;
			free_element(elem) ;
		}
	}
	free(l->elements) ;
	free(l) ;
}

int 
arraylist_length (arraylist_t * l)
{
	return l->length ;
}

void
arraylist_print (arraylist_t * l, void (* print_element)(void * e)) 
{
	int i ;
	for (i = 0 ; i < l->length ; i++) {
		print_element(l->elements + l->unit * i) ;
	}
}

void
arraylist_insert_first (arraylist_t * l, void * e)
{
	if (l->length == l->capacity) {
		l->capacity *= 2 ;
		l->elements = (int *) realloc(l->elements, (size_t) l->capacity * l->unit) ;
	}
	int i ;
	for (i = l->length - 1 ; i >= 0 ; i--)
		memcpy(l->elements + (i + 1) * l->unit, l->elements + i, l->unit) ;
	memcpy(l->elements, e, l->unit) ;
	l->length += 1 ;
}

void
arraylist_insert_last (arraylist_t * l, void * e)
{
	if (l->length == l->capacity) {
		l->capacity *= 2 ;	
		l->elements = (int *) realloc(l->elements, (size_t) l->capacity * l->unit ) ;
	}
	memcpy(l->elements + l->length * l->unit, e, l->unit) ;
	l->length += 1 ;
}

int
arraylist_remove_first (arraylist_t * l, void * e) 
{
	if (l->length == 0)
		return 1 ;
	
	memcpy(e, l->elements, l->unit) ;
	int i ;
	for (i = 1 ; i < l->length ; i++) 
		memcpy(l->elements + (i - 1) * l->unit, l->elements + i, l->unit) ;
	l->length -= 1 ;
	return 0 ;
}

int
arraylist_remove_last (arraylist_t * l, void * e) 
{
	if (l->length == 0)
		return 1 ;
	
	memcpy(e, l->elements + (l->length - 1) * l->unit, l->unit) ;
	l->length -= 1 ;
	return 0 ;
}

int
arraylist_get (arraylist_t * l, int pos, void * e)
{
	if (l->length <= pos) 
		return 1 ;
	
	memcpy(e, l->elements + pos * l->unit, l->unit) ;
	return 0 ;
}

void
arraylist_sort (arraylist_t * l, int (* cmp_elements)(void * e1, void * e2))
{
	int i, j, m ;
	char * t = malloc(l->unit) ;
	for (i = 0 ; i < l->length - 1 ; i++) {
		m = i ;
		for (j = i + 1 ; j < l->length ; j++) {
			if (cmp_elements(l->elements + j * l->unit, l->elements  + m * l->unit) < 0)
				m = j ;
		}
		memcpy(t, l->elements + i * l->unit, l->unit) ;
		memcpy(l->elements + i * l->unit, l->elements + m * l->unit, l->unit) ;
		memcpy(l->elements + m * l->unit, t, l->unit) ;
	}
	free(t) ;
}

void
_arraylist_qsort (arraylist_t * l, int (* cmp_elements)(void * e1, void * e2), void * begin, void * end)
{
	if (begin >= end - l->unit)
		return ;

	int unit = l->unit ;
	void * t = malloc(sizeof(unit)) ;

	void * pivot = begin ;
	void * lbound = begin + unit ;
	void * rbound = end - unit ;
	
	while (lbound <= rbound) {
		while (lbound <= end - unit && cmp_elements(lbound, pivot) <= 0) 
			lbound += unit ;
			
		while (begin < rbound && cmp_elements(pivot, rbound) < 0) 
			rbound -= unit ;
		
		if (lbound <= rbound) {
			memcpy(t, lbound, unit) ;
			memcpy(lbound, rbound, unit) ;
			memcpy(rbound, t, unit) ;
			lbound += unit ;
			rbound -= unit ;
		}
	}
	memcpy(t, rbound, unit) ;
	memcpy(rbound, pivot, unit) ;
	memcpy(pivot, t, unit) ;
	free(t) ;

	if(rbound != end - unit){
		_arraylist_qsort(l, cmp_elements, begin, rbound + unit) ;
		_arraylist_qsort(l, cmp_elements, rbound + unit, end) ;
	}
	else{
		_arraylist_qsort(l, cmp_elements, begin, rbound) ;
	}
}

void
arraylist_qsort (arraylist_t * l, int (* cmp_elements)(void * e1, void * e2))
{
	_arraylist_qsort(l, cmp_elements, l->elements, l->elements + l->length * l->unit) ;
}

void
free_float (void * p)
{ 
	interval_i ** i = (interval_i **) p ;
	free(*i) ;
}

int
cmp_float (void * e1, void * e2)
{
	interval_i * i1 = *((interval_i **) e1) ;
	interval_i * i2 = *((interval_i **) e2) ;

    if(i1->value==i2->value){
		if(i1->type=='o' && i2->type=='c'){
			return 1;
		}
		else{
			return -1;
		}
	}
	return (i1->value - i2->value) ;
}

void
print_float (void * p) 
{
	interval_i * f = *((interval_i **) p) ;
	printf("%f\n", f->value) ;
}

int main()
{
    arraylist_t * l=arraylist_alloc(sizeof(interval_i *));
	interval_i * i1;
	interval_i * i2;

    int size;
    scanf("%d", &size);

    float input[200];
    for(int i=0; i<2*size; i+=2){
		i1=(interval_i *)malloc(sizeof(interval_i));
		i2=(interval_i *)malloc(sizeof(interval_i));
        scanf("%f %f", &input[i], &input[i+1]);
		i1->value=input[i];
		i1->type='o';
		i2->value=input[i+1];
		i2->type='c';
        arraylist_insert_last(l, &i1);
		arraylist_insert_last(l, &i2);
    }

    arraylist_qsort(l, cmp_float);

    int max_overlap=1;
    int overlap=0;
    int i;

    for(i=0; i<2*size; i++){
        interval_i * interval;
        arraylist_get(l, i, &interval);

		if(interval->type=='o'){
			overlap+=1;
			if(max_overlap < overlap){
				max_overlap = overlap;
			}
		}
		else{
			overlap-=1;
		}
    }
    printf("%d\n", max_overlap);
	arraylist_free(l, free_float) ;
}