#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef 
	struct {
		void * buffer ;
		int unit ;
		int capacity ;
		int front ;
		int rear ;
		int full ;
	} 
	queue ;

queue * 
create_queue (int capacity, int unit) 
{
	queue * que = malloc(sizeof(queue)) ;
	que->capacity = capacity ;
	que->unit = unit ;
	que->buffer = calloc(capacity, unit) ;
	que->front = 0 ;
	que->rear = 0 ;
	que->full = 0 ;
	return que ;
}

void
delete_queue (queue * que) 
{
	if (que->buffer != 0x0)
		free(que->buffer) ;
	free(que) ;
}

int 
is_empty (queue * que) 
{
	return (que->front == que->rear) && (que->full == 0) ;
}

int 
is_full (queue * que) 
{
	return que->full ;
}

int 
enqueue (queue * que, void * elem)
{
	if (is_full(que))
		return 1 ;

	memcpy(que->buffer + ((que->rear) * (que->unit)), elem, que->unit) ;
	que->rear = (que->rear + 1) % que->capacity ;

	if (que->rear == que->front)
		que->full = 1 ;

	return 0 ;
}

int
dequeue (queue * que, void * elem)
{
	if (is_empty(que)) 
		return 1 ;
	
	memcpy(elem, que->buffer + que->front * que->unit, que->unit) ;
	que->front = (que->front + 1) % que->capacity ;	
	que->full = 0 ;

	return 0;
}

void
print_queue (queue * que, void (* print_element)(void * elem)) 
{
	int i ;
	if (que->front == que->rear && que->full == 0)
		return ;

	for (i = que->front ; i != que->rear ; i = (i + 1) % (que->capacity)) {
		printf("[") ;
		print_element(que->buffer + i * que->unit) ;
		printf("] ") ;
	}
	printf("\n") ;
}

typedef struct {
	int x ;
	int y ;
} pos ;

void
print_element (void * p)
{
	pos * elem = (pos *) p ;
	printf("%d,%d", elem->y, elem->x) ;
}

const int d[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}} ;

int main()
{
    int W, H;
	int area=0,num=0,max=0;

	scanf("%d %d", &W, &H);
	int min=W*H;

	queue * tasks ;
	tasks = create_queue(W*H, sizeof(pos)) ;
	
	int map[20][20];
	int visited[20][20];

	for(int i=0;i<H;i++){
		for(int j=0;j<W;j++){
			scanf("%d", &map[i][j]);
			visited[i][j]=0;
		}
	}

	for(int i=0;i<H;i++){
		for(int j=0;j<W;j++){
			if(map[i][j]==1 && visited[i][j]==0){
				pos init;
				init.y=i;
				init.x=j;
				enqueue(tasks, &init); area+=1;
				visited[i][j]=1;
				while(!is_empty(tasks)){
					pos curr;

					dequeue(tasks, &curr) ;
					for (int i_d = 0 ; i_d < 4 ; i_d++) {
						pos next ;

						next.y = curr.y + d[i_d][0] ;
						next.x = curr.x + d[i_d][1] ;
						if (0 <= next.x && next.x < W) {
							if (0 <= next.y && next.y < H) {
								if (map[next.y][next.x]==1 && visited[next.y][next.x]==0) {
									enqueue(tasks, &next) ; area+=1;
									visited[next.y][next.x] = 1 ;
								}
							}
						}
					}
				}
				num+=1;
				if(max<area){
					max=area;
				}
				if(area<min){
					min=area;
				}
				area=0;
			}
		}
	}
	printf("%d %d %d\n", num, min, max);
	delete_queue(tasks);
	return 0;
}