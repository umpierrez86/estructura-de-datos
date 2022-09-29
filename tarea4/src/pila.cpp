/* 5083168 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/pila.h"

struct nodo{
  TInfo elem;
  nodo *sig;
};

struct _rep_pila {
  nat cant;
  nodo *primero;
};

TPila crearPila() {
  TPila p = new _rep_pila;
  p->primero = NULL;
  p->cant = 0;
  return p;
}

void liberarPila(TPila p) {
  if(p->primero != NULL){
    nodo *iterador = p->primero;
    while(iterador != NULL){
      nodo *aborrar = iterador;
      liberarInfo(aborrar->elem);
      iterador = iterador->sig;
      delete aborrar;
    }
  }
  delete p;
}

nat cantidadEnPila(TPila p) {
  return p->cant;
}

TPila apilar(TInfo info, TPila p) {
	nodo *nuevo = new nodo;
	nuevo->elem = copiaInfo(info);
	if(p->primero == NULL){
	  nuevo->sig = NULL;
	}else{
	  nuevo->sig = p->primero;
	}
	p->primero = nuevo;
        p->cant = p->cant + 1;
	return p;
}

TInfo cima(TPila p) {
  return p->primero->elem;
}

TPila desapilar(TPila p) {
	nodo* aborrar = p->primero;
	p->primero = p->primero->sig;
	liberarInfo(aborrar->elem);
	delete aborrar;
	p->cant = p->cant - 1;
	return p;
}
