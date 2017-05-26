// Author: Chris Darnell
// 4/30/2017
// unittest1.c - getCost

#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "dominion_helpers.h"
#include "assert.h"

#define TESTUNIT "adventurer_getcost"
#define TESTUONE "embargo_getcost"
#define TESTUTWO "village_getcost"
#define TESTUTHR "minion_getcost"
#define TESTUFOU "mine_getcost"
#define TESTUFIV "cutpurse_getcost"
#define TESTUSIX "sea_hag_getcost"
#define TESTUSEV "tribute_getcost"
#define TESTUEIG "smithy_getcost"
#define TESTUNIN "council_room_getcost"

// Unit Test  -- getCost

// Test if cost of ______ card being gathered by getCost is correct. 


int main() {

// Init costs.

    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
   

 // Init new game instance


   int r = initializeGame(2, k, 2, &G);
   assert(r == 0);



   printf("----------------- Testing: getCost ----------------\n");

    
// Game should init to something...

    printf(" TEST PASS\n");

// Adventurer should be 6

	printf("----------------- Testing Unit: %s ----------------\n", TESTUNIT);
   

        assert(getCost(adventurer) == 6);

		printf(" TEST PASS\n");

// Embargo should be 2	

		printf("----------------- Testing Unit: %s ----------------\n", TESTUONE);

        assert(getCost(embargo) == 2);
       
        printf(" TEST PASS\n");

 // Village should be 3	

		printf("----------------- Testing Unit: %s ----------------\n", TESTUTWO);

        assert(getCost(village) == 3);

        printf(" TEST PASS\n");


// Minion should be 5	

		printf("----------------- Testing Unit: %s ----------------\n", TESTUTHR);

      
        assert(getCost(minion) == 5);

        printf(" TEST PASS\n");

// Mine should be 5	

		printf("----------------- Testing Unit: %s ----------------\n", TESTUFOU);

        assert(getCost(mine) == 5);

        printf(" TEST PASS\n");

 // cutPurse should be 4	

		printf("----------------- Testing Unit: %s ----------------\n", TESTUFIV);

      
        assert(getCost(cutpurse) == 4);

        printf(" TEST PASS\n");


 // Sea Hag should be 4	

		printf("----------------- Testing Unit: %s ----------------\n", TESTUSIX);

        assert(getCost(sea_hag) == 4);

        printf(" TEST PASS\n");

 // Tribute should be 5	

		printf("----------------- Testing Unit: %s ----------------\n", TESTUSEV);

        assert(getCost(tribute) == 5);

        printf(" TEST PASS\n");

  // Smithy should be 4	

		printf("----------------- Testing Unit: %s ----------------\n", TESTUEIG);

        assert(getCost(smithy) == 4);

        printf(" TEST PASS\n");

 // Council Room should be 5	

		printf("----------------- Testing Unit: %s ----------------\n", TESTUNIN);

    
        assert(getCost(council_room) == 5);

        printf(" TEST PASS\n");


    	printf("\n >>>>> SUCCESS: Testing complete getCost <<<<<\n");


	return 0;
}