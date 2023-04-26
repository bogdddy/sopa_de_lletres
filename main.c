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

    s->n_par = 5;
    strcpy(s->paraules[0].ll, "ALZINA");
    strcpy(s->paraules[1].ll, "ARBUST");
    strcpy(s->paraules[2].ll, "BOLET");
    strcpy(s->paraules[3].ll, "CAMI");
    strcpy(s->paraules[4].ll, "PEDRA");

    s->n_encerts = 2;
    s->paraules[0].enc = false;
    s->paraules[1].enc = true;
    s->paraules[2].enc = true;
    s->paraules[3].enc = false;
    s->paraules[4].enc = false;

    // Ara posem un parell de paraules a la sopa com si s'haguessin encertat
    s->lletres[5] = 'B'; s->encertades[5] = false;
    s->lletres[6] = 'O'; s->encertades[6] = false;
    s->lletres[7] = 'L'; s->encertades[7] = false;
    s->lletres[8] = 'E'; s->encertades[8] = false;
    s->lletres[9] = 'T'; s->encertades[9] = false;

    s->lletres[65 + s->dim] = 'A'; s->encertades[65 + s->dim] = true;
    s->lletres[65 + 2 * s->dim] = 'R'; s->encertades[65 + 2 * s->dim] = false;
    s->lletres[65 + 3 * s->dim] = 'B'; s->encertades[65 + 3 * s->dim] = false;
    s->lletres[65 + 4 * s->dim] = 'U'; s->encertades[65 + 4 * s->dim] = false;
    s->lletres[65 + 5 * s->dim] = 'S'; s->encertades[65 + 5 * s->dim] = false;
    s->lletres[65 + 6 * s->dim] = 'T'; s->encertades[65 + 6 * s->dim] = false;
    
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

int comparar_alfabeticamente(const void *paraula_a, const void *paraula_b)
{
    return strcmp(((paraula_t *)paraula_a)->ll, ((paraula_t *)paraula_b)->ll);
}

void ordenar_alfabeticamente(paraula_t paraules[], int n)
{
    qsort(paraules, n, sizeof(paraula_t), comparar_alfabeticamente);
}

int comparar_longitud(const void *paraula_a, const void *paraula_b)
{
    return strlen(((paraula_t *)paraula_a)->ll) - strlen(((paraula_t *)paraula_b)->ll);
}

void ordenar_longitud(paraula_t paraules[], int n)
{
    qsort(paraules, n, sizeof(paraula_t), comparar_longitud);
}

bool comprovar_encert(sopa_t* s, int fil, int col, int dir) {
   
    bool encert = false;

   for(int i=0;i<MAX_PARAULES; i++){
        if (!s->paraules[i].enc) {

            if (fil == s->paraules[i].x && col == s->paraules[i].y && dir == s->paraules[i].z) {
                s->n_encerts++;
                encert = true;
            }

        }
   }

   return encert;
}

void marcar_encert(sopa_t *s, paraula_t paraula){
    
    int lon = strlen(paraula.ll) -1;
    int start, end;
    
    for (int i=0; i<=lon; i++){

        if (paraula.z == UP || paraula.z == DOWN)
            s->encertades[s->dim * (paraula.x + i) + paraula.y] =  true;

        else 
            s->encertades[s->dim*paraula.y + paraula.x + i] =  true;

        
    }

}

int main() {

    sopa_t sopa;    // La sopa de 
    
    // paraules de prova
    paraula_t bolet, arbust;

    strcpy(bolet.ll, "BOLET");
    bolet.x = 5;
    bolet.y = 0;
    bolet.z = 2;
    
    strcpy(arbust.ll, "ARBUST");
    arbust.x = 3;
    arbust.y = 5;
    arbust.z = -1;

    genera_sopa(&sopa);     // La generem (exemple)

    mostra_sopa(&sopa);

    // check 
    marcar_encert(&sopa, bolet);
    marcar_encert(&sopa, arbust);
    
    mostra_sopa(&sopa);      

    return 0;
}