/* 5083168 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

struct _rep_cadena {
	TInfo elem;
	_rep_cadena *sig;
	_rep_cadena *ant;
};



TCadena crearCadena() { 
  TCadena cad;
  cad = NULL;
  return cad;//NULL
}


void liberarCadena(TCadena cad) {
	if(cad != NULL){
		//TCadena principio = cad;
		TCadena aux = cad->sig;
		while(aux != cad){
			TCadena aborrar = aux;
			aux = aux->sig;
			liberarInfo(aborrar->elem);
			delete aborrar;
	        }
		liberarInfo(cad->elem);
	    delete cad;
	    //cad = NULL;
	}
}


nat cantidadEnCadena(TCadena cad) {
  int contador = 0;
  if(cad == NULL){
  	return contador; 
  }else{
  	contador = 1;
  	TCadena primero = cad;
  	TCadena actual = cad->sig;
  	while(actual != primero){
  		contador = contador + 1;
  		actual = actual->sig;
  	}
  	return contador;//0
  }//else
}

bool estaEnCadena(nat natural, TCadena cad) {
  if(cad == NULL){
  	return false;
  }else if(natInfo(cad->elem) == natural){
  	return true;
  }else{
  	//TCadena primero = cad;
  	TCadena actual = cad->sig;
  	while(actual != cad && natInfo(actual->elem) != natural){
  		actual = actual->sig;
  	}
  	return (actual != cad);//false
  }//else
}

TCadena insertarAlInicio(nat natural, double real, TCadena cad) {
  _rep_cadena *nuevo = new _rep_cadena;
  nuevo->elem = crearInfo(natural,real);
  if(cad == NULL){
  	nuevo->sig = nuevo;
  	nuevo->ant = nuevo;
  	cad = nuevo;
  }else{
  	TCadena ultimo = cad->ant;
  	nuevo->sig = cad;
  	ultimo->sig = nuevo;
  	cad->ant = nuevo;
  	nuevo->ant = ultimo;
  	cad = nuevo;
  }//else
  return cad;//NULL
}

TInfo infoCadena(nat natural, TCadena cad) {
  if(natInfo(cad->elem) == natural){
  	return cad->elem;
  }else{
  	TCadena aux = cad->sig;
  	while(aux != cad && natInfo(aux->elem) != natural){
  		aux = aux->sig;
  	}
  	return aux->elem;//NULL
  }//else
}

TInfo primeroEnCadena(TCadena cad) {
  return cad->elem;//NULL
}

TCadena cadenaSiguiente(TCadena cad) {
  if(cad == NULL || cad == cad->sig){
  	return cad;
  }else{
  	cad = cad->sig;
  	return cad;	
  }//else
}//NULL

TCadena removerDeCadena(nat natural, TCadena cad) {
  if(natInfo(cad->elem) == natural){
  	if(cad == cad->sig){
  		liberarInfo(cad->elem);
  		delete cad;
		cad = NULL;
  		return cad;
  	}else{
  		TCadena aux = cad;
  		TCadena ultimo = cad->ant;
  		cad = cad->sig;
  		ultimo->sig = cad;
  		cad->ant = ultimo;
  		liberarInfo(aux->elem);
  		delete aux;
  		return cad;
       }
    }else{
  	TCadena aux = cad->sig;
  	while(aux != cad && natInfo(aux->elem) != natural){
  		aux = aux->sig;
  	}
  	TCadena anterior = aux->ant;
  	TCadena siguiente = aux->sig;
  	anterior->sig = siguiente;
  	siguiente->ant = anterior;
  	liberarInfo(aux->elem);
  	delete aux; 
  	return cad;
  }//else
}//NULL

void imprimirCadena(TCadena cad) {
	if(cad != NULL){
		TCadena aux = cad->sig;
		imprimirInfo(cad->elem);
		while(aux != cad){
			imprimirInfo(aux->elem);
			aux = aux->sig;
	    }
	}
	printf("\n");
}
