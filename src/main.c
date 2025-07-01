#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "blackjack.h"
//cus
int main() {
    gmState gm = {0};
    card deck[52];
    gm.cash = 100;
    srand(time(NULL));
    int g = 5;
    initColors();
    loadConfig();
    printWelcome();
    buildCards(deck);
    char input[32];
    
    startGame(deck, &gm);
    
    while(true) {
        printTable(&gm);
        while(!gm.stand && !gm.end) {
            printf("\n>> ");
            scanf(" %31s", input);
            lowerStr(input);
            
            if (strcmp(input, "h") == 0 || strcmp(input, "hit") == 0) {
                card newCard = drawCard(deck);
                addCardToHand(&gm, newCard, true);
                
                while(gm.pSum > 21 && gm.pAces > 0) {
                    convertAce(&gm, true);
                }
                break;
            }
            else if(strcmp(input, "s") == 0 || strcmp(input, "stand") == 0) {
                gm.stand = true;
                break;
            }
            else if(strcmp(input, "q") == 0 || strcmp(input, "quit") == 0) {
                printGoodbye(&gm);
                return 0;
            }
            else if(strcmp(input, "help") == 0) {
                printHelp();
            }
            else if(strcmp(input, "settings") == 0 || strcmp(input, "cfg") == 0) {
                showSettingsMenu();
                printf("\n");
                printTable(&gm);
            }
            else {
                printf("Invalid input\n");
            }
        }
        
        while(gm.dSum < 17 && gm.stand) {
            card newCard = drawCard(deck);
            addCardToHand(&gm, newCard, false);
            printf("Dealer draws...\n\n");
            while(gm.dSum > 21 && gm.dAces > 0) {
                convertAce(&gm, false);
            }
            
            #ifdef _WIN32
                system("timeout /t 1 >nul");
            #else
                system("sleep 1");
            #endif
            break;
        }
        
        if(gm.pSum > 21) {
            printEnd(&gm, 2);
        }
        if (gm.dSum >= 17){
            if(gm.dSum > 21) {
                printEnd(&gm, 1);
            }
            else if(gm.pSum > gm.dSum) {
                printEnd(&gm, 1);
            }
            else if(gm.pSum < gm.dSum) {
                printEnd(&gm, 2);
            }
            else {
                printEnd(&gm, 0);
            }
        }
        
        if(gm.end) {
            gameEnd(&gm, deck);
        }
    }
    return 0;
}

void debugPrint(gmState *gm) {
    printf("phs: %d, dhs: %d\n", gm->phs, gm->dhs);
    printf("pSum: %d, dSum: %d\n", gm->pSum, gm->dSum);
    printf("pAces: %d, dAces: %d\n", gm->pAces, gm->dAces);
    printf("stand: %d, end: %d, insured: %d\n", gm->stand, gm->end, gm->insured);
    printf("cash: %d, betCash: %d, insuranceCash: %d\n", gm->cash, gm->betCash, gm->insuranceCash);
}