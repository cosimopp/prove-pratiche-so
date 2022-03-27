#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct string {
	size_t length;
	char *data;
} string_t;

string_t* create_string(const char *str);
void append_string(string_t *s, const char *toAdd);
int substring_occurrences(string_t *s, const char * sub);
void split_string(string_t *s, const char *delim, char** array);