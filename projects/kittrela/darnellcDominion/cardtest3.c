// Author: Chris Darnell
// 4/30/2017
// cardtest3.c - Council Room


#include "assert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>


#define TESTCARD "council_room"

// Unit Test -- Council Room 

// Council Room should result in player that plays CR card drawing +4 cards & gain +1 buy 

int main () {

  struct gameState G;
  int choice1 = 0, choice2 = 0, choice3 = 0;
  int temp;
  int k[10] = {adventurer, council_room, embargo, village, minion, mine, cutpurse,
         sea_hag, tribute, smithy};

// init game instance

  initializeGame(2, k, 4, &G);

  printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    temp = numHandCards(&G);
    cardEffect(council_room, choice1, choice2, choice3, &G, NULL);

// Check four cards drawn

  assert(numHandCards(&G) == temp + 3);
  printf("Council Room - 4 cards drawn TEST PASS\n");
  printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

  return 0;
}


