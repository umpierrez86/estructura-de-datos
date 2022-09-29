/* 5083168 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/colaDePrioridad.h"
#include "../include/info.h"

struct _rep_colaDePrioridad {
  TInfo *heap;
  nat tope;
  nat *posiciones;
  nat max;
  int tipo;
};

TColaDePrioridad crearCP(nat N) {
  TColaDePrioridad cp = new _rep_colaDePrioridad;
  cp->tope = 0;
  cp->tipo = 1;
  cp->heap = new TInfo[N+1];
  cp->posiciones = new nat[N+1];
  cp->max = N;
  /*for(nat i = 1; i <= N; i++)
    cp->heap[i] = NULL;*/
  for(nat i = 1; i <= N; i++)
		cp->posiciones[i] = 0;
  return cp;
}

bool comparacion(TInfo a, TInfo b, int tipo){
  return (realInfo(a)-realInfo(b))*tipo < 0;
}

void filtradoAscendente(TColaDePrioridad &cp, nat pos){
  TInfo inicial = cp->heap[pos];
  while(pos > 1 && comparacion(inicial, cp->heap[pos/2], cp->tipo)){
    cp->heap[pos] = cp->heap[pos/2];
    cp->posiciones[natInfo(cp->heap[pos])] = pos;
    pos = pos/2;
  }
  cp->heap[pos] = inicial;
  cp->posiciones[natInfo(cp->heap[pos])] = pos;
}

/*void filtradoAscendente(TColaDePrioridad &cp, nat pos, int tipo){
  if(tipo == 1){
    TInfo inicial = cp->heap[pos];
    while(pos > 1 && realInfo(cp->heap[pos/2]) > realInfo(inicial)){
      cp->heap[pos] = cp->heap[pos/2];
      cp->posiciones[natInfo(cp->heap[pos])] = pos;
      pos = pos/2;
    }
    cp->heap[pos] = inicial;
    cp->posiciones[natInfo(cp->heap[pos])] = pos;
  }else{
    TInfo inicial = cp->heap[pos];
    while(pos > 1 && realInfo(cp->heap[pos/2]) < realInfo(inicial)){
      cp->heap[pos] = cp->heap[pos/2];
      cp->posiciones[natInfo(cp->heap[pos])] = pos;
      pos = pos/2;
    }
    cp->heap[pos] = inicial;
    cp->posiciones[natInfo(cp->heap[pos])] = pos;
  }
}*/

void filtradoDescendente(TColaDePrioridad cp, nat n, nat pos){
  if(2*pos <= n){
    nat cambio = 2*pos;
    if((2*pos+1 <= n) && comparacion(cp->heap[2*pos+1],cp->heap[cambio], cp->tipo))
      cambio = 2*pos+1;
    if(comparacion(cp->heap[cambio], cp->heap[pos], cp->tipo)){
      TInfo swap = cp->heap[pos];
      double lugar = cp->posiciones[natInfo(cp->heap[pos])];
      cp->heap[pos] = cp->heap[cambio];
      cp->heap[cambio] = swap;
      cp->posiciones[natInfo(cp->heap[cambio])] = cp->posiciones[natInfo(cp->heap[pos])];
      cp->posiciones[natInfo(cp->heap[pos])] = lugar;
      filtradoDescendente(cp,n,cambio);
    }
  }
}

