/*
*   Basic templating provided by betterTestDrawCard.c via
*   Oregon State's CS 362 class.
*
*   Test for the Adventurer card
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
    int i, n, p, deckCount, discardCount, handCount, numTreasure;

    SelectStream(2);
    PutSeed(3);

    for (n = 0; n < NUM_ITR; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
          ((char*)&post)[i] = floor(Random() * 256);
        }
//printf("After first for\n");
    p = floor(Random() * 2);
    post.deckCount[p] = floor(Random() * MAX_DECK);
    post.discardCount[p] = floor(Random() * MAX_DECK);
    post.handCount[p] = floor(Random() * MAX_HAND);

    numTreasure = floor(Random() * 3);
    if(numTreasure == 3){
        numTreasure = 0;
    }
    int treasureType;
    int curTreasures[3];    //holds random selected treasures
    for(i=0; i<numTreasure; i++){
        treasureType = floor(Random() * 3);
        if(treasureType == 1)
                curTreasures[i] = copper;
            else if(treasureType == 2)
                curTreasures[i] = silver;
            else
                curTreasures[i] = gold;
    }
//    printf("After treasure Assignments\n");
    //adds either 0, 1, or 2 treasure cards to deck/discard.
    switch (numTreasure){
        case 1://1 treasure in deck/discard
//            printf("in case 1\n");
            if(floor(Random() * 2 == 1))
                post.deck[p][0] = curTreasures[0];
            else
                post.discard[p][0] = curTreasures[0];
            break;
        case 2:
//            printf("in case 2\n");
            i = 0;
            while(i < 2){
                if(floor(Random() * 2 == 1))
                    post.deck[p][i] = curTreasures[i];
                else
                    post.discard[p][i] = curTreasures[i];
                i++;
            }
            break;
        case 0: //no treasures in deck or discard. clear cards to non-treasure cards
//            printf("in case 0\n");
 //           printf("deck count: %d\n", post.deckCount[p]);
            for(i=0; i<post.deckCount[p]; i++){
                //printf("p = %d, number is: %d\n", p, post.deck[p][i]);
                post.deck[p][i] = estate;
            }
//           printf("Going to assign card to discard\n");
            for(i=0; i<post.discardCount[p]; i++){
                post.discard[p][i] = estate;
            }
            break;
        default:
            break;
    }
//    printf("After Switch statement from hell\n");

    memcpy (&pre, &post, sizeof(struct gameState));
    cardEffect(adventurer, 0,0,0, &post, 0, 0);
	//cardAdventurer(&post, p);
    //check if no treasures are in the deck or discard.
    if(numTreasure == 0){
        pre.handCount[p]--;
        pre.discardCount[p]++;
        pre.playedCardCount++;
    }
    else if (numTreasure == 1){
        //total hand count stays the same
        pre.discardCount[p]++;//should contain the adventurer card
        pre.playedCardCount++;
        pre.coins += getCost(pre.hand[p][pre.handCount[p]]);
    }
    else if (numTreasure == 2){
        pre.handCount[p]++; //player has gained 1 card in total
        pre.discardCount[p]++; //should contain the adventurer card
        pre.playedCardCount++;
        pre.coins += getCost(pre.hand[p][pre.handCount[p]-1]) + getCost(pre.hand[p][pre.handCount[p]-2]);
    }

    printf("\n---------------TESTING MEMORY COMPARISON---------------\n");
    //if it does not pass, dig deeper and figure out what is not matching up.
    if(assertTrue(memcmp(&pre, &post, sizeof(struct gameState)), 0, "Memory Comparison") != 1){
        printf("\n----------------TEST FAILURE----------------\n");
        printf("\nSpecifics:\n");
        printf("NumTreasure: %d\n", numTreasure);
        assertTrue(pre.discardCount[p], post.discardCount[p], "0 Discard Count Comparison");
        assertTrue(pre.handCount[p], post.handCount[p], "1 Hand Count Comparison");
        assertTrue(pre.playedCardCount, post.playedCardCount, "2 playedCardCount Count Comparison");
        assertTrue(pre.coins, post.coins, "3 Coins Count Comparison");
        printf("\n\n");
    }


    }
return 0;

}
