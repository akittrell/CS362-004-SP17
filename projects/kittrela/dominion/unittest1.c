/*
*   Basic templating provided by cardtest4.c and testUpdateCoins.c via
*   Oregon State's CS 362 class.
*
*   Test for the buyCard function
*   Need to check:
    1) Current player does not have enough coins to purchase said card
    2) Current Player has enough money and buys left
        - Player has +1 cards in discard
        - Player has 1 less buy
        - Players gold has decreased by the number of coins the card has cost
        - The supplyCount that held the card is -1 card
        - No other gameState has changed
        - Cannot purchase if card the supply count is 0
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main(){
    int i;
    int passed;
    int seed = 100;
    int numPlayer = 2;
    int handCount;
    //Kingdom Cards we will use for testing.
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel,
                 smithy, village, baron, great_hall };
    struct gameState G;
    struct gameState testG; //The gamestate we will use for testing consistency

    //initialize game state with our selected player cards.
    initializeGame(numPlayer, k, seed, &G);

    printf("---------------| TESTING buyCard() |-------------------\n");
    G.whoseTurn = 0; //player 1 is going to be the test player here

    printf("---------| TEST 1: NOT ENOUGH MONEY TO PURCHASE |------------\n");
    passed = 1;
        //replace all cards in hand with estates (ie, no coins)
    printf("Coin amount BEFORE estate replacement: %d\n", G.coins);
    for (i=0; i<G.handCount[0];i++){
        G.hand[0][i] = estate;
    }
    updateCoins(0, &G, 0);
    printf("Coin amount after estate replacement: %d\n", G.coins);
    //copy current game state into our test state
    memcpy(&testG, &G, sizeof(struct gameState));

    buyCard(adventurer, &G);
    passed *= assertTrue(G.supplyCount[adventurer], testG.supplyCount[adventurer], "supplyCount");
    passed *= assertTrue(G.handCount[0], testG.handCount[0], "handCount");
    passed *= assertTrue(G.numActions, testG.numActions, "numActions");
    passed *= assertTrue(G.numBuys, testG.numBuys, "numBuys");
    for (i = 0; i < 5 ; i++){
        passed *= assertTrue(G.hand[0][i], estate, "cards in hand");
    }

    if(passed == 1){
        printf("--------------| TEST SUCCESSFUL |-------------\n\n");
    }
    else{
        printf("--------------| TEST FAILED |-------------\n\n");
    }
    printf("---------| TEST 2: CARD CAN BE PURCHASED AND CARD SUPPLY > 0 |------------\n");
    passed = 1;
    //replace all cards in player 1's hand with gold, so that they have enough to purchase desired card
    //for both test states
    for (i=0; i<G.handCount[0];i++){
        G.hand[0][i] = gold;
        testG.hand[0][i]=gold;
    }
    updateCoins(0, &G, 0);
    updateCoins(0,&testG, 0);
    buyCard(adventurer, &G);

    passed *= assertTrue(G.supplyCount[adventurer], ((testG.supplyCount[adventurer])-1), "supplyCount");
    passed *= assertTrue(G.handCount[0], testG.handCount[0], "handCount");
    passed *= assertTrue(G.numActions, testG.numActions, "numActions"); //should not change
    passed *= assertTrue(G.numBuys, testG.numBuys-1, "numBuys");
    passed *= assertTrue(G.discardCount[0], testG.discardCount[0]+1, "discardCount"); //bought card
    passed *= assertTrue(G.coins, testG.coins-6, "coin amount"); //make sure 6 coins was taken from the current player

    if(passed == 1){
        printf("--------------| TEST SUCCESSFUL |-------------\n\n");
    }
    else{
        printf("--------------| TEST FAILED |-------------\n\n");
    }
    printf("---------| TEST 3: SUPPLY OF CARD = 0 |------------\n");
    passed = 1;
    memcpy(&G, &testG, sizeof(struct gameState));

    //set supply to 0 for adventurer
    G.supplyCount[adventurer] = 0;
    testG.supplyCount[adventurer]= 0;
    //set player up for enough gold to purchase card
    for (i=0; i<G.handCount[0];i++){
        G.hand[0][i] = gold;
        testG.hand[0][i] = gold;
    }
    updateCoins(0, &G, 0);
    updateCoins(0,&testG, 0);

    buyCard(adventurer, &G);
    //no differences should be present between the two states
    passed *= assertTrue(G.supplyCount[adventurer], ((testG.supplyCount[adventurer])), "supplyCount");
    passed *= assertTrue(G.handCount[0], testG.handCount[0], "handCount");
    passed *= assertTrue(G.numActions, testG.numActions, "numActions"); //should not change
    passed *= assertTrue(G.numBuys, testG.numBuys, "numBuys");
    passed *= assertTrue(G.discardCount[0], testG.discardCount[0], "discardCount"); //bought card
    passed *= assertTrue(G.coins, testG.coins, "coin amount"); //make sure 6 coins was taken from the current player

    if(passed == 1){
        printf("--------------| TEST SUCCESSFUL |-------------\n\n");
    }
    else{
        printf("--------------| TEST FAILED |-------------\n\n");
    }
return 0;
}
