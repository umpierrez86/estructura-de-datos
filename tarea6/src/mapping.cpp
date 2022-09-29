/* 5083168 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/mapping.h"
#include "../include/cadena.h"

/*struct nodo{
	TCadena cad;
};
typedef nodo *lista;*/

struct _rep_mapping {
	TCadena *tabla;
	int max;
	int tope;
};

TMapping crearMap(nat M) {
	TMapping map = new _rep_mapping;
	map->max = M;
	map->tope = 0;
	map->tabla = new TCadena[M];
	for(nat i = 0; i < M; i++)
		map->tabla[i] = crearCadena();
	return map;
}

void liberarMap(TMapping map) {
	for(int i = 0; i < map->max; i++){
		liberarCadena(map->tabla[i]);
        //delete map->tabla[i];
    }
	delete [] map->tabla;
	delete map;
	//map->tope = 0;
}

TMapping asociarEnMap(nat clave, double valor, TMapping map) {
	int pos = clave % map->max;
	/*nodo *nuevo = new nodo;
	nuevo->elem = crearInfo(clave,valor);
	nuevo->sig = map->tabla[pos];
	map->tabla[pos] = nuevo;*/
	map->tope = map->tope + 1;
	map->tabla[pos] = insertarAlInicio(clave,valor,map->tabla[pos]);
	return map;
}

TMapping desasociarEnMap(nat clave, TMapping map) {
	int pos = clave % map->max;
	/*while(map->tabla[pos]->clave != clave)*/
	map->tope = map->tope - 1;
	map->tabla[pos] = removerDeCadena(clave, map->tabla[pos]);
	return map;
}

bool esClaveEnMap(nat clave, TMapping map) {
	int pos = clave % map->max;
	/*nodo *iter = map->tabla[pos];
	while(iter != NULL && natInfo(map->tabla[pos]->elem) != clave)
		iter = iter->sig;
	return iter != NULL;*/
	return estaEnCadena(clave,map->tabla[pos]);
}

double valorEnMap(nat clave, TMapping map) {
	int pos = clave % map->max;
	/*double este;
	nodo *iter = map->tabla[pos];
	while(natInfo(map->tabla[pos]->elem) != clave)
		iter = iter->sig;
	este = realInfo(iter->elem);
	return este;*/
	return realInfo(infoCadena(clave,map->tabla[pos]));
}

bool estaLlenoMap(TMapping map) {
	return map->tope == map->max;
}


