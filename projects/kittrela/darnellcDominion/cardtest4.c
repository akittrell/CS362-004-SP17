// Author: Chris Darnell
// 4/30/2017
// cardtest4.c - Village


#include "assert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

// Unit Test -- Village 

// Village should result in player that plays Village card drawing +1 card & gain +2 actions 

int main() {
 
    
  struct gameState G;
  int choice1 = 0, choice2 = 0, choice3 = 0;
  int temp;
  int k[10] = {adventurer, council_room, embargo, village, minion, mine, cutpurse,
         sea_hag, tribute, smithy};

// initialize a game state and player cards
	initializeGame(2, k, 4, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	temp = numHandCards(&G);
  cardEffect(village, choice1, choice2, choice3, &G, NULL);

 // Check +1 card drawn

  assert(numHandCards(&G) == temp);
  printf("Village - 1 card drawn TEST PASS\n");
  printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

  return 0;
}
