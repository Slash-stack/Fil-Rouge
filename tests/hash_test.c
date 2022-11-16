#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

uint32_t hash(const char *str)
{
    uint32_t i = 0, res_hash = 5381;
    char string = *str;
    while (str[i] != '\0') {
        res_hash = res_hash * 33 + str[i];
        i++;
    }
    return res_hash;
}

void main(void)
{
    printf("%d\n",hash("Colonel Moutarde"));
    printf("%d\n",hash("Caporal Ketchup"));
    printf("%d\n",hash("Sergent Mayo"));
}