/*
*   Basic templating provided by cardtest4.c and testUpdateCoins.c via
*   Oregon State's CS 362 class.
*
*   Test for the Adventurer card:
*   TEXT: Reveal cards from your deck until you reveal 2 Treasure cards. Put those
*       Treasure cards into your hand and discard the other revealed cards.
*   Need to check:
*   1) If 2 treasure cards exists in deck and discard, +2 cards to current player hand
*   2) If only 1 treasure card in deck and discard, only +1 card added to hand.
*   3) If no treasure in deck or hand, then +0 added to hand.
*   4) Discard+deck should have minus the # of treasure cards taken
*   5) No state change besides the above
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
    char *card = "Adventurer";  //card name we are testing
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


    printf("---------------| TESTING CARD: %s|-------------------\n", card);
    printf("---------| TEST 1: 2 TREASURE CARDS EXIST IN DISCARD AND DECK, -2 CARDS IN DECK + DISCARD |------------\n");
    passed = 1;
    //make sure 2 treasure cards for sure exist for drawing
    G.deck[curPlayer][0] = gold;
    G.deck[curPlayer][1] = gold;
    memcpy(&testG, &G, sizeof(struct gameState));

    cardAdventurer(&testG, testG.whoseTurn);
    passed *= assertTrue(testG.handCount[curPlayer], G.handCount[curPlayer] + 2 -1, "cur players hand count"); //+2 from deck, -1 from playing adventurer
    passed *= assertTrue(testG.handCount[opponent], G.handCount[opponent], "opponents hand count");//make sure this has not changed

    passed *= assertTrue(testG.deckCount[curPlayer]+testG.discardCount[curPlayer], G.deckCount[curPlayer]+G.discardCount[curPlayer]-2 +1, "deck+discard count"); //discard+deck should have -2 cards, +1 card for adventurer

    for(i=0; i < 17; i++){
        passed *= assertTrue(testG.supplyCount[ allCards[i] ], G.supplyCount[ allCards[i] ], "other supply counts");
    }

    if(passed == 1){
        printf("--------------| TEST SUCCESSFUL |-------------\n\n");
    }
    else{
        printf(" !!!!!!!!!!!!!!! TEST FAILED !!!!!!!!!!!!!!!\n\n");
    }

    printf("---------| TEST 2: 1 TREASURE CARDS EXIST IN DISCARD AND DECK, +1 To HAND, -1 CARDS IN DECK + DISCARD |------------\n");
    passed = 1;
    //make sure 1 treasure cards for sure exist for drawing
    for(i = 0; i < G.deckCount[curPlayer]; i++){
        G.deck[curPlayer][i] = estate;//set all cards in deck to estates (ie not treasures)
    }
    for(i = 0; i < G.discardCount[curPlayer]; i++){
        G.discard[curPlayer][i] = estate;//set all card in discard to estate (non-treasure)
    }
    G.deck[curPlayer][0] = gold;
    memcpy(&testG, &G, sizeof(struct gameState));

    cardAdventurer(&testG, testG.whoseTurn);
    passed *= assertTrue(testG.handCount[curPlayer], G.handCount[curPlayer] + 1 -1, "cur players hand count"); //+1 treasure,-1 for played adventurer
    passed *= assertTrue(testG.handCount[opponent], G.handCount[opponent], "opponents hand count");//make sure this has not changed

    passed *= assertTrue(testG.deckCount[curPlayer]+testG.discardCount[curPlayer], G.deckCount[curPlayer]+G.discardCount[curPlayer]-1 +1, "deck+discard count");//discard+deck should have -1 for treasure, +1 for adventurer


    for(i=0; i < 17; i++){
        passed *= assertTrue(testG.supplyCount[ allCards[i] ], G.supplyCount[ allCards[i] ], "other supply counts");
    }

    if(passed == 1){
        printf("--------------| TEST SUCCESSFUL |-------------\n\n");
    }
    else{
        printf(" !!!!!!!!!!!!!!! TEST FAILED !!!!!!!!!!!!!!!\n\n");
    }


    printf("---------| TEST 3: 0 TREASURE CARDS EXIST IN DISCARD AND DECK, +0 IN HAND |------------\n");
     passed = 1;
    for(i = 0; i < G.deckCount[curPlayer]; i++){
        G.deck[curPlayer][i] = estate;//set all cards in deck to estates (ie not treasures)
    }
    for(i = 0; i < G.discardCount[curPlayer]; i++){
        G.discard[curPlayer][i] = estate;//set all card in discard to estate (non-treasure)
    }
    memcpy(&testG, &G, sizeof(struct gameState));

    cardAdventurer(&testG, testG.whoseTurn);
    passed *= assertTrue(testG.handCount[curPlayer], G.handCount[curPlayer] -1, "cur players hand count"); //played adventurer to no effect
    passed *= assertTrue(testG.handCount[opponent], G.handCount[opponent], "opponents hand count");//make sure this has not changed

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
