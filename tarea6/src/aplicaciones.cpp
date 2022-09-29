/* 5083168 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/aplicaciones.h"
#include "../include/colCadenas.h"
#include "../include/mapping.h"

int max(int a, int b){
	if(a>b)
		return a;
	else if(a<b)
		return b;
	else
		return a;	
}

int esAvlAux(TAbb abb, bool &es){
	if(es){
		if(esVacioAbb(abb))
			return 0;
		else{
			int izq = esAvlAux(izquierdo(abb),es);	
			int der = esAvlAux(derecho(abb),es);	
			if((izq-der) > 1 || (izq-der) < -1)
				es = false;
			return max(izq,der) + 1;
		}
	}else
		return 0;
}

bool esAvl(TAbb abb) {
	bool es = true;
	if(!esVacioAbb(abb))
		esAvlAux(abb, es);
	return es;
}

TAbb avlMinAux(nat &ini, nat h){
	if(h == 0){
        return crearAbb();
    }else if(h == 1){
        TInfo info = crearInfo(ini,0);
        ini++;
        return consAbb(info,crearAbb(),crearAbb());
    }else{
        TAbb izq = avlMinAux(ini,h-1);
        TInfo info = crearInfo(ini,0);
        ini++;
        TAbb der = avlMinAux(ini,h-2);
        return consAbb(info,izq,der);
    }
}	

TAbb avlMin(nat h) {
	TAbb nuevo = crearAbb();
	//int contador = 0;
    nat ini = 1;
	nuevo = avlMinAux(ini, h);
	return nuevo;	
}

TCadena filtradaOrdenada(TCadena cad, TIterador it) {
	TCadena res = crearCadena();
	reiniciarIterador(it);
	nat cant = cantidadEnCadena(cad);
	if(cant != 0 && estaDefinidaActual(it)){
		TMapping map = crearMap(cant);
		for(nat i = 0; i < cant; i++){
			if(!esClaveEnMap(natInfo(primeroEnCadena(cad)), map)){
				map = asociarEnMap(natInfo(primeroEnCadena(cad)), 					realInfo(primeroEnCadena(cad)), map);
				cad = cadenaSiguiente(cad);
			}else{
				double viejo = valorEnMap(natInfo(primeroEnCadena(cad)), map);
				map = desasociarEnMap(natInfo(primeroEnCadena(cad)), map);
				map = asociarEnMap(natInfo(primeroEnCadena(cad)), 					realInfo(primeroEnCadena(cad)) + viejo, map);
				cad = cadenaSiguiente(cad);
			}	
		}
		while(estaDefinidaActual(it)){
            if(esClaveEnMap(actualEnIterador(it),map))
                res = insertarAlFinal(actualEnIterador(it), 						valorEnMap(actualEnIterador(it), map), res);
			avanzarIterador(it);
		}
        liberarMap(map);
	}
	return res;
}

bool estaOrdenada(TCadena cad) {
	nat cant = cantidadEnCadena(cad);
	if(cant == 0)
		return true;
	else{
		nat elem = natInfo(primeroEnCadena(cad));
		TCadena aux = cadenaSiguiente(cad);
		while(elem < natInfo(primeroEnCadena(aux)) && aux != cad){
			elem = natInfo(primeroEnCadena(aux));
			aux = cadenaSiguiente(aux);
		}
		return aux == cad;
	}
}

TCadena mezclaCadenas(TCadena cad1, TCadena cad2) {
	TCadena nueva = crearCadena();
	int contador1 = cantidadEnCadena(cad1);
	int contador2 = cantidadEnCadena(cad2);
	if(contador1 == 0 && contador2 == 0)
		nueva = crearCadena();
	else if(contador2 == 0){
		nueva = copiaCadena(cad1);	
	}else if(contador1 == 0){
		nueva = copiaCadena(cad2);
	}else{
		//int contador1 = cantidadEnCadena(cad1);
		//int contador2 = cantidadEnCadena(cad2);
		while(contador1 != 0 || contador2 != 0){
			if(contador2 == 0){
				TInfo info = primeroEnCadena(cad1);
				nueva = insertarAlFinal(natInfo(info),realInfo(info),nueva);
				cad1 = cadenaSiguiente(cad1);
				contador1 = contador1 - 1;
			}
			else if(contador1 == 0){
				TInfo info = primeroEnCadena(cad2);
				nueva = insertarAlFinal(natInfo(info),realInfo(info),nueva);
				cad2 = cadenaSiguiente(cad2);
				contador2 = contador2 - 1;
			}else if(natInfo(primeroEnCadena(cad1)) == 					natInfo(primeroEnCadena(cad2))){
				TInfo info = primeroEnCadena(cad1);
				nueva = insertarAlFinal(natInfo(info),realInfo(info),nueva);
				cad1 = cadenaSiguiente(cad1);
				cad2 = cadenaSiguiente(cad2);
				contador1 = contador1 - 1;
				contador2 = contador2 - 1;
			}else if(natInfo(primeroEnCadena(cad1)) > 					natInfo(primeroEnCadena(cad2))){
				TInfo info = primeroEnCadena(cad2);
				nueva = insertarAlFinal(natInfo(info),realInfo(info),nueva);
				cad2 = cadenaSiguiente(cad2);
				contador2 = contador2 - 1;
			}else{
				TInfo info = primeroEnCadena(cad1);
				nueva = insertarAlFinal(natInfo(info),realInfo(info),nueva);
				cad1 = cadenaSiguiente(cad1);
				contador1 = contador1 - 1;
			}
		}
		
	}
	return nueva;	
}

TAbb cosoBalanceado(TInfo *arreglo,int ini, int fin){
	//TAbb nuevo = crearAbb();
	int mitad = (ini + fin)/2;
	TAbb izq = crearAbb();
	TAbb der = crearAbb();
	TInfo raiz = copiaInfo(arreglo[mitad]);
	if(ini != mitad){
		izq = cosoBalanceado(arreglo,ini,mitad-1);
	}
	if(fin != mitad){
		der = cosoBalanceado(arreglo,mitad+1,fin);
	}
	return consAbb(raiz,izq,der);
}

TAbb crearBalanceado(TInfo *arreglo, nat n) {
	TAbb nuevo = crearAbb();
	if(n == 0)
		return nuevo;
	else{
		nuevo = cosoBalanceado(arreglo,0,n-1);
		return nuevo;
	}
}

TAbb unionAbbs(TAbb abb1, TAbb abb2) {
	TCadena cad1 = linealizacion(abb1);
	TCadena cad2 = linealizacion(abb2);
	TCadena res = mezclaCadenas(cad1,cad2);
	nat contador = cantidadEnCadena(res);
	TInfo arreglo[contador];
	for(nat i = 0; i < contador; i++){
		arreglo[i] = copiaInfo(primeroEnCadena(res));
		res = cadenaSiguiente(res);
	}
	TAbb nuevo = crearBalanceado(arreglo,contador);
	for(nat i = 0; i < contador; i++){
		liberarInfo(arreglo[i]);
	}
	//delete arreglo;
	liberarCadena(cad1);
	liberarCadena(cad2);
	liberarCadena(res);
	return nuevo;
}

void insertarRev(TCola c, TCadena cad, nat cuantos){
	if(cuantos != 0){
		insertarRev(c,cadenaSiguiente(cad),cuantos-1);
		c = encolar(primeroEnCadena(cad),c);
	}
}

TCola ordenadaPorModulo(nat p, TCadena cad) {
	TColCadenas col = crearColCadenas(p);
	TCola c = crearCola();
	nat cant = cantidadEnCadena(cad);
	if(cant != 0){
		for(nat i = 0; i < cant; i++){
			TInfo info = copiaInfo(primeroEnCadena(cad));
			nat pos = natInfo(info) % p;
			col = insertarEnColCadenas(natInfo(info),realInfo(info),pos,col);
			cad = cadenaSiguiente(cad);
			liberarInfo(info);
		}
		//nat indice = 0;
		for(nat i = 0; i < p; i++){
			nat cuantos = cantidadColCadenas(i,col);
			if(cuantos != 0){
				TCadena cade = cadenaDeColCadenas(i,col);
				insertarRev(c,cade,cuantos);
				/*for(nat i = 0; i <= cuantos; i++){
					TCadena cade = cadenaDeColCadenas(indice,col);
					c = encolar(primeroEnCadena(cade),c);
					cade = cadenaSiguiente(cade);
				}*/
			}
			//indice = indice + 1;
		}
	}
	liberarColCadenas(col);
	return c;	
}

