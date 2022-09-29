/* 5083168 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/aplicaciones.h"
//#include <stdio.h>

TCadena linealizacionAux(TAbb abb, TCadena cad){
	if(!(esVacioAbb(abb))){
		cad = insertarAlInicio(natInfo(raiz(abb)), realInfo(raiz(abb)), cad);
		if(!esVacioAbb(izquierdo(abb))){
			//cad = cadenaSiguiente(cad);
			linealizacionAux(izquierdo(abb), cad);
		}
		cad = cadenaSiguiente(cad);
		if(!esVacioAbb(derecho(abb)))
			linealizacionAux(derecho(abb), cad);
	}
	return cad;
}

TCadena linealizacion(TAbb abb) {
	TCadena cad = crearCadena();
	if(!(esVacioAbb(abb))){
		cad = linealizacionAux(abb, cad);
	}
	return cad;
}

void imprimirAux(TAbb abb, int contador){
	if(!(esVacioAbb(abb))){
		if(!(esVacioAbb(derecho(abb))))
			imprimirAux(derecho(abb), contador+1);
		for(int i = 1; i <= contador; i++){
			printf("-");
		}
		//printf("\n");
		imprimirInfo(raiz(abb));
		printf("\n");
		if(!(esVacioAbb(izquierdo(abb))))
			imprimirAux(izquierdo(abb), contador + 1);
	}
}


void imprimirAbb(TAbb abb) {
	int contador = 0;
	if(!esVacioAbb(abb))
		imprimirAux(abb,contador);
}

int max(int a, int b){
	if(a > b)
		return a;
	else if(a < b)
		return b;
	else
		return a;
}

int pow(int numero, int potencia){
	if(potencia <= 0){
		return 1;
	}else{
		return numero * pow(numero, potencia - 1);
	}
}

int contarHojas(TAbb abb){
	if(abb == NULL){
		return 0;
	}else if(izquierdo(abb) == NULL && derecho(abb) == NULL){
		return 1;
	}else
		return contarHojas(izquierdo(abb)) + contarHojas(derecho(abb));
	
}

int altura(TAbb abb){
	if(abb == NULL){
		return 0;
	}else
		return 1 + max(altura(izquierdo(abb)),altura(derecho(abb)));
}

bool esPerfecto(TAbb abb) {
	if(abb == NULL){
		return true;
	}else{ 
		int cant_hojas = contarHojas(abb);
		int alt = altura(abb);
		int potencia = pow(2, alt - 1);
		return potencia == cant_hojas;
	}
}


TAbb menores(double limite, TAbb abb) {
	TAbb res;
	if(abb == NULL){
		res = NULL;
	}else{
		TAbb izq = menores(limite, izquierdo(abb));
		TAbb der = menores(limite, derecho(abb));
		if(realInfo(raiz(abb)) < limite){
			TInfo elcopia = copiaInfo(raiz(abb));
			res = consAbb(elcopia, izq, der);
		}else if(izq == NULL){
			res = der;
		}else if(der == NULL){
			res = izq;
		}else{
			TInfo mayor = copiaInfo(mayorEnAbb(izq));
			res = consAbb(mayor, izq, der);
			res = removerDeAbb(natInfo(mayor),res);
		}
	}
	return res;
}

nat contarElems(TIterador iter){
	reiniciarIterador(iter);
	nat cantidad = 0;
	while(estaDefinidaActual(iter)){
		cantidad = cantidad + 1;
		avanzarIterador(iter);
	}
	return cantidad;
}

TIterador caminoAux(nat clave, nat k, TAbb abb, TIterador iter){
	TInfo elem = copiaInfo(raiz(abb));
	if(clave != natInfo(raiz(abb))){
		if(clave < natInfo(raiz(abb)))
			iter = caminoAux(clave, k, izquierdo(abb), iter);
		else
			iter = caminoAux(clave,k,derecho(abb),iter);
	}
	nat cant = contarElems(iter);
	if(cant < k){
		agregarAIterador(natInfo(elem), iter);
		//cant = cant + 1;
		//liberarInfo(elem);
	}
	liberarInfo(elem);
	return iter;
}

TIterador caminoAscendente(nat clave, nat k, TAbb abb) {
	TIterador iter = crearIterador();
	//nat cant = 0;
	iter = caminoAux(clave, k, abb, iter);
	return iter;
}

void imprimirPalabrasAux(nat k, TPalabras palabras,ArregloChars aux, nat contador){
	if(letra(palabras) == '\0'){
		aux[contador] = '\0';
		printf("%s",aux);
		printf("\n");
	}else if(contador<k){	
		aux[contador] = letra(palabras);
		imprimirPalabrasAux(k,subarboles(palabras),aux,contador+1);
	}
	if(siguientes(palabras) != NULL)
		imprimirPalabrasAux(k,siguientes(palabras),aux,contador);
}

void imprimirPalabrasCortas(nat k, TPalabras palabras) {
	nat contador = 0;
	char aux[k];
	imprimirPalabrasAux(k,subarboles(palabras),aux,contador);
}

TPalabras PrefijoAux(ArregloChars prefijo, TPalabras palabras, nat contador){
	if(palabras != NULL){
		if(prefijo[contador] == letra(palabras)){
			if(prefijo[contador+1] == '\0')
				return palabras;
			else
				return PrefijoAux(prefijo,subarboles(palabras),contador+1);
		}//if(siguientes(palabras) != NULL)
		return PrefijoAux(prefijo,siguientes(palabras),contador);
	}
	return palabras;
}

TPalabras buscarFinPrefijo(ArregloChars prefijo, TPalabras palabras) {
	nat contador = 0;	
	palabras = PrefijoAux(prefijo,subarboles(palabras),contador);
	return palabras;
}
