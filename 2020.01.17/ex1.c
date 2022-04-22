/*
Scrivere un programma searchlink che dati due parametri (nell'ordine un file f ed una directory d)
metta in output l'elenco dei path all'interno dell'albero che ha radice in d che fanno riferimento ad f
o come link fisico o come link simbolico.

es:

searchlink myfile mydir
link a
link d/b
symlink e/s

significa che dir/a e dir/d/b si riferisono a f come link fisici mentre dir/e/s e' un link simbolico che punta ad f.
*/

#include "davolib.h"

int main(int argc, char const *argv[]){

	int len = getNumDirElems(argv[2]); //numero di file nella directory 
	char *list[len]; init_array(list);
	lsFilesDirTree()
	return 0;
}