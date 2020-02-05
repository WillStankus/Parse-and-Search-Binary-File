#include "card.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>

void PrintPointerArray(CARD **pointers_to_cards){

	char *rare_names[] = {"Common","Uncommon","Rare","Mythic"};
	
	
	size_t index;
	
	for (index=0; index <= 1612; index++){
      		printf("%-30s%20s\n%-40s%10s\n%s\n%s\n%s\n%50d\n\n\n", pointers_to_cards[index]->name, pointers_to_cards[index]->cost,pointers_to_cards[index]->type, "Rare","--------------------------------------------------",pointers_to_cards[index]->text,"--------------------------------------------------",pointers_to_cards[index]->converted_cost);
   	}
}
int sort_By_Name(const void *p1, const void *p2){
	
	CARD **a = (CARD **)p1;
	CARD **b = (CARD **)p2;
	printf("%s ... %s\n", (*a)->name, (*b)->name);
	return strcmp((*a)->name, (*b)->name);
}


void SortArray(CARD** pointers_to_cards){

	printf("Sort Array");
	
	qsort(pointers_to_cards, 1612, sizeof(CARD*), sort_By_Name);

}

void WriteToFiles(CARD** pointers_to_cards){


	FILE index_file;
	FILE cards_file;

	char* name;

	// INDEX FILE

	// CARDS FILE
	

}

int main (int argc, char* argv[]){

	char *buf = malloc(1024);
	//temporary buffer for manipulation
	char temp[1024];
	//bool for two quotes
	int twoQuotes = 0;
	//temp buf tracker
	int tempPos = 0;
	int i = 0;
	//which column its in
	int column = 0;
	int pointerPos = 0;
	CARD **pointers_to_cards = malloc(1612 * sizeof(CARD*));

	FILE *csv = fopen(argv[1],"r");

	if(!csv) {
		printf("ERROR\n");
		return -1;
	}

	char *line = fgets(buf,1024,csv);
	
	while (fgets(buf,1024,csv)){

		column = 0;
		i = 0;

		//Allocated memory for index of pointers and for the card itself
		pointers_to_cards[pointerPos] = malloc(sizeof(CARD));
		CARD *some_card = malloc(sizeof(CARD));

		//GET RID OF DUPLICATES HERE
		
		do{

			temp[tempPos++] = buf[i];

			//Connect both the memory addresses that were allocated
			pointers_to_cards[pointerPos] = some_card;

			
			if(!twoQuotes && (buf[i]) == ',' || buf[i] == '\n') {
				temp[tempPos - 1] = 0;
				tempPos = 0;
				switch (column){
					case 0:
						some_card->id = atoi(temp);
						break;
					case 1:
						some_card->name = malloc(strlen(temp) + 1);
						strncpy(some_card->name, temp, strlen(temp));
						break;
					case 2:
						some_card->cost = malloc(strlen(temp) + 1);
						strncpy(some_card->cost, temp, strlen(temp));
						break;
					case 3:
						some_card->converted_cost = atoi(temp);
						break;
					case 4:
						some_card->type = malloc(strlen(temp) + 1);
						strncpy(some_card->type, temp, strlen(temp));
						break;
					case 5:
						some_card->text = malloc(strlen(temp) + 1);
						strncpy(some_card->text, temp, strlen(temp));
						break;
					case 6:
						some_card->stats = malloc(strlen(temp) + 1);
						strncpy(some_card->stats, temp, strlen(temp));
						break;
					case 7:
						
						// Couldn't figure out enum
						break;
				}
				column++;
			}
			if(buf[i] == '"' && buf[i + 1] != '"'){
				tempPos--;
				twoQuotes = !twoQuotes;
			}
			if(buf[i] == '"' && buf[i + 1] == '"'){
				i++;
			}
			if(buf[i] == '\\' && buf[i + 1] == 'n'){
				i++;
				tempPos--;
				temp[tempPos++] = '\n';
			}
			
			
		}while(buf[++i]);

		
		//printf("%s\n", buf);
		//printf("%s\n",pointers_to_cards[pointerPos]->name);
		pointerPos++;
	
	}

	SortArray(pointers_to_cards);
	PrintPointerArray(pointers_to_cards);
	WriteToFiles(pointers_to_cards);
	
	return 0;
}

