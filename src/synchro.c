#include "synchro.h"
#include "ensitheora.h"

#include <semaphore.h> 

bool fini;

/* les variables pour la synchro, ici */

sem_t *semaphore_taille_fenetre;
sem_t *semaphore_fenetre_texture;
sem_t *semaphore_texture_vide;
sem_t *semaphore_texture_plein;
pthread_mutex_t *mutex_consommer_texture;
pthread_mutex_t *mutex_deposer_texture;

// https://www.theora.org/doc/libtheora-1.0/structth__img__plane.html
struct th_img_plane * TailleFenetre;


void semaphores_init() {
	sem_init(semaphore_taille_fenetre, 0, 0);
	sem_init(semaphore_fenetre_texture, 0, 0);
	sem_init(semaphore_texture_vide, 0, NBTEX);
	sem_init(semaphore_texture_plein, 0, 0);
}

void semaphores_destroy(){
	sem_destroy(semaphore_taille_fenetre);
	sem_destroy(semaphore_fenetre_texture);
	sem_destroy(semaphore_texture_vide);
	sem_destroy(semaphore_texture_plein);
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
	sem_wait(semaphore_texture_plein);
	pthread_mutex_lock(mutex_consommer_texture);
}

void finConsommerTexture() {
	pthread_mutex_unlock(mutex_consommer_texture);
	sem_post(semaphore_texture_vide);
}


void debutDeposerTexture() {
	sem_wait(semaphore_texture_vide);
	pthread_mutex_lock(mutex_deposer_texture);
}

void finDeposerTexture() {
	pthread_mutex_unlock(mutex_deposer_texture);
	sem_post(semaphore_texture_plein);
}
