#include "assert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

// Unit Test -- Smithy

// Smithy should result in player that plays Smithy card drawing +3 cards from deck

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
    cardEffect(smithy, choice1, choice2, choice3, &G, NULL);

// Check three cards drawn

  assert(numHandCards(&G) == temp + 2);
  printf("Smithy - 3 cards drawn TEST PASS\n");
  printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

  return 0;
}