TPila menoresQueElResto(TCadena cad, nat cantidad) {
	TPila p = crearPila();
	while(cantidad != 0){
	  while(cantidadEnPila(p) != 0 &&  natInfo(cima(p)) >= natInfo(primeroEnCadena(cad)))
		p = desapilar(p);
	  p = apilar(primeroEnCadena(cad),p);
	  cad = cadenaSiguiente(cad);
	  cantidad = cantidad - 1;
	}
	return p;
}

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

int min(int a, int b){
	if(a<b)
		return a;
	else if(a>b)
		return b;
	else
		return a;	
}

int esPerfectAux(TAbb abb, bool &es){
	if(esVacioAbb(abb))
		return 0;		
	else{
		int izq = esPerfectAux(izquierdo(abb),es);			
		int der = esPerfectAux(derecho(abb),es);
		if(izq != der)
			es = false;
		return min(izq,der) + 1;
	}
}

bool esPerfecto(TAbb abb) {
	bool es = true;
	if(!esVacioAbb(abb))
		esPerfectAux(abb, es);
	return es;
}

TAbb menores(double limite, TAbb abb) {
	TAbb res;
	if(esVacioAbb(abb)){
		res = crearAbb();
	}else{
		TAbb izq = menores(limite, izquierdo(abb));
		TAbb der = menores(limite, derecho(abb));
		if(realInfo(raiz(abb)) < limite){
			TInfo elcopia = copiaInfo(raiz(abb));
			res = consAbb(elcopia, izq, der);
		}else if(esVacioAbb(izq)){
			res = der;
		}else if(esVacioAbb(der)){
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

void  auxreverso(TIterador copia, TIterador iter,nat elcopia){
  if(estaDefinidaActual(iter)){
    elcopia = actualEnIterador(iter);
    avanzarIterador(iter);
    auxreverso(copia,iter,elcopia);
    if(!estaDefinidaActual(iter)){
		agregarAIterador(elcopia,copia);
    }
  }
}

TIterador reversoDeIterador(TIterador iter) {
	TIterador copia = crearIterador();
  	nat elcopia = 0;
  	reiniciarIterador(iter);
  	if(estaDefinidaActual(iter))
    		auxreverso(copia,iter,elcopia);
  	return copia;
}
