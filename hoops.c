#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>
#include <pthread.h>

#define TRUE 1
#define FALSE 0

pthread_mutex_t mutexsum; 
int scores[100];

struct Args{
	int numberOfShots; 
	int index; 	
};

void * score(void * a){
	struct Args * arg = (struct Args * ) a; 
	bool shotmade = NULL; 
	bool threePointer = NULL;  
	srand(time(NULL));
	
	pthread_mutex_lock (&mutexsum);
		for(int i = 0; i<arg->numberOfShots; ++i){
			shotmade = (rand()%2);
			threePointer = (rand()%2); 
			if(shotmade){
				if(threePointer){
					scores[arg->index] += 3;
				}else{
					scores[arg->index] += 2;
				}
			}
		}
	pthread_mutex_unlock (&mutexsum); 
	pthread_exit((void *) 0); 
}


int main(int argc, char *argv[]) {
	(void)argc;
	void * status;
	const int numberOfPlayers = atoi(argv[1]); 
	int numberOfShots = atoi(argv[2]); 
	
	for(int i = 0; i<numberOfPlayers; ++i){
		scores[i] = 0; 
	}

	pthread_t threads[numberOfPlayers]; 
	pthread_attr_t attr; 
	pthread_mutex_init(&mutexsum, NULL); 
	pthread_attr_init(&attr); 
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); 

	struct Args * args = malloc(numberOfPlayers * sizeof(args)); 

	for(int i = 0; i<numberOfPlayers; ++i){
		args[i].index = i; 
		args[i].numberOfShots = numberOfShots; 	
		pthread_create(&threads[i], &attr, score, (void *)&args[i]);
	}

	pthread_attr_destroy(&attr); 
	for(int i = 0; i<numberOfPlayers; ++i){
		pthread_join(threads[i], &status); 
	}

	int highScore = 0; 

	// print all scores 
	for(int i = 0; i< numberOfPlayers-1; ++i){
		printf("Player %d -> Score %d, ", i+1, scores[i]); 
		if(scores[i] > highScore)
			highScore = scores[i]; 
	}
	printf("Player %d -> Score %d\n", numberOfPlayers, scores[numberOfPlayers-1]);
	
	if(scores[numberOfPlayers-1] > highScore){
		highScore = scores[numberOfPlayers-1]; 
	}
	
	for(int i = 0; i<numberOfPlayers-1; ++i ){
		if(scores[i] == highScore)
			printf("Player %d is a winner with %d points\n", i+1, highScore); 
	}
	pthread_mutex_destroy(&mutexsum); 
	pthread_exit(NULL);	
	free(args); 
	
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
