#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>


/*
  Renvoie un entier calculé à partir d'une chaîne de caractères
*/
uint32_t hash(const char *str)
{
    uint32_t i = 0, res_hash = 5381;
    while (str[i] != '\0') {
        res_hash = res_hash * 33 + str[i];
        i++;
    }
    return res_hash;
}
