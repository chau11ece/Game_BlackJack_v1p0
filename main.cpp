/* BlackJack Game
Author: vanchautran11ece@gmail.com
*/

#include <iostream>
#include <string>
#include <array>
#include <cstdlib> // for std::rand() and std::srand()
#include <ctime> // for std::time()
#include <limits>

using namespace std;


/// 6a) A deck of cards has 52 unique cards (13 card ranks of 4 suits).
/// Create enumerations for the card ranks (2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King, Ace)
enum CardRank
{
    RANK_2,
    RANK_3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8,
    RANK_9,
    RANK_10,
    RANK_Jack,
    RANK_Queen,
    RANK_King,
    RANK_Ace,
    MAX_RANKS   // number of ranks
};

/// and suits (clubs, diamonds, hearts, spades)
enum CardSuit
{
    SUIT_CLUB,
    SUIT_DIAMOND,
    SUIT_HEART,
    SUIT_SPADE,
    MAX_SUITS   // number of suits
};

/// 6b) Each card will be represented by a struct named Card that contains a rank and a suit. Create the struct.
/// i.e. JD - Jack Diamond, 2H - 2 HEART, ...
struct Card
{
    CardRank rank;
    CardSuit suit;
};

/// If the player and dealer have the same score (and the player has not gone bust), the result is a TIE and neither wins.
enum BlackjackResult
{
    BLACKJACK_PLAYER_WIN,
    BLACKJACK_DEALER_WIN,
    BLACKJACK_TIE,
    MAX_STATES
};

/// 6c) Create a printCard() function that takes a const Card reference as a parameter ( const Card &card)
/// and prints the card rank and values as a 2-letter code (e.g. JS : Jack Spade)
void printCard(const Card &card)    // a const Card ref as a param
{
    // check rank
    switch(card.rank)
    {
    case RANK_2:
        cout << "2";
        break;
    case RANK_3:
        cout << "3";
        break;
    case RANK_4:
        cout << "4";
        break;
    case RANK_5:
        cout << "5";
        break;
    case RANK_6:
        cout << "6";
        break;
    case RANK_7:
        cout << "7";
        break;
    case RANK_8:
        cout << "8";
        break;
    case RANK_9:
        cout << "9";
        break;
    case RANK_10:
        cout << "10";
        break;
    case RANK_Jack:
        cout << "J";
        break;
    case RANK_King:
        cout << "K";
        break;
    case RANK_Queen:
        cout << "Q";
        break;
    case RANK_Ace:
        cout << "A";
        break;
    default:
        cout << "Unkown CARD RANK.\n";
    }

    // check suit
    switch(card.suit)
    {
    case SUIT_HEART:
        cout << "H";
        break;
    case SUIT_DIAMOND:
        cout << "D";
        break;
    case SUIT_CLUB:
        cout << "C";
        break;
    case SUIT_SPADE:
        cout << "S";
        break;
    default:
        cout << "Unknown CARD SUIT.\n";
    }
}

/// 6e) Write a function named printDeck() that takes the deck as a const reference parameter and prints the values in the deck. Use a for-each loop.
void printDeck(const std::array<Card, 52> &deck)    // deck as a const ref param
{
for (const auto &card : deck)
    {
        /// call printCard() to cout all cards (e.g. 2H, 2D, 2C, 2S, 3H, 3D, 3C, 3S, ..., AH, AD, AC, AS)
        printCard(card);
        std::cout << " ";
    }
    std::cout << '\n';
}

/// 6f) Write a swapCard function that takes two Cards and swaps their values.
void swapCard(Card &card1, Card &card2)
{
    Card temp;

    temp = card1;
    card1 = card2;
    card2 = temp;

}

/// Generate a random number btw 'min' and 'max' (inclusive)
/// Assume std::srand() has already been called
/// Assume max - min <= RAND_MAX
int getRandomNumber(int min, int max)
{

    static const double fraction = 1.0 / (RAND_MAX + 1.0);
    return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));

}

