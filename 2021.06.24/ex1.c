/*
Usando il metodo inotify implementare il programma dircat.
dircat ha 2 parametri: il pathname di una directory (vuota) D e di un file F.
Ogni volta che un file viene messo in D il programma dircat aggiunge a F una riga di testata
contenente il nome del file e ne copia il contenuto in F. Finita la copia il file che era stato messo in D
viene cancellato (la directory D torna vuota).
(per fare gli esperimenti si consiglia di preparare i file di prova in un'altra directory e copiarli in D).
*/
/*
completare dircat. Se il file aggiunto a D è un eseguibile dircat deve inserire in F dopo la riga di testata
l'output dell'esecuzione del nuovo file non già il suo contenuto. Completata l'esecuzione il file
eseguibile deve venir cancellato come nell'esercizio 1.
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>

void main(int argc, char const *argv[])
{
	if (argc != 3){
		fprintf(stderr, "usage: %s EMPTYDIRPATH LOGFILEPATH\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	/* Create the file descriptor for accessing the inotify API */
	int fd = inotify_init1(); //creates an inotify instance and returns a file descriptor referring to the inotify instance (everything is a file)
	FILE *logFile = fopen(argv[2], "a");
	inotify_add_watch(fd, argv[1], IN_CREATE); //controllo solo una directory => non c'è necessità di una watchList.
	//inoltre questa libreria freedda tutte le risorse associate all'istanza non appena la chiudiamo con close(fd).
	//La lista wd conterrebbe ID per identificare directory (tramite wd[i] == event->wd) quando si verifica un evento
	//L'identificativo è un descrittore all'evento di ogni directory: wd[i] = inotify_add_watch(fd, argv[i], IN_OPEN | IN_CLOSE); if (wd[i] == event->wd); //è avvenuto per quella directory

	//variabili usate per salvare e leggere l'evento (dovremo fare un casting per interpretare cosa abbiamo salvato)
	char buf[4096];
	size_t len;
	struct inotify_event *event;

	while (1){
		len = read(fd, buf, sizeof(buf));
		if (len == -1 && errno != EAGAIN) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        //If the nonblocking read() found no events to read, then it returns -1 with errno set to EAGAIN. EAGAIN = Resource temporarily unavailable
      	if (len == -1 && errno == EAGAIN) continue; //found no events to read
      	
      	/* Loop over all events in the buffer */
      	for (char *ptr = buf; ptr < buf + len; ptr += sizeof(struct inotify_event) + event->len){

      		event = (const struct inotify_event *) ptr;
        	
        	if(event->mask & IN_ISDIR || !event->len) continue;
        	fprintf(logFile, "%s: ", event->name);
      	}
	

	}

}	