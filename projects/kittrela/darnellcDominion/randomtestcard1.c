/*
*   Basic templating provided by betterTestDrawCard.c via
*   Oregon State's CS 362 class.
*
*   Test for Smithy card
*   +
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
    int NUM_ITR = 50;
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

    handP = abs(floor(Random() * MAX_HAND));
    post.hand[p][handP] = smithy;   //because smithy requires it's hand position, make sure hand pos is used

    memcpy (&pre, &post, sizeof(struct gameState));
	playSmithy( p, &post, handP);
    //cardSmithy(&post, p, handP);
    //The following if/else block is taken directly from testDrawCard.c, and modified for the current card
    if (pre.deckCount[p] > 2) { //if there are 3 cards to draw
        pre.handCount[p] += 2;  //hand increases by 2, as smithy has been played
        pre.hand[p][pre.handCount[p]-1] = pre.deck[p][pre.deckCount[p]-1];  //whatever was in the deck, is now in the hand
        pre.hand[p][pre.handCount[p]-2] = pre.deck[p][pre.deckCount[p]-2];
        pre.hand[p][pre.handCount[p]-3] = pre.deck[p][pre.deckCount[p]-3];
        pre.deckCount[p] -= 3;  //3 cards have been removed from the deck
        pre.discardCount[p]++;  //smithy is added to discard
    }
    else if(pre.deckCount[p] == 2 && pre.discardCount[p] > 0){// if there are only 2 cards in the deck, and more than 0 in discard
        pre.handCount[p] += 2;  //hand increases by 2, as smithy has been played
        pre.hand[p][pre.handCount[p]-1] = pre.deck[p][pre.deckCount[p]-1];  //whatever was in the deck, is now in the hand
        pre.hand[p][pre.handCount[p]-2] = pre.deck[p][pre.deckCount[p]-2];  //whatever was in the deck, is now in the hand
        memcpy(pre.deck[p], post.deck[p], sizeof(int) * pre.discardCount[p]); //move what is now in the post deck into new deck
        memcpy(pre.discard[p], post.discard[p], sizeof(int)*pre.discardCount[p]); //move what is in the discard of post deck into new discard
        pre.deckCount[p] = pre.discardCount[p]-1;   //what was in the discard is now in the deck
        pre.discardCount[p] = 1;    //discard now holds the smithy card only
    }
    else if (pre.deckCount[p] == 1 && pre.discardCount[p] > 1) {
        pre.handCount[p] += 2;  //hand increases by 2, as smithy has been played
        pre.hand[p][pre.handCount[p]-1] = pre.deck[p][pre.deckCount[p]-1];  //whatever was in the deck, is now in the hand
        memcpy(pre.deck[p], post.deck[p], sizeof(int) * pre.discardCount[p]);
        memcpy(pre.discard[p], post.discard[p], sizeof(int)*pre.discardCount[p]);
        pre.hand[p][post.handCount[p]-1] = post.hand[p][post.handCount[p]-1];    //now that discard is shuffled into deck, first two
        pre.hand[p][post.handCount[p]-1] = post.hand[p][post.handCount[p]-2];    //  cards are also added to hand
        pre.deckCount[p] = pre.discardCount[p]-1;
        pre.discardCount[p] = 1;
  }

    printf("\n---------------TESTING MEMORY COMPARISON---------------\n");
    //if it does not pass, dig deeper and figure out what is not matching up.
    if(assertTrue(memcmp(&pre, &post, sizeof(struct gameState)), 0, "Memory Comparison") != 1){
        printf("\n----------------TEST FAILURE----------------\n");
        printf("\nSpecifics:\n");
        assertTrue(pre.discardCount[p], post.discardCount[p], "0 Discard Count Comparison");
        assertTrue(pre.handCount[p], post.handCount[p], "1 Hand Count Comparison");
        assertTrue(pre.deckCount[p], post.deckCount[p], "Deck count");
        printf("\n\n");
    }


    }
return 0;

}
