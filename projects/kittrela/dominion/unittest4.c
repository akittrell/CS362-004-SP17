/*
*   Basic templating provided by cardtest4.c and testUpdateCoins.c via
*   Oregon State's CS 362 class.
*
*   Test for the numHandCards function
*   Need to check:
*   1) numHandCards returns +1 cards when card is added to hand
*       - Check that other players hand remains the same
*   2) numHandCards returns -1 cards when a card is removed form the hand
*       -does not affect other player's hand
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main(){
    int i, j, l, m, n, o;
    int seed = 100;

    //set up the number of special cards that depend on the number of players
    int numPlayer = 2;
    int handCount;
    int passed;
    //Kingdom Cards we will use for testing.
    int allCards[17] = { copper, silver, gold, estate, duchy, province, curse, adventurer, council_room, feast, gardens, mine, remodel,
                 smithy, village, baron, great_hall};    //all cards in the current game
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel,
                 smithy, village, baron, great_hall };
    struct gameState G;
    struct gameState testG; //The gamestate we will use for testing consistency

    //initialize game state with our selected player cards.
    initializeGame(numPlayer, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));

    printf("---------------| TESTING numHandCards() |-------------------\n");
    printf("---------| TEST 1: +1 CARD ADDED TO PLAYER 1 HAND |------------\n");
    passed = 1;
    //check each card in play.
    testG.handCount[0]++;
    passed *= assertTrue(numHandCards(&testG), numHandCards(&G)+1, "plus 1 card");
    passed *= assertTrue(testG.handCount[1], G.handCount[1], "other player's hand");//make sure other players hand was not affected
    if(passed == 1){
        printf("--------------| TEST SUCCESSFUL |-------------\n\n");
    }
    else{
        printf("--------------| TEST FAILED |-------------\n\n");
    }

    printf("---------| TEST 2: -1 CARD ADDED TO PLAYER 1 HAND |------------\n");
    passed = 1;
    memcpy(&testG, &G, sizeof(struct gameState));

    //check each card in play.
    testG.handCount[0]--;
    passed *= assertTrue(numHandCards(&testG), numHandCards(&G)-1, "minus 1 card");
    passed *= assertTrue(testG.handCount[1], G.handCount[1], "other player's hand");//make sure other players hand was not affected

    if(passed == 1){
        printf("--------------| TEST SUCCESSFUL |-------------\n\n");
    }
    else{
        printf("--------------| TEST FAILED |-------------\n\n");
    }

return 0;
}
