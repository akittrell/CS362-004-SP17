/*
*   Basic templating provided by cardtest4.c and testUpdateCoins.c via
*   Oregon State's CS 362 class.
*
*   Test for the supplyCount function
*   Need to check:
*   1) All supplies are full when nothing has occurred in the game
*   2) Supply count -1 when a card is taken from the corresponding supply
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
    int numVictory, numCurse;
    int numCopper, numSilver, numGold;
    int seed = 100;

    //set up the number of special cards that depend on the number of players
    int numPlayer = 2;
    if(numPlayer == 2){
        numVictory = 8;
        numCurse = 10;
    }
    else{
        numVictory = 12;
    }
    if(numPlayer == 3){
        numCurse = 20;
    }
    if(numPlayer == 4){
        numCurse =40;
    }

    numGold = 30;
    numSilver = 40;
    numCopper = 60 - (7 * numPlayer);

    int handCount;
    int passed; //indicator of a failed subtest in a larger test. If a subtest fails, passed = 0;
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
    printf("---------------| TESTING supplyCount() |-------------------\n");
    printf("---------| TEST 1: ALL SUPPLY PILES = STARTING SUPPLY WHEN NOTHING HAS OCCURRED|------------\n");
    passed = 1;
    //check each card in play.
    for(i = 0; i < 17; i++){
        if(allCards[i] <= province && allCards[i] >= estate || allCards[i] == gardens || allCards[i] == great_hall){
            passed *= assertTrue(supplyCount(allCards[i], &testG), numVictory, "Victory Card Supply");//depends on the number of players
        }
        else if(allCards[i] == curse){
            passed *= assertTrue(supplyCount(allCards[i], &testG), numCurse, "Curse Card Supply"); //depends on the number of players
        }
        else if(allCards[i] == gold){
            passed *= assertTrue(supplyCount(allCards[i], &testG), numGold, "Gold Supply");
        }
        else if(allCards[i] == silver){
            passed *= assertTrue(supplyCount(allCards[i], &testG), numSilver, "Silver Supply");
        }
        else if(allCards[i] == copper){
            passed *= assertTrue(supplyCount(allCards[i], &testG), numCopper, "Copper Supply"); //depends on the number of players
        }
        else{
            passed *= assertTrue(supplyCount(allCards[i], &testG), 10, "Kingdom Supply Card"); //should always be 10
        }
    }
    if(passed == 1){
        printf("--------------| TEST SUCCESSFUL |-------------\n\n");
    }
    else{
        printf("--------------| TEST FAILED |-------------\n\n");
    }

    printf("---------| TEST 2: CARD SUPPLY DECREMENTED WHEN CARD IS TAKEN FROM PILE |------------\n");
    passed = 1;
    memcpy(&testG, &G, sizeof(struct gameState));


    for(i = 0; i < 17; i++){
        //remove card from allCards[i] supply
        testG.supplyCount[ allCards[i] ] = testG.supplyCount[ allCards[i] ] -1;
        passed *= assertTrue(supplyCount(allCards[i], &testG), supplyCount(allCards[i], &G) -1, "");//depends on the number of players
    }
    if(passed == 1){
        printf("--------------| TEST SUCCESSFUL |-------------\n\n");
    }
    else{
        printf("--------------| TEST FAILED |-------------\n\n");
    }
return 0;
}
