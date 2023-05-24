#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "sopa_de_lletres.h"

// llegir paraules del fitxer i guardar en sopa->paraules
void llegir_fitxer(sopa_t *s, char nom_fitxer[], bool *error){

        FILE *f;
        f = fopen(nom_fitxer, "r");
        char paraula[MAX_LLETRES + 1];
        (*error) = false;

        if (f == NULL) {
            fprintf(stderr, "error al obrir el fitxer %s\n", nom_fitxer);
            (*error) = true;
        }
        else {

            int i=0;
            while (fgets(paraula, MAX_LLETRES + 1 , f)) {
                paraula[strcspn(paraula, "\n")] = '\0';
                s->paraules[i] = (paraula_t) { .ll = "", .enc = false };
                strcpy( s->paraules[i].ll, paraula);
                i++;
            }

            s->n_par = i;

        }
        
        fclose(f);
}

void genera_sopa(sopa_t *s)
{

    srand(time(NULL));

    s->lletres = malloc(s->dim * s->dim * sizeof(char));   // Espai per a les lletres
    s->encertades = malloc(s->dim * s->dim * sizeof(char)); // Per saber si una lletra correspon a encert
    s->n_encerts = 0;
    
    // inicialitzem la sopa
    for (int i = 0; i < s->dim * s->dim; i++){
        s->encertades[i] = false;
        s->lletres[i] = '?';
    }

    ordenar_longitud(s->paraules, s->n_par);

    int x, y, z, pos, lon, intents=0;
    char contingut;
    bool ok, horitzontal, revers;
    char paraula[MAX_LLETRES+1];

    for(int i=0; i<s->n_par; i++){

        ok = true;
        lon = strlen(s->paraules[i].ll);
    
        // generar direcció aleatoria
        z = (rand() % 4) + 1;
        horitzontal = z>2;
        revers = z%2 == 0 ? false : true;

        strcpy(paraula, s->paraules[i].ll);
        if ( revers ) girar_string(paraula); // girar paraula en cas UP i LEFT

        // generar posicio
        x = rand() % (s->dim - (horitzontal ? 0 : lon));
        y = rand() % (s->dim - (horitzontal ? lon : 0)); 

        // comprovar que els espais estiguin buits o hi hagi la lletra que toca
        for (int j=0; j<lon && ok; j++){

            pos = horitzontal ? (s->dim * x) + y + j : s->dim * (x + j) + y;
            contingut = s->lletres[pos];
            if (contingut != '?' && contingut != paraula[j]) ok = false;
            
        }

        // ficar la paraula
        if (ok) {

            for (int j=0; j<lon; j++){
                pos = horitzontal ? (s->dim * x) + y + j: s->dim * (x + j) + y;
                s->lletres[pos] = paraula[j];
            }

            s->paraules[i].x = z!=UP ? x : x + --lon;
            s->paraules[i].y = z!=LEFT ? y: y + --lon;
            s->paraules[i].z = z;
            intents = 0;
        }

        if (!ok){
          i--;
          // tornar a generar sopa en cas de no trobar espai 
          if (++intents>30) genera_sopa(s); 
        } 

    }

    // Descomentar aquesta part per a jugar
    // Omplir la resta de la sopa
    // for (int i = 0; i < s->dim * s->dim; i++)
    //     if (s->lletres[i] == '?') s->lletres[i] = 'A' + (rand() % ('Z'-'A' + 1));
    
}


/* Mostra la sopa de lletres pel terminal */
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

    if (s->n_encerts != s->n_par) {
        printf("Portes %d encerts.\n", s->n_encerts);
        printf("Paraules a trobar: %d\n", s->n_par - s->n_encerts);
        mostrar_paraules(s->paraules, s->n_par);
    } 
    
    printf("\n");

}

void mostrar_paraules (paraula_t paraules[], int n) {

    printf("Hi han les seguents paraules: \n");

    for (int i=0; i<n; i++)
        if (!paraules[i].enc) printf("%s\n", paraules[i].ll);

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

void girar_string(char* str)
{
    int lon = strlen(str)-1;
    int i, j;
    char temp;

    for (i = 0, j = lon; i < j; i++, j--)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }

}

void preguntar_mida(sopa_t *s) {
    int mida;
    
    do {
        printf("\nLa mida de la taula ha de ser de 10x10 fins a 40x40, quina mida vols?\n");
        scanf("%d", &mida);
    } while (MAX_MIDA_TAULER < mida || mida < MIN_MIDA_TAULER);
    
    s->dim = mida;
}

void crear_taules(sopa_t *s) {
    s->lletres = malloc(s->dim * s->dim * sizeof(char));   // Espai per a les lletres
    s->encertades = malloc(s->dim * s->dim * sizeof(char)); // Per saber si una lletra correspon a encert
}

bool demanar_paraula( paraula_t *paraula){
        
    bool fi = false;

    printf("\nIntrodueix la paraula que has trobat: \n");
    scanf("%s", &paraula->ll);

    if ( !strcmp( paraula->ll, "RENDICIO") || !strcmp( paraula->ll, "rendicio")) fi = true;
    
    else {

        printf("Introdueix la fila de la paraula (X): \n");
        scanf("%d", &paraula->x);
        printf("Introdueix la columna de la paraula (Y): \n");
        scanf("%d", &paraula->y);
        printf("Introdueix la direccio de la paraula: \n");
        printf("UP:1 DOWN:2 LEFT:3 RIGHT:4 \n");
        scanf("%d", &paraula->z);

    }

    return fi;

}

int comprovar_encert(sopa_t* s, paraula_t *paraula) {

    bool encert = false;
    int posicio = -1;

   for(int i=0; i<MAX_PARAULES && !encert; i++){

        if (!s->paraules[i].enc) {

            if ((paraula->x -1) == s->paraules[i].x && (paraula->y -1) == s->paraules[i].y && paraula->z == s->paraules[i].z)  {
                encert = true;
                posicio = i;
            }

        }

   }

   return posicio;
}

void marcar_encert(sopa_t *s, paraula_t *paraula){
    
    int lon, pos;
    bool horitzontal, revers;
    
    lon = strlen(paraula->ll);
    horitzontal = paraula->z>2;
    revers = paraula->z%2 == 0 ? false : true;

    //marcar encert
    for (int j=0; j<lon; j++){
        pos = horitzontal ? 
            (s->dim * paraula->x) + paraula->y + (revers ? j*(-1) : j) :
            s->dim * (paraula->x + (revers ? j*(-1) : j)) + paraula->y;
        s->encertades[pos] = true;
    }

    // actualitzar total encerts
    s->n_encerts++; 
    paraula->enc = true;
    
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
    bool fi = false, victoria = false;
    paraula_t user_input;
    int encert;
    bool error;

    mostrar_saludo();

    // LECTURA DE PARAULES
    llegir_fitxer(&sopa, argv[1], &error);
    if (!error) {
        ordenar_alfabeticamente(sopa.paraules, sopa.n_par);
        mostrar_paraules(sopa.paraules, sopa.n_par);

        // GENERAR SOPA
        preguntar_mida(&sopa);
        genera_sopa(&sopa);
        ordenar_alfabeticamente(sopa.paraules, sopa.n_par);     
        mostra_sopa(&sopa);

        while ( !victoria && !fi ){

            fi = demanar_paraula( &user_input );
            
            if (!fi) {
                encert = comprovar_encert( &sopa, &user_input);

                if ( encert != -1 ) marcar_encert(&sopa, &sopa.paraules[encert]);
                else printf("La paraula es incorrecte o ja ha estat introduida \n");

                if (sopa.n_encerts == sopa.n_par) victoria = true;
            }
            

        }

        printf(victoria ? "FELICITATS HAS GUANYAT !! \n": "MES SORT EL PROXIM COP !! \n");
        mostrar_despedida();
    }
    

    return 0;
}