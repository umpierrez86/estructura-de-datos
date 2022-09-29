/* 5083168 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/iterador.h"

struct nodo{
  nat elem;
  nodo *sig;
};

struct _rep_iterador {
  nodo *primero;
  nodo *actual;
  nodo *ultimo;
};

TIterador crearIterador() {
  _rep_iterador *iter = new _rep_iterador;
  iter->primero = NULL;
  iter->actual = NULL;
  iter->ultimo = NULL;
  return iter;
}

void liberarIterador(TIterador iter) {
  if(iter->primero != NULL){
    nodo *aborrar;
    iter->actual = iter->primero;
    while(iter->actual != NULL){
      aborrar = iter->actual;
      iter->actual = aborrar->sig;
      delete aborrar;
    }
  }
  delete iter;
}

bool estaDefinidaActual(TIterador iter) {
  return (iter->actual != NULL);
}

void agregarAIterador(nat elem, TIterador const iter) {
  nodo *nuevo = new nodo;
  nuevo->elem = elem;
  nuevo->sig = NULL;
  if(iter->primero == NULL){
    iter->primero = nuevo;
    iter->ultimo = nuevo;
  }else{
    iter->ultimo->sig = nuevo;
    iter->ultimo = nuevo;
  }
}

void reiniciarIterador(TIterador const iter) {
  if(iter->primero != NULL){
    iter->actual = iter->primero;
  }
}

void avanzarIterador(TIterador const iter) {
  if(iter->actual == NULL){
    iter->actual = NULL;
  }else{
    iter->actual = iter->actual->sig;
  }
}

nat actualEnIterador(TIterador iter) {
  return iter->actual->elem;
}
