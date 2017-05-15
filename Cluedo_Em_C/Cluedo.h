#define MAX 4
#define MAX2 9
#define Susp 6
#define Wep 6
#define Room 9
#define All 18
#define NumPlayers 3
#define PlCards 6

#pragma region BooleanDef

#ifndef BOOLEAN
#define BOOLEAN
typedef enum { FALSE, TRUE } boolean;
#endif // !BOOLEAN

#pragma endregion

#pragma region StringDef

#ifndef STRING
#define STRING
typedef char *string;
#endif // !STRING

#pragma endregion

#pragma region Cards

 ///There are 21 cards, each defined by a name. 3 are put to the murder envelope, 18 are given to the players (6 to each)

typedef struct {
	string name;
	boolean available;
 }Card;

Card SuspectCards[Susp];
Card WeaponCards[Wep];
Card RoomCards[Room];
Card AllCards[All];

#pragma endregion 

#pragma region DetectiveNotes

#pragma region Marks in Detective Notes

 ///The marks in the Detective Notes are fundamental to indicate your suspicion/knowledge of player possession of cards
 //You can take conclusions about the player possession of a card:
 //Empty - You haven't taken any conclusion yet;
 //Cross - The player in question doesn't have a card;
 //Check - The player in question has this card (meaning that it can't be involved in the "crime");
 //Doubt - You suspect that the player in question doesn't have the card;
 //Suspicion - You suspect the player in question has the card;

#ifndef MARKS
#define MARKS
enum DetNotesMarks { empty = 1, cross, check, doubt, suspicion };
#endif // !MARKS

#pragma endregion

#pragma region Written Notes in Detective Notes

#ifndef NOTA
#define NOTA
 struct nota {
	int number;
	string text;
	struct nota *next;
 };
typedef struct nota nota, *notaPtr;
#endif // !NOTA

#pragma endregion

 ///The detective notes are the main tool in Cluedo to help you keep track of player possession of cards, ultimately helping you solve the "murder mistery"
 //Includes the various parts of the detective notes, which include the following:
 //A board correspondant to the possession of suspect/character cards by you and other players(which will be filled by the marks);
 //A board correspondant to the possession of weapon cards by you and other players;
 //A board correspondant to the possession of room cards by you and other players;
 //A list of strings which includes the a number and the text you want to write(This is used if you want to keep written notes, which may prove useful);
 //                                         >the number is used to organize by order of entry and to delete entries

#ifndef DETECTIVENOTES
#define DETECTIVENOTES
 typedef struct {
	//Bidimensional array of marks for the first board: Suspect/Character Cards per player
	enum DetNotesMarks SuspMarks[Susp][NumPlayers];

	//Bidimensional array of marks for the first board: Weapon Cards per player
	enum DetNotesMarks WepMarks[Wep][NumPlayers];

	//Bidimensional array of marks for the first board: Room Cards per player
	enum DetNotesMarks RoomMarks[Room][NumPlayers];

	notaPtr head;
 }DetectiveNotes;
#endif // !DETECTIVENOTES

#pragma endregion

#pragma region Weapons
 ///There are 6 weapons
 //Array with all 6 weapons(string)
#ifndef WEAPONS
#define WEAPONS
 string Weapons[Wep] = { "Candlestic", "Dagger" , "Lead Pipe", "Revolver", "Rope", "Wrench" };
#endif // !WEAPONS
#pragma endregion

#pragma region Rooms
 ///There are 9 rooms
 //Array with all 9 rooms(string)
#ifndef ROOMYS
#define ROOMYS
 string Roomys[Room] = { "Hall", "Lounge", "Dining Room", "Kitchen", "Ballroom", "Conservatory", "Billiard Room", "Library", "Study" };
#endif // !ROOMYS

#pragma endregion

#pragma region Player

#pragma region Playing Piece
 ///There are 6 characters
 //Playing piece - can be one of 6 characters: Col. Mustard, Rev. Green, Ms. Scarlett, Mrs. Peacock, Prof. Plum, Mrs. White;
#ifndef CHARACTERS
#define CHARACTERS
 string PlayingPiece[Susp] = { "Ms. Scarlett", "Col. Mustard" , "Mrs. White", "Rev. Green", "Mrs. Peacock", "Prof. Plum" };
#endif // !CHARACTERS
#pragma endregion

 ///Each player has a playing piece, a sheet of detective notes, and 6 random cards
 //Playing piece - can be one of 6 characters: Col. Mustard, Rev. Green, Ms. Scarlett, Mrs. Peacock, Prof. Plum, Mrs. White;
 //One set of detective notes for each;
 //An array of cards of size PlCards(6) (each player recieves 6 cards);
#ifndef PLAYER
#define PLAYER
 typedef struct {
	 string Piece;
	 string Roomy;
	 DetectiveNotes DetNotes;
	 Card PlayerCards[PlCards];
 }Player, *PlayerPtr;
 Player players[NumPlayers];
#endif // !PLAYER 

#pragma endregion 

#pragma region MurderEnvelope

 ///3 cards, one of each type
 //struct containing a character card, weapon card, and room card
#ifndef MURDERENVELOPE
#define MURDERENVELOPE
 struct MurderEnvelope {
	 Card SuspectCard;
	 Card WeaponCard;
	 Card RoomCard;
 };
 typedef struct MurderEnvelope MurderEnvelope, *MurderEnvelopePtr;
#endif // !MURDERENVELOPE

#pragma endregion

#pragma region Dice

 ///Three dice which values range from 0 to 3 and are generated randomly. Total value is between 0 and 9. If total value = 0, the dice are "rolled" again
 //Dice structure is composed by 4 int values
#ifndef DICE
#define DICE
 struct Dice {
	 int Rand1;
	 int Rand2;
	 int Rand3;
	 int sumRand;
 };
#endif // !DICE

#pragma endregion
  

 //Signatures
 int lengthof(Card arr[]);
 PlayerPtr CreatePlayer(Player *p, int x);
 struct Dice DiceRandomizer(/*int seed*/);
 void TransferToRoom(Player *p, int diceresult);
 notaPtr CreateWrittenNote(int number, string note);
 notaPtr AddWrittenNote(Player *p, notaPtr novanota);
 notaPtr RemoveWrittenNotes(Player *p, int number);
 void ShowWrittenNotesByNumber(Player *p, int number);
 string MarkPrinterSystem(enum DetNotesMarks m);
 void PrintDetectiveNotes(Player *p);
 DetectiveNotes EditDetectiveNotes(Player *p, enum DetNotesMarks m, int t, int j, int i);
 void Swap(int *a, int *b);
 void Shuffle(Card arr[]/*, int seed*/);
 void CardsToMurderEnvelope(MurderEnvelopePtr envelope, Card SuspCards[], Card WepCards[], Card RoomCards[]/*, int seed*/);
 void PutCardsInDeck(Card AllCards[], Card SuspCards[], Card WepCards[], Card RoomCards[]);
 void CardsToPlayers(Player *p, Player *q, Player *r, Card AllCards[]/*, int seed*/);
 boolean CheckCardPossession(Player p, string SuspectN, string WeaponN, string RoomN);
 Card ShowRandomCard(Player p, string SuspectN, string WeaponN, string RoomN);
 boolean SuspectAccusation(string name, MurderEnvelope envelope);
 boolean WeaponAccusation(string name, MurderEnvelope envelope);
 boolean RoomAccusation(string name, MurderEnvelope envelope);