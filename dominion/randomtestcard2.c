/*
*   Basic templating provided by betterTestDrawCard.c via
*   Oregon State's CS 362 class.
*
*   Test for Salvager card
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
#include <math.h>


int main(){
    int NUM_ITR = 5000;
    struct gameState pre, post;
    int i, n, p, deckCount, discardCount, handCount, handP;

    SelectStream(2);
    PutSeed(3);

    for (n = 0; n < NUM_ITR; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
          ((char*)&post)[i] = floor(Random() * 256);
        }
    p = floor(Random() * 2);
    post.deckCount[p] = floor(Random() * MAX_DECK);
    post.discardCount[p] = floor(Random() * MAX_DECK);
    post.handCount[p] = abs(floor(Random() * MAX_HAND));
    post.playedCardCount = 0;
    post.whoseTurn = p;
    int trashCard = abs(floor(Random() * 26));   //get a random card that we will want to trash.
    handP = abs(floor(Random() * MAX_HAND));    //come up with random hand position for our salvager card
    int trashCardPos = abs(floor(Random() * MAX_HAND));
    while(trashCardPos == handP){ //change the position in case we somehow got the same random number
        trashCardPos = abs(floor(Random() * MAX_HAND));
    }
    post.hand[p][handP] = salvager;
    post.hand[p][trashCardPos] = trashCard;   //so we can follow the random card that was chosen to trash, and it's wort in gold.
    int cost = getCost(trashCard); //get the cost of the trashed card for comparison later on

    memcpy (&pre, &post, sizeof(struct gameState));
    cardSalvager(&post, trashCardPos, p, handP);
    pre.coins += cost; //coins should be equal to the cost of the card.
    pre.handCount[p] = pre.handCount[p] - 2; //We have gotten rid of both salvager and the trashed card
    pre.numBuys++; //number of buys has increased.
    pre.discardCount[p]++; //salvager should be placed here


    printf("\n---------------TESTING MEMORY COMPARISON---------------\n");
    //if it does not pass, dig deeper and figure out what is not matching up.
    if(assertTrue(memcmp(&pre, &post, sizeof(struct gameState)), 0, "Memory Comparison") != 1){
        printf("\n----------------TEST FAILURE----------------\n");
        printf("\nSpecifics:\n");
        printf("Trashed card: %d\tCost: %d\n", trashCard, cost);
        assertTrue(pre.discardCount[p], post.discardCount[p], "Discard Count Comparison");
        assertTrue(pre.handCount[p], post.handCount[p], "Hand Count Comparison");
        assertTrue(pre.deckCount[p], post.deckCount[p], "Deck count");
        assertTrue(pre.numBuys, post.numBuys, "Number of buys");
        assertTrue(pre.coins, post.coins, "Number of coins");

        printf("\n\n");
    }


    }
return 0;

}
