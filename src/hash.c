#include "funciones_aux.h"
#include "hash.h"

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

	if((float)hash->cantidad/(float)hash->capacidad >= FACTOR_CARGA_MAXIMO){
		hash = rehash(hash);
	}

	struct par* nuevo_par = crear_par(clave, elemento);
	if(!nuevo_par)
		return NULL;

	return insertar_par(hash, nuevo_par, anterior);
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

	hash->tabla[posicion] = quitar_recu(actual, clave, &elemento);

	if(elemento){
		hash->cantidad--;
		return elemento;
	}
	return NULL;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
	if (!hash || !clave)
		return NULL;

	int posicion = (int)(funcion_hash(clave)%(unsigned)hash->capacidad);

	struct par *actual = hash->tabla[posicion];

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

void destruir_recu(struct par *actual, void(*f)(void*)){
	
	if(actual)
		destruir_recu(actual->siguiente, f);

	if(f)
		f(actual->valor);
	free(actual->clave);
	free(actual);
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	if (!hash)
		return;

	for(int i = 0; i < hash->capacidad; i++){
		struct par* actual = hash->tabla[i];
		destruir_recu(actual, destructor);
	}
	free(hash);
}

size_t hash_con_cada_clave(hash_t *hash, bool (*f)(const char *clave, void *valor, void *aux), void *aux)
{
	size_t n = 0;
	if (!hash || !f)
		return n;

	for(int i = 0; i < hash->capacidad; i++){
		struct par* actual = hash->tabla[i];
		while (actual && f(actual->clave, actual->valor,aux))
		{
			n++;
			actual = actual->siguiente;
		}
	}

	return n;
}
