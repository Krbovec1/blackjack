#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <stdbool.h>

typedef struct tCard {
    int val;
    int suit;
    char* rank;
} card;

typedef struct tgmState {
    card pHand[9];
    card dHand[9];
    int phs, dhs;
    int pSum, dSum;
    int pAces, dAces;
    bool stand, end;
    int cash, betCash;
} gmState;

extern const char *ranks[];
extern bool values;
extern bool cash;
extern bool usedCards[52];

void buildCards(card cards[52]);
void printHand(card hand[], int handSize);
void printTable(gmState *gm);
void startGame(card deck[52], gmState *gm);
card drawCard(card deck[52]);
int getNewIndex();
void restart(card deck[52], gmState *gm);
void placeBet(gmState *gm);
void printHelp();
void printEnd(gmState *gm, int result);// result val - 0: push, 1: win, 2: lose
void printWelcome();
void printGoodbye(gmState *gm);

#endif