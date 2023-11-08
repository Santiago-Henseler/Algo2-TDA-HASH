#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hash.h"

#define FACTOR_CARGA_MAXIMO 0.7

struct par{
	char *clave;
	void *valor;
	struct par* siguiente;
};

struct hash{
	struct par** tabla;
	size_t cantidad;
	size_t capacidad;
};

/* aux*/
unsigned int funcion_hash(const char *clave) {
        int hash = 5381;
        int c;
        while ((c = *clave++))
            hash = ((hash << 5) + hash) + c;
        return (unsigned)hash;
}

struct par* crear_par(const char *clave, void *elemento){
	struct par * nuevo_par = calloc(1, sizeof(struct par));
	
	if(!nuevo_par)
		return NULL;

	nuevo_par->clave = calloc(1, strlen(clave)+1);

	if(!nuevo_par->clave){
		free(nuevo_par);
		return NULL;
	}

	strcpy(nuevo_par->clave, clave);

	nuevo_par->valor = elemento;
	return nuevo_par;
}

hash_t * insertar_par(hash_t *hash,struct par* par, void **anterior){

	int posicion = (int)(funcion_hash(par->clave)%(unsigned)hash->capacidad);
	
	struct par* actual = hash->tabla[posicion];
	bool insertado = false;

	while (actual && !insertado)
	{
		if(strcmp(par->clave, actual->clave) == 0){
			anterior = par->valor;
			actual->valor = par->valor;
			insertado = true;
		}
		actual = actual->siguiente;
	}

	if(!insertado){
		anterior = NULL;
		par->siguiente = actual;
		hash->tabla[posicion] = par;
		hash->cantidad++;
		insertado = true;	
	}

	if(!insertado){
		return NULL;
	}
	return hash;
}

hash_t *rehash(hash_t *hash){

	struct par** viejo_par = hash->tabla;

	hash->capacidad *=2;
	hash->tabla = malloc(hash->capacidad);
	if(!hash->tabla)
		return NULL;

	hash->cantidad = 0;

	for(int i = 0; i < hash->capacidad; i++){
		struct par* actual = viejo_par[i];
		while (actual)
		{
			insertar_par(hash, actual, NULL);
			actual = actual->siguiente;
		}
	}

	free(viejo_par);

	return hash;
}
/* aux*/

hash_t *hash_crear(size_t capacidad)
{
	size_t max = capacidad < 3 ? 3:capacidad;

	struct hash * nuevo_hash = calloc(1,sizeof(struct hash));

	if(!nuevo_hash)
		return NULL;

	nuevo_hash->tabla = calloc(max, sizeof(struct par));
	nuevo_hash->capacidad = max;

	if(!nuevo_hash->tabla){
		free(nuevo_hash);
		return NULL;
	}

	return nuevo_hash;
}

hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento, void **anterior)
{
	if (!hash || !clave)
		return NULL;

	if((float)hash->cantidad/(float)hash->capacidad >= FACTOR_CARGA_MAXIMO)
		rehash(hash);
	else{
		struct par* nuevo_par = crear_par(clave, elemento);
		if(!nuevo_par)
			return NULL;

		return insertar_par(hash, nuevo_par, anterior);
	}
	return NULL;
}

struct par* quitar_recu(struct par *actual, const char *clave, void * elemento){

	if(strcmp(clave, actual->clave) == 0){
		struct par* aux = actual;
		elemento = aux->valor;
		free(aux);
		return actual->siguiente;
	}

	actual->siguiente = quitar_recu(actual->siguiente, clave, elemento);

	return actual;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
	if (!hash || !clave)
		return NULL;

	int posicion = (int)(funcion_hash(clave)%(unsigned)hash->capacidad);

	struct par *actual = hash->tabla[posicion];

	if(!actual)
		return NULL;

	void * elemento = NULL;

	quitar_recu(actual, clave, elemento);

	return elemento;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
	if (!hash || !clave)
		return NULL;

	int posicion = (int)(funcion_hash(clave)%(unsigned)hash->capacidad);

	struct par *actual = hash->tabla[posicion];

	if(!actual)
		return NULL;

	bool encontrado = false;
	void * elemento = NULL;

	while (actual && !encontrado)
	{
		if(strcmp(clave, actual->clave) == 0){
			elemento = actual->valor;
			encontrado = true;
		}

		actual = actual->siguiente;
	}
	
	return elemento;
}

bool hash_contiene(hash_t *hash, const char *clave)
{
	if (!hash || !clave)
		return false;

	return hash_obtener(hash, clave)?true:false;
}

size_t hash_cantidad(hash_t *hash)
{
	if (!hash)
		return 0;
	return hash->cantidad;
}

void hash_destruir(hash_t *hash)
{
	hash_destruir_todo(hash, NULL);
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	if (!hash)
		return;

	for(int i = 0; i < hash->capacidad; i++){
		struct par* actual = hash->tabla[i];
		while (actual)
		{
			
			actual = actual->siguiente;
		}
		free(actual);
	}
	free(hash);
}

size_t hash_con_cada_clave(hash_t *hash, bool (*f)(const char *clave, void *valor, void *aux), void *aux)
{
	size_t n = 0;
	if (!hash || !f)
		return n;

	bool finalizar = false;

	for(int i = 0; i < hash->capacidad && !finalizar; i++){
		struct par* actual = hash->tabla[i];
		while (actual)
		{
			finalizar = f(actual->clave, actual->valor,aux);
			n++;
			actual = actual->siguiente;
		}
	}

	return n;
}
