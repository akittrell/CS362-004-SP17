// Author: Chris Darnell
// 4/30/2017
// unittest3.c - isGameOver



#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


// Unit Test  -- isGameOver

// Testing isGameOver ends game as it is supposed to 



int main () {
   struct gameState G;
   int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
   

 // Init new game instance


   int r = initializeGame(2, k, 2, &G);
   assert(r == 0);

   printf("----------------- Testing: isGameOver ----------------\n");

	
// Game should init to something...

 	printf(" TEST PASS\n");



 // Test if game will end when fed end signal 0


   printf("----------------- Testing Unit: Game will end if appropriate signal given ----------------\n");

   
   int a = isGameOver(&G);
   assert(a == 0);
   printf(" TEST PASS\n");


	printf("\n >>>>> SUCCESS: Testing complete isGameOver <<<<<\n");


	return 0;

}