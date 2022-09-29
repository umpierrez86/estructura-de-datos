/* 5083168 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/abb.h"

struct _rep_abb {
	TInfo elem;
	_rep_abb *izq, *der;
};

TAbb crearAbb() { 
	TAbb abb;
	abb = NULL;
	return abb;
}

void liberarAbb(TAbb abb) {
	if(abb != NULL){
		liberarAbb(derecho(abb));
		liberarAbb(izquierdo(abb));
		liberarInfo(raiz(abb));
		delete abb;
	}
}

bool esVacioAbb(TAbb abb) { 
	return abb == NULL;
}

TAbb buscarSubarbol(nat clave, TAbb abb) {
	if(abb == NULL){
		return NULL;
	}else if(natInfo(abb->elem) == clave){
		return abb;
	}else if(natInfo(abb->elem) > clave){
		return buscarSubarbol(clave, abb->izq);
	}else{
		return buscarSubarbol(clave, abb->der);
	}	
}

TInfo raiz(TAbb abb) {
	return abb->elem; 
}

TAbb izquierdo(TAbb abb) {
	return abb->izq; 
}

TAbb derecho(TAbb abb) {
	return abb->der;
}

TInfo menorEnAbb(TAbb abb) {
	if(abb->izq == NULL){
		return abb->elem;
	}else{
		return menorEnAbb(abb->izq);
	}
}

TInfo mayorEnAbb(TAbb abb) {
	if(abb->der == NULL){
		return abb->elem;
	}else{
		return mayorEnAbb(abb->der);
	}
}

TAbb consAbb(TInfo dato, TAbb izq, TAbb der) {
	_rep_abb *abb = new _rep_abb;
	abb->elem = dato;
	abb->izq = izq;
	abb->der = der;
	return abb;
}

TAbb insertarEnAbb(TInfo dato, TAbb abb) {
	TAbb res;
	if(abb == NULL){
		abb = new _rep_abb;
		abb->elem = dato;
		abb->izq = abb->der = NULL;
		res = abb;
	}else{
		if(natInfo(abb->elem) > natInfo(dato)){
			res = abb;
			res->izq = insertarEnAbb(dato,res->izq);
		}
		if(natInfo(abb->elem) < natInfo(dato)){
			res = abb;
			res->der = insertarEnAbb(dato,res->der);
		}
	}
	return res;
}

TAbb removerDeAbb(nat clave, TAbb abb) {
	if(abb != NULL){
		if(natInfo(abb->elem) == clave){
			if(abb->der == NULL){
				_rep_abb *aborrar = abb;
				abb = abb->izq;
				liberarInfo(aborrar->elem);
				delete aborrar;
			}else if(abb->izq == NULL){
				_rep_abb *aborrar = abb;
				abb = abb->der;
				liberarInfo(aborrar->elem);
				delete aborrar;
			}else{
				TInfo max_izq = copiaInfo(mayorEnAbb(abb->izq));
				liberarInfo(abb->elem);
				abb->elem = max_izq;
				abb->izq = removerDeAbb(natInfo(abb->elem),abb->izq);
				//liberarInfo(max_izq);
			}
		}else if(natInfo(abb->elem) > clave){
			abb->izq = removerDeAbb(clave, abb->izq);
		}else{
			abb->der = removerDeAbb(clave, abb->der);
		}
	}return abb;
}

TAbb copiaAbb(TAbb abb) {
	if(abb == NULL){
		return NULL;
	}else{
		_rep_abb *copia = new _rep_abb;
		copia->elem = copiaInfo(abb->elem);
		copia->izq = copiaAbb(abb->izq);
		copia->der = copiaAbb(abb->der);
		return copia;		
	}
}
