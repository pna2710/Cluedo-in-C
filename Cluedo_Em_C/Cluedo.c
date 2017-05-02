#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Cluedo.h"

//Function to get length of an array of cards
int lengthof(Card arr[]) {
	int length;
	length = (sizeof(arr) / (sizeof(arr[0])));
	return length;
}

//All things related to dice and movement
#pragma region MovementAndDice

//Returns a structure with all the values from the dice(randomized) and their sum (all values are gonna be displayed. in order to simulate dice throw)
struct Dice DiceRandomizer(int seed) {
	struct Dice Rand;
	seed++;
	Rand.Rand1 = rand() % 4;
	seed++;
	Rand.Rand2 = rand() % 4;
	seed++;
	Rand.Rand3 = rand() % 4;
	Rand.sumRand = Rand.Rand1 + Rand.Rand2 + Rand.Rand3;
	return Rand;
}

//"Transfers" player to room indicated in the dice
void TransferToRoom(Player *p, int diceresult) {
	p->Roomy = Roomys[diceresult - 1];
	return p->Roomy;
}

#pragma endregion

//All things related to editing, seeing, adding and removing detective notes
#pragma region DetectiveNotes

///Adds or Removes written notes for a player
//Creates the WrittenNote and returns the space in memory in which it is stored
notaPtr CreateWrittenNote(int number, string note) {
	notaPtr newnote = (notaPtr)malloc(sizeof(nota));
	newnote->number = number;
	newnote->text = note;
	newnote->next = NULL;
	return newnote;
}

//Adds a Written note to the list of written notes of a player
notaPtr AddWrittenNote(Player *p, notaPtr newnote) {
	notaPtr aux = p->DetNotes.head;
	int option = -1;
	//If head is null then head is the new note
	if (p->DetNotes.head == NULL)
	{
		p->DetNotes.head = newnote;
		return p->DetNotes.head;
	}
	//The cycle stops either if the number in the next note in the list matches the new note's number or if next note in the list doesn't exist
	while (newnote->next->number != aux->next->number && aux->next != NULL)
	{
		aux = aux->next;
	}
	//if next note in the list doesn't exist(end of list) the note we want to add is added there
	if (aux->next == NULL)
	{
		aux->next = newnote;
		return p->DetNotes.head;
	}
	//else if the cycle stopped beacuse of next note's number being equal to new note's number, an option is given to change the number
	else if (newnote->next->number == aux->next->number) {
		while (option != 0 || option != 1) {
			printf("THE NUMBER OF THE NOTE ALREADY EXISTS. DO YOU WANT TO CHANGE IT OR DISCARD THE NOTE?\n1 - Change\n0 - Discard\nOPTION: ");
			scanf("%d", &option);
			switch (option) {
			//if player wants to discard the note, choosing zero, while cycle stops and function ends. doesn' add anything
			case 0:
				break;
			//if player wants to change, the newnote's number is changed and the function runs again with the modified newnote
			case 1:
				printf("\n\nNew Number: ");
				scanf("%d", &newnote->number);
				AddWrittenNote(p, newnote);
				break;
			//in case player chooses an invalid option a message is printed and the cycle runs again
			default:
				printf("\nINVALID OPTION\n\n");
				break;
			}
		}
	}
}

//Shows the Written Detective Notes(with numbers, can be used as reference for removing them)
///to review text formatting(paragraf if too long)
void ShowWrittenNotes(Player *p) {
	notaPtr aux = p->DetNotes.head;
	if (aux != NULL)
	{
		while (aux != NULL) {
			printf("%d - ", aux->number);
			printf("%c", aux->text);
			aux = aux->next;
			printf("\n\n");
		}
	}
	else printf("NO WRITTEN NOTES WERE FOUND");
	
}

//Removes a Written Detective Note(receives the number)
notaPtr RemoveWrittenNotes(Player *p, int number) {
	notaPtr aux = p->DetNotes.head;
	notaPtr aux2 = NULL;
	if (p->DetNotes.head->number = number) {
		aux2 = p->DetNotes.head;
		p->DetNotes.head = aux->next;
		free(aux2);
	}
	else {
		while (aux != NULL && aux->next->number != number) {
			aux = aux->next;
		}
	}

	if (aux->next->number == number) {
		aux2 = aux->next;
		aux->next = aux->next->next;
		free(aux2);
	}
}

//Serches written Note by number
void ShowWrittenNotesByNumber(Player *p, int number) {
	notaPtr aux = p->DetNotes.head;
	while(aux != NULL && aux->number != number){
		aux = aux->next;
	}

	if (aux->number == number) {
		printf("%d - ", aux->number);
		printf("%c", aux->text);
	}
	else {
		printf("WRITTEN NOTE NOT FOUND");
	}
}



///Prints and edits the marks in the detective notes table for the player
//Associates the various marks with symbols/letters to use
string MarkPrinterSystem(enum DetNotesMarks m) {
	string mark;
	switch (m) {
	case 1:
		mark = (" ");
		break;
	case 2:
		mark = ("X");
		break;
	case 3:
		mark = ("V");
		break;
	case 4:
		mark = ("?");
		break;
	case 5:
		return ("!");
		break;
	default:
		break;
	}
	return mark;
}

