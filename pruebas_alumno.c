#include "pa2m.h"
#include "src/hash.h"

void CreacionDeHash()
{
	hash_t *hash1 =  hash_crear(1);
	pa2m_afirmar(hash1 != NULL, "Creo un hash con menor capacidad y se crea correctamente");

	hash_t *hash2 =  hash_crear(10000);
	pa2m_afirmar(hash2 != NULL, "Creo un hash con mucha capacidad y se crea correctamente");

	//hash_destruir(hash1);
	//hash_destruir(hash2);
}

void InsertarElementosSinRehashYLosBusco(){
	hash_t *hash =  hash_crear(10);

	int n[6] = {1,2,3,4,5,6};

	hash_insertar(hash, "v1", &n[0], NULL);
	hash_insertar(hash, "v2", &n[1], NULL);
	hash_insertar(hash, "v3", &n[2], NULL);
	hash_insertar(hash, "v4", &n[3], NULL);
	hash_insertar(hash, "v5", &n[4], NULL);

	pa2m_afirmar(hash_cantidad(hash) == 5, "Inserto 5 elementos y se insertan 5");	

	pa2m_afirmar(hash_contiene(hash, "v4"), "Busco una clave insertada y existe");	

	pa2m_afirmar(hash_obtener(hash, "v5") == &n[4], "El elemento encontrado concuerda con la clave");	

	hash_insertar(hash, "v1", &n[5], NULL);

	pa2m_afirmar(hash_obtener(hash, "v1") == &n[5], "Se modifica correctamente un valor");	

	//hash_destruir(hash);
}

void InsertoElementosHastaRehashYLosBusco(){
	hash_t *hash =  hash_crear(3);

	int n[6] = {1,2,3,4,5,6};

	hash_insertar(hash, "v1", &n[0], NULL);
	hash_insertar(hash, "v2", &n[1], NULL);
	hash_insertar(hash, "v3", &n[2], NULL);
	hash_insertar(hash, "v4", &n[3], NULL);
	hash_insertar(hash, "v5", &n[4], NULL);

	pa2m_afirmar(hash_cantidad(hash) == 5, "Inserto 5 elementos y se insertan 5");	

	pa2m_afirmar(hash_contiene(hash, "v4"), "Busco una clave insertada y existe");	

	pa2m_afirmar(hash_obtener(hash, "v5") == &n[4], "El elemento encontrado concuerda con la clave");	

	hash_insertar(hash, "v1", &n[5], NULL);

	pa2m_afirmar(hash_obtener(hash, "v1") == &n[5], "Se modifica correctamente un valor");	

	//hash_destruir(hash);

}

void QuitoElementos(){
	hash_t *hash =  hash_crear(10);

	int n[6] = {1,2,3,4,5,6};

	hash_insertar(hash, "v1", &n[0], NULL);
	hash_insertar(hash, "v2", &n[1], NULL);
	hash_insertar(hash, "v3", &n[2], NULL);
	hash_insertar(hash, "v4", &n[3], NULL);
	hash_insertar(hash, "v5", &n[4], NULL);

	pa2m_afirmar(hash_quitar(hash, "v1") == &n[0], "El elemento quitado es el correcto");
	pa2m_afirmar(hash_quitar(hash, "v1") == &n[0], "El elemento quitado es el correcto");


	//hash_destruir(hash);
}

int main()
{
	pa2m_nuevo_grupo("\n======================== Pruebas Hash ========================");
	CreacionDeHash();
	InsertarElementosSinRehashYLosBusco();

	pa2m_nuevo_grupo("\n======================== Pruebas ReHash ========================");
	InsertoElementosHastaRehashYLosBusco();

	pa2m_nuevo_grupo("\n======================== Pruebas Quitar ========================");
	QuitoElementos();
	
	return pa2m_mostrar_reporte();
}
