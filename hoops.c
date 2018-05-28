#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0

typedef struct QUEUE{
	int front, rear, size; 
	int capcity; 
	int * array; 
} Queue; 

Queue * createQueue(int capacity){
	Queue * queue = (Queue *) malloc(sizeof(Queue));
	queue->capcity = capacity; 
	queue->front = queue->size = 0; 
	queue->rear = capacity -1; 
	queue->array = (int *) malloc(queue->capcity * sizeof(int));
	return queue; 
}

int isFull(Queue * queue){
	return (queue->size == queue->capcity); 
}

int isEmpty(Queue * queue){
	return (queue->size == 0); 
}

void enqueue(Queue* queue, int item){
	if(isFull(queue))
	{
		return; 
	}
	
	queue->rear = (queue->rear + 1)%queue->capcity;
	queue->array[queue->rear] = item;
	queue->size = queue->size + 1; 
	printf("%d enqueued to queue\n", item); 
}

int dequeue(Queue * queue){
	if(isEmpty(queue))
	{
		return INT_MIN;
	}
	int item = queue->array[queue->front];
	queue->front = (queue->front +1)%queue->capcity;
	queue->size = queue->size -1;
	return item; 
}


int front(Queue * queue){
	if(isEmpty(queue))
	{
		return INT_MIN;	
	}
	return queue->array[queue->front];
}

int rear(Queue * queue){
	if(isEmpty(queue)){
		return INT_MIN;
	}
	
	return queue->array[queue->rear];
}



typedef enum POINT_VALUE {
	three, two
} PointValue; 

int main(int argc, char *argv[]) {
	(void)argc;
	
	int numberOfPlayers = atoi(argv[1]); 
	int numberOfSeconds = atoi(argv[2]); 
	Queue * queue = createQueue(numberOfPlayers);
	
	
	
	
	
	
	
	
	
	// generate a random bool value
	srand(time(NULL));
	bool tf = FALSE;
	tf = (rand()%2);




	
	
	
	
	
	
	return 0; 
	
} 

/*
	REFEREE THREAD
		create players
		wait till players are ready then start the game
		ensure that the game ends after t seconds 
		print stats (order does not matter)
				Player 1 -> Score 2, Player 4 -> Score 3,...
		print winner
		
	PLAYER
		shoot once every second
		at the end of T "join" 
*/




