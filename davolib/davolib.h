#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct string {
	size_t length;
	char *data;
} string_t;

#define init_array(T) ( memset((T), 0, sizeof((T))) )

void _pause();

string_t* create_string(const char *str);
void append_string(string_t *s, const char *toAdd);
int substring_occurrences(char *str, const char * sub);
void split_string(char *str, const char *delim, char** array);
void update_string(string_t* s, const char *newStr);

int readWholeFile(const char *filePath, char **buf);
int appendFileToFile(const char *toAppendPath, const char *dstPath);
int getOutput(const char *filePath, char const *argv[], char *buf, int bufSize);