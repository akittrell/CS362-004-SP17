// Author: Chris Darnell
// 4/30/2017
// unittest2.c - numHandCards 



#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


// Unit Test  -- numHandCards

// Testing number of cards in players hand pulled by numHandCards function is correct



int main () {
   struct gameState G;
   int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
   

 // Init new game instance


   int r = initializeGame(2, k, 2, &G);
   assert(r == 0);

   printf("----------------- Testing: numHandCards ----------------\n");

	
// Game should init to something...

 	printf(" TEST PASS\n");


// Player One starts with correct cards. Should be 5


   printf("----------------- Testing Unit: Player 1 starts w/ 5 cards in hand ----------------\n");

   int a = numHandCards(&G);
   assert(a == 5);
   printf(" TEST PASS\n");


 // Test if it will work when hand is empty, 0 cards

   printf("----------------- Testing Unit: No cards in hand ----------------\n");

   G.handCount[0] = 0;
   a = numHandCards(&G);  
   assert(a == 0);
   printf(" TEST PASS\n");


 // Can a hand have a negative number cards.

   printf("----------------- Testing Unit: Negative Number of Cards in hand ----------------\n");

   G.handCount[0] = -1;
   a = numHandCards(&G);
   assert(a == -1);
   printf(" TEST PASS\n");


 // Test if we change number cards, numHandCards gets that new number cards correct


   printf("----------------- Testing Unit: Player 1 has correct number cards we place in hand ----------------\n");

   
   G.handCount[0] = 8;
   a = numHandCards(&G);
   assert(a == 8);
   printf(" TEST PASS\n");


	printf("\n >>>>> SUCCESS: Testing complete numHandCards <<<<<\n");


	return 0;
}

