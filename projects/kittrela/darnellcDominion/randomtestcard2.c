// Random Card Tester for card Great Hall

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
    int failHandCount = 0;
    int allPass = 0;
    int testPass;
    int currentPlayer = 0;
    int k[10] = {adventurer, embargo, village, great_hall, mine, cutpurse,
      sea_hag, tribute, smithy, council_room};  
    int sizeofDeck, sizeofHand, stateofHand, startHand, currentHand, i;
   
    
    srand(time(NULL));
    printf("Testing Card - Great Hall \n");

    // Get start game values for comparison...
   
    for(i = 0; i < 1000000; i++){
        initializeGame(numberofPlayers, k, seed, &G);
        sizeofDeck = rand() % (MAX_DECK + 1);
        sizeofHand = rand() % (sizeofDeck + 1);
        
        G.deckCount[0] = sizeofDeck - sizeofHand;
        G.handCount[0] = sizeofHand;
        stateofHand = G.hand[currentPlayer][G.handCount[currentPlayer] - 1];
        
  
        startHand = G.handCount[0];
         
        
        playGreatHall(currentPlayer, &G, stateofHand);

        
   
        currentHand = G.handCount[0];
    
        
        testPass = 1;

 // Card draw/count tests, great hall should add one then discard one

     
        
        if(currentHand != startHand){
            printf("FAIL - Card Draw\n\n");
            printf("Currenthand = %i \n",  currentHand);
            printf("starthand = %i \n",  startHand);
            failHandCount++;
            testPass = 0;
        }
        

        
        if(testPass == 1){
            printf("PASS - All\n\n");
            allPass++;
        }
        
    }

    printf("\n\n");
   printf("Great Hall Tests - PASS %d\n", allPass);
   printf("FAIL - Draw Count %d\n", failHandCount);


      return 0;
}

