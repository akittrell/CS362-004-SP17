/*
*   Basic templating provided by cardtest4.c and testUpdateCoins.c via
*   Oregon State's CS 362 class.
*
*   Test for the salvager card:
*   TEXT:
*    +1 Buy
*   Trash a card from your hand
*   + G equal to its cost
*   Need to check:
*   1) +1 buy for current player
*   2) +G of trashed card added to current players coin count
*   4) Hand count -2 for current player (-1 trashed, -1 played salvager)
*   5) No other state changes
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
    char *card = "Salvager";  //card name we are testing
    int i, j, l, m, n, o;
    int seed = 100;
    int handpos = 0, curPlayer = 0, opponent = 1;

    //set up the number of special cards that depend on the number of players
    int numPlayer = 2;
    int handCount;
    int passed;

    //Kingdom Cards we will use for testing.
    int allCards[17] = { copper, silver, gold, estate, duchy, province, curse, adventurer, council_room, feast, gardens, mine, remodel,
                 smithy, village, cutpurse, great_hall};    //all cards in the current game
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel,
                 smithy, village, cutpurse, great_hall };
    struct gameState G;
    struct gameState testG; //The gamestate we will use for testing consistency

    //initialize game state with our selected player cards.
    initializeGame(numPlayer, k, seed, &G);
    printf("---------------| TESTING CARD: %s|-------------------\n", card);
    printf("---------| TEST 1: +1 BUY |------------\n");
    passed = 1;
    G.whoseTurn = curPlayer; //player 1's turn
    memcpy(&testG, &G, sizeof(struct gameState));
    //cardSalvager(&testG, 0, curPlayer, 0);
		cardEffect(salvager, 0, 0, 0, &testG, 0, 0);

    passed *= assertTrue(testG.numBuys, G.numBuys +1, "number of buys");


    for(i=0; i < 17; i++){
        passed *= assertTrue(testG.supplyCount[ allCards[i] ], G.supplyCount[ allCards[i] ], "other supply counts");
    }
    passed *= assertTrue(testG.discardCount[0], G.discardCount[0], "discard count of current player");
    if(passed == 1){
        printf("--------------| TEST SUCCESSFUL |-------------\n\n");
    }
    else{
        printf(" !!!!!!!!!!!!!!! TEST FAILED !!!!!!!!!!!!!!!\n\n");
    }

    printf("---------| TEST 2: +G TO COINS EQUAL TO CHOSEN TRASHED CARD |------------\n");
    passed = 1;
    G.whoseTurn = curPlayer; //player 1's turn
    memcpy(&testG, &G, sizeof(struct gameState));

    for(i = 0; i< G.handCount[0]; i++){
        memcpy(&testG, &G, sizeof(struct gameState));

        testG.hand[curPlayer][i] = salvager; //salvagers card costs 4 gold
      //  cardSalvager(&testG, i, curPlayer, i);
		cardEffect(salvager, 0, 0, 0, &testG, 0, 0);

        passed *= assertTrue(testG.coins, G.coins +4, "coins after trash");
        passed *= assertTrue(testG.discardCount[0], G.discardCount[0], "discard count of current player");

    }

    for(i=0; i < 17; i++){
        passed *= assertTrue(testG.supplyCount[ allCards[i] ], G.supplyCount[ allCards[i] ], "other supply counts");
    }

    if(passed == 1){
        printf("--------------| TEST SUCCESSFUL |-------------\n\n");
    }
    else{
        printf(" !!!!!!!!!!!!!!! TEST FAILED !!!!!!!!!!!!!!!\n\n");
    }

    printf("---------| TEST 3: -2 CARDS FROM HAND |------------\n");
    passed = 1;
    G.whoseTurn = curPlayer; //player 1's turn
    memcpy(&testG, &G, sizeof(struct gameState));
    //cardSalvager(&testG, 0, curPlayer, 0);
		cardEffect(salvager, 0, 0, 0, &testG, 0, 0);

    passed *= assertTrue(testG.handCount[curPlayer], G.handCount[curPlayer]-2, "current player hand count");
    passed *= assertTrue(testG.handCount[opponent], G.handCount[opponent], "opponent player hand count"); //should not change

    for(i=0; i < 17; i++){
        passed *= assertTrue(testG.supplyCount[ allCards[i] ], G.supplyCount[ allCards[i] ], "other supply counts");
    }

    passed *= assertTrue(testG.discardCount[0], G.discardCount[0], "discard count of current player");

    if(passed == 1){
        printf("--------------| TEST SUCCESSFUL |-------------\n\n");
    }
    else{
        printf(" !!!!!!!!!!!!!!! TEST FAILED !!!!!!!!!!!!!!!\n\n");
    }
return 0;
}
