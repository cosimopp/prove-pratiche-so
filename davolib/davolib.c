#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct string {
	size_t length;
	char *data;
} string_t;

void _pause(){//aggiunto prefisso poichè anche unistd ha pause()
	printf("\nPress any key to continue . . .");
	getchar();
}

//https://www.programiz.com/dsa/avl-tree *((int*)void_PTR)
//inizializzare array di stringhe => inizializza ogni stringa?
#define init_array_of_strings(T) ()
#define TIME_CONVERT(T) ((T) * (*((memaddr *) TIMESCALEADDR)))

//every EDIT on data buffer should be carried out by davolib API in order to have up-to-date length
void update_string(const char *str, const char *newStr){}

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

void append_string(string_t *s, const char *toAdd){ //https://stackoverflow.com/questions/5901181/c-string-append
	char *new = malloc(strlen(s->data) + strlen(toAdd) + 1); //strlen(s->data) anzichè s->length poichè l'utente può aver modificato s->data nel mentre
	new[0] = '\0';
    strcat(new, s->data);
    strcat(new, toAdd);
    size_t newLen = strlen(new);
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