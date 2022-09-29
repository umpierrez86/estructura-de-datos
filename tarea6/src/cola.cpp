/* 5083168 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/cola.h"

struct nodo{
	TInfo elem;
	nodo *sig;
};

struct _rep_cola {
	nodo *primero; 
	nodo *ultimo;
	nat cant;
};

TCola crearCola() {
	TCola c = new _rep_cola;
	c->primero = NULL;
	c->ultimo = NULL;
	c->cant = 0;
	return c;
}

void liberarCola(TCola c) {
	nodo *iterador = c->primero;
	if(c->primero != NULL){
		while(iterador != NULL){
			nodo *aborrar = iterador;
			liberarInfo(aborrar->elem);
			iterador = iterador->sig;
			delete aborrar;
		} 
	}
	delete c;
}

nat cantidadEnCola(TCola c) {
	return c->cant;
}

TCola encolar(TInfo info, TCola c) {
	nodo *nuevo = new nodo;
	nuevo->elem = copiaInfo(info);
	nuevo->sig = NULL;
	if(c->primero == NULL){
		c->primero = nuevo;
		c->ultimo = nuevo;
	}else{
		c->ultimo->sig = nuevo;
		c->ultimo = nuevo;
	}
	c->cant = c->cant + 1;
	return c;
}

TInfo frente(TCola c) {
	return c->primero->elem;
}

TCola desencolar(TCola c) {
	nodo *aborrar;
	aborrar = c->primero;
	c->primero = c->primero->sig;
	liberarInfo(aborrar->elem);
	delete aborrar;
	c->cant = c->cant - 1;
	return c;
}
