#include "card.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

bool isDuplicate = false;
int result = 0;

void swap(CARD **x, CARD **y) 
{ 
    CARD** temp = *x; 
    *x = *y; 
    *y = temp; 
} 
void WriteToFiles(CARD** pointers_to_cards, int cardCounter){


	FILE *index_file;
	FILE *cards_file;
	char* buf[100];
	

	//INDEX FILE
	
	index_file = fopen("index.bin","wb");  // w for write, b for binary
	cards_file = fopen("cards.bin","wb");
	int offset = 0;

	for (int index=0; index < cardCounter; index++) {

		char* name = pointers_to_cards[index]->name;
		int name_length = strlen(name) + 1;

		fwrite(&name_length,sizeof(int),1,index_file);
		fwrite(name,name_length,1,index_file);
		fwrite(&offset, sizeof(int),1,index_file);

		//WRTIE TO CARD FILE

		int id = pointers_to_cards[index]->id;
		char* cost = pointers_to_cards[index]->cost;
		int converted_cost = pointers_to_cards[index]->converted_cost;
		char* type = pointers_to_cards[index]->type;
		char* text = pointers_to_cards[index]->text;
		char* stats = pointers_to_cards[index]->stats;
		int rarity = pointers_to_cards[index]->rarity;

		fwrite(&id,sizeof(int),1,cards_file);
		offset = offset + sizeof(int);

		int length = strlen(name) + 1;
		fwrite(&length,sizeof(int),1,cards_file);
		fwrite(name,length,1,cards_file);
		offset = offset + sizeof(int);
		offset = offset + length;
		
		length = strlen(cost) + 1;
		fwrite(&length,sizeof(int),1,cards_file);
		fwrite(cost,length,1,cards_file);
		offset = offset + sizeof(int);
		offset = offset + length;

		fwrite(&converted_cost,sizeof(int),1,cards_file);
		offset = offset + sizeof(int);
	
		length = strlen(type) + 1;
		fwrite(&length,sizeof(int),1,cards_file);
		fwrite(type,length,1,cards_file);
		offset = offset + sizeof(int);
		offset = offset + length;

		length = strlen(text) + 1;
		fwrite(&length,sizeof(int),1,cards_file);
		fwrite(text,length,1,cards_file);
		offset = offset + sizeof(int);
		offset = offset + length;

		length = strlen(stats) + 1;
		fwrite(&length,sizeof(int),1,cards_file);
		fwrite(stats,length,1,cards_file);
		offset = offset + sizeof(int);
		offset = offset + length;
		
		
		fwrite(&rarity,sizeof(int),1,cards_file);
		offset = offset + sizeof(int);
	
	}

	fclose(index_file);
	fclose(cards_file);
	
}

void SortArray(CARD **pointers_to_cards, int cardCounter){
	

	int i, j; 
   	for (i = 0; i < cardCounter; i++){       
       		// Last i elements are already in place    
       		for (j = 0; j < cardCounter-i-1; j++) { 
           		if (strcmp(pointers_to_cards[j]->name, pointers_to_cards[j+1]->name) > 0) {
              			swap((pointers_to_cards + j), ((pointers_to_cards) + j + 1));
			}
		}
	}
       

}
void FreePointers(CARD **pointers_to_cards, int cardCounter){

	for (int index=0; index < cardCounter; index++){
	
		free(pointers_to_cards[index]->name);
		free(pointers_to_cards[index]->cost);
		free(pointers_to_cards[index]->type);
		free(pointers_to_cards[index]->text);
		free(pointers_to_cards[index]->stats);
		free(pointers_to_cards[index]);

	}

	free(pointers_to_cards);



}

int CheckDuplicate(CARD **pointers_to_cards, char* name, int cardCounter){

	for (int index=0; index < cardCounter; index++){
      		if (strcmp(pointers_to_cards[index]->name, name) == 0){
			return 0;
		
		}
   	}
	
	return 1;

}

int main (int argc, char* argv[]){

	char *buf = malloc(1024);		
	char temp[1024];		//temporary buffer for manipulation
	int twoQuotes = 0;		//bool for two quotes
	int tempPos = 0;		//temp buf tracker
	int i = 0;
	int column = 0;			//which column its in
	int pointerPos = 0;
	int cardCounter = 0;
	int startingAmount = 100;
	
	CARD **pointers_to_cards = malloc(startingAmount * sizeof(CARD*));

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
		
		do{
			temp[tempPos++] = buf[i];
			
			//If card counter is more than starting amount reallocate more memory

			if(cardCounter >= startingAmount){
				startingAmount += 50;
				pointers_to_cards = realloc(pointers_to_cards, 					startingAmount*sizeof(CARD));
			}

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
						result = CheckDuplicate(pointers_to_cards,temp,cardCounter);
						if (result == 0) {
							isDuplicate = true;
						}
						else {
							some_card->name = malloc(strlen(temp) + 1);
							strncpy(some_card->name, temp, strlen(temp) + 1);
						}
						
					
						break;
					case 2:
						some_card->cost = malloc(strlen(temp) + 1);
						strncpy(some_card->cost, temp, strlen(temp) + 1);
						break;
					case 3:
						some_card->converted_cost = atoi(temp);
						break;
					case 4:
						some_card->type = malloc(strlen(temp) + 1);
						strncpy(some_card->type, temp, strlen(temp) + 1);
						break;
					case 5:
						some_card->text = malloc(strlen(temp) + 1);
						strncpy(some_card->text, temp, strlen(temp) + 1);
						break;
					case 6:
						some_card->stats = malloc(strlen(temp) + 1);
						strncpy(some_card->stats, temp, strlen(temp) + 1);
						break;
					case 7:
						if(strncmp("common", temp, 6) == 0){
							some_card->rarity = 0;
						}
						if(strncmp("uncommon", temp, 8) == 0){
							some_card->rarity = 1;
						}
						if(strncmp("rare", temp, 4) == 0){
							some_card->rarity = 2;
						}
						if(strncmp("mythic", temp, 6) == 0){
							some_card->rarity = 3;
						}
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

		if (isDuplicate == false){
			cardCounter++;
			pointerPos++;
		}
		else {
			isDuplicate = false;
		}
		
		
	
	}
	
	SortArray(pointers_to_cards, cardCounter);
	WriteToFiles(pointers_to_cards, cardCounter);
	FreePointers(pointers_to_cards, cardCounter);
	fclose(csv);
	free(buf);
	return 0;
}
