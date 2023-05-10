#include <stdbool.h>

/* Archivo de cabecera para la inclusión */

#define MAX_LLETRES 8
#define MAX_PARAULES 10

#define MIN_TAMANY_TAULER 10
#define MAX_TAMANY_TAULER 40

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4


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
void llegir_fitxer(sopa_t *s, char nom_fitxer[]);

/**
 * Ordena el array de paraules segun el alfabeto.
 * @param paraules El array de paraules a ordenar.
 * @param n Cantidad de paraules
 * @pre El parametro paraules[] debe tener al menos un objeto paraula_t.
 */
void ordenar_alfabeticamente(paraula_t paraules[], int n);

/**
 * Compara dos palabras e indica cual es mayor segun el alfabeto.
 * @param paraula_a Palabra a ordenar.
 * @param paraula_b Palabra de palabras a ordenar.
 * @pre Los char[] de caracteres ll en paraula_a y paraula_b no pueden ser nulos ni vacíos.
 */
int comparar_alfabeticamente(const void *paraula_a, const void *paraula_b);

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

/**
 * Pregunem la mida de la taula a l'usuari
 * @param s sopa
 */
void preguntar_tamany(sopa_t *s);

/**
 * Creem les taules
 * @param s sopa
 */
void crear_taules(sopa_t *s);

/**
 * @brief funcio general per generar la sopa de lletres
*/
void genera_sopa(sopa_t *s);

/**
 * @brief mostra les paraules no encertades per pantalla
*/
void mostrar_paraules (paraula_t paraules[], int n);

/**
 * @brief demana una paraula a l'usuari i la guarda en el struct
 * @param paraula on guardem la paraula 
*/
bool demanar_paraula(paraula_t *paraula);

/**
* comprova si la paraula introduida per l'usuari esta en el lloc indicat
* @param s sopa de lletres
* @param paraula paraulta_t introduida per l'usuari
* @return la posició de la paraula en sopa->paraules[], si no existeix -1
*/
int comprovar_encert(sopa_t* s, paraula_t paraula);

/**
 * @brief marcar la paraula encertada a la sopa de lletres
 * @param s sopa_t status joc
 * @param paraula paraulta_t paraula a marcar
*/
void marcar_encert(sopa_t *s, paraula_t paraula);

/**
* saludem a l'usuari
*/
void mostrar_saludo();

/**
* ens acomiadem de l'usuari
*/
void mostrar_despedida();