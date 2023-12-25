#include "pa2m.h"
#include <string.h>
#include "src/hash.h"

void CreacionDeHash()
{
	hash_t *hash1 = hash_crear(1);
	pa2m_afirmar(
		hash1 != NULL,
		"Creo un hash con menor capacidad y se crea correctamente");

	hash_t *hash2 = hash_crear(10000);
	pa2m_afirmar(
		hash2 != NULL,
		"Creo un hash con mucha capacidad y se crea correctamente");

	hash_destruir(hash1);
	hash_destruir(hash2);
}

void InsertarElementosSinRehashYLosBusco()
{
	hash_t *hash = hash_crear(50);

	int n[6] = { 1, 2, 3, 4, 5, 6 };

	hash_insertar(hash, "v1", &n[0], NULL);
	hash_insertar(hash, "v2", &n[1], NULL);
	hash_insertar(hash, "v3", &n[2], NULL);
	hash_insertar(hash, "v4", &n[3], NULL);
	hash_insertar(hash, "v5", &n[4], NULL);

	pa2m_afirmar(hash_cantidad(hash) == 5,
		     "Inserto 5 elementos y se insertan 5");

	pa2m_afirmar(hash_contiene(hash, "v4"),
		     "Busco una clave insertada y existe");

	pa2m_afirmar(hash_obtener(hash, "v5") == &n[4],
		     "El elemento encontrado concuerda con la clave");

	hash_insertar(hash, "v1", &n[5], NULL);

	pa2m_afirmar(hash_obtener(hash, "v1") == &n[5],
		     "Se modifica correctamente un valor");

	pa2m_afirmar(hash_insertar(NULL, "v4", &n[4], NULL) == NULL,
		     "Inserto en un hash nulo y no se inserta");
	pa2m_afirmar(hash_insertar(hash, NULL, &n[4], NULL) == NULL,
		     "Inserto una clave nula y no se inserta");
	pa2m_afirmar(hash_insertar(hash, "v12", NULL, NULL) == hash,
		     "Inserto un valor nulo y se inserta");

	hash_destruir(hash);
}

void InsertoElementosHastaRehashYLosBusco()
{
	hash_t *hash = hash_crear(3);

	int n[6] = { 1, 2, 3, 4, 5, 6 };

	hash_insertar(hash, "v1", &n[0], NULL);
	hash_insertar(hash, "v2", &n[1], NULL);
	hash_insertar(hash, "v3", &n[2], NULL);
	hash_insertar(hash, "v4", &n[3], NULL);
	hash_insertar(hash, "v5", &n[4], NULL);

	pa2m_afirmar(hash_cantidad(hash) == 5,
		     "Inserto 5 elementos y se insertan 5");

	pa2m_afirmar(hash_contiene(hash, "v4"),
		     "Busco una clave insertada y existe");

	pa2m_afirmar(hash_obtener(hash, "v5") == &n[4],
		     "El elemento encontrado concuerda con la clave");

	hash_insertar(hash, "v1", &n[5], NULL);

	pa2m_afirmar(hash_obtener(hash, "v1") == &n[5],
		     "Se modifica correctamente un valor");

	hash_destruir(hash);
}

void QuitoElementos()
{
	hash_t *hash = hash_crear(50);

	int n[6] = { 1, 2, 3, 4, 5, 6 };

	hash_insertar(hash, "v1", &n[0], NULL);
	hash_insertar(hash, "v2", &n[1], NULL);
	hash_insertar(hash, "v3", &n[2], NULL);
	hash_insertar(hash, "v4", &n[3], NULL);
	hash_insertar(hash, "v5", &n[4], NULL);

	pa2m_afirmar(hash_quitar(hash, "v1") == &n[0],
		     "El elemento quitado es el correcto");
	pa2m_afirmar(hash_quitar(hash, "v1") == NULL,
		     "No puedo quitar un elemento ya quitado");

	pa2m_afirmar(hash_quitar(NULL, "v1") == NULL,
		     "No puedo quitar de un hash inexistente");
	pa2m_afirmar(hash_quitar(hash, NULL) == NULL,
		     "No puedo quitar de una clave inexistente");

	hash_quitar(hash, "v2");
	hash_quitar(hash, "v3");
	hash_quitar(hash, "v4");
	hash_quitar(hash, "v5");

	pa2m_afirmar(hash_cantidad(hash) == 0,
		     "Quito todos los elementos correctamente");

	hash_destruir(hash);
}

void ObtenerElementos()
{
	hash_t *hash = hash_crear(50);

	int n[6] = { 1, 2, 3, 4, 5, 6 };

	hash_insertar(hash, "v1", &n[0], NULL);
	hash_insertar(hash, "v2", &n[1], NULL);
	hash_insertar(hash, "v3", &n[2], NULL);
	hash_insertar(hash, "v4", &n[3], NULL);
	hash_insertar(hash, "v5", &n[4], NULL);

	pa2m_afirmar(hash_obtener(hash, "v5") == &n[4],
		     "El elemento obtenido concuerda con el buscado");

	pa2m_afirmar(hash_obtener(NULL, "v5") == NULL,
		     "No se puede obtener de un hash nulo");

	pa2m_afirmar(hash_obtener(hash, NULL) == NULL,
		     "No se puede obtener una clave nula");

	pa2m_afirmar(hash_obtener(hash, "v1000") == NULL,
		     "No se puede obtener una clave que no este en el hash");

	hash_destruir(hash);
}

bool iterar_todas(const char *clave, void *valor, void *aux)
{
	return true;
}

bool iterar_algunos(const char *clave, void *valor, void *aux)
{
	if (strcmp(clave, "v4") == 0)
		return false;

	return true;
}

void IterarElementos()
{
	hash_t *hash = hash_crear(50);

	int n[6] = { 1, 2, 3, 4, 5, 6 };

	hash_insertar(hash, "v1", &n[0], NULL);
	hash_insertar(hash, "v2", &n[1], NULL);
	hash_insertar(hash, "v3", &n[2], NULL);
	hash_insertar(hash, "v4", &n[3], NULL);
	hash_insertar(hash, "v5", &n[4], NULL);

	pa2m_afirmar(hash_cantidad(hash) ==
			     hash_con_cada_clave(hash, iterar_todas, NULL),
		     "Se itera todos los elementos");

	pa2m_afirmar(0 == hash_con_cada_clave(NULL, iterar_todas, NULL),
		     "no se itera un hash nulo");
	pa2m_afirmar(0 == hash_con_cada_clave(hash, NULL, NULL),
		     "no se itera un hash sin funcion");

	pa2m_afirmar(4 == hash_con_cada_clave(hash, iterar_algunos, NULL),
		     "Se itera algunos elementos");

	hash_destruir(hash);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== Pruebas Hash ========================");
	CreacionDeHash();
	InsertarElementosSinRehashYLosBusco();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas ReHash ========================");
	InsertoElementosHastaRehashYLosBusco();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas Quitar ========================");
	QuitoElementos();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas Obtener ========================");
	ObtenerElementos();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas Iterador ========================");
	IterarElementos();

	return pa2m_mostrar_reporte();
}
