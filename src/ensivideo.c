#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <pthread.h>
#include "synchro.h"

#include "stream_common.h"
#include "oggstream.h"


int main(int argc, char *argv[]) {
    int res;

    if (argc != 2) {
	   fprintf(stderr, "Usage: %s FILE", argv[0]);
	   exit(EXIT_FAILURE);
    }
    assert(argc == 2);


    // initialisation des semaphores
    semaphores_init();



    // Initialisation de la SDL
    res = SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_EVENTS);
    atexit(SDL_Quit);
    assert(res == 0);
    
    // start the two stream readers
    void * status;
    pthread_t theora_pid, vorbis_pid;
    pthread_create(&theora_pid, NULL, theoraStreamReader, (void *)argv[1]);
    pthread_create(&vorbis_pid, NULL, vorbisStreamReader, (void *)argv[1]);
    
    // TODO

    // wait audio thread
    pthread_join(vorbis_pid, &status);

    // 1 seconde de garde pour le son,
    sleep(1);

    // TODO
    // tuer les deux threads videos si ils sont bloqués
    pthread_cancel(theora_pid);
    pthread_cancel(theora2sdlthread);

    // attendre les 2 threads videos
    pthread_join(theora_pid, &status);
    pthread_join(theora2sdlthread, &status);

    // nettoyage des semaphores
    semaphores_destroy();
    
    exit(EXIT_SUCCESS);    
}
