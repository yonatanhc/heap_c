#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "heap.h"

#define CAPACIDAD_INICIAL 100
#define FACTOR_REDIMENSION 2

struct heap{
	void** datos;
	size_t cantidad;
	size_t capacidad;
	cmp_func_t cmp;
};


bool redimensionar(heap_t* heap, size_t nueva_capacidad){
	void** datos = malloc(sizeof(void*)*nueva_capacidad);
	if(nueva_capacidad > 0 && !datos){
		return false;
	}
	for (int i = 0; i < nueva_capacidad; ++i){
		datos[i] = NULL;
	}
	for (int i = 0; i < heap->cantidad; ++i){
		datos[i] = heap->datos[i];
	}
	free(heap->datos);
	heap->datos = datos;
	heap->capacidad = nueva_capacidad;
	return true;
}

heap_t *heap_crear(cmp_func_t cmp) {
	heap_t* heap = malloc(sizeof(heap_t));
	if(!heap) return NULL;
	void** datos = malloc(sizeof(void*)*CAPACIDAD_INICIAL);
	if(CAPACIDAD_INICIAL > 0 && !datos){
		free(heap);
		return NULL;
	}
	for (int i = 0; i < CAPACIDAD_INICIAL; ++i){
		datos[i] = NULL;
	}
	heap->datos = datos;
	heap->cantidad = 0;
	heap->cmp = cmp;
	heap->capacidad = CAPACIDAD_INICIAL;
	return heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp) {
	heap_t* heap = malloc(sizeof(heap_t));
	if(!heap) return NULL;
	heap->datos = malloc(sizeof(void*)*CAPACIDAD_INICIAL);
	if(CAPACIDAD_INICIAL > 0 && !heap->datos){
		free(heap);
		return NULL;
	}
	for (int i = 0; i < CAPACIDAD_INICIAL; ++i){
		heap->datos[i] = NULL;
	}
	heap->cantidad = 0;
	heap->cmp = cmp;
	heap->capacidad = CAPACIDAD_INICIAL;
	for (int i = 0; i < n; ++i){
		heap_encolar(heap,arreglo[i]);
	}

	return heap;
}

void upheap(heap_t* heap,size_t posicion){
	if(posicion > 0){
		size_t padre = ((posicion - 1)/2);
		int comparar = heap->cmp(heap->datos[padre],heap->datos[posicion]) ;
		if(comparar < 0) {
			void* aux=heap->datos[padre];
			heap->datos[padre]=heap->datos[posicion];
			heap->datos[posicion]=aux;
			upheap(heap,padre);
		} 
	}
}

bool heap_encolar(heap_t *heap, void *elem){
	if (heap->cantidad >= heap->capacidad){
		if(!redimensionar(heap,FACTOR_REDIMENSION*heap->capacidad)) return false;
	}
	heap->datos[heap->cantidad] = elem;
	heap->cantidad++;
	upheap(heap,heap->cantidad - 1);
	return true;
}

void downheap(void** datos,int posicion,cmp_func_t cmp,int cantidad){
	int hijo_izq = 2*posicion + 1;
	int hijo_der = 2*posicion + 2;
	int comparar;
	int comparar_aux;
	int pos_aux;
	if (hijo_izq > cantidad && hijo_der > cantidad) return;
	if (hijo_izq <= cantidad && hijo_der <= cantidad){
		comparar = cmp(datos[hijo_izq],datos[hijo_der]);
		if(comparar < 0) {
			comparar_aux = cmp(datos[posicion],datos[hijo_der]);
			pos_aux = hijo_der;
		}
		else {
			comparar_aux = cmp(datos[posicion],datos[hijo_izq]);
			pos_aux = hijo_izq;
		}
	}
	else {
		if(hijo_izq <= cantidad) {
		 	comparar_aux = cmp(datos[posicion],datos[hijo_izq]);
		 	pos_aux = hijo_izq;
		}
		else {
			comparar_aux = cmp(datos[posicion],datos[hijo_der]);
			pos_aux = hijo_der;
		}
	}
	if(comparar_aux < 0) {
		void* aux=datos[posicion];
		datos[posicion]=datos[pos_aux];
		datos[pos_aux]=aux;
		downheap(datos,pos_aux,cmp,cantidad);
	}
	return;

}

size_t heap_cantidad(const heap_t *heap) {
	return heap->cantidad;
}

bool heap_esta_vacio(const heap_t *heap) {
	return heap_cantidad(heap) == 0;
}

void *heap_desencolar(heap_t *heap) {
	if(heap_esta_vacio(heap)) return NULL;
	void* dato = heap->datos[0];
	void* aux=heap->datos[0];
	heap->datos[0]=heap->datos[heap->cantidad-1];
	heap->datos[heap->cantidad-1]=aux;
	heap->cantidad--;
	int cant = (int)heap->cantidad;
	if(heap->cantidad > 1) downheap(heap->datos,0,heap->cmp,cant-1);
	return dato;
}

void *heap_ver_max(const heap_t *heap) {
	if(heap_esta_vacio(heap)) return NULL;
	return heap->datos[0];
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
	while(!heap_esta_vacio(heap)){
		void* aux = heap_desencolar(heap);
		if(destruir_elemento) destruir_elemento(aux); 
	}
	free(heap->datos);
	free(heap);
}

void heapify(void *elementos[], int cant, cmp_func_t cmp){
	for (int  i = cant-1; i >= 0; i--){
		int  padre = (i-1)/2;
		if(padre >= 0){
			if(cmp(elementos[padre],elementos[i]) < 0) {
				void* aux=elementos[padre];
				elementos[padre]=elementos[i];
				elementos[i]=aux;
				downheap(elementos,i,cmp,cant-1);
			}
		}	
	}
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp) {
	int cantidad = (int)cant;
	heapify(elementos,cantidad,cmp);
	int  ultimo = cantidad - 1;
	int primero = 0;
	while (ultimo > 0){
		void* aux=elementos[primero];
		elementos[primero]=elementos[ultimo];
		elementos[ultimo]=aux;
		ultimo--;
		if(ultimo > 0) downheap(elementos,primero,cmp,ultimo);
		
	}

}