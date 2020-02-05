#include <stdio.h>

int main(int argc, char* argv[]) {
	
	char str[100];

   	printf( "> ");

	scanf("%s", str);

	while(str != "Quit"){

	printf("\n> ");

	scanf("%s", str);

	printf("%s",str);

	}



	return 0;

}