/// 6g) Write a function to shuffle the deck of cards called shuffleDeck().
void shuffleDeck(std::array<Card, 52> &deck)    // deck as a const ref param
{
    /// use a for loop to step through each element of your array
    /// Pick a random number between 1 and 52
    /// Call swapCard() with the current card and the card picked at random

    //std::srand(static_cast<unsigned int>(std::time(nullptr))); // set initial seed value to system clock
    // Step through each card in the deck
    for (int currCard = 0; currCard< 52; ++currCard)
    {
        // Pick a random card, any card
        int randCard = getRandomNumber(0, 51);
        // Swap two cards' position.
        swap(deck[currCard], deck[randCard]);
    }

}

/// 6h) Write a function named getCardValue() that returns the value of a Card (e.g. a 2 is worth 2, a ten, jack, queen, or king is worth 10.
///Assume an Ace is worth 11).
int getCardValue(const Card &card, int &aceCount)
{
    switch(card.rank)
    {
    case RANK_2:
        return 2;
    case RANK_3:
        return 3;
    case RANK_4:
        return 4;
    case RANK_5:
        return 5;
    case RANK_6:
        return 6;
    case RANK_7:
        return 7;
    case RANK_8:
        return 8;
    case RANK_9:
        return 9;
    case RANK_10:
    case RANK_Jack:
    case RANK_Queen:
    case RANK_King:
        return 10;
    case RANK_Ace:
        aceCount++;
        return 11;
    default:
        cout << "Unknown CARD RANK.\n";
    }

    return 0;
}

