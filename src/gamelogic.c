#include <stdio.h>
#include <stdlib.h>
#include "blackjack.h"
#include "colors.h"

void startGame(card deck[52], gmState* gm) {
    if(cash == true){
        placeBet(gm);
    }
    gm->end = false;
    for(int i = 0; i < 2; i++) {
        gm->pHand[gm->phs] = drawCard(deck);
        
        if(gm->pHand[gm->phs].val == 1) {
            if((gm->pSum + 11) <= 21) {
                gm->pSum += 11;
                gm->pAces++;
            } else {
                gm->pSum += 1;
            }
        } else {
            gm->pSum += gm->pHand[gm->phs].val;
        }
        gm->phs++;
    }
    
    gm->dHand[gm->dhs] = drawCard(deck);
    if(gm->dHand[gm->dhs].val == 1) {
        if((gm->dSum + 11) <= 21) {
            gm->dSum += 11;
            gm->dAces++;
        } else {
            gm->dSum += 1;
        }
    } else {
        gm->dSum += gm->dHand[gm->dhs].val;
    }
    gm->dhs++;
    if(gm->pHand->val == 21){
        printf(BOLD GREEN "Blackjack!\n" RESET);
        printEnd(gm, 1);
        gameEnd(gm, deck);
        return;
    }
    if(gm->dAces == 1){
        insurance(gm);
    }
}

void placeBet(gmState* gm) {
    do {
        printf("Your cash: %i\n", gm->cash);
        printf("Your bet: ");
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
    gm->insuranceCash = 0;
    gm->stand = false;
    gm->insured = false;
    for (int i = 0; i < 52; i++) {
        usedCards[i] = false;
    }
    startGame(deck, gm);
}

void printTable(gmState* gm) {
    if(values == true) {
        printf(BOLD "Your hand (%i):\n" RESET, gm->pSum);
        printHand(gm->pHand, gm->phs);
        printf(BOLD "Dealer hand (%i):\n" RESET, gm->dSum);
        printHand(gm->dHand, gm->dhs);
    } else {
        printf(BOLD "Your hand:\n" RESET);
        printHand(gm->pHand, gm->phs);
        printf(BOLD "Dealer hand:\n" RESET);
        printHand(gm->dHand, gm->dhs);
    }
}

void insurance(gmState* gm) {
    char choice;
    do {
        printf("Dealer has ace, do you want to insure? (y/n): ");
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'Y') {
            break;
        } else if (choice == 'n' || choice == 'N') {
            return;
        } else {
            printf("Invalid input.\n");
        }
    } while (1);

    printf("Your cash: %i\n", gm->cash);
    do{
        printf("Your insurance: ");
        scanf(" %i", &gm->insuranceCash);
        if(gm->insuranceCash <= gm->cash) {
            gm->cash -= gm->insuranceCash;
            break;
            
        } else {
            printf("Not enough cash.\n");
        }
    } while(1);
}

void gameEnd(gmState* gm, card deck[52]) {
    char replay;
    gm->cash = gm->cash + gm->betCash;
    if(autoplay == true){
        restart(deck, gm);
        return;
    }
    do {
        printf(BOLD "Play again? (y/n): " RESET);
        scanf(" %c", &replay);
        printf("\n");
        
        if (replay == 'y' || replay == 'Y') {
            restart(deck, gm);
            break;
        } else if (replay == 'n' || replay == 'N') {
            printGoodbye(gm);
            return;
        } else {
            printf("Invalid input\n");
        }
    } while (1);
}