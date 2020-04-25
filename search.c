#include "card.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
struct Card_Entry {
		char name[30];
		int offset;
} typedef entry;

void PrintCard(int offset){

	FILE *cards_file;
	cards_file = fopen("cards.bin","rb");

	fseek(cards_file,offset,SEEK_CUR);		//Seek to offset of the card
	
	//READ CARD INFO FROM FILE
	int length = 0;
	int id;
	int converted_cost;
	enum Rarity rarity;

	char *rare_names[] = {"Common","Uncommon","Rare","Mythic"};
	
	fread(&id,sizeof(int),1,cards_file);		//Read the id
	fread(&length,sizeof(int),1,cards_file);	//Read the length of name
	char name[length];
	fread(&name,length,1,cards_file);		//Read name
	
	fread(&length,sizeof(int),1,cards_file);	//Read the length of cost
	char cost[length];
	fread(&cost,length,1,cards_file);		//Read cost

	fread(&converted_cost,sizeof(int),1,cards_file);	//Read converted cost
	
	fread(&length,sizeof(int),1,cards_file);	//Read length of type
	char type[length];
	fread(&type,length,1,cards_file);		//Read type

	fread(&length,sizeof(int),1,cards_file);	//Read length of text
	char text[length];
	fread(&text,length,1,cards_file);		//Read text

	fread(&length,sizeof(int),1,cards_file);	//Read length of stats
	char stats[length];
	fread(&stats,length,1,cards_file);		//Read stats

	fread(&rarity,sizeof(int),1,cards_file);	//Read rarity

	printf("\n\n%-30s%20s\n%-40s%10s\n%s\n%s\n%s\n%50d\n\n\n", name, cost,type, rare_names[rarity],"--------------------------------------------------",text,"--------------------------------------------------",converted_cost);
}

int BinarySearch(char* name, entry* cards, int low, int high){

	if (high >= low) { 
        int mid = low + (high - low) / 2;
	char* match = cards[mid].name;

        if (strcmp(name,match) == 0) {		//If name matches return
		return mid;
	}
            
        if (strcmp(name,match) < 0) {		//If name is lower return binary search with the lower half
		return BinarySearch(name, cards, low, mid - 1); 
	}
 	if (strcmp(name,match) > 0) {		//If name is higher return binary search with the upper half
		 return BinarySearch(name, cards, mid + 1, high); 
	}

    	} 
  
    return -1;

}


int main(int argc, char* argv[]) {
	
	
	FILE *index_file;
	index_file = fopen("index.bin","rb");

	entry* cards = malloc(1415 * sizeof(entry));

	for(int i = 0; i < 1415; i++) {    		
		int length = 0;
		int offset = 0;
		fread(&length,sizeof(int),1,index_file);	//Read length of name
		char named[length];
		
		fread(named,length,1,index_file);		//Read name
		fread(&offset,sizeof(int),1,index_file);	//Read offset
	
		entry some_card;
		cards[i] = some_card;
		strncpy(some_card.name, named, length);		//String copy name into card name
		some_card.offset = offset;			//Connect card offset and offset
	}

	char input[40];
	printf("> ");
	gets(input);
	int result;
	result = BinarySearch(input, cards, 0, 1414);
	if (result != -1){
		PrintCard(cards[result].offset);
	}
	if (result == -1 && strcmp(input,"q") != 0) {
		printf("No results found for '%s'\n\n",input);
	}
	
	
	while (strcmp(input,"q") > 0 || strcmp(input,"q") < 0){
		printf("> ");
		gets(input);
		int result;
		result = BinarySearch(input, cards, 0, 1414);
		if (result != -1){
		PrintCard(cards[result].offset);
	}
	if (result == -1 && strcmp(input,"q") != 0) {
		printf("No results found for '%s'\n\n",input);
	}
	
	
	}

	free(cards);
	return 0;
}

