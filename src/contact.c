#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "contact.h"

/*
  Affiche les contacts contenue dans la liste chainée.
*/
void afficher(struct contact *cell) {
    struct contact *cont = cell;
    while (cont != NULL) {
        printf("%s -> %s // ", cont->nom, cont->num);
        cont = cont->suiv;
    };
}

/*
  Insére un nouveau contact dans la liste chainée donnée en paramètre.
*/
void inserer_tete(struct contact **pl, const char * name, const char * numero)
{
    struct contact *liste = (struct contact *) malloc(sizeof(struct contact));
    assert(liste != NULL);
    liste->nom = (char *) name;
    liste->num = (char *) numero;
    liste->suiv = *pl;
    *pl = liste;
}

/*
  Supprime le contact dont le nom est donné en paramètre.
*/
int supprimer(struct contact **cell, const char *name) {
    struct contact sentinelle = {"0", "0", *cell};
    struct contact *contact_courant = &sentinelle;
    while (contact_courant->suiv != NULL) {
        if (strcmp(contact_courant->suiv->nom, name) == 0) {
            contact_courant->suiv = contact_courant->suiv->suiv;
            *cell = sentinelle.suiv;
            return 0;
        };
        contact_courant = contact_courant->suiv;
    };
    *cell = sentinelle.suiv;
    return 1;
}

