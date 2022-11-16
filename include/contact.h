#ifndef _CONTACT_H_
#define _CONTACT_H_

/*
  Un contact représente une association {nom, numéro, contact suivant}.
*/
struct contact 
{
    char *nom;
    char *num;
    struct contact *suiv;
};

/*
  Affiche les contacts contenue dans la liste chainée.
*/
extern void afficher(struct contact *cell);

/*
  Insére un nouveau contact dans la liste chainée donnée en paramètre.
*/
extern void inserer_tete(struct contact **,const char *,const char *);

/*
  Supprime le contact dont le nom est donné en paramètre.
*/
extern int supprimer(struct contact **cell, const char *name);

/* Profitez de cette période sombre pour braver les interdits et rétablir le contact. */

#endif /* _CONTACT_H_ */
