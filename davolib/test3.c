#include "davolib.h"

int main(){

	char *result[getNumDirElems(".")];


	printf("%d/n", getNumDirElems("."));

	lsFilesDirTree(".", result, 0);
	
	for (int i=0; i< getNumDirElems("."); i++) {
		printf("/n%s", *(result + i));	
	}

	return 0;

}
