/*
*   Basic templating provided by cardtest4.c and testUpdateCoins.c via
*   Oregon State's CS 362 class.
*
*   Test for the Cutpurse card:
*   TEXT:
*    +2 G
*    Each other player discards a Copper Card (or reveals a hand with no Copper)
*   Need to check:
*   1) Num gold for current player +2
*   2) If copper in opponents hand, then -1 card in hand
*        -discard should +1 for opponent
    3) If no copper, no change in opponent hand or discard
*   4) Current players handCount -1 for playing
*
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
    char *card = "cutpurse";  //card name we are testing
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
    printf("---------| TEST 1: +2 GOLD |------------\n");
    passed = 1;
    //make sure opponent has at lease 1 copper
    G.whoseTurn = curPlayer; //player 1's turn
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(cutpurse, 0, 0, 0, &testG, handpos, 0);
    passed *= assertTrue(testG.coins, G.coins +2, "current player coin amount");

    for(i=0; i < 17; i++){
        passed *= assertTrue(testG.supplyCount[ allCards[i] ], G.supplyCount[ allCards[i] ], "other supply counts");
    }

    if(passed == 1){
        printf("--------------| TEST SUCCESSFUL |-------------\n\n");
    }
    else{
        printf(" !!!!!!!!!!!!!!! TEST FAILED !!!!!!!!!!!!!!!\n\n");
    }

    printf("---------| TEST 2: OPPONENT(S) HAS COPPER IN HAND|------------\n");
    passed = 1;
    //make sure opponent has at lease 1 copper
    G.whoseTurn = 0; //player 1's turn

    for(i = 1; i< numPlayer; i++){
        G.hand[i][0] = copper;
    }
    memcpy(&testG, &G, sizeof(struct gameState));

    cardEffect(cutpurse, 0, 0, 0, &testG, handpos, 0);

    for(i = 1; i< numPlayer; i++){
        passed *= assertTrue(testG.handCount[i], G.handCount[i]-1, "opponent hand count");
        passed *= assertTrue(testG.handCount[curPlayer], G.handCount[curPlayer]-1, "current player's hand count");

        passed *= assertTrue(testG.discardCount[i], G.discardCount[i] +1, "discard of opponent");
        passed *= assertTrue(testG.discardCount[curPlayer], G.discardCount[curPlayer] +1, "discard of current player");
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

        printf("---------| TEST 3: OPPONENT(S) HAS NO COPPER IN HAND|------------\n");
    passed = 1;
    G.whoseTurn = 0; //player 1's turn
    for(i = 1; i< numPlayer; i++){
        for(j=0; j<G.handCount[i]; j++){
            G.hand[i][j] = estate;//replace all opponents hands with estate cards (ie no coppers)
        }
    }
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(cutpurse, 0, 0, 0, &testG, handpos, 0);
    for(i = 1; i< numPlayer; i++){
        passed *= assertTrue(testG.handCount[i], G.handCount[i], "opponent hand count");
        passed *= assertTrue(testG.handCount[curPlayer], G.handCount[curPlayer]-1, "current player's hand count");

        passed *= assertTrue(testG.discardCount[i], G.discardCount[i], "discard of opponent");
        passed *= assertTrue(testG.discardCount[curPlayer], G.discardCount[curPlayer] +1, "discard of current player");
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
return 0;
}
