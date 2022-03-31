#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct string {
	size_t length;
	char *data;
} string_t;

#define init_array(T) ( memset((T), 0, sizeof((T))) )

string_t* create_string(const char *str);
void append_string(string_t *s, const char *toAdd);
int substring_occurrences(string_t *s, const char * sub);
void split_string(string_t *s, const char *delim, char** array);
void update_string(string_t* s, const char *newStr);

void readWholeFile(const char *filePath, char *buf);
int getFileSize(const char *filePath);
int writeFromFileToFile(const char *srcPath, const char *dstPath);