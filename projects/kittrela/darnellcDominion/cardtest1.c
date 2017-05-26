// Author: Chris Darnell
// 4/30/2017
// cardtest1.c - Adventurer

#include <assert.h>
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
// for rand
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TESTCARD "adventurer"

// Unit Test  -- Adventurer

// Adventurer should be an Action that digs for Treasure cards in your deck

int main() 

{

	int i, numPlayers, handPos, randomSeed;
	int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int currentPlayer = 0, testPass = 0, oneFail = 0, twoFail = 0;
	struct gameState beforePlay, afterPlay;
	int k[10] = {adventurer, remodel, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	
// seed rand within bounds for numPlayers/handPos/randomSeed
	
	srand(time(NULL));
	numPlayers = (rand() % 3) + 2;
	handPos = (rand() % 5);
	randomSeed = (rand() % 100);



	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);


	printf("----------------- Test: 2 or More Treasure Cards in Deck ----------------\n");

// Initialize a game state 
	
	initializeGame(numPlayers, k, randomSeed, &afterPlay);
	
// Set Adventurer for testing
	
	afterPlay.hand[currentPlayer][handPos] = adventurer;
	
	memcpy(&beforePlay, &afterPlay, sizeof(struct gameState));

		
	
// check AdventurerEffect
	
	if (cardEffect(adventurer, choice1, choice2, choice3, &afterPlay, handPos, &bonus) != 1) {
		printf("TEST PASS\n");
		testPass = -1;
	}
	



// Check currentPlayer handCount.

// Should be +1 for treasure add , -1 for play of adventurer card

printf("----------------- Test: Current Player Hand Count ----------------\n");
	
	if (afterPlay.handCount[currentPlayer] = beforePlay.handCount[currentPlayer]) {
		printf("TEST PASS\n");
		testPass = -1;
	}
	
	

// Check that adventurer card added to played pile

printf("----------------- Test: Adventurer Added to Played Card Pile After Play ----------------\n");

	if  (afterPlay.playedCards[beforePlay.playedCardCount] = adventurer) {
		printf("TEST PASS\n");
		testPass = -1;
	}


// Test playedCardCount incremented by 1

printf("----------------- Test: Number of Cards Played Incremented ----------------\n");


	if  (afterPlay.playedCardCount = beforePlay.playedCardCount + 1) {
		printf("TEST PASS\n");
		testPass = -1;
	}

	
// Verify card added is treasure
	
printf("----------------- Test: Card Added is treasure ----------------\n");

	int addedCard = afterPlay.hand[currentPlayer][afterPlay.handCount[currentPlayer] - 1];
	if ((addedCard = copper) || (addedCard = silver) || (addedCard = gold)) {
		printf("TEST PASS\n");
	}

	addedCard = afterPlay.hand[currentPlayer][afterPlay.handCount[currentPlayer] - 2];
	if ((addedCard = copper) || (addedCard = silver) || (addedCard = gold)) {
		printf("TEST PASS\n");
	}
	

	addedCard = afterPlay.hand[currentPlayer][afterPlay.handCount[currentPlayer] - 1];
	if ((addedCard = copper) || (addedCard = silver) || (addedCard = gold)) {
		printf("TEST PASS\n");
	}
	

// Check other player's hand/deck count were not changed

	printf("----------------- Test: Hand/Deck Count of Opponent not Changed ----------------\n");


	for (i = 1; i < numPlayers; i++) {
		if (afterPlay.deckCount[i] != beforePlay.deckCount[i]) {
			oneFail = -1;
		}
		if (afterPlay.handCount[i] != beforePlay.handCount[i]) {
			twoFail = -1;
		}
	}
	if (oneFail != -1) {
		printf("TEST PASS\n");
	}
	
	if (twoFail != -1) {
		printf("TEST PASS\n");
	}
	
	if (testPass == -1) {
		printf("TEST PASS\n");
	}



	
	
// Test if adventurer works when there is only one Treasure to find

	printf("----------------- Test: 1 Treasure Card in Deck ----------------\n"); 
	
// Init game with one treasure card in deck

	initializeGame(numPlayers, k, randomSeed, &afterPlay);
	afterPlay.hand[currentPlayer][handPos] = adventurer;

	for (i = 1; i < afterPlay.deckCount[currentPlayer]; i++) {
		afterPlay.deck[currentPlayer][i] = duchy;
	}
	
	memcpy(&beforePlay, &afterPlay, sizeof(struct gameState));
	

// check cardEffect actually calls something
	
	if (cardEffect(adventurer, choice1, choice2, choice3, &afterPlay, handPos, &bonus) != 1) {
		printf("TEST PASS\n");
		testPass = -1;
	}


// Check currentPlayer handCount.

// Should be +1 for treasure add , -1 for play of adventurer card

printf("----------------- Test: Current Player Hand Count ----------------\n");
	
	if (afterPlay.handCount[currentPlayer] = beforePlay.handCount[currentPlayer]) {
		printf("TEST PASS\n");
		testPass = -1;
	}
	

// Check that adventurer card added to played pile

printf("----------------- Test: Adventurer Added to Played Card Pile After Play ----------------\n");

	if  (afterPlay.playedCards[beforePlay.playedCardCount] = adventurer) {
		printf("TEST PASS\n");
		testPass = -1;
	}


// Test playedCardCount incremented by 1

printf("----------------- Test: Number of Cards Played Incremented ----------------\n");


	if  (afterPlay.playedCardCount = beforePlay.playedCardCount + 1) {
		printf("TEST PASS\n");
		testPass = -1;
	}

// Verify card added is treasure
	
printf("----------------- Test: Card Added is Treasure ----------------\n");

	addedCard = afterPlay.hand[currentPlayer][afterPlay.handCount[currentPlayer]-1];
	if ((addedCard = copper) || (addedCard = silver) || (addedCard = gold)) {
		printf("TEST PASS\n");
	}
	

// Check other player's hand/deck count were not changed

	printf("----------------- Test: Hand/Deck Count of Opponent not Changed ----------------\n");


	for (i = 1; i < numPlayers; i++) {
		if (afterPlay.deckCount[i] != beforePlay.deckCount[i]) {
			oneFail = -1;
		}
		if (afterPlay.handCount[i] != beforePlay.handCount[i]) {
			twoFail = -1;
		}
	}
	if (oneFail != -1) {
		printf("TEST PASS\n");
	}
	
	if (twoFail != -1) {
		printf("TEST PASS\n");
	}
	
	if (testPass != 0) {
		printf("TEST PASS\n");
	}


	printf("\n >>>>> testPass: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;

}