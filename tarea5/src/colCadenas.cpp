/* 5083168 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/colCadenas.h"

struct _rep_colCadenas {
	TCadena *colcadenas;
	nat cota;
};

TColCadenas crearColCadenas(nat tamanio) {
	TColCadenas col = new _rep_colCadenas;
	col->colcadenas = new TCadena [tamanio];
	col->cota = 0;
  	for(nat i=0; i < tamanio; i++){
    	col->colcadenas[i] = crearCadena();
    	col->cota = col->cota + 1;
  	}
  	return col;
}

void liberarColCadenas(TColCadenas col) {
	nat top = 0;
  	while(top < col->cota){
    	liberarCadena
     	(col->colcadenas[top]);
     	top = top + 1;
    }
    delete [] col->colcadenas;
  	delete col;
}

nat tamanioColCadenas(TColCadenas col) {
	return col->cota;
}

TCadena cadenaDeColCadenas(nat pos, TColCadenas col) {
	return col->colcadenas[pos];
}

nat cantidadColCadenas(nat pos, TColCadenas col) {
	return cantidadEnCadena(col->colcadenas[pos]);
}

bool estaEnColCadenas(nat natural, nat pos, TColCadenas col) {
	return estaEnCadena(natural,col->colcadenas[pos]);
}

TColCadenas insertarEnColCadenas(nat natural, double real, nat pos,
                                 TColCadenas col) {
  col->colcadenas[pos] = insertarAlInicio(natural,real,col->colcadenas[pos]);
  return col;
}

TInfo infoEnColCadenas(nat natural, nat pos, TColCadenas col) {
	return infoCadena(natural,col->colcadenas[pos]);
}

TColCadenas removerDeColCadenas(nat natural, nat pos, TColCadenas col) {
  col->colcadenas[pos] = removerDeCadena(natural,col->colcadenas[pos]);
  return col;
}
