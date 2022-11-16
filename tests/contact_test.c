#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct contact 
{
    const char *nom;
    const char *num;
    struct contact *suiv;
};

void afficher(struct contact *cell) {
    struct contact *cont = cell;
    while (cont != NULL) {
        printf("%s -> %s // ", cont->nom, cont->num);
        cont = cont->suiv;
    };
    printf("\n");
}

const char* inserer(struct contact **cell, const char *name, const char *numero) {
    struct contact sentinelle = {"0", "0", *cell};
    struct contact *contact_courant = &sentinelle;
    while (contact_courant->suiv != NULL) {
        if (*contact_courant->nom == *name) {
            const char *ancien_num = contact_courant->num;
            contact_courant->num = numero;
            return ancien_num;
        };
        contact_courant = contact_courant->suiv;
    };
    contact_courant->suiv = malloc(sizeof(struct contact));
    contact_courant->suiv->nom = name;
    contact_courant->suiv->num = numero;
    contact_courant->suiv->suiv = NULL;
    *cell = sentinelle.suiv;
    return NULL;
}

int supprimer(struct contact **cell, const char *name) {
    struct contact sentinelle = {"0", "0", *cell};
    struct contact *contact_courant = &sentinelle;
    while (contact_courant->suiv != NULL) {
        if (*contact_courant->suiv->nom == *name) {
            contact_courant->suiv = contact_courant->suiv->suiv;
            return 0;
        };
    };
    *cell = sentinelle.suiv;
    return 1;
}

void main(void) {
    struct contact *cont = NULL;
    inserer(&cont, "Bennaceur Zerhouni", "0634379854");
    afficher(cont);
    inserer(&cont, "Bennaceur Zerhouni", "0634379855");
    afficher(cont);
}