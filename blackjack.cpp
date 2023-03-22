#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <string>
using namespace std;

const int MAX_HAND_SIZE = 10;
int NUM_CARDS = 52;

// playing card
struct Card {
    int value;
    char suit;
};

void printCard(Card card) {
    if (card.value == 1) {
        cout << "Ace";
    }
    else if (card.value == 11) {
        cout << "Jack";
    }
    else if (card.value == 12) {
        cout << "Queen";
    }
    else if (card.value == 13) {
        cout << "King";
    }
    else {
        cout << card.value;
    }
    cout << " of " << card.suit << "s";
}

// calculating the value of a hand of cards
int calculateHandValue(Card hand[], int handSize) {
    int value = 0;
    int numAces = 0;
    for (int i = 0; i < handSize; i++) {
        if (hand[i].value == 1) {
            numAces++;
            value += 11;
        }
        else if (hand[i].value >= 10) {
            value += 10;
        }
        else {
            value += hand[i].value;
        }
    }
    while (value > 21 && numAces > 0) {
        value -= 10;
        numAces--;
    }
    return value;
}


int getBet(int bankroll) {
    int bet = 0;
    while (bet < 1 || bet > bankroll) {
        cout << "Bankroll: $" << bankroll << endl;
        cout << "Enter your bet amount: $";
        cin >> bet;
        if (bet < 1 || bet > bankroll) {
            cout << "Invalid bet amount." << endl;
            	Sleep(800);
        	system("CLS");
        }
    }
    return bet;
}

// hit & stand
bool getPlayerAction() {
    string input = "";
    while (true) {
    	Sleep(900);
        cout << "Do you want to hit (h) or stand (s)? ";
        cin >> input;
        if (input == "h" || input == "H") {
            return true;
            Sleep(760);
        }
        else if (input == "s" || input == "S") {
            return false;
            Sleep(760);
        }
        else {
            cout << "Invalid input. Try again." << endl;
            Sleep(500);
            system("CLS");
        }
    }
}

int main() {
    srand(time(NULL));
    int bankroll = 150;

    // main
    while (bankroll > 0) {
        // initializing the deck of cards
        Card deck[NUM_CARDS];
        int cardIndex = 0;
        for (int suit = 1; suit <= 4; suit++) {
            for (int value = 1; value <= 13; value++) {
                deck[cardIndex].value = value;
                deck[cardIndex].suit = 'C' + suit - 1;
                cardIndex++;
            }
        }

        // shuffling the deck
        for (int i = 0; i < NUM_CARDS; i++) {
            int j = rand() % NUM_CARDS;
            Card temp = deck[i];
                    deck[i] = deck[j];
        deck[j] = temp;
    }

    // dealing the initial cards
    Card playerHand[MAX_HAND_SIZE];
    int playerHandSize = 0;
    playerHand[playerHandSize] = deck[0];
    playerHandSize++;
    deck[0] = deck[NUM_CARDS - 1];
    NUM_CARDS--;
    playerHand[playerHandSize] = deck[0];
    playerHandSize++;
    deck[0] = deck[NUM_CARDS - 1];
    NUM_CARDS--;

    Card dealerHand[MAX_HAND_SIZE];
    int dealerHandSize = 0;
    dealerHand[dealerHandSize] = deck[0];
    dealerHandSize++;
    deck[0] = deck[NUM_CARDS - 1];
    NUM_CARDS--;
    dealerHand[dealerHandSize] = deck[0];
    dealerHandSize++;
    deck[0] = deck[NUM_CARDS - 1];
    NUM_CARDS--;

    // placing the bet
    int bet = getBet(bankroll);
    bankroll -= bet;

    // inital hands
    cout<<"Wait.. Dealer is shuffling the deck." << endl;
    Sleep(1000);
    system("CLS");
    cout << "Your hand: ";
    printCard(playerHand[0]);
    cout << ", ";
    printCard(playerHand[1]);
    cout << endl;
    Sleep(900);
    cout << "Dealer's hand: ";
    printCard(dealerHand[0]);
    cout << ", [hidden]" << endl;

    // player's turn
    while (true) {
        bool hit = getPlayerAction();
        if (hit) {
            playerHand[playerHandSize] = deck[0];
            playerHandSize++;
            deck[0] = deck[NUM_CARDS - 1];
            NUM_CARDS--;
            Sleep(800);
            cout << "Your new card: ";
            printCard(playerHand[playerHandSize - 1]);
            cout << endl;
            int handValue = calculateHandValue(playerHand, playerHandSize);
            Sleep(900);
            cout << "Your hand value: " << handValue << endl;
            if (handValue > 21) {
            	Sleep(550);
                cout << "You bust!" << endl;
                break;
            }
        }
        else {
            break;
        }
    }

  // dealer's turn
if (calculateHandValue(playerHand, playerHandSize) <= 21) {
    cout << "Dealer's turn:" << endl;
    Sleep(900);
    cout << "Dealer's hand: ";
    printCard(dealerHand[0]);
    cout << ", ";
    Sleep(900);
    printCard(dealerHand[1]);
    cout << endl;
    while (calculateHandValue(dealerHand, dealerHandSize) < 17) {
        // removing the top card from the deck and add it to the dealer's hand
        dealerHand[dealerHandSize] = deck[NUM_CARDS - 1];
        dealerHandSize++;
        NUM_CARDS--;
        // print the card that the dealer drew
        Sleep(900);
        cout << "Dealer hits and gets: ";
        printCard(dealerHand[dealerHandSize - 1]);
        cout << endl;
    }
    // calculate the value of the dealer's hand - and printing
    int dealerHandValue = calculateHandValue(dealerHand, dealerHandSize);
    cout << "Dealer's hand value: " << dealerHandValue << endl;
    if (dealerHandValue > 21) {
    	Sleep(400);
        cout << "Dealer busts!" << endl;
    }
}
// calculate the value of the player's hand
int playerHandValue = calculateHandValue(playerHand, playerHandSize);
int dealerHandValue = calculateHandValue(dealerHand, dealerHandSize);

// winner - updating bankroll
if (playerHandValue > 21) {
	Sleep(670);
    cout << "You lose!" << endl;
    bankroll -= bet;
} else if (dealerHandValue > 21 || playerHandValue > dealerHandValue) {
	Sleep(670);
    cout << "You win!" << endl;
    bankroll += bet;
} else if (playerHandValue < dealerHandValue) {
	Sleep(670);
    cout << "You lose!" << endl;
    bankroll -= bet;
} else {
	Sleep(670);
    cout << "It's a tie!" << endl;
}

// again or not
Sleep(500);
cout << "Your bankroll is now $" << bankroll << endl;
cout << "Would you like to play another hand? (y/n) ";
string playAgain;
cin >> playAgain;

if (playAgain == "y") {
	Sleep(300);
	system("CLS");
    // reset hands and start a new game
} else {
	Sleep(750);
	system("CLS");
    cout << "Thanks for playing! Your final bankroll is $" << bankroll;
    exit(0);
 	}
  }
return 0;
}


