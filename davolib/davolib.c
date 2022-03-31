#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct string {
	size_t length;
	char *data;
} string_t;
//we deal with strings!
//0 file 1 dir 2 exec
int whatTypeIsIt(const char *filePath){}

void getOutput(const char *filePath){}

//con queste funzioni è meglio controllare di volta in volta le varie aperture/interazioni con i file
int getFileSize(const char *filePath){

	// opening the file in read mode
    FILE *fp = fopen(filePath, "r");
  
    // checking if the file exist or not
    if (fp == NULL) {
        return 1;
    }
  	
  	//get current position
	long pos = ftell(fp);

    fseek(fp, 0L, SEEK_END);
  
    // calculating the size of the file
    long size = ftell(fp);
  
    //ripristino - fp temporaneo => ridondante
    fseek(fp, 0L, (int)pos);

    // closing the file
    fclose(fp);

    return (int)size;

}

int writeFromFileToFile(const char *srcPath, const char *dstPath){//append, non sovrascrive

	FILE *src = fopen(srcPath, "r");
	FILE *dst = fopen(dstPath, "a");

	if (src == NULL || dst == NULL){
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	int size = getFileSize(srcPath);
	char buf[size + 1]; //buffer temporaneo di appoggio
  	size_t len;
  	
  	while(fread(buf, sizeof(char), (size_t)size, src)){

		if(fwrite(buf, sizeof(char), (size_t)size, dst) != (size_t)size){
			perror("fwrite");
			exit(EXIT_FAILURE);
		}
    	printf("wrote %ld from %s to %s\n", (size_t)size, srcPath, dstPath);
  	}

  	fclose(src);
  	fclose(dst);

  	return 0;

}
void writeIntoFile(const char *filePath, char *data){

}

void _pause(){//aggiunto prefisso poichè anche unistd ha pause()
	printf("\nPress any key to continue . . .");
	getchar();
}

int readWholeFile(const char *filePath, char *buf){
	//http://www.fundza.com/c4serious/fileIO_reading_all/index.html
	/* declare a file pointer and open an existing file for reading*/
	FILE *fp = fopen(filePath, "r");

	/* quit if the file does not exist */
	if(fp == NULL){
    	return 1;
	}

	//get current position
	//long pos = ftell(fp); non necessario poichè è un fp temporaneo

	//The new position, measured in bytes, is obtained by adding offset bytes (0 long) to the position specified by whence (from what place or source.)
	fseek(fp, 0L, SEEK_END);//in order to get size
	
	//The ftell() function obtains the current value of the file position indicator for the stream pointed to by stream.
	long size = ftell(fp);

	fseek(fp, 0L, SEEK_SET); //necessario altrimenti non leggeva
	
	/* copy all the text into the buffer */
	fread(buf, sizeof(char), (size_t)size, fp); //The function fread() reads size items of data, each sizeof(char) bytes long,
    //from the stream pointed to by stream, storing them at the location given by buf.
	
	/* reset the file position indicator to the beginning of the file */
	//rewind(fp);//fseek(fp, 0L, SEEK_SET);
	//fseek(fp, 0L, (int)pos);

	fclose(fp);

	return 0;

}

//https://www.programiz.com/dsa/avl-tree *((int*)void_PTR)
//inizializzare array di stringhe => inizializza ogni stringa?
#define init_array(T) ( memset((T), 0, sizeof((T))) )

//every EDIT on data buffer should be carried out by davolib API in order to have up-to-date length
void update_string(string_t* s, const char *newStr){
	size_t len;
	if (newStr != NULL){
		len = strlen(newStr);
	} else {
		len = 0;
	}
	//liberiamo la precedente
	free(s->data);
	s->data = (char *)malloc(len + 1); //Because of NULL terminator
	if (newStr != NULL){
		memcpy(s->data, newStr, len);
	}
	s->data[len] = '\0'; //memory returned by malloc isn't initialized to 0. Setting the first byte of new string to zero ensures that it looks like an empty string
	s->length = len;
}

string_t* create_string(const char *str){
	string_t* s = malloc(sizeof(string_t)); //It returns a POINTER to the reserved space
	size_t len;
	if (str != NULL){
		len = strlen(str);
	} else {
		len = 0;
	}
	s->data = (char *)malloc(len + 1); //Because of NULL terminator
	if (str != NULL){
		memcpy(s->data, str, len);
	}
	s->data[len] = '\0'; //memory returned by malloc isn't initialized to 0. Setting the first byte of new string to zero ensures that it looks like an empty string
	s->length = len;
	return s;
}

void free_string(string_t *s){

}

//a differenza di strncpy, lo user non si deve preoccupare delle dimensioni della stringa dst
void append_string(string_t *s, const char *toAdd){ //https://stackoverflow.com/questions/5901181/c-string-append
	char *new = malloc(strlen(s->data) + strlen(toAdd) + 1); //strlen(s->data) anzichè s->length poichè l'utente può aver modificato s->data nel mentre
	new[0] = '\0';
    strcat(new, s->data);
    strcat(new, toAdd);
    size_t newLen = strlen(new);
    //liberiamo la precedente
    free(s->data);
    s->data = (char *)malloc(newLen + 1);
    memcpy(s->data, new, newLen);
    free(new);
    s->data[newLen] = '\0';
	s->length = newLen;
}

char *extract_substring_at(string_t *s, int startPos, int endPos){}

//inserts substring at position i into string
void insert_substring_at(string_t *s, const char *toInsert, int startPos){}
//removes substring from string
void remove_substring(string_t *s, const char *toRemove){}

//returns occurrences number of a single char in a string
int substring_occurrences(string_t *s, const char * sub){ //l'algoritmo ha costo O(n^2)(successione gaussiana) nel caso pessimo
	//non eseguo direttamente questo algoritmo per splittare la stringa perchè non so quanti token dovrò inserire nell'array
	char *str = s->data; //temp per comodità di lettura

	int i = 0, j = 0, k = 0, flag = 0, count = 0;
	for(i = 0 ; *(str + i) != '\0' ; i++){

		k = i; //k è una copia di i in caso ci "illudiamo" di aver trovato una sottostringa (e quindi incrementiamo i) e.g. main=aabc, sub=abc
		while((*(str + i) == *(sub + j)) && flag == 0){
			i++; j++; //se i caratteri coincidono i contatori avanzano assieme 
			
			if (strlen(sub) == j){
				count++; //un'occorrenza trovata
				flag = 1; //usciamo dal while
			}
		}
		j = 0;//ripristino contatore sottostringa
		if (flag == 0) i = k; //sottostringa non trovata
		else flag = 0; //cerca nuova sottostringa 
	}
	return count;
}
//fills given array with string tokens
void split_string(string_t *s, const char *delim, char** array){

	//e.g. 192.168.0.1 => 3 punti => 3+1 token. array 0 based
	/*Example
	#include "davolib.h"
	#include <stdio.h>
 	void main(){
 		string_t *str = create_string("192.168.0.1");
 		int len = substring_occurrences(str, ".") +1;
 		char *token[len];
 		split_string(str, ".", token);
 		for (int i = 0; i < len; i++){
 			printf("%s\n", *(token+i));
 		}
 	}
	*/

	char *str = s->data; //temp per comodità di lettura (strtok cambia offset di lettura?)

	//per non ricordarsi ogni volta di passare alla funzione anche la lunghezza dell'array da riempire
	int arrayLen = substring_occurrences(s, delim) +1;

	char *firstToken = strtok(str, delim); //"idiosincrasia" di strtok
	*(array + 0) = firstToken;


	for(int i = 1 ; i < arrayLen; i++){
		*(array + i) = strtok(NULL, delim); //strtok può avere più delim!
	}

}

//implementare stack, code e dizionari generici