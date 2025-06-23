#include <stdio.h>
#include <stdlib.h>
#include "blackjack.h"

const char *ranks[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
bool values = false;
bool cash = false;
bool usedCards[52] = {false};

card drawCard(card deck[52]) {
    int cIndex = getNewIndex();
    return deck[cIndex];
}

int getNewIndex() {
    int index = 0;
    do {
        index = rand() % 52;
    } while(usedCards[index] == true);
    usedCards[index] = true;
    return index;
}

void buildCards(card cards[52]) {
    int cardIndex = 0;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 13; j++) {
            cards[cardIndex].suit = i;
            cards[cardIndex].rank = (char*)ranks[j];

            if(j == 0) {
                cards[cardIndex].val = 1;
            }
            else if(j > 9) {
                cards[cardIndex].val = 10;
            }
            else {
                cards[cardIndex].val = (j + 1);
            }
            cardIndex++;
        }
    }
}

const char* getSuitColor(int suit) {
    switch(suit) {
        case 0: return SPADES;
        case 1: return HEARTS;
        case 2: return DIAMONDS;
        case 3: return CLUBS;
        default: return "";
    }
}

// 0 = Spades 1 = Hearts 2 = Diamonds 3 = Clubs
void printHand(card hand[], int handSize) {
    // Top border
    for(int i = 0; i < handSize; i++) {
        printf("%s+-------+ %s", getSuitColor(hand[i].suit), RESET);
    }
    printf("\n");
    
    // Top rank
    for(int i = 0; i < handSize; i++) {
        printf("%s|%-2s     | %s", getSuitColor(hand[i].suit), hand[i].rank, RESET);
    }
    printf("\n");
    
    // Middle suit symbols (your existing code with colors)
    for(int row = 0; row < 3; row++) {
        for(int i = 0; i < handSize; i++) {
            const char* color = getSuitColor(hand[i].suit);
            switch(hand[i].suit) {
                case 0: 
                    if(row == 0) printf("%s|   ^   | %s", color, RESET);
                    else if(row == 1) printf("%s|  /|\\  | %s", color, RESET);
                    else printf("%s|   |   | %s", color, RESET);
                    break;
                case 1:
                    if(row == 0) printf("%s| /\\ /\\ | %s", color, RESET);
                    else if(row == 1) printf("%s| \\   / | %s", color, RESET);
                    else printf("%s|  \\ /  | %s", color, RESET);
                    break;
                case 2:
                    if(row == 0) printf("%s|   /\\  | %s", color, RESET);
                    else if(row == 1) printf("%s|  <  > | %s", color, RESET);
                    else printf("%s|   \\/  | %s", color, RESET);
                    break;
                case 3:
                    if(row == 0) printf("%s|   o   | %s", color, RESET);
                    else if(row == 1) printf("%s|  ooo  | %s", color, RESET);
                    else printf("%s|   |   | %s", color, RESET);
                    break;
            }
        }
        printf("\n");
    }
    
    // Bottom rank
    for(int i = 0; i < handSize; i++) {
        printf("%s|     %-2s| %s", getSuitColor(hand[i].suit), hand[i].rank, RESET);
    }
    printf("\n");
    
    // Bottom border
    for(int i = 0; i < handSize; i++) {
        printf("%s+-------+ %s", getSuitColor(hand[i].suit), RESET);
    }
    printf("\n");
}


void printHelp(){
    printf("\n");
    printf("Rules: Try to get as close to 21 as possible without going over.\n");
    printf("Aces can count as 1 or 11, face cards are worth 10.\n");
    printf("You can hit (draw a card) or stand (keep your current hand).\n");
    printf("You can no longer hit after standing.\n");
    printf("\n");
    printf("  (h)/(hit): Hit\n");
    printf("  (s)/(stand): Stand\n");
    printf("  (q)/(quit): Quit game\n");
    printf("  (v) / (value): Display hand values\n");
    printf("  (c) / (cash): Play with bets\n");
    printf("  (help): Display help\n");
    printf("\n");
}

void printEnd(gmState *gm, int result) {
    printTable(gm);
    printf("\n");
    if (result == 1) {
        printf(BOLD GREEN "You won! \n" RESET);
        gm->betCash *= 2;
    } else if (result == 0) {
        printf(BOLD YELLOW "Push. \n" RESET);
    } else {
        printf(BOLD RED "You lost. \n"RESET);
        gm->betCash = 0;
        if(gm->insured) {//needs to be changed to payout only if dealer hand is ace and 10
            gm->cash += gm->insuranceCash*2;
            gm->insuranceCash = 0;
            printf("You got your insurance.\n");
        }
    }
    printf("\n");
    gm->end = true;
}

void printWelcome() {
    printf("Welcome to Blackjack!\n");
    printf("For usage/rules type (help).\n");
    printf("\n");
}

void printGoodbye(gmState *gm) {
    printf("Thank you for playing Blackjack!\n");
    if (cash) {
        printf("Your final cash balance: %d\n", gm->cash);
    }
    printf("Goodbye!\n");
}

#ifdef _WIN32
#include <windows.h>
#include <io.h>

void enableWindowsColors() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;
    
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;
    
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#endif

void initColors() {
#ifdef _WIN32
    enableWindowsColors();
#endif
}