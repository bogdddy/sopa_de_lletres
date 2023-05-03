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

    s->paraules[2].x = 5;
    s->paraules[2].y = 0;
    s->paraules[2].z = 2;

    s->n_encerts = 2;
    s->paraules[0].enc = false;
    s->paraules[1].enc = false;
    s->paraules[2].enc = false;
    s->paraules[3].enc = false;
    s->paraules[4].enc = false;

    // Ara posem un parell de paraules a la sopa com si s'haguessin encertat
    s->lletres[5] = 'B'; s->encertades[5] = false;
    s->lletres[6] = 'O'; s->encertades[6] = false;
    s->lletres[7] = 'L'; s->encertades[7] = false;
    s->lletres[8] = 'E'; s->encertades[8] = false;
    s->lletres[9] = 'T'; s->encertades[9] = false;

    s->lletres[65 + s->dim] = 'A'; s->encertades[65 + s->dim] = false;
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

void preguntar_tamany(sopa_t *s) {
    int tamany;
    
    do {
        printf("El tamany de la taula ha de ser de 10x10 fins a 40x40, quina mida vols?");
        scanf("%d", tamany);
    } while (MAX_TAMANY_TAULER < tamany || tamany < MIN_TAMANY_TAULER);
    
    s->dim = tamany;
}

void crear_taules(sopa_t *s) {
    s->lletres = malloc(s->dim * s->dim * sizeof(char));   // Espai per a les lletres
    s->encertades = malloc(s->dim * s->dim * sizeof(char)); // Per saber si una lletra correspon a encert
}

bool demanar_paraula( paraula_t *paraula){
        
    bool fi = false;

    printf("Introdueix la paraula que has trobat: \n");
    scanf("%s", &paraula->ll);

    if ( !strcmp( paraula->ll, "RENDICIO") ) fi = true;
    
    else {

        printf("Introdueix la fila de la paraula (X): \n");
        scanf("%d", &paraula->x);
        printf("Introdueix la columna de la paraula (Y): \n");
        scanf("%d", &paraula->y);
        printf("Introdueix la direccio de la paraula: \n");
        scanf("%d", &paraula->z);

    }

    return fi;

}

int comprovar_encert(sopa_t* s, paraula_t paraula) {

    printf("%s %d %d %d \n", paraula.ll, paraula.x, paraula.y, paraula.z);
   
    bool encert = false;
    int posicio = -1;

   for(int i=0; i<MAX_PARAULES && !encert; i++){


        if (!s->paraules[i].enc) {

        // printf("%s %d %d %d \n", s->paraules[i].ll, s->paraules[i].x, s->paraules[i].y, s->paraules[i].z);
            

            if (paraula.x == s->paraules[i].x && paraula.y == s->paraules[i].y && paraula.z == s->paraules[i].z) {
                s->n_encerts++; // sumar 1 a les paraules encertades
                encert = true;
                posicio = i;
            }

        }

   }

   return posicio;
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

    mostra_sopa(s);

}

void mostrar_saludo() {
    printf("*****************************************************************");
    printf("Us donem la benvinguda al joc de la sopa de lletres!");
    printf("Autors: Ian Lopez Molina, Bogdan Struk, Pol Verdejo Marrugat");
    printf("*****************************************************************");
}

void mostrar_despedida() {
    printf("*****************************************************************");
    printf("Us donem les gracies per jugar amb nosaltres!");
    printf("Autors: Ian Lopez Molina, Bogdan Struk, Pol Verdejo Marrugat");
    printf("*****************************************************************");
}

int main( int argc, char *argv[] ) {

    sopa_t sopa;    
    bool fi = false;
    paraula_t user_input;   // paraula que introduexi l'usuari
    int encert;

    
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


    mostrar_saludo();
    // llegir_fitxer(&sopa);
    genera_sopa(&sopa);     // generem (exemple)
    mostra_sopa(&sopa);


    while ( ( *sopa.encertades < sopa.n_par ) && !fi ){

        fi = demanar_paraula( &user_input );
        
        encert = comprovar_encert( &sopa, user_input);

        if ( encert != -1 ) marcar_encert(&sopa, sopa.paraules[encert]);
        else printf("La paraula es incorrecte o ja ha estat introduida \n");

    }

    mostrar_despedida();

    return 0;
}