/* 1234567 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/colCadenas.h"
#include "../include/cadena.h"

struct _rep_colCadenas {
  TCadena colcadenas[CANT_CADS];
};

TColCadenas crearColCadenas() {
  TColCadenas col = new _rep_colCadenas;
  for(int i=0; i < CANT_CADS; i++){
    col->colcadenas[i] = crearCadena();
  }
  return col;
}

void liberarColCadenas(TColCadenas col) {
  nat top = 0;
  while(top < CANT_CADS){
     liberarCadena
     (col->colcadenas[top]);
     top = top + 1;
    }
  delete col;
}

TCadena cadenaDeColCadenas(nat pos, TColCadenas col) {
  return col->colcadenas[pos] ;
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
