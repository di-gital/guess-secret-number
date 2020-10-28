#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

struct Guess {
	int val;
	struct Guess *next;
};

struct Guess *guessList;
struct Guess *topOfList;

void guessLoop(int guess);
int traverseList(int valueToFind);
void addToList(int number);
void clearGuessList();

int main(void) {
	srand(time(NULL));
	int randomNum = rand() % 100;
	guessList = NULL;
	topOfList = guessList;

	guessLoop(randomNum);
	clearGuessList();
}

void guessLoop(int randomNum) {
	bool isCorrectGuess = false;
	int wrongGuesses = 0;
	int currGuess;

	while(!isCorrectGuess) {
		printf("Please input a number from 0 to 99\n");
		scanf("%d", &currGuess);	
		if(currGuess == randomNum) {
			printf("Correct! Guesses: %d", wrongGuesses);
			return;
		}
		if(!traverseList(currGuess)) {
			addToList(currGuess); 
			++wrongGuesses;
			if(currGuess < randomNum)
				printf("Too Low!\n");
			else printf("Too high!\n");
		}
	}	
}

int traverseList(int valueToFind) {
	struct Guess *bottom = guessList;
	while(guessList) {
		if(guessList->val == valueToFind) {
			guessList = bottom;
			return true;	
		}	
		guessList = guessList->next;
	}
	guessList = bottom;
	return false;
}

void addToList(int number) {
	if(!guessList) {
		guessList = malloc(sizeof(struct Guess));
		guessList->val = number;
		guessList->next = NULL;
		topOfList = guessList;
	}
	topOfList->next = malloc(sizeof(struct Guess));
	topOfList->next->val = number;
	topOfList->next->next = NULL;
	topOfList = topOfList->next;
}

void clearGuessList() {
	struct Guess *last = guessList;
	while(guessList) {
      		last = guessList;
	        guessList = guessList->next;
       		free(last);	       
	}	       
}
