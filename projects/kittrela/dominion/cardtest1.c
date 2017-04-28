/*
*   Basic templating provided by cardtest4.c and testUpdateCoins.c via
*   Oregon State's CS 362 class.
*
*   Test for the Smithy card:
*   TEXT: +3 Cards
*   Need to check:
*   1) -3 cards in current players deck
*   2) +3 cards in current players hand
*   3) -1 Action for current player
*   4) +0 Cards in opponents hand
*   5) No other card piles have changed values
*
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
    char *card = "Smithy";  //card name we are testing
    int i, j, l, m, n, o;
    int seed = 100;
    int handpos = 0, curPlayer = 0, opponent = 1;

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
    G.whoseTurn = 0;    //player 1's turn
    memcpy(&testG, &G, sizeof(struct gameState));

    printf("---------------| TESTING CARD: %s|-------------------\n", card);
    printf("---------| TEST 1: -3 CARDS FROM PLAYER 1 DECK |------------\n");
    passed = 1;

    cardSmithy(&testG, testG.whoseTurn, handpos);
    passed *= assertTrue(testG.deckCount[curPlayer], G.deckCount[curPlayer]-3, "current players deck count");
    passed *= assertTrue(testG.deckCount[opponent], G.deckCount[opponent], "opponents deck count");

    if(passed == 1){
        printf("--------------| TEST SUCCESSFUL |-------------\n\n");
    }
    else{
        printf(" !!!!!!!!!!!!!!! TEST FAILED !!!!!!!!!!!!!!!\n\n");
    }

    printf("---------| TEST 2: +3 CARDS ADDED TO PLAYER 1) |------------\n");
    passed = 1;
    memcpy(&testG, &G, sizeof(struct gameState));
    cardSmithy(&testG, testG.whoseTurn, handpos);

    passed *= assertTrue(testG.handCount[curPlayer], G.handCount[curPlayer] +3, "current player hand count");
    passed *= assertTrue(testG.handCount[opponent], G.handCount[opponent], "opponent hand count");
    if(passed == 1){
        printf("--------------| TEST SUCCESSFUL |-------------\n\n");
    }
    else{
        printf(" !!!!!!!!!!!!!!! TEST FAILED !!!!!!!!!!!!!!!\n\n");
    }

    printf("---------| TEST 3: NO OTHER SUPPLY PILES HAVE CHANGED COUNT |------------\n");
    passed = 1;
    memcpy(&testG, &G, sizeof(struct gameState));
    cardSmithy(&testG, testG.whoseTurn, handpos);

    for(i=0; i < 17; i++){
        passed *= assertTrue(testG.supplyCount[ allCards[i] ], G.supplyCount[ allCards[i] ], "other supply counts");
    }
    if(passed == 1){
        printf("--------------| TEST SUCCESSFUL |-------------\n\n");
    }
    else{
        printf(" !!!!!!!!!!!!!!! TEST FAILED !!!!!!!!!!!!!!!\n\n");
    }


return 0;
}