/*void filtradoDescendente(TColaDePrioridad cp, nat n, nat pos, int tipo){
  if(tipo == 1){
    if(2*pos <= n){
      nat cambio = 2*pos;
      if((2*pos+1 <= n) && realInfo(cp->heap[2*pos+1]) < realInfo(cp->heap[cambio]))
        cambio = 2*pos+1;
      if(realInfo(cp->heap[cambio]) < realInfo(cp->heap[pos])){
        TInfo swap = cp->heap[pos];
        double lugar = cp->posiciones[natInfo(cp->heap[pos])];
        cp->heap[pos] = cp->heap[cambio];
        cp->heap[cambio] = swap;
        cp->posiciones[natInfo(cp->heap[cambio])] = cp->posiciones[natInfo(cp->heap[pos])];
        cp->posiciones[natInfo(cp->heap[cambio])] = lugar;
        filtradoDescendente(cp,n,cambio,tipo);
      }
    }
  }else{
    if(2*pos <= n){
      nat cambio = 2*pos;
      if((2*pos+1 <= n) && realInfo(cp->heap[2*pos+1]) > realInfo(cp->heap[cambio]))
        cambio = 2*pos+1;
      if(realInfo(cp->heap[cambio]) > realInfo(cp->heap[pos])){
        TInfo swap = cp->heap[pos];
        double lugar = cp->posiciones[natInfo(cp->heap[pos])];
        cp->heap[pos] = cp->heap[cambio];
        cp->heap[cambio] = swap;
        cp->posiciones[natInfo(cp->heap[cambio])] = cp->posiciones[natInfo(cp->heap[pos])];
        cp->posiciones[natInfo(cp->heap[cambio])] = lugar;
        filtradoDescendente(cp,n,cambio,tipo);
      }
    }
  }
}*/

TColaDePrioridad nuevoHeap(TColaDePrioridad &cp, nat n){
  for(nat i = n/2; i >= 1; i--)
    filtradoDescendente(cp,n,i);
  return cp;
}

TColaDePrioridad invertirPrioridad(TColaDePrioridad cp) {
  if(cp->tipo == 1)
    cp->tipo = -1;
  else
    cp->tipo = 1;
  cp = nuevoHeap(cp,cp->tope);
  return cp;
}
  
void liberarCP(TColaDePrioridad cp) {
  for(nat i = 1; i <= cp->tope; i++)
		liberarInfo(cp->heap[i]);
  delete [] cp->heap;
  delete [] cp->posiciones;
  delete cp;
}

TColaDePrioridad insertarEnCP(nat elem, double valor, TColaDePrioridad cp) {
  if(elem >= 1 && elem <= cp->max){
    TInfo nuevo = crearInfo(elem,valor);
    if(cp->posiciones[elem] != 0){
      liberarInfo(cp->heap[cp->posiciones[elem]]);
      cp->heap[cp->posiciones[elem]] = nuevo;
      filtradoAscendente(cp,cp->posiciones[elem]);
      filtradoDescendente(cp,cp->tope,cp->posiciones[elem]);
    }else{
      cp->tope++;
      cp->heap[cp->tope] = nuevo;
      cp->posiciones[elem] = cp->tope;
      filtradoAscendente(cp, cp->tope);
    }
  }
  return cp;
}

bool estaVaciaCP(TColaDePrioridad cp) {
  return cp->tope == 0; 
}

nat prioritario(TColaDePrioridad cp)  {
  return natInfo(cp->heap[1]);
}

TColaDePrioridad eliminarPrioritario(TColaDePrioridad cp)  {
  if(!estaVaciaCP(cp)){
    cp->posiciones[natInfo(cp->heap[1])] = 0;
    liberarInfo(cp->heap[1]);
    //cp->tope--;
    //if(cp->tope > 1){
    //TInfo cambio = crearInfo(natInfo(cp->heap[cp->tope]),realInfo(cp->heap[cp->tope]));
    cp->heap[1] = cp->heap[cp->tope];
    //cp->posiciones[natInfo(cp->heap[1])] = 1;
    //liberarInfo(cp->heap[cp->tope]);
    cp->tope--;
    //if(cp->tope > 1)
    if(!estaVaciaCP(cp)){
      cp->posiciones[natInfo(cp->heap[1])] = 1;
      filtradoDescendente(cp, cp->tope, 1);  
    }  
  }
  return cp;
}

bool estaEnCP(nat elem, TColaDePrioridad cp)  {
  if(elem >= 1 && elem <= cp->max)
    return cp->posiciones[elem] != 0;
  else
    return false;
}

double prioridad(nat elem, TColaDePrioridad cp)  {
  return realInfo(cp->heap[cp->posiciones[elem]]);
}
