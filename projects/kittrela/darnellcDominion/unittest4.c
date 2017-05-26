// Author: Chris Darnell
// 4/30/2017
// unittest4.c - whoseTurn


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


// Unit Test  -- whoseTurn

// Testing if whoseTurn keeps track of which player's turn it is correctly.  


int main () {
   struct gameState G;
   int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
   

 // Init new game instance


   int r = initializeGame(2, k, 2, &G);
   assert(r == 0);

   printf("----------------- Testing: whoseTurn ----------------\n");

	
// Game should init to something...

 	printf(" TEST PASS\n");



 // Test if Player 0 gets a turn...


   printf("----------------- Testing Unit: Player 0's Turn ----------------\n");

   
   int a = whoseTurn(&G);
   assert(a == 0);
   printf(" TEST PASS\n");

// ...and once that turn ends...

   int b = endTurn(&G);


// Test if Player 1 gets a turn.


   printf("----------------- Testing Unit: Player 1's Turn ----------------\n");
   a = whoseTurn(&G);      
   assert(a == 1);
   printf(" TEST PASS\n");

// ...and once that turn ends...

   b = endTurn(&G);

 // Test if Player 1 gets the next turn


   printf("----------------- Testing Unit: Player 0's Next Turn ----------------\n");

   
   a = whoseTurn(&G);
   assert(a == 0);
   printf(" TEST PASS\n");


	printf("\n >>>>> SUCCESS: Testing complete whoseTurn <<<<<\n");


	return 0;
}
