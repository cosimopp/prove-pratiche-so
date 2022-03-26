/*
Rendete la vostra directory home inaccessibile ad altri utenti (sia in lettura che in esecuzione)
	sudo chmod 0700 ~/ oppure sudo chmod 0700 /home/matteo.manuelli

Si puo’ tenere una sola directory in /public che abbia come nome il vostro username e.g. “/public/giovanni.rossi” e che abbia permessi 700
	cd /public sudo mkdir matteo.manuelli sudo chmod 0700 ./matteo.manuelli
*/
/*
Sia dato questo programma hw.c:

#include <stdio.h>

int main(int argc, char*argv[]) {
	printf("hello world:");
	for(argv++, argv--; argc > 0; argv++, argc--) //se rimuovo "argv++, argv--" il risultato è lo stesso
		printf(" %s",*argv);
	printf("\n");
	return 0;
}

Il programma hw.c può essere compilato come libreria dinamica:
	gcc --shared -o hw.so hw.c

La libreria dinamica non è un eseguibile
	$ ./hw.so 1 2 3 4
	Segmentation fault

ma può essere caricata a tempo di esecuzione tramite dlopen. Scrivere un programma "lancia" in grado di eseguire il codice di hw.so
	$ ./lancia hw.so 1 2 3 4
	hello world: hw.so 1 2 3 4

(suggerimenti: dlopen non cerca nella directory corrente, occorre passare il path assoluto della libreria.
"main" in hw.so è una normale funzione: occorre cercare l'indirizzo della funzione main nella libreria
ed invocarla,)
*/
//gcc -o lancia ex1.c
#include <dlfcn.h> //man dlopen
#include <stdio.h>

void main(int argc, char const *argv[])
{
	if (argc < 2){
		fprintf(stderr, "usage: %s <file.so> ...\n", argv[0]);
		return 1;
	}
	//https://www.youtube.com/watch?v=_kIa4D7kQ8I
}
