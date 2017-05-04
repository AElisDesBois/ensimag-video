#include "synchro.h"
#include "ensitheora.h"

#include <semaphore.h> 

bool fini;

/* les variables pour la synchro, ici */

sem_t *semaphore_taille_fenetre;
sem_t *semaphore_fenetre_texture;

// https://www.theora.org/doc/libtheora-1.0/structth__img__plane.html
struct th_img_plane * TailleFenetre;


void semaphores_init() {
	sem_init(semaphore_taille_fenetre, 0, 0);
	sem_init(semaphore_fenetre_texture, 0, 0);
}

void semaphores_destroy(){
	sem_destroy(semaphore_taille_fenetre);
	sem_destroy(semaphore_fenetre_texture);
}

/* l'implantation des fonctions de synchro ici */

void envoiTailleFenetre(th_ycbcr_buffer buffer) {
	TailleFenetre = (struct th_img_plane *) buffer;
	sem_post(semaphore_taille_fenetre);
}

void attendreTailleFenetre() {
	sem_wait(semaphore_taille_fenetre);
}

void signalerFenetreEtTexturePrete() {
	sem_post(semaphore_fenetre_texture);
}

void attendreFenetreTexture() {
	sem_wait(semaphore_fenetre_texture);
}

void debutConsommerTexture() {
}

void finConsommerTexture() {
}


void debutDeposerTexture() {
}

void finDeposerTexture() {
}
