<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TDA HASH

## Repositorio de Santiago Henseler - 110732 - shenseler@fi.uba.com

- Para compilar:

```bash
make prueba_alumno
```

- Para ejecutar:

```bash
./prueba_alumno
```

- Para ejecutar con valgrind:
```bash
make valgrind_alumno
```
---
##  ¿Que es un diccionario?

Un diccionario es un T.D.A. el cual permite almacenar y organizar información en pares clave-valor. Cada elemento en un diccionario consiste en una clave única y un valor asociado. La clave funciona como un identificador único y se utiliza para acceder al valor correspondiente de una manera más eficaz.

Las ventajas de este T.D.A. salen a la luz en las operaciónes de buscar, insertar y modificar rápidamente datos. En general, puede variar con la implementación, las operaciones eficientes son `O(1)`.

<div align="center">
<img width="70%" src="img/diccionario.png">
</div>

---
##  ¿Que es un diccionario?


En el archivo `sarasa.c` la función `funcion1` utiliza `realloc` para agrandar la zona de memoria utilizada para conquistar el mundo. El resultado de `realloc` lo guardo en una variable auxiliar para no perder el puntero original en caso de error:

```c
int *vector = realloc(vector_original, (n+1)*sizeof(int));

if(vector == NULL)
    return -1;
vector_original = vector;
```


<div align="center">
<img width="70%" src="img/diagrama2.svg">
</div>

---

## Respuestas a las preguntas teóricas
Incluír acá las respuestas a las preguntas del enunciado (si aplica).
