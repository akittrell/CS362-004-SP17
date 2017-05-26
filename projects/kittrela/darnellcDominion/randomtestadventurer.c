// Random Card Tester for card Adventurer

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

int main() {
    struct gameState G;
    int seed = 1000;
    int passAll = 0;
    int testDraw = 0;
    int failDiscard = 0;
    int numberPlayers = 2;
    int currentPlayer = 0;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};  
    int sizeofDeck, sizeofHand;
    int i, j, q, m, x;
    int randomCard, randK;
    int treasureCopper, treasureSilver, treasureGold;
    int startCoin, currentCoin;
    
    
    srand(time(NULL));
   
    for(i = 0; i < 1000000; i++){
        initializeGame(numberPlayers, k, seed, &G);
        startCoin = 0;
        sizeofDeck = rand() % (MAX_DECK + 1);
   
        sizeofHand = rand() % (sizeofDeck + 1);
      
        
        G.deckCount[0] = sizeofDeck - sizeofHand;
        G.handCount[0] = sizeofHand;
        
      

 // Determine treasure cards...      
        
        for (j = 0; j < numberPlayers; j++){
            for(q = 0;q < G.deckCount[j]; q++){
                randomCard = rand() % (50 + 1);
                randK = rand() % (10);
                if(randomCard == 1){
                    G.deck[j][q] = copper;
                } else if(randomCard == 2){
                    G.deck[j][q] = silver;
                }else if(randomCard == 3){
                    G.deck[j][q] = gold;
                }else {
                    G.deck[j][q] = k[randK];
                }
            }
        }

 //...and get counts for compare. 
        
        for(m = 0; m < G.handCount[currentPlayer]; m++){
            if(G.hand[currentPlayer][m] == copper || G.hand[currentPlayer][m] == silver || G.hand[currentPlayer][m] == gold){
                startCoin++;
            }
        }
   
        playAdventurer(currentPlayer, &G);   
        
        currentCoin = 0;
        
        for(m = 0; m < G.handCount[currentPlayer]; m++){
            if(G.hand[currentPlayer][m] == copper || G.hand[currentPlayer][m] == silver || G.hand[currentPlayer][m] == gold){
                currentCoin++;
            }
        }
       
        treasureCopper = 0;
        treasureSilver = 0;
        treasureGold = 0;


        for(x = 0; x < G.discardCount[currentPlayer]; x++){
            if(G.discard[currentPlayer][x] == copper) {
                treasureCopper++;
            } else if(G.discard[currentPlayer][x] == silver) {
                treasureSilver++;
            } else if(G.discard[currentPlayer][x] == gold) {
                treasureGold++;
            }
        }

// Card count/drawn tests


        int passTest = 1;
        printf("Testing Card - Adventurer\n");
        if(currentCoin > (startCoin + 2)){
            printf("FAIL - Card draw\n\n");
            testDraw++;
            passTest = 0;
        }
        
        if(currentCoin < startCoin){
            printf("FAIL - Card count\n\n");
            testDraw++;
            passTest = 0;
        }


   // Test if adventurer pulls treasure cards from hand 


        if(treasureGold != 0){
            printf("FAIL - Gold\n\n");
            failDiscard++;
            passTest = 0;
        }

         if(treasureSilver != 0){
            printf("FAIL - Silver\n\n");
            failDiscard++;
            passTest = 0;
        }

        if(treasureCopper != 0){
            printf("FAIL - Copper\n\n");
            failDiscard++;
            passTest = 0;
        }

        if(passTest == 1){
            printf("PASS - All\n\n");
            passAll++;
        }
   }
   
   printf("\n\n");
   printf("Adventurer Tests - PASS %d\n", passAll);
   printf("FAIL - Draw Count %d\n", testDraw);
   printf("FAIL - Discard Count %d\n\n", failDiscard);
   
   return 0;
}