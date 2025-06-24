#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "blackjack.h"
#include "colors.h"

const char *ranks[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
bool values = false;
bool cash = false;
bool autoplay = false;
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
    for(int i = 0; i < handSize; i++) {
        printf("%s+-------+ %s", getSuitColor(hand[i].suit), RESET);
    }
    printf("\n");
    
    for(int i = 0; i < handSize; i++) {
        printf("%s|%-2s     | %s", getSuitColor(hand[i].suit), hand[i].rank, RESET);
    }
    printf("\n");
    
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
    
    for(int i = 0; i < handSize; i++) {
        printf("%s|     %-2s| %s", getSuitColor(hand[i].suit), hand[i].rank, RESET);
    }
    printf("\n");
    
    for(int i = 0; i < handSize; i++) {
        printf("%s+-------+ %s", getSuitColor(hand[i].suit), RESET);
    }
    printf("\n");
}


void printHelp(){
    printf("\nRules: Try to get as close to 21 as possible without going over.\n");
    printf("Aces can count as 1 or 11, face cards are worth 10.\n");
    printf("You can hit (draw a card) or stand (keep your current hand).\n");
    printf("You can no longer hit after standing.\n\n");
    printf("Inputs:\n");
    printf("  (h)/(hit): Hit\n");
    printf("  (s)/(stand): Stand\n");
    printf("  (q)/(quit): Quit game\n");
    printf("  (cfg) / (settings): Open settings\n");
    printf("  (help): Display help\n");
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
    saveConfig();
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

void lowerStr(char* str) {
    for (; *str; ++str) {
        *str = tolower((unsigned char)*str);
    }
}

void loadConfig() {
    FILE *f = fopen("blackjack.cfg", "r");
    if (!f) return;

    char line[128];
    while (fgets(line, sizeof(line), f)) {
        char key[64], value[64];
        if (sscanf(line, "%63[^=]=%63s", key, value) == 2) {
            if (strcmp(key, "values") == 0) values = atoi(value);
            else if (strcmp(key, "cash") == 0) cash = atoi(value);
            else if (strcmp(key, "autoplay") == 0) autoplay = atoi(value);
            else if (strcmp(key, "spades_color") == 0) SPADES = strdup(value);
            else if (strcmp(key, "hearts_color") == 0) HEARTS = strdup(value);
            else if (strcmp(key, "diamonds_color") == 0) DIAMONDS = strdup(value);
            else if (strcmp(key, "clubs_color") == 0) CLUBS = strdup(value);
        }
    }
    fclose(f);
}

void saveConfig() {
    FILE *f = fopen("blackjack.cfg", "w");
    if (!f) return;
    fprintf(f, "values=%d\n", values ? 1 : 0);
    fprintf(f, "cash=%d\n", cash ? 1 : 0);
    fprintf(f, "autoplay=%d\n", autoplay ? 1 : 0);
    fprintf(f, "spades_color=%s\n", SPADES);
    fprintf(f, "hearts_color=%s\n", HEARTS);
    fprintf(f, "diamonds_color=%s\n", DIAMONDS);
    fprintf(f, "clubs_color=%s\n", CLUBS);
    fclose(f);
}

void showSettingsMenu() {
    int choice;
    char color[32];

    while (1) {
        printf("\nSettings Menu:\n");
        printf("1. Toggle hand value display (currently: %s)\n", values ? "ON" : "OFF");
        printf("2. Toggle betting (currently: %s)\n", cash ? "ON" : "OFF");
        printf("3. Toggle auto-continue (currently: %s)\n", autoplay ? "ON" : "OFF");
        printf("4. Change Spades color\n");
        printf("5. Change Hearts color\n");
        printf("6. Change Diamonds color\n");
        printf("7. Change Clubs color\n");
        printf("0. Exit settings\n");
        printf("Settings: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }
        switch (choice){
            case 1:
                values = !values;
                printf("Hand value display is now %s\n", values ? "ON" : "OFF");
                break;
            case 2:
                cash = !cash;
                printf("Betting is now %s\n", cash ? "ON" : "OFF");
                break;
            case 3:
                autoplay = !autoplay;
                printf("Auto-continue is now %s\n", autoplay ? "ON" : "OFF");
                break;
            case 4:
                printf("Spades color: ");
                scanf("%s", color);
                changeColor(color, 0);
                break;
            case 5:
                printf("Hearst color: ");
                scanf("%s", color);
                changeColor(color, 1);
                break;
            case 6:
                printf("Diamonds color: ");
                scanf("%s", color);
                changeColor(color,2);
                break;
            case 7:
                printf("Clubs color: ");
                scanf("%s", color);
                changeColor(color, 3);
                break;
            case 0:
                return;
            default:
                printf("Invalid input.\n");
        }
    }
}

void changeColor(char* color, int suit){
    lowerStr(color);
    const char* ansiVal = getColorAnsi(color);
    if (!ansiVal) {
        printf("Unknown color name.\n");
        return;
    }
    char* newColor = strdup(ansiVal);;
    switch(suit){
        case 0:
            if (SPADES) free(SPADES);
            SPADES = newColor;
            break;
        case 1:
            if (HEARTS) free(HEARTS);
            HEARTS = newColor;
            break;
        case 2:
            if (DIAMONDS) free(DIAMONDS);
            DIAMONDS = newColor;
            break;
        case 3:
            if (CLUBS) free(CLUBS);
            CLUBS = newColor;
            break;
        default:
            perror("Suit not specified in changeColor");
            free(newColor);
    }
}

const char* getColorAnsi(const char* name) {
    if (strcasecmp(name, "black") == 0) return BLACK;
    if (strcasecmp(name, "red") == 0) return RED;
    if (strcasecmp(name, "green") == 0) return GREEN;
    if (strcasecmp(name, "yellow") == 0) return YELLOW;
    if (strcasecmp(name, "blue") == 0) return BLUE;
    if (strcasecmp(name, "magenta") == 0) return MAGENTA;
    if (strcasecmp(name, "cyan") == 0) return CYAN;
    if (strcasecmp(name, "white") == 0) return WHITE;
    if (strcasecmp(name, "orange") == 0) return ORANGE;
    return NULL;
}