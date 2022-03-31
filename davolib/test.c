#include "davolib.h"
#include <stdio.h>
 void main(){
 	string_t *str = create_string("192.168.0.1");
 	int len = substring_occurrences(str, ".") +1;
 	char *tokens[len];
 	split_string(str, ".", tokens);
 	for (int i = 0; i < len; i++){
 		printf("%s\n", *(tokens+i));
    }

    char contenuto[getFileSize("./dddd") +1];
    init_string_array(contenuto);
    readWholeFile("./dddd", contenuto);
    printf("%s\n", contenuto);

    writeFromFileToFile("./mondo.txt", "./ciao.txt");

 }