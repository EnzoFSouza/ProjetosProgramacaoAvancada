#include <iostream>
#include "BigInt.h"

using namespace std;

//Cponstrutor default
BigInt::BigInt(){
    neg = false;
    nDig = 1;
    d = new int8_t[1]; //Alocando espaco para 1 digito
}

BigInt::BigInt(bool isNeg, int tamanho){
    neg = isNeg;
    if (tamanho > 0){
        //usar construtor aqui??
        //assistir video do construtor, oop, funcoes
        nDig = tamanho;
        d = new int8_t[nDig]; //alocando espaco para N digitos
        //preenchendo com zeros
    }
    else {
        nDig = 0;
        d = nullptr;
    }
}

// Destrutor
BigInt::~BigInt(){
    delete[] d;
    d = nullptr;
}
