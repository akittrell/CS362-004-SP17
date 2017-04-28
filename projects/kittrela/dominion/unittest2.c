/*
*   Basic templating provided by cardtest4.c and testUpdateCoins.c via
*   Oregon State's CS 362 class.
*
*   Test for the isGameOver function
*   Need to check:
    1) Only Province cards are empty
    2) 3 supplies are empty
    3) 2 supplies are empty
    4) 1 supply is empty
    5) Nothing is empty
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "assertTrue.h"

int main(){
    int i, j, l, m, n, o;
    int seed = 100;
    int numPlayer = 2;
    int handCount;
    int passed; //indicator of a failed subtest in a larger test. If a subtest fails, passed = 0;
    //Kingdom Cards we will use for testing.
    int mostCards[16] = { copper, silver, gold, estate, duchy, curse, adventurer, council_room, feast, gardens, mine, remodel,
                 smithy, village, baron, great_hall};    //all cards in the game, minus Province
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel,
                 smithy, village, baron, great_hall };
    struct gameState G;
    struct gameState testG; //The gamestate we will use for testing consistency

    //initialize game state with our selected player cards.
    initializeGame(numPlayer, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("---------------| TESTING isGameOver() |-------------------\n");
    printf("---------| TEST 0: ALL CARDS SUPPLY > 0 |------------\n");
    passed = 1;
    passed *= assertTrue(isGameOver(&testG), isGameOver(&G), "");

    if(passed == 1){
        printf("--------------| TEST SUCCESSFUL |-------------\n\n");
    }
    else{
        printf("--------------| TEST FAILED |-------------\n\n");
    }

    printf("---------| TEST 1: PROVINCE SUPPLY IS 0 |------------\n");
    testG.supplyCount[province] = 0;
    passed *= assertTrue(isGameOver(&testG), 1, ""); //game should be over with province supply = 0.
    if(passed == 1){
        printf("--------------| TEST SUCCESSFUL |-------------\n\n");
    }
    else{
        printf("--------------| TEST FAILED |-------------\n\n");
    }
    printf("---------| TEST 2: PROVINCE SUPPLY IS > 0, ALL OTHER PILES HAVE > 0 CARDS |------------\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    passed *= assertTrue(isGameOver(&testG), isGameOver(&G), ""); //game should not be over/
    if(passed == 1){
        printf("--------------| TEST SUCCESSFUL |-------------\n\n");
    }
    else{
        printf("--------------| TEST FAILED |-------------\n\n");
    }
    printf("---------| TEST 3: 1 SUPPLY IS EMPTY (OTHER THAN PROVINCE), OTHERS > 0 |------------\n");
    memcpy(&testG, &G, sizeof(struct gameState));

    for (i = 0; i < 16; i++){
        l = testG.supplyCount[ mostCards[i] ];
        testG.supplyCount[ mostCards[i] ] = 0;
        passed *= assertTrue(isGameOver(&testG), isGameOver(&G), "");// game should still be in play

        //no other aspect of the game state should change
        passed *= assertTrue(G.handCount[0], testG.handCount[0], "handCount");
        passed *= assertTrue(G.numActions, testG.numActions, "numActions"); //should not change
        passed *= assertTrue(G.numBuys, testG.numBuys, "numBuys");
        passed *= assertTrue(G.discardCount[0], testG.discardCount[0], "discardCount"); //bought card
        passed *= assertTrue(G.coins, testG.coins, "coin amount"); //make sure 6 coins was taken from the current player

        testG.supplyCount[ mostCards[i] ] = l;
    }

    if(passed == 1){
        printf("--------------| TEST SUCCESSFUL |-------------\n\n");
    }
    else{
        printf("--------------| TEST FAILED |-------------\n\n");
    }

    printf("---------| TEST 4: 2 SUPPLY IS EMPTY (OTHER THAN PROVINCE), OTHERS > 0 |------------\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    //test all combinations of 2 piles being empty
    for(i = 0; i < 16; i++){
        for(j=i+1; j < 16; j++){
            l = testG.supplyCount[ mostCards[i] ];
            m = testG.supplyCount[ mostCards[j] ];
            testG.supplyCount[ mostCards[i] ] = 0;
            testG.supplyCount[ mostCards[j] ] = 0;
            passed *= assertTrue(isGameOver(&testG), isGameOver(&G), "");// game should still be in play

            //no other aspect of the game state should change
            passed *= assertTrue(G.handCount[0], testG.handCount[0], "handCount");
            passed *= assertTrue(G.numActions, testG.numActions, "numActions"); //should not change
            passed *= assertTrue(G.numBuys, testG.numBuys, "numBuys");
            passed *=  assertTrue(G.discardCount[0], testG.discardCount[0], "discardCount"); //bought card
            passed *= assertTrue(G.coins, testG.coins, "coin amount"); //make sure 6 coins was taken from the current player

            testG.supplyCount[ mostCards[i] ] = l;
            testG.supplyCount[ mostCards[j] ] = m;
        }
    }

    if(passed == 1){
        printf("--------------| TEST SUCCESSFUL |-------------\n\n");
    }
    else{
        printf("--------------| TEST FAILED |-------------\n\n");
    }

    printf("---------| TEST 5: 3 SUPPLY IS EMPTY (OTHER THAN PROVINCE), OTHERS > 0 |------------\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    for(i = 0; i < 16; i++){
        for(j=i+1; j < 16; j++){
            for(n=j+1; n < 16; n++){
                l = testG.supplyCount[ mostCards[i] ];
                m = testG.supplyCount[ mostCards[j] ];
                o = testG.supplyCount[ mostCards[n] ];
                testG.supplyCount[ mostCards[i] ] = 0;
                testG.supplyCount[ mostCards[j] ] = 0;
                testG.supplyCount[ mostCards[n] ] = 0;

                passed *= assertTrue(isGameOver(&testG), 1, "");// game should be over, return of 1

                //no other aspect of the game state should change
                passed *= assertTrue(G.handCount[0], testG.handCount[0], "handCount");
                passed *= assertTrue(G.numActions, testG.numActions, "numActions"); //should not change
                passed *= assertTrue(G.numBuys, testG.numBuys, "numBuys");
                passed *= assertTrue(G.discardCount[0], testG.discardCount[0], "discardCount"); //bought card
                passed *= assertTrue(G.coins, testG.coins, "coin amount"); //make sure 6 coins was taken from the current player

                testG.supplyCount[ mostCards[i] ] = l;
                testG.supplyCount[ mostCards[j] ] = m;
                testG.supplyCount[ mostCards[n] ] = o;
            }
        }
    }
    if(passed == 1){
        printf("--------------| TEST SUCCESSFUL |-------------\n\n");
    }
    else{
        printf("--------------| TEST FAILED |-------------\n\n");
    }
return 0;
}
