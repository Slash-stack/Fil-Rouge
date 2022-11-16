#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <directory.h>
#include <contact.h>
#include <hash.h>

/*
  Crée un nouvel annuaire contenant _len_ listes vides.
*/
struct dir *dir_create(uint32_t len)
{
    struct dir *annuaire = (struct dir *) malloc(sizeof(struct dir));
    annuaire->taille = len;
    annuaire->nb_contact = 0;
    annuaire->tab = (struct contact **) calloc(annuaire->taille, sizeof(struct contact **));
    uint32_t i = 0;
    while (i < len) {
      annuaire->tab[i] = NULL;
      i++;
    };
    return annuaire;
}

/*
  Insère un nouveau contact dans l'annuaire _dir_, construit à partir des nom et
  numéro passés en paramètre. Si il existait déjà un contact du même nom, son
  numéro est remplacé et la fonction retourne une copie de l'ancien numéro.
  Sinon, la fonction retourne NULL.
*/
char *dir_insert(struct dir *dir, const char *name, const char *num)
{
    uint32_t res_hash = hash(name) % dir->taille;
    struct contact *contact_courant = dir->tab[res_hash];
    char *ancien_num;

    // Vérification de si le contact est déjà présent dans l'annuaire
    
    while (contact_courant != NULL) {
        if (strcmp(contact_courant->nom, name) == 0) {
            ancien_num = (char *) contact_courant->num;
            contact_courant->num = (char *) num;
            return ancien_num;
        }
        contact_courant = contact_courant->suiv;
    }

    dir->nb_contact++;

    if (dir->nb_contact >= 0.75 * dir->taille) {

      // Agrandissement du directory grâce à la création d'un nouveau tableau

      uint32_t new_taille = 2 * dir->taille;
      struct contact **new_tab = (struct contact **) calloc(new_taille, sizeof(struct contact **));
      uint32_t i = 0;
      while (i < new_taille) {
        new_tab[i] = NULL;
        i++;
      };
      for (uint32_t i = 0; i < dir->taille; i++) {
        struct contact *cont = dir->tab[i];
        while (cont != NULL) {
          uint32_t new_hash = hash(cont->nom) % (new_taille);
          inserer_tete(&new_tab[new_hash], cont->nom, cont->num);
          cont = cont->suiv;
        }
      }
      uint32_t new_hash = hash(name) % (new_taille);
      inserer_tete(&new_tab[new_hash], name, num);
      dir->taille = new_taille;
      dir->tab = new_tab;
      return NULL;

    } else {

      // Insertion du contact sans agrandissement

      inserer_tete(&dir->tab[res_hash], name, num);
      return NULL;
    }
}

/*
  Retourne le numéro associé au nom _name_ dans l'annuaire _dir_. Si aucun contact
  ne correspond, retourne NULL.
*/
const char *dir_lookup_num(struct dir *dir, const char *name)
{
    uint32_t index = hash(name) % dir->taille;
    struct contact *contact_courant = dir->tab[index];
    while (contact_courant != NULL) {
      if (contact_courant->nom == name) {
        return contact_courant->num;
      }
      contact_courant = contact_courant->suiv;
    }
    return NULL;
}

/*
  Supprime le contact de nom _name_ de l'annuaire _dir_. Si aucun contact ne
  correspond, ne fait rien.
*/
void dir_delete(struct dir *dir, const char *name)
{
  // Suppression du contact
    uint32_t index = hash(name) % dir->taille;
    int supp = supprimer(&dir->tab[index], name);
    if (supp == 0) {
      dir->nb_contact--;
    }

    if (dir->taille >= 10 && dir->nb_contact <= 0.15 * dir->taille) {

      //Rétrecissement du directory grâce à la création d'un nouveau tableau

      uint32_t new_taille = (dir->taille / 2 <= 10) ? 10 : dir->taille / 2;
      struct contact **new_tab = (struct contact **) calloc(new_taille, sizeof(struct contact **));
      uint32_t i = 0;
      while (i < new_taille) {
        new_tab[i] = NULL;
        i++;
      };
      for (uint32_t i = 0; i < dir->taille; i++) {
        struct contact *cont = dir->tab[i];
        while (cont != NULL) {
          uint32_t new_hash = hash(cont->nom) % (new_taille);
          inserer_tete(&new_tab[new_hash], cont->nom, cont->num);
          cont = cont->suiv;
        }
      }
      dir->taille = new_taille;
      dir->tab = new_tab;
    }
}

/*
  Libère la mémoire associée à l'annuaire _dir_.
*/
void dir_free(struct dir *dir)
{
    free(dir);
}

/*
  Affiche sur la sortie standard le contenu de l'annuaire _dir_.
*/
void dir_print(struct dir *dir)
{
    for (uint32_t i = 0; i < dir->taille; i++) {
      afficher(dir->tab[i]);
    };
    printf("\n");
}