char getPlayerChoice()
{
    std::cout << "(h) to hit, or (s) to stand - Enter your choice: ";
    char choice;
    do
    {
        cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    while (choice != 'h' && choice != 's');

    return choice;

}
/// Create a function named playBlackjack() that returns true if the player wins, and false if they lose.

BlackjackResult playBlackJack(const std::array<Card, 52> &deck)    /// Accept a shuffled deck of cards as a parameter.
{
    /// Initialize a pointer to the first Card named cardPtr. This will be used to deal out cards from the deck.
    /// i.e. short value = 7;
    ///      short *ptr = &value;
    //const Card *cardPtr = &deck[0];
    /// You learned that a fixed array can decay into a pointer that points to the first element (element 0) of the array.
    const Card *cardPtr = &deck[0];
    /// Create two integers to hold the player’s and dealer’s total score so far.
    int playerTotal = 0;
    int playerAces = 0;
    int dealerTotal = 0;
    int dealerAces = 0;

    /*
        Way to deal cards from the deck is to keep a pointer to the next card in the deck that will be dealt out.
        Whenever we need to deal a card, we get the value of the current card, and then advance the pointer to point at the next card. This can be done in one operation:
        getCardValue(*cardPtr++);
        This returns the current card’s value (which can then be added to the player or dealer’s total), and advances cardPtr to the next card.
    */
    /// The dealer gets one card to start
    dealerTotal += getCardValue(*cardPtr++, dealerAces);
    std::cout << "The dealer is showing: " << dealerTotal << '\n';
    /// The player gets two cards to start.
    playerTotal += getCardValue(*cardPtr++, playerAces);
    playerTotal += getCardValue(*cardPtr++, playerAces);

    /// The player goes first. A player's turn is in which he can deal to get out card as many as the total scores <= 21.
    while (true) /// ***** infinite loop (until we BREAK or return FALSE) *****
    {
        std::cout << "You have: " << playerTotal << '\n';
        /// See if the player has busted
        /// If the player goes over a score of 21, they bust and lose immediately.
        if (playerTotal > 21)
        {
            if (playerAces > 0)
            {
                playerAces--;
                playerTotal -= 10;
            }
            else
                return BlackjackResult::BLACKJACK_DEALER_WIN;
        }

        char choice = getPlayerChoice();
        if (choice == 's')
            break;                  // BREAK

        playerTotal += getCardValue(*cardPtr++, playerAces);
    }

    /// If player hasn't busted, dealer goes until he has at least 17 points
    /// dealer's turn.
    while (dealerTotal < 17)
    {
        dealerTotal += getCardValue(*cardPtr++, dealerAces);
        if (dealerTotal > 21)
        {
            if (dealerAces > 0)
            {
                dealerAces--;
                dealerTotal -= 10;
            }
        }

        std::cout << "The dealer now has: " << dealerTotal << '\n';
    }

    /// If dealer busted, player wins.
    if (dealerTotal > 21 || playerTotal > dealerTotal)
        return BlackjackResult::BLACKJACK_PLAYER_WIN;
    else if (dealerTotal == playerTotal)
        return BlackjackResult::BLACKJACK_TIE;
    else
        return BLACKJACK_DEALER_WIN;

}

int main()
{
    // Card deck[52];

    std::srand(static_cast<unsigned int>(std::time(nullptr)));  /// set initial seed value to system clock
    rand(); /// If using Visual Studio, discard first random value

    /// 6d) A deck of cards has 52 cards. Create an array (using std::array) to represent the deck of cards,
    /// and initialize it with one of each card.
    std::array<Card, 52> deck;
    /// We could initialize each card individually.
    /*
            deck[0].rank = CardRank[0]      // "2"
            deck[0].suit = CardSuit[0]          // "H"
            deck[0].rank = CardRank[0]      // "2"
            deck[0].suit = CardSuit[1]          // "D"
            deck[0].rank = CardRank[0]      // "2"
            deck[0].suit = CardSuit[2]          // "C"
            deck.[0].rank = CardRank[0]     // "2"
            deck.[0].suit = CardRank[3]     // "S"

            deck[1].rank = CardRank[1]      // "3"
            deck[1].suit = CardSuit[0]          // "H"
            deck[1].rank = CardRank[1]      // "3"
            deck[1].suit = CardSuit[1]          // "D"
            deck[1].rank = CardRank[1]      // "3"
            deck[1].suit = CardSuit[2]          // "C"
            deck.[1].rank = CardRank[1]     // "3"
            deck.[1].suit = CardRank[3]     // "S"

            ..........

            deck[51].rank = CardRank[51]      // "A"
            deck[51].suit = CardSuit[0]          // "H"
            deck[51].rank = CardRank[51]      // "A"
            deck[51].suit = CardSuit[1]          // "D"
            deck[51].rank = CardRank[51]      // "A"
            deck[51].suit = CardSuit[2]          // "C"
            deck.[51].rank = CardRank[51]     // "A"
            deck.[51].suit = CardRank[3]     // "S"
    */
    int numCard = 0;
    for (int rankIndex = 0; rankIndex < MAX_RANKS; ++rankIndex)
    {
        for (int suitIndex = 0; suitIndex < MAX_SUITS; ++suitIndex)
        {
            //deck[numCard].rank = CardRank[rankIndex];
            //deck[numCard].suit = CardSuit[suitIndex];
            /// Use static_cast if you need to convert an integer into an enumerated type.
            deck[numCard].rank = static_cast<CardRank>(rankIndex);
            deck[numCard].suit = static_cast<CardSuit>(suitIndex);
            numCard++;
        }
    }

    printDeck(deck);
    /// Update main function to shuffle the deck and print out the shuffled deck.
    shuffleDeck(deck);
    printDeck(deck);

    BlackjackResult result = playBlackJack(deck);

    switch (result)
    {
    case BlackjackResult::BLACKJACK_PLAYER_WIN:
        cout << "You win!\n";
        break;
    case BlackjackResult::BLACKJACK_DEALER_WIN:
        cout << "You lose!\n";
        break;
    case BlackjackResult::BLACKJACK_TIE:
        cout  << "It's a tie!";
        break;
    default:
        cout << "Error!\n";
    }

    return 0;
}

