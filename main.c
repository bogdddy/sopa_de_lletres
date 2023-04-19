#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "sopa_de_lletres.h"

// llegir paraules del fitxer i guardar en sopa->paraules
void llegir_fitxer(sopa_t *s){

        FILE *f;
        char const *nom = "paraules.txt";
        f = fopen(nom, "r");
        char paraula[MAX_LLETRES + 1];
        

        if (f == NULL) fprintf(stderr, "error al obrir el fitxer %s\n", nom);
        else {

            int i=0;
            while (fgets(paraula, MAX_LLETRES + 1 , f)) {
                // printf("%s", paraula);
                s->paraules[i] = (paraula_t) { .ll = "", .enc = false };
                strcpy( s->paraules[i].ll, paraula);
                i++;
            }

            s->n_par = i+1;

        }
        
        fclose(f);

}

/* Aquesta funcio genera la sopa de lletres, a partir del fitxer i altres parametres */
/* que ja decidireu. En aquest cas només l'emplena amb una SOPA d'EXEMPLE, es a dir */
/* que haureu de fer la vostra pròpia. */
void genera_sopa(sopa_t *s)
{
    s->dim = 30;    // Mida màxima: 40 x 40
    s->lletres = malloc(s->dim * s->dim * sizeof(char));   // Espai per a les lletres
    s->encertades = malloc(s->dim * s->dim * sizeof(char)); // Per saber si una lletra correspon a encert
    for (int i = 0; i < s->dim * s->dim; i++)
    {
        s->encertades[i] = false;
        // Generem una lletra aleatoriament
        s->lletres[i] = 'A' + (rand() % ('Z'-'A' + 1));
    }

    // 1 - generar_posicion()
    // 2 - comprueba_disponibilidad()
    // 3 - colocar_palabra()
    // 4 - repetir 1-3

    // s->n_par = 5;
    // strcpy(s->par[0].ll, "ALZINA");
    // strcpy(s->par[1].ll, "ARBUST");
    // strcpy(s->par[2].ll, "BOLET");
    // strcpy(s->par[3].ll, "CAMI");
    // strcpy(s->par[4].ll, "PEDRA");

    // s->n_encerts = 2;
    // s->par[0].enc = false;
    // s->par[1].enc = true;
    // s->par[2].enc = true;
    // s->par[3].enc = false;
    // s->par[4].enc = false;

    // // Ara posem un parell de paraules a la sopa com si s'haguessin encertat
    // s->lletres[5] = 'B'; s->encertades[5] = true;
    // s->lletres[6] = 'O'; s->encertades[6] = true;
    // s->lletres[7] = 'L'; s->encertades[7] = true;
    // s->lletres[8] = 'E'; s->encertades[8] = true;
    // s->lletres[9] = 'T'; s->encertades[9] = true;

    // s->lletres[65 + s->dim] = 'A'; s->encertades[65 + s->dim] = true;
    // s->lletres[65 + 2 * s->dim] = 'R'; s->encertades[65 + 2 * s->dim] = true;
    // s->lletres[65 + 3 * s->dim] = 'B'; s->encertades[65 + 3 * s->dim] = true;
    // s->lletres[65 + 4 * s->dim] = 'U'; s->encertades[65 + 4 * s->dim] = true;
    // s->lletres[65 + 5 * s->dim] = 'S'; s->encertades[65 + 5 * s->dim] = true;
    // s->lletres[65 + 6 * s->dim] = 'T'; s->encertades[65 + 6 * s->dim] = true;
    
}


/* Mostra la sopa de lletres pel terminal */
/* En principi, NO HAURIEU DE MODIFICAR AQUEST CODI SI NO TOQUEU LES ESTRUCTURES DE DADES*/
void mostra_sopa (sopa_t *s)
{
    // Mostrem els numeros de columna
    printf("\033[0;31m");   // Color 
    printf("  ");
    for (int i = 10; i < s->dim + 1; i+=10)
    {
        for (int j=0; j < 18; j++)
            printf(" ");
        printf(" %d", i/10);

    }

    printf("\n  ");   
    for (int i = 0; i < s->dim; i++)
    {   
        int p = (i % 10) + 1;
        p != 10 ? printf(" %d", p) : printf(" 0");
    }

    printf("\n");
    printf("\033[0m");  // Tornem al color per defecte


    // Mostrem les lletres. Cada lletra ocupa dos espais: 
    // Si correspon a un encert, es marca
    for (int i = 0; i < s->dim ; i++)
    {
        printf("\033[0;31m");   // Color 
        printf("%-2d", i + 1);  // Mostrar numero de linia
        printf("\033[0m");  // Tornem al color per defecte

        for (int j = 0; j < s->dim; j++)
        {
            if (s->encertades[i * s->dim + j]) 
            {
                printf("\033[0;42m");   // Color verd de fons
                printf(" %c", s->lletres[i * s->dim + j]);
                printf("\033[0m");  // Tornem al color per defecte
            }
            else
            {
                printf(" %c", s->lletres[i * s->dim + j]);
            }
        }
        printf("\n");
    }
    printf("\n");

    printf("Portes %d encerts.\n", s->n_encerts);
    printf("Paraules a trobar: %d\n", s->n_par - s->n_encerts);
    for (int i = 0; i < s->n_par; i++)
    {
        if (!s->paraules[i].enc)
            printf("%s\n", s->paraules[i].ll);
    }

}

int main() {

    sopa_t sopa;    // La sopa de lletres

    // genera_sopa(&sopa);     // La generem (exemple)

    // mostra_sopa(&sopa);      // La mostrem per pantalla


    return 0;
}