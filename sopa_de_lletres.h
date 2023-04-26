#include <stdbool.h>

/* Archivo de cabecera para la inclusión */

#define MAX_LLETRES 8
#define MAX_PARAULES 10

#define UP 1
#define DOWN -1
#define LEFT -2
#define RIGHT 2

#define FORWARD 1
#define REVERSE -1


/* Definicio del tipus per a desar les dades de la sopa de lletres */
/* Es una proposta que podeu canviar, ampliar, etc. */
typedef struct 
{
    char ll[MAX_LLETRES + 1];   // Lletres de la paraula (comptem centinella)
    bool enc;   // La paraula s'ha encertat
    int x, y, z;    // x -> row, y -> col, z -> direction
} paraula_t;


typedef struct 
{
    int dim;        // Nombre de files = nombre de columnes
    char *lletres;  // Taula amb les lletres
    bool *encertades;   // Les lletres son d'una paraula que s'ha encertat
    paraula_t paraules[MAX_PARAULES];    // Les paraules
    int n_par;  // Nombre de paraules
    int n_encerts;    // Nombre de paraules encertades
} sopa_t;

// llegir paraules del fitxer i guardar en sopa->paraules
void llegir_fitxer( sopa_t *s);

/**
 * Ordena el array de paraules segun el alfabeto.
 * @param paraules El array de paraules a ordenar.
 * @param n Cantidad de paraules
 * @pre El parametro paraules[] debe tener al menos un objeto paraula_t.
 */
void ordenar_alfabeticament(paraula_t paraules[], int n);

/**
 * Compara dos palabras e indica cual es mayor segun el alfabeto.
 * @param paraula_a Palabra a ordenar.
 * @param paraula_b Palabra de palabras a ordenar.
 * @pre Los char[] de caracteres ll en paraula_a y paraula_b no pueden ser nulos ni vacíos.
 */
int comparar_longitud(const void *paraula_a, const void *paraula_b);

/**
 * Ordena el array de paraules segun la longitud de las palabras.
 * @param paraules El array de paraules a ordenar.
 * @param n Cantidad de paraules
 * @pre El parametro paraules[] debe tener al menos un objeto paraula_t.
 */
void ordenar_longitud(paraula_t paraules[], int n);

/**
 * Compara dos palabras e indica cual es mayor segun su longitud.
 * @param paraula_a Palabra a ordenar.
 * @param paraula_b Palabra de palabras a ordenar.
 * @pre Los char[] de caracteres ll en paraula_a y paraula_b no pueden ser nulos ni vacíos.
 */
int comparar_longitud(const void *paraula_a, const void *paraula_b);

// funcio principal per generar la sopa
void genera_sopa(sopa_t *s);

/**
* comprova si la paraula introduida per l'usuari esta en el lloc indicat
* @param s paraula a comprovar
* @param fil numero de fila a comprovar
* @param col numero de columna a comprovar
* @param dir direccio de la paraula
*/
bool comprovar_encert(sopa_t* s, int fil, int col, int dir);

/**
 * @brief marcar la paraula encertada a la sopa de lletres
 * @param s sopa_t status joc
 * @param paraula paraulta_t paraula a marcar
*/
void marcar_encert(sopa_t *s, paraula_t paraula);
