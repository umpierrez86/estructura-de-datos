/* 5083168 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/aplicaciones.h"
#include "../include/cadena.h"
#include "../include/iterador.h"


TCadena insertarAlFinal(nat natural, double real, TCadena cad) {
    cad = insertarAlInicio(natural,real,cad);
    cad = cadenaSiguiente(cad);
    return cad;
}

TCadena removerPrimero(TCadena cad) {
    TInfo primero = primeroEnCadena(cad);
    cad = removerDeCadena(natInfo(primero),cad);
    return cad;
}


TCadena copiaCadena(TCadena cad) {
    TCadena copia = crearCadena();
    nat contador = cantidadEnCadena(cad);
    for(nat i=0; i<contador; i++){
        TInfo info = primeroEnCadena(cad);
        copia = insertarAlFinal(natInfo(info),realInfo(info),copia);
        cad = cadenaSiguiente(cad);
    }
    return copia;
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

