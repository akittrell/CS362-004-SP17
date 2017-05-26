// Random Card Tester for card Smithy


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
    int numberofPlayers = 2;
    int failDeckCount = 0;
    int failHandCount = 0;
    int failDiscardCount = 0;
    int allPass = 0;
    int testPass;
    int currentPlayer = 0;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};  
    int sizeofDeck, sizeofHand, stateofHand, startDeck, currentDeck, startHand, currentHand, startDiscard, currentDiscard, i;
   
    
    srand(time(NULL));


 // Get start game values for comparison...
   
    for(i = 0; i < 1000000; i++){
        initializeGame(numberofPlayers, k, seed, &G);
        sizeofDeck = rand() % (MAX_DECK + 1);
        sizeofHand = rand() % (sizeofDeck + 1);
        
        G.deckCount[0] = sizeofDeck - sizeofHand;
        G.handCount[0] = sizeofHand;
        stateofHand = G.hand[currentPlayer][G.handCount[currentPlayer] - 1];
        
        startDeck = G.deckCount[0];
        startHand = G.handCount[0];
        startDiscard = G.playedCardCount;
     
        
        playSmithy(stateofHand, currentPlayer, &G);

        
        currentDeck = G.deckCount[0];
        currentHand = G.handCount[0];
        currentDiscard = G.playedCardCount;
       
        
        testPass = 1;

 // Card draw/count tests

		printf("Testing Card - Smithy\n");
        if(currentDeck != (startDeck - 3)){
            printf("FAIL - Deck Count\n\n");
            failDeckCount++;
            testPass = 0;
        }
        
        
        if(currentHand != (startHand + 2)){
            printf("FAIL - Card Draw\n\n");
            failHandCount++;
            testPass = 0;
        }
        

 // Smithy should be discarded after play...
        
        if(currentDiscard != (startDiscard + 1)){
            printf("FAIL - Smithy in hand\n\n");
            failDiscardCount++;
            testPass = 0;
        }
        
        if(testPass == 1){
            printf("PASS - All\n\n");
            allPass++;
        }
        
    }
  
        
   printf("\n\n");
   printf("Smithy Tests - PASS %d\n", allPass);
   printf("FAIL - Draw Count %d\n", failHandCount);
   printf("FAIL - Discard Count %d\n\n", failDiscardCount);        
   
   return 0;
}
