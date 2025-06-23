#include <stdio.h>
#include <stdlib.h>
#include "blackjack.h"

void startGame(card deck[52], gmState* gm) {
    if(cash == true){
        placeBet(gm);
    }
    gm->end = false;
    for(int i = 0; i < 2; i++) {
        gm->pHand[gm->phs] = drawCard(deck);
        if(gm->pHand[gm->phs].val == 1) {
            if((gm->pHand[gm->phs].val + gm->pSum + 10) <= 21) {
                gm->pHand[gm->phs].val += 10;
            }
        }
        gm->pSum += gm->pHand[gm->phs].val;
        gm->phs++;
    }
    gm->dHand[gm->dhs] = drawCard(deck);
    if(gm->dHand[gm->dhs].val == 1) {
        if((gm->dHand[gm->dhs].val + gm->dSum + 10) <= 21) {
            gm->dHand[gm->dhs].val += 10;
        }
    }
    gm->dSum += gm->dHand[gm->dhs].val;
    gm->dhs++;
}

void placeBet(gmState* gm) {
    do {
        printf("Your cash: %i\n", gm->cash);
        printf("Your bet:");
        scanf(" %i", &gm->betCash);
        printf("\n");
        if(gm->betCash <= gm->cash) {
            break;
        }
        printf("Not enough cash\n");
    } while(1);
    gm->cash -= gm->betCash;
}

void restart(card deck[52], gmState* gm) {
    gm->dhs = 0;
    gm->phs = 0;
    gm->pSum = 0;
    gm->dSum = 0;
    gm->pAces = 0;
    gm->dAces = 0;
    gm->stand = false;
    for (int i = 0; i < 52; i++) {
        usedCards[i] = false;
    }
    startGame(deck, gm);
}

void printTable(gmState* gm) {
    if(values == true) {
        printf("Your hand (%i):\n", gm->pSum);
        printHand(gm->pHand, gm->phs);
        printf("Dealer hand (%i):\n", gm->dSum);
        printHand(gm->dHand, gm->dhs);
    } else {
        printf("Your hand:\n");
        printHand(gm->pHand, gm->phs);
        printf("Dealer hand:\n");
        printHand(gm->dHand, gm->dhs);
    }
}