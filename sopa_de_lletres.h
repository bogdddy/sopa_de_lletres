/* Archivo de cabecera para la inclusión */

#define MAX_LLETRES 8
#define MAX_PARAULES 10

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

// ordena les paraules alfabeticament
void ordenar_alfabeticament( paraula_t[] paraules);

// ordena les paraules descendentment
void ordenar_longitud( paraula_t[] paraules);

// funcio principal per generar la sopa
void genera_sopa(sopa_t *s);

// comprova si la paraula esta en el lloc indicat
bool comprovar_encert(sopa_t *s, int x, int y, int z);

// marcar la paraula encertada a la sopa de lletres
void marcar_encert( sopa_t *s, paraula_t paraula);





