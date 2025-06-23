#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "blackjack.h"

int main(int argc, char* argv[]) {
    gmState gm = {0};
    card deck[52];
    gm.cash = 100;
    srand(time(NULL));

    for(int i = 1; i < argc; i++) {
        if(argv[i] != NULL) {
            if(strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--cash") == 0) {
                cash = true;
            } else if(strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--values") == 0) {
                values = true;
            } else if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "help") == 0) {
                printHelp();
                return 0;
            }
        }
    }

    void initColors();
    printWelcome();
    buildCards(deck);
    char hitStand[10];
    char replay;
    
    startGame(deck, &gm);
    while(true) {
        printTable(&gm);
        do {
            printf("\n");
            printf(">> ");
            scanf(" %s", hitStand);
            //printf("\n");
            for(int i = 0; hitStand[i] != '\0'; i++) {
                hitStand[i] = tolower(hitStand[i]);
            }
            if ((strcmp(hitStand, "h") == 0|| strcmp(hitStand, "hit") == 0) && gm.stand == false) {
                gm.pHand[gm.phs] = drawCard(deck);
                if(gm.pHand[gm.phs].val == 1) {
                    if((gm.pHand[gm.phs].val + gm.pSum + 10) <= 21) {
                        gm.pHand[gm.phs].val += 10;
                        gm.pAces++;
                    }
                }
                gm.pSum += gm.pHand[gm.phs].val;
                gm.phs++;
                break;
            } else if((strcmp(hitStand, "s") == 0 || strcmp(hitStand, "stand") == 0) || gm.stand == true) {
                gm.stand = true;
                gm.dHand[gm.dhs] = drawCard(deck);
                if(gm.dHand[gm.dhs].val == 1) {
                    if((gm.dHand[gm.dhs].val + gm.dSum + 10) <= 21) {
                        gm.dHand[gm.dhs].val += 10;
                        gm.dAces++;
                    }
                }
                gm.dSum += gm.dHand[gm.dhs].val;
                gm.dhs++;
                break;
            } else if((strcmp(hitStand, "q") == 0 || strcmp(hitStand, "quit") == 0) || gm.stand == true) {
                printGoodbye(&gm);
                return 0;
            } else if(strcmp(hitStand, "help") == 0) {
                printHelp();
                continue;
            } else if(strcmp(hitStand, "value") == 0) {
                if(values) {
                    printf("Hand value displaying is now turned off\n");
                    values = false;
                    continue;
                }else{
                    printf("Each hand will now display its value\n");
                    values = true;
                    continue;
                }
            } else if(strcmp(hitStand, "cash") == 0) {
                if(cash) {
                    printf("Betting is turned off starting next game\n");
                    cash = false;
                    gm.cash = 100;
                    continue;
                }else{
                    printf("Betting is turned on starting next game\n");
                    cash = true;
                    continue;
                }
            } else {
                printf("Invalid input\n");
            }
        } while (1);

        if(gm.pSum > 21) {
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
            do {
                printf("Play again? (y/n): ");
                scanf(" %c", &replay);
                printf("\n");
                
                if (replay == 'y' || replay == 'Y') {
                    gm.cash = gm.cash + gm.betCash;
                    restart(deck, &gm);
                    break;
                } else if (replay == 'n' || replay == 'N') {
                    gm.cash = gm.cash + gm.betCash;
                    printGoodbye(&gm);
                    return 0;
                } else {
                    printf("Invalid input\n");
                }
            } while (1);
        }
    }
    return 0;
}