#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "blackjack.h"

int main() {
    gmState gm = {0};
    card deck[52];
    gm.cash = 100;
    srand(time(NULL));

    initColors();
    loadConfig();
    printWelcome();
    buildCards(deck);
    char input[10];
    
    startGame(deck, &gm);
    while(true) {
        printTable(&gm);
        do {
            printf("\n");
            printf(">> ");
            scanf(" %s", input);
            //printf("\n");
            lowerStr(input);
            if ((strcmp(input, "h") == 0|| strcmp(input, "hit") == 0) && gm.stand == false) {
                gm.pHand[gm.phs] = drawCard(deck);
                if(gm.pHand[gm.phs].val == 1) {
                    if((gm.pSum + 11) <= 21) {
                        gm.pSum += 11;
                        gm.pAces++;
                    } else {
                        gm.pSum += 1;
                    }
                } else {
                    gm.pSum += gm.pHand[gm.phs].val;
                }
                gm.phs++;
                break;
            }
            else if((strcmp(input, "s") == 0 || strcmp(input, "stand") == 0) || gm.stand == true) {
                gm.stand = true;
                gm.dHand[gm.dhs] = drawCard(deck);
                
                if(gm.dHand[gm.dhs].val == 1) {
                    if((gm.dSum + 11) <= 21) {
                        gm.dSum += 11;
                        gm.dAces++;
                    } else {
                        gm.dSum += 1;
                    }
                } else {
                    gm.dSum += gm.dHand[gm.dhs].val;
                }
                gm.dhs++;
                break;
            } else if((strcmp(input, "q") == 0 || strcmp(input, "quit") == 0) || gm.stand == true) {
                printGoodbye(&gm);
                return 0;
            } else if(strcmp(input, "help") == 0 ) {
                printHelp();
                continue;
            } else if(strcmp(input, "settings") == 0 || strcmp(input, "cfg") == 0) {
                showSettingsMenu();
                printf("\n");
                printTable(&gm);
                continue;
            } else {
                printf("Invalid input\n");
            }
        } while (1);
        if(gm.dSum == 21 && gm.insured == true) {
            printEnd(&gm, 1);
        }
        else if(gm.pSum > 21) {
            if(gm.pAces > 0) {
                gm.pSum = gm.pSum - 10;
                gm.pAces--;
                continue;
            }
            printEnd(&gm, 2);
        }
        else if(gm.dSum >= 17) {
            if(gm.dSum > 21) {
                if(gm.dAces > 0) {
                    gm.dSum = gm.dSum - 10;
                    gm.dAces--;
                    continue;
                }
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
        
        if (gm.end == true) {
            gameEnd(&gm, deck);
    }
    }
    return 0;
}