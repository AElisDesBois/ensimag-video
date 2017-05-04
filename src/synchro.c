#include "synchro.h"
#include "ensitheora.h"

#include <semaphore.h> 

bool fini;

/* les variables pour la synchro, ici */

sem_t *semaphore_taille_fenetre;
// https://www.theora.org/doc/libtheora-1.0/structth__img__plane.html
th_ycbcr_buffer TailleFenetre;




void semaphores_init() {
	sem_init(semaphore_taille_fenetre, 0, 0);
}

void semaphores_destroy(){
	sem_destroy(semaphore_taille_fenetre);
}

/* l'implantation des fonctions de synchro ici */

void envoiTailleFenetre(th_ycbcr_buffer buffer) {
	TailleFenetre =  buffer;
	sem_post(semaphore_taille_fenetre);
}

void attendreTailleFenetre() {
	sem_wait(semaphore_taille_fenetre);
}

void signalerFenetreEtTexturePrete() {
}

void attendreFenetreTexture() {
}

void debutConsommerTexture() {
}

void finConsommerTexture() {
}


void debutDeposerTexture() {
}

void finDeposerTexture() {
}
