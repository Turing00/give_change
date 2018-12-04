#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

void Afficher (int, char *);

int main (int argc, char **argv)
{
    // somme transmise : sommeTotale
    // nombre de billets de 50
    int sommeTotale = atoi(argv[1]), nbreBillet50 = 0, nbreBillet20 = 0, nbreBillet10 = 0, k = 0;
    int val [4] = {50, 20, 12, 1};
    int *tab = NULL;
    tab = (int*)calloc(4, sizeof(int));

    Afficher (sommeTotale, (char*) "euros");
    printf ("\n");
    printf ("Pour %d euros :\n\n", sommeTotale);

    while (sommeTotale > 0)
    {
        while (val[k] > sommeTotale) k++;
        if (val[k] > (2 * val[k+1]) || (sommeTotale - val[k])%val[k+1] != 0 || (sommeTotale - val[k])%val[k+1] == 0)
        {
            tab[k]++;
            sommeTotale -= val[k];
        }
        else
        {
            tab[k+1]++;
            sommeTotale -= val[k+1];
        }
    }

    for(int i = 0; i < 4; ++i)
    {
        char *money = NULL;
        money = (char*) malloc(22);
        if (val[i] != 1)
        {
            if (tab[i] == 0 || tab[i] == 1)
               sprintf(money, "billet de %d euros", val[i]);
            else
               sprintf(money, "billets de %d euros", val[i]);
        }
        else
        {
            if (tab[i] == 0 || tab[i] == 1)
                sprintf(money, "piece de %d euros", val[i]);
            else
                sprintf(money, "pieces de %d euros", val[i]);
        }
        Afficher(tab[i], money);
    }

    // this is a naive implementation
    // while (sommeTotale != 0)
    // {
    //     if (sommeTotale >= 50)
    //     {
    //         sommeTotale -= 50;
    //         nbreBillet50++;
    //     }
    //     else if (sommeTotale >= 20 )
    //     {
    //         sommeTotale -= 20;
    //         nbreBillet20++;
    //     
    //     else
    //     {
    //         sommeTotale -= 10;
    //         nbreBillet10++;
    //     }
    // }

    // Afficher (nbreBillet50, "billets de 50 euros");
    // Afficher (nbreBillet20, "billets de 20 euros");
    // Afficher (nbreBillet10, "billets de 10 euros");
    return 0;
}

void Afficher (int value, char *message) {
    printf("Il y a %d %s\n", value, message);
}