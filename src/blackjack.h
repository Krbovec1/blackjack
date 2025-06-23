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
    bool stand, end, insured;
    int cash, betCash, insuranceCash;
} gmState;

extern const char *ranks[];
extern bool values;
extern bool cash;
extern bool usedCards[52];

#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

#define BRIGHT_BLACK   "\033[90m"
#define BRIGHT_RED     "\033[91m"
#define BRIGHT_GREEN   "\033[92m"
#define BRIGHT_YELLOW  "\033[93m"
#define BRIGHT_BLUE    "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN    "\033[96m"
#define BRIGHT_WHITE   "\033[97m"
#define BRIGHT_ORANGE  "\033[38;5;214m"

#define BG_BLACK   "\033[40m"
#define BG_RED     "\033[41m"
#define BG_GREEN   "\033[42m"
#define BG_YELLOW  "\033[43m"
#define BG_BLUE    "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN    "\033[46m"
#define BG_WHITE   "\033[47m"

#define BOLD      "\033[1m"
#define UNDERLINE "\033[4m"

#define SPADES   BRIGHT_YELLOW
#define HEARTS   BRIGHT_ORANGE
#define DIAMONDS  BRIGHT_RED
#define CLUBS     BRIGHT_MAGENTA

void buildCards(card cards[52]);
void printHand(card hand[], int handSize);
void printTable(gmState *gm);
void startGame(card deck[52], gmState *gm);
card drawCard(card deck[52]);
int getNewIndex();
void restart(card deck[52], gmState *gm);
void placeBet(gmState *gm);
void printHelp();
void printEnd(gmState *gm, int result);// result val - 0 = push, 1 = win, 2 = lose
void printWelcome();
void printGoodbye(gmState *gm);
void enableWindowsColors();
void initColors();
const char* getSuitColor(int suit);
void gameEnd(gmState* gm, card deck[52]);
void insurance(gmState* gm);

#endif