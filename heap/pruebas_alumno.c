#include "heap.h"
#include "testing.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

/* ******************************************************************
 *                      FUNCIONES AUXILIARES
 * *****************************************************************/

// Funcion auxiliar para comparar enteros.
int comparar_enteros(const void* a, const void* b) {
	if (*(const int*) a == *(const int*) b) return 0;
	
	if (*(const int*) a > *(const int*) b) return 1;
	
	return -1;
}


/* ******************************************************************
 *                       PRUEBAS UNITARIAS
 * *****************************************************************/

// Pruebas para un heap vacio.
void pruebas_heap_vacio() {
	printf("-------------INICIO DE PRUEBAS: CREAR HEAP-------------\n");

	// Declaro las variables a utilizar.
	heap_t* heap = heap_crear(comparar_enteros);

	// Pruebo comportamiento de un heap vacio.
	print_test("Prueba p1: El heap fue creado", heap);
	print_test("Prueba p1: El heap se encuentra vacio", heap_esta_vacio(heap));
	print_test("Prueba p1: La cantidad de elementos es la correcta", heap_cantidad(heap) == 0);
	print_test("Prueba p1: Ver maximo devuelve NULL", heap_ver_max(heap) == NULL);
	print_test("Prueba p1: Desencolar devuelve NULL", heap_desencolar(heap) == NULL);

	// Destruyo el heap.
	heap_destruir(heap, NULL);
	print_test("Prueba p1: El heap fue destruido", true);
}

// Pruebas para encolar en un heap.
void pruebas_heap_encolar() {
	printf("-------------INICIO DE PRUEBAS: ENCOLAR-------------\n");

	// Declaro las variables a utilizar.
	heap_t* heap = heap_crear(comparar_enteros);
	int elemento1 = 50, elemento2 = 51, elemento3 = 33, elemento4 = 100;

	// Pruebo encolar.
	print_test("Prueba p2: Encolar elemento 1", heap_encolar(heap, &elemento1));
	print_test("Prueba p2: El heap no se encuentra vacio", !heap_esta_vacio(heap));
	print_test("Prueba p2: La cantidad de elementos es la correcta", heap_cantidad(heap) == 1);
	print_test("Prueba p2: Ver max devuelve el elemento correcto", heap_ver_max(heap) == &elemento1);
	print_test("Prueba p2: Encolar elemento 2", heap_encolar(heap, &elemento2));
	print_test("Prueba p2: El heap no se encuentra vacio", !heap_esta_vacio(heap));
	print_test("Prueba p2: La cantidad de elementos es la correcta", heap_cantidad(heap) == 2);
	print_test("Prueba p2: Ver max devuelve el elemento correcto", heap_ver_max(heap) == &elemento2);
	print_test("Prueba p2: Encolar elemento 3", heap_encolar(heap, &elemento3));
	print_test("Prueba p2: La cantidad de elementos es la correcta", heap_cantidad(heap) == 3);
	print_test("Prueba p2: Ver max devuelve el elemento correcto", heap_ver_max(heap) == &elemento2);
	print_test("Prueba p2: Encolar elemento 4", heap_encolar(heap, &elemento4));
	print_test("Prueba p2: La cantidad de elementos es la correcta", heap_cantidad(heap) == 4);
	print_test("Prueba p2: Ver max devuelve el elemento correcto", heap_ver_max(heap) == &elemento4);
	print_test("Prueba p2: El heap no se encuentra vacio", !heap_esta_vacio(heap));

	// Destruyo el heap.
	heap_destruir(heap, NULL);
	print_test("Prueba p2: El heap fue destruido", true);
}

// Pruebas para desencolar en un heap.
void pruebas_heap_desencolar() {
	printf("-------------INICIO DE PRUEBAS: DESENCOLAR-------------\n");

	// Declaro las variables a utilizar.
	heap_t* heap = heap_crear(comparar_enteros);
	int elemento1 = 50, elemento2 = 25, elemento3 = 33, elemento4 = 100;

	// Encolo y desencolo.
	print_test("Prueba p3: El heap se encuentra vacio", heap_esta_vacio(heap));
	print_test("Prueba p3: Encolar elemento 1", heap_encolar(heap, &elemento1));
	print_test("Prueba p3: El heap no se encuentra vacio", !heap_esta_vacio(heap));
	print_test("Prueba p3: Ver max devuelve el elemento correcto", heap_ver_max(heap) == &elemento1);
	print_test("Prueba p3: Desencolar devuelve el elemento correcto", heap_desencolar(heap) == &elemento1);
	print_test("Prueba p3: El heap se encuentra vacio", heap_esta_vacio(heap));
	print_test("Prueba p3: La cantidad de elementos es la correcta", heap_cantidad(heap) == 0);
	print_test("Prueba p3: Ver maximo devuelve NULL", heap_ver_max(heap) == NULL);
	print_test("Prueba p3: Desencolar devuelve NULL", heap_desencolar(heap) == NULL);

	print_test("Prueba p3: Encolar elemento 1", heap_encolar(heap, &elemento1));
	print_test("Prueba p3: El heap no se encuentra vacio", !heap_esta_vacio(heap));
	print_test("Prueba p3: Ver max devuelve el elemento correcto", heap_ver_max(heap) == &elemento1);
	print_test("Prueba p3: Encolar elemento 2", heap_encolar(heap, &elemento2));
	print_test("Prueba p3: Encolar elemento 3", heap_encolar(heap, &elemento3));
	print_test("Prueba p3: Encolar elemento 4", heap_encolar(heap, &elemento4));
	print_test("Prueba p3: Ver max devuelve el elemento correcto", heap_ver_max(heap) == &elemento4);
	print_test("Prueba p3: La cantidad de elementos es la correcta", heap_cantidad(heap) == 4);
	print_test("Prueba p3: El heap no se encuentra vacio", !heap_esta_vacio(heap));

	print_test("Prueba p3: Desencolar devuelve el elemento correcto", heap_desencolar(heap) == &elemento4);
	print_test("Prueba p3: Ver max devuelve el elemento correcto", heap_ver_max(heap) == &elemento1);
	print_test("Prueba p3: La cantidad de elementos es la correcta", heap_cantidad(heap) == 3);
	print_test("Prueba p3: Desencolar devuelve el elemento correcto", heap_desencolar(heap) == &elemento1);
	print_test("Prueba p3: Ver max devuelve el elemento correcto", heap_ver_max(heap) == &elemento3);
	print_test("Prueba p3: La cantidad de elementos es la correcta", heap_cantidad(heap) == 2);
	print_test("Prueba p3: Desencolar devuelve el elemento correcto", heap_desencolar(heap) == &elemento3);
	print_test("Prueba p3: Ver max devuelve el elemento correcto", heap_ver_max(heap) == &elemento2);
	print_test("Prueba p3: La cantidad de elementos es la correcta", heap_cantidad(heap) == 1);
	print_test("Prueba p3: Desencolar devuelve el elemento correcto", heap_desencolar(heap) == &elemento2);
	print_test("Prueba p3: La cantidad de elementos es la correcta", heap_cantidad(heap) == 0);
	print_test("Prueba p3: El heap se encuentra vacio", heap_esta_vacio(heap));

	// Destruyo el heap.
	heap_destruir(heap, NULL);
	print_test("Prueba p3: El heap fue destruido", true);
}



// Pruebas para un heap vacio con funcion de destruccion de datos.
void pruebas_heap_vacio_con_destruccion() {
	printf("-------------INICIO DE PRUEBAS: HEAP VACIO CON DESTRUCCION DE DATOS-------------\n");

	// Declaro las variables a utilizar.
	heap_t* heap = heap_crear(comparar_enteros);

	// Pruebo comportamiento de un heap vacio.
	print_test("Prueba p5: El heap fue creado", heap);
	print_test("Prueba p5: El heap se encuentra vacio", heap_esta_vacio(heap));
	print_test("Prueba p5: La cantidad de elementos es la correcta", heap_cantidad(heap) == 0);
	print_test("Prueba p5: Ver maximo devuelve NULL", heap_ver_max(heap) == NULL);
	print_test("Prueba p5: Desencolar devuelve NULL", heap_desencolar(heap) == NULL);

	// Destruyo el heap.
	heap_destruir(heap, free);
	print_test("Prueba p5: El heap fue destruido", true);
}

// Pruebas para un heap no vacio con funcion de destruccion de datos.
void pruebas_heap_no_vacio_con_destruccion() {
	printf("-------------INICIO DE PRUEBAS: HEAP NO VACIO CON DESTRUCCION DE DATOS-------------\n");

	// Declaro las variables a utilizar.
	heap_t* heap = heap_crear(comparar_enteros);
	int* elemento1 = malloc(sizeof(int));
	int* elemento2 = malloc(sizeof(int));
	int* elemento3 = malloc(sizeof(int));
	*elemento1 = 5456, *elemento2 = 4949494, *elemento3 = 9999;

	// Pruebo encolar elementos.
	print_test("Prueba p6: El heap fue creado", heap);
	print_test("Prueba p6: El heap se encuentra vacio", heap_esta_vacio(heap));
	print_test("Prueba p6: Encolo elemento 1", heap_encolar(heap, elemento1));
	print_test("Prueba p6: Encolo elemento 2", heap_encolar(heap, elemento2));
	print_test("Prueba p6: Encolo elemento 3", heap_encolar(heap, elemento3));
	print_test("Prueba p6: La cantidad de elementos es la correcta", heap_cantidad(heap) == 3);
	print_test("Prueba p6: El heap no se encuentra vacio", !heap_esta_vacio(heap));

	// Destruyo el heap.
	heap_destruir(heap, free);
	print_test("Prueba p6: El heap fue destruido y los datos liberados", true);
}

// Pruebas para un heap no vacio sin funcion de destruccion de datos.
void pruebas_heap_no_vacio_sin_destruccion() {
	printf("-------------INICIO DE PRUEBAS: HEAP NO VACIO SIN DESTRUCCION DE DATOS-------------\n");

	// Declaro las variables a utilizar.
	heap_t* heap = heap_crear(comparar_enteros);
	size_t tam = 10;
	int datos[tam];
	for (int i = 0; i < tam; i++) {
		datos[i] = i;
	}

	// Pruebo encolar elementos.
	bool ok_encolar = true;
	for (size_t i = 0; i < tam; i++) {
		ok_encolar = heap_encolar(heap, &datos[i]);
		if (!ok_encolar) {
			break;
		}
	}

	print_test("Prueba p7: Todos los elementos fueron encolados", ok_encolar && heap_cantidad(heap) == tam);

	// Destruyo el heap.
	heap_destruir(heap, NULL);
	bool datos_no_modificados = true;
	for (size_t i = 0; i < tam; i++) {
		datos_no_modificados = datos[i] == i;
		if (!datos_no_modificados) {
			break;
		}
	}
	print_test("Prueba p7: El heap fue destruido y los datos no fueron modificados", datos_no_modificados);
}

// Pruebas para heap sort.
void pruebas_heap_sort() {
	printf("-------------INICIO DE PRUEBAS: HEAP SORT-------------\n");

	void** arreglo=malloc(sizeof(void*)*10);

	int valor1=5;
	int* dato1=&valor1;

	int valor2=1;
	int* dato2=&valor2;

	int valor3=8;
	int* dato3=&valor3;

	int valor4=9;
	int* dato4=&valor4;

	int valor5=4;
	int* dato5=&valor5;

	int valor6=2;
	int* dato6=&valor6;

	int valor7=10;
	int* dato7=&valor7;

	int valor8=7;
	int* dato8=&valor8;

	int valor9=6;
	int* dato9=&valor9;

	int valor10=3;
	int* dato10=&valor10;

	arreglo[0]=dato1;
	arreglo[1]=dato2;
	arreglo[2]=dato3;
	arreglo[3]=dato4;
	arreglo[4]=dato5;
	arreglo[5]=dato6;
	arreglo[6]=dato7;
	arreglo[7]=dato8;
	arreglo[8]=dato9;
	arreglo[9]=dato10;

	heap_sort(arreglo,10,comparar_enteros);

	bool ok = true;
	for (int i = 0; i < 10 ; ++i){
		int* n = arreglo[i];
		ok &= ( *n == i+1);
	}
	
	print_test("esta ordenado", ok);
	free(arreglo);
}

void prueba_de_volumen_heap(int cantidad){
	heap_t* heap = heap_crear(comparar_enteros);
	int* vector[cantidad];
	for (int i = 1; i <= cantidad ; ++i){
		vector[i-1] = &i;
	}
	print_test("heap esta vacio", heap_esta_vacio(heap));
	bool ok = true;
	for (int i = 0; i < cantidad; ++i){
		ok &= heap_encolar(heap,vector[i]);
		ok &= (heap_ver_max(heap) == vector[i]);
	}
	print_test("se encolaron correctamente todos los datos",ok);
	print_test("la cantidad de datos es el correcto", heap_cantidad(heap) == cantidad);

	for (int i = cantidad-1; i >= 0; --i){
		ok &= (heap_desencolar(heap) == vector[i]);
		if(i > 1) ok &= (heap_ver_max(heap) == vector[i-1]);
	}
	print_test("se desencolaron correctamente todos los datos",ok);
	print_test("el heap esta vacio", heap_esta_vacio(heap));

	heap_destruir(heap,NULL);

}

/* ******************************************************************
 *                        FUNCIÓN PRINCIPAL
 * *****************************************************************/
 
 void pruebas_heap_alumno() {
 	pruebas_heap_vacio();
 	
 	pruebas_heap_encolar();
 	
 	pruebas_heap_desencolar();
 	
 	pruebas_heap_vacio_con_destruccion();
 	
 	pruebas_heap_no_vacio_con_destruccion();
 	
 	pruebas_heap_no_vacio_sin_destruccion();
 	
 	prueba_de_volumen_heap(5000);
 	
 	pruebas_heap_sort();
 
 }