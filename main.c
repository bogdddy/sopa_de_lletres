#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "sopa_de_lletres.h"

// llegir paraules del fitxer i guardar en sopa->paraules
void llegir_fitxer(sopa_t *s, char nom_fitxer[]){

        FILE *f;
        f = fopen(nom_fitxer, "r");
        char paraula[MAX_LLETRES + 1];
        

        if (f == NULL) fprintf(stderr, "error al obrir el fitxer %s\n", nom_fitxer);
        else {

            int i=0;
            while (fgets(paraula, MAX_LLETRES + 1 , f)) {
                // printf("%s \n", paraula);
                s->paraules[i] = (paraula_t) { .ll = "", .enc = false };
                strcpy( s->paraules[i].ll, paraula);
                i++;
            }

            s->n_par = i;

        }
        
        fclose(f);
}

/* Aquesta funcio genera la sopa de lletres, a partir del fitxer i altres parametres */
/* que ja decidireu. En aquest cas només l'emplena amb una SOPA d'EXEMPLE, es a dir */
/* que haureu de fer la vostra pròpia. */
void genera_sopa(sopa_t *s)
{

    srand(time(NULL));

    s->lletres = malloc(s->dim * s->dim * sizeof(char));   // Espai per a les lletres
    s->encertades = malloc(s->dim * s->dim * sizeof(char)); // Per saber si una lletra correspon a encert
    
    // inicialitzem la sopa
    for (int i = 0; i < s->dim * s->dim; i++){
        s->encertades[i] = false;
        // s->lletres[i] = 'A' + (rand() % ('Z'-'A' + 1));
        s->lletres[i] = '?';
    }

    ordenar_longitud(s->paraules, s->n_par);

    int x, y, z;
    char pos;
    bool ok;

    for(int i=0; i<s->n_par; i++){

        ok = true;
    
        // generar direcció aleatoria
        z = (rand() % 2) + 1;

        switch (z) {

            case UP:

            x = rand() % (s->dim - (strlen(s->paraules[i].ll)-1)) + strlen(s->paraules[i].ll)-1;  // mirar rango
            y = rand() % s->dim; 
            
            // printf("%s \n", s->paraules[i].ll);
            // printf("x:%d y:%d z:%d \n", x, y, z);
            // printf("strlen %d \n", strlen(s->paraules[i].ll))-1;
            
            // comprovar que els espais estiguin buits o hi hagi la lletra que toca
            for (int j=0; j<(strlen(s->paraules[i].ll)-1) && ok; j++){

                pos = s->lletres[s->dim * (x - j) + y];
                if (pos != '?' && pos != s->paraules[i].ll[j]) ok = false;
                
            }

            // ficar la paraula
            if (ok) {
                for (int j=x, k=0; j>x-(strlen(s->paraules[i].ll)-1); j--, k++){
                    s->lletres[s->dim * (j) + y] = s->paraules[i].ll[k];
                }
            }

            break;

            case DOWN:

            printf("down");

            x = rand() % (s->dim - (strlen(s->paraules[i].ll)-1));  // mirar rango
            y = rand() % s->dim; 
            
            // comprovar que els espais estiguin buits o hi hagi la lletra que toca
            for (int j=0; j<(strlen(s->paraules[i].ll)-1) && ok; j++){

                pos = s->lletres[s->dim * (x + j) + y];
                if (pos != '?' && pos != s->paraules[i].ll[j]) ok = false;
                
            }

            // ficar la paraula
            if (ok) {
                for (int j=0; j<(strlen(s->paraules[i].ll)-1); j++){
                    s->lletres[s->dim * (j +x) + y] = s->paraules[i].ll[j];
                }
            }

            break;

            case LEFT:
            
            if (z == LEFT && (y - strlen(s->paraules[i].ll) < 0)) ok = false;

            break;

            case RIGHT:

            if (z == RIGHT && (y + strlen(s->paraules[i].ll) > s->dim)) ok = false;
            break;
            

            default:
            break;
        }

        if (!ok) i--;
        else {
            s->paraules[i].x = x;
            s->paraules[i].y = y;
            s->paraules[i].z = z;
        }

    }

    // rellenar espacios bacios con letras

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

void mostrar_paraules (paraula_t paraules[], int n) {

    printf("Hi han les seguents paraules: \n");

    for (int i=0; i<n; i++){
        if (paraules[i].enc == false){
            printf("%s", paraules[i].ll);
        }
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
    return strlen(((paraula_t *)paraula_b)->ll) - strlen(((paraula_t *)paraula_a)->ll) ;
}

void ordenar_longitud(paraula_t paraules[], int n)
{
    qsort(paraules, n, sizeof(paraula_t), comparar_longitud);
}

void preguntar_tamany(sopa_t *s) {
    int tamany;
    
    do {
        printf("\n\nEl tamany de la taula ha de ser de 10x10 fins a 40x40, quina mida vols?");
        scanf("%d", &tamany);
    } while (MAX_TAMANY_TAULER < tamany || tamany < MIN_TAMANY_TAULER);
    
    s->dim = tamany;
}

void crear_taules(sopa_t *s) {
    s->lletres = malloc(s->dim * s->dim * sizeof(char));   // Espai per a les lletres
    s->encertades = malloc(s->dim * s->dim * sizeof(char)); // Per saber si una lletra correspon a encert
}

bool demanar_paraula( paraula_t *paraula){
        
    bool fi = false;

    printf("\nIntrodueix la paraula que has trobat: \n");
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

    bool encert = false;
    int posicio = -1;

   for(int i=0; i<MAX_PARAULES && !encert; i++){


        if (!s->paraules[i].enc) {

        printf("%s %d %d %d \n", s->paraules[i].ll, s->paraules[i].x, s->paraules[i].y, s->paraules[i].z);
            

            if ((paraula.x -1) == s->paraules[i].x && (paraula.y -1) == s->paraules[i].y && paraula.z == s->paraules[i].z) {
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
    
    if (paraula.z == UP){
         for (int i=paraula.x; i>paraula.x-lon; i--){
            s->encertades[s->dim * (i) + paraula.y] =  true;
         }

    } else if ( paraula.z == DOWN){
        for (int i=0; i<lon; i++){
            s->encertades[s->dim * (paraula.x + i) + paraula.y] =  true;
        }
    } else if (paraula.z == LEFT){
         for (int i=paraula.y; i>=lon; i--){
            s->encertades[s->dim * (paraula.x + i) + paraula.y] =  true;
         }

    } else if ( paraula.z == RIGHT){
        for (int i=0; i<=lon; i++){
                s->encertades[(s->dim * paraula.x) + paraula.y + i] =  true;
        }
    }
    


    mostra_sopa(s);

}

void mostrar_saludo() {
    printf("*****************************************************************\n");
    printf("Us donem la benvinguda al joc de la sopa de lletres!\n");
    printf("Autors: Ian Lopez Molina, Bogdan Struk, Pol Verdejo Marrugat\n");
    printf("*****************************************************************\n");
}

void mostrar_despedida() {
    printf("*****************************************************************\n");
    printf("Us donem les gracies per jugar amb nosaltres!\n");
    printf("Autors: Ian Lopez Molina, Bogdan Struk, Pol Verdejo Marrugat\n");
    printf("*****************************************************************\n");
}

int main( int argc, char *argv[] ) {

    sopa_t sopa;    
    bool fi = false;
    paraula_t user_input;   // paraula que introduexi l'usuari
    int encert;

    
    // paraules de prova
    paraula_t bolet, arbust;

    strcpy(bolet.ll, "BOLET");
    bolet.x = 0;
    bolet.y = 5;
    bolet.z = 2;
    
    strcpy(arbust.ll, "ARBUST");
    arbust.x = 3;
    arbust.y = 5;
    arbust.z = -1;


    mostrar_saludo();

    // LECTURA DE PARAULES
    llegir_fitxer(&sopa, argv[1]);
    ordenar_alfabeticamente(sopa.paraules, sopa.n_par);
    mostrar_paraules(sopa.paraules, sopa.n_par);

    // GENERAR SOPA
    preguntar_tamany(&sopa);
    genera_sopa(&sopa);     
    // printf("generada");
    mostra_sopa(&sopa);
    // printf("mostrar");


    while ( ( *sopa.encertades < sopa.n_par ) && !fi ){

        fi = demanar_paraula( &user_input );
        
        encert = comprovar_encert( &sopa, user_input);

        if ( encert != -1 ) marcar_encert(&sopa, sopa.paraules[encert]);
        else printf("La paraula es incorrecte o ja ha estat introduida \n");

    }

    mostrar_despedida();

    return 0;
}