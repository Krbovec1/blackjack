#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct tCard
{
    int val;
    int suit;
    char* rank;
    bool isAce;
} card;

bool gameEnded = false;
bool usedCards[52] = {false};
const int goal = 21;
const char *ranks[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
card playerHand[9];
int phs = 0;
card dealerHand[9];
int dhs = 0;
int playerSum = 0;
int dealerSum = 0;
bool stand = false;

void buildCards(card cards[52]);
void printHand(card hand[], int handSize);
void printTable();
void startGame(card deck[52]);
card drawCard(card deck[52]);
int rnd();
void restart(card deck[52]);

int main (int argc, char* argv[]){
    int usedCards[52];
    card deck[52];
    buildCards(deck);
    srand(time(NULL));
    for (int i = 0; i < 9; i++){
        playerHand[i].val = 0;
        dealerHand[i].val = 0;
    }
    char hitStand;
    char replay;


    startGame(deck);
    while(true){
        printTable();
        do {
            printf("Hit or Stand?(h/s): ");
            scanf(" %c", &hitStand);
            printf("\n");
            
            if ((hitStand == 'h' || hitStand == 'H') && stand == false) {
                playerHand[phs] = drawCard(deck);
                if(playerHand[phs].val == 1){
                    if((playerHand[phs].val + playerSum + 10) <= 21){
                        playerHand[phs].val += 10;
                    }
                }
                playerSum += playerHand[phs].val;
                phs++;
                break;
            } else if((hitStand == 's' || hitStand == 'S') || stand == true) {
                stand = true;
                dealerHand[dhs] = drawCard(deck);
                if(dealerHand[phs].val == 1){
                    if((dealerHand[phs].val + playerSum + 10) <= 21){
                        dealerHand[phs].val += 10;
                    }
                }
                dealerSum += dealerHand[dhs].val;
                dhs++;
                break;
            } else {
                printf("Invalid input\n");
            }
        } while (1);

        if(playerSum > 21){
            printTable();
            printf("You lost :( \n");
            gameEnded = true;
        }
        else if(dealerSum >= 17){
            if(dealerSum > 21 || playerSum > dealerSum){
                printTable();
                printf("You won !! \n");
                gameEnded = true;
            }
            else if(playerSum < dealerSum){
                printTable();
                printf("You lost :( \n");
                gameEnded = true;
            }
            else{
                printTable();
                printf("Tie \n");
                gameEnded = true;
            }

        }
        if (gameEnded == true){
            do {
                printf("Play again? (y/n): ");
                scanf(" %c", &replay);
                printf("\n");
                
                if (replay == 'y' || replay == 'Y') {
                    restart(deck);
                    break;
                } else if (replay == 'n' || replay == 'N') {
                    return 0;
                } else {
                    printf("Invalid input\n");
                }
            } while (1);
        }
    }
    return 0;
}

void restart(card deck[52]){
    dhs = 0;
    phs = 0;
    playerSum = 0;
    dealerSum = 0;
    stand = false;
    for (int i = 0; i < 52; i++){
        usedCards[i] = false;
    }
    startGame(deck);
}

void printTable(){
        printf("Your hand:\n");
        printHand(playerHand, phs);
        printf("Dealer hand:\n");
        printHand(dealerHand, dhs);
}


void startGame(card deck[52]){
    gameEnded = false;
    for(int i = 0; i < 2; i++){
        playerHand[phs] = drawCard(deck);
        if(playerHand[phs].val == 1){
            if((playerHand[phs].val + playerSum + 10) <= 21){
                playerHand[phs].val += 10;
            }
        }
        playerSum += playerHand[phs].val;
        phs++;
    }
    dealerHand[dhs] = drawCard(deck);
    if(dealerHand[phs].val == 1){
        if((dealerHand[phs].val + playerSum + 10) <= 21){
            dealerHand[phs].val += 10;
        }
    }
    dealerSum += dealerHand[dhs].val;
    dhs++;
}

card drawCard(card deck[52]){
    int cIndex = rnd();
    return deck[cIndex];
}

int rnd(){
    int index = 0;
    do {
    index = rand() % 52;
    }while(usedCards[index] == true);
    usedCards[index] = true;
    return index;
}

void buildCards(card cards[52]){
    int cardIndex = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            cards[cardIndex].suit = i;
            cards[cardIndex].rank = (char*)ranks[j];
            cards[cardIndex].isAce = false;

            if(j == 0){
                cards[cardIndex].val = 1;
                cards[cardIndex].isAce = true;
            }
            else if(j > 9){
                cards[cardIndex].val = 10;
            }
            else{
              cards[cardIndex].val = (j + 1);
            }
            cardIndex++;
        }
    } 
}

void printHand(card hand[], int handSize) {
    for(int i = 0; i < handSize; i++) {
        printf("+-------+ ");
    }
    printf("\n");
    
    for(int i = 0; i < handSize; i++) {
        printf("|%-2s     | ", hand[i].rank);
    }
    printf("\n");
    
    for(int row = 0; row < 3; row++) {
        for(int i = 0; i < handSize; i++) {
            switch(hand[i].suit) {
                case 0: 
                    if(row == 0) printf("|   ^   | ");
                    else if(row == 1) printf("|  /|\\  | ");
                    else printf("|   |   | ");
                    break;
                case 1:
                    if(row == 0) printf("| /\\ /\\ | ");
                    else if(row == 1) printf("| \\   / | ");
                    else printf("|  \\ /  | ");
                    break;
                case 2:
                    if(row == 0) printf("|   /\\  | ");
                    else if(row == 1) printf("|  <  > | ");
                    else printf("|   \\/  | ");
                    break;
                case 3:
                    if(row == 0) printf("|   o   | ");
                    else if(row == 1) printf("|  ooo  | ");
                    else printf("|   |   | ");
                    break;
            }
        }
        printf("\n");
    }
    
    for(int i = 0; i < handSize; i++) {
        printf("|     %-2s| ", hand[i].rank);
    }
    printf("\n");
    
    for(int i = 0; i < handSize; i++) {
        printf("+-------+ ");
    }
    printf("\n");
}