all: parser search
	
parser : parser.c 
	gcc -o parser parser.c -g
	./parser cards.csv
search : search.c
	gcc -o search search.c -g
	./search
.PHONY : all clean
clean: 
	rm parser
	rm search
	rm cards.bin
	rm index.bin