//Prints the marks in a table
///table format
void PrintDetectiveNotes(Player *p) {
	int i, j;

	//Prints suspects and marks
	printf("Suspects     ");
	for (i = 0; i < lengthof(Susp); i++) {
		printf("  %c  |", PlayingPiece[i]);
	}
	printf("\n");
	for (i = 0; i < lengthof(Susp); i++) {
		printf("%c | ", PlayingPiece[i]);
		for (j = 0; j < lengthof(NumPlayers); j++) {
			printf("  %c  |", MarkPrinterSystem(p->DetNotes.SuspMarks[i][j]));
		}
		printf("\n");
	}

	//Prints weapons and marks
	printf("Weapons       ");
	printf("\n");
	for (i = 0; i < lengthof(Wep); i++) {
		printf("  %c  |", Weapons[i]);
		for (j = 0; j < lengthof(NumPlayers); j++) {
			printf("  %c  |", MarkPrinterSystem(p->DetNotes.WepMarks[i][j]));
		}
		printf("\n");
	}

	//Prints rooms and marks
	printf("Rooms         ");
	printf("\n");
	for (i = 0; i < lengthof(Room); i++) {
		printf("  %c  |", Roomys[i]);
		for (j = 0; j < lengthof(NumPlayers); j++) {
			printf("  %c  |", MarkPrinterSystem(p->DetNotes.RoomMarks[i][j]));
		}
		printf("\n");
	}

}

//Edits the Marks on the Detective Notes of a chosen table(Suspect Table, Weapon Table or Room Table)
DetectiveNotes EditDetectiveNotes(Player *p, enum DetNotesMarks m, int t, int i, int j) {
	//t is the number corresponding to each par of the table(1 is SuspMarks, 2 is WepMarks, 3 is RoomMarks)

	switch (t) {
	case 1:
		p->DetNotes.SuspMarks[i][j] = m;
		break;
	case 2:
		p->DetNotes.WepMarks[i][j] = m;
		break;
	case 3:
		p->DetNotes.RoomMarks[i][j] = m;
		break;
	default:
		break;
	}
}

#pragma endregion

//All things related to shuffling and giving card to the players
#pragma region CardDeliverance

///Shuffles the cards
//Function used by the shuffle function in order to swap two cards
void Swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

//Shuffles an array of cards
void Shuffle(Card arr[], int seed)
{
	for (int i = 0; i < lengthof(arr); i++)
	{
		seed++;

		// Picks a random index from 0 to the last index of the array
		int j = rand() % lengthof(arr);
		
		// Swaps arr[i] with the element at random index
		Swap(&arr[i], &arr[j]);
	}
}


///Gives out the cards to the murder envelope and the player
//Puts the cards in the murder envelope and sets the available variable in them as false so that they won't be given to any player
void CardsToMurderEnvelope(MurderEnvelopePtr envelope, Card SuspCards[], Card WepCards[], Card RoomCards[], int seed) {
	int r;
	seed++;
	Shuffle(SuspCards, seed);
	seed++;
	Shuffle(WepCards, seed);
	seed++;
	Shuffle(RoomCards, seed);
	seed++;
	r = rand() % Susp;
	envelope->SuspectCard = SuspCards[r];
	SuspCards[r].available = FALSE;
	seed++;
	r = rand() % Wep;
	envelope->WeaponCard = WepCards[r];
	WepCards[r].available = FALSE;
	seed++;
	r = rand() % Room;
	envelope->RoomCard = RoomCards[r];
	RoomCards[r].available = FALSE;
}

//Copies all the remaining cards(18) to an array(the deck), if available on the card is set to TRUE
void PutCardsInDeck(Card AllCards[], Card SuspCards[], Card WepCards[], Card RoomCards[]) {
	int i = 0, 
		j = 0,
		k = Susp - 1, 
		l = Susp + Wep - 2;
	//j vai ser o indice de todos os arrays que vão ser copiados
	while(j < Room){
		//
		if (i < (Susp - 1) && j < Susp && SuspCards[j].available == TRUE) {
			AllCards[i] = SuspCards[j];
			i++;
		}
		if (k < (Susp + Wep - 2) && j < Wep && WepCards[j].available == TRUE) {
			AllCards[k] = WepCards[j];
			k++;
		}
		if (l < All &&  RoomCards[j].available == TRUE) {
			AllCards[l] = RoomCards[j];
			k++;
		}
		j++;
	}
}

//Gives the remaining 18 cards to the players. Shuffles them and then deals them to the players, giving one at a time to each player
//One Card to Player 1, one to Player 2, one to Player 3, then another to player 1, etc. until every card is dealt
void CardsToPlayers(Player *p, Player *q, Player *r, Card AllCards[], int seed) {
	int i, j;
	seed++;
	Shuffle(AllCards, seed);
	for (i = 0, j = 0; i < PlCards, j < All; i++, j+3){
		p->PlayerCards[i] = AllCards[j];
		q->PlayerCards[i] = AllCards[j + 1];
		r->PlayerCards[i] = AllCards[j + 2];
	}
}
#pragma endregion