#include <iostream>
#include <cmath>

#include "bigint.h"

using namespace std;

//Construtores e Destrutores
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//Construtor default
BigInt::BigInt(){
    neg = false;
    nDig = 1;
    d = new int[1]; //Alocando espaco para 1 digito, ponteiro passa a apontar para local válido
    *d = 0;
}

//Construtor por cópia
BigInt::BigInt(const BigInt& B){
    neg = B.neg; //copiando mesmo sinal de B
    nDig = B.nDig; //copiando valor do nDig de B (passado por paramaetro) para o meu objeto
    d = B.d;
}

//Construtor por movimento
BigInt::BigInt(BigInt&& Temp){
    neg = Temp.neg;
    nDig = Temp.nDig;
    d = Temp.d;

    //Zerando o temporário
    Temp.nDig = 0;
    Temp.d = nullptr;
}

//Construtor específico 1: a partir de bool e int
BigInt::BigInt(bool isNeg, int tamanho){
    neg = isNeg;
    if (tamanho > 0){
        nDig = tamanho;
        d = new int[nDig]; //alocando espaco para N digitos

        //preenchendo com zeros
        for(int i = 0; i < nDig; i++){
            d[i] = 0;
            //*(d + i) = 0;
        }
    }
    else {
        nDig = 0;
        d = nullptr;
    }
}

//Construtor específico 2: a partir de long long int
BigInt::BigInt(long long int N){
    if (N == 0){
        neg = false;
        nDig = 1;
        d = new int[1]; //Alocando espaco para 1 digito, ponteiro passa a apontar para local válido
        *d = 0;
    }

    else if(N < 0){
        neg = true;
        nDig = 1 + log10(fabs(N));
        d = new int[nDig];
        for(int i = 0; i < nDig; i++){
            d[i] = fabs(N%10);
            N = N / 10;
        }
    }

    else{
        neg = false;
        nDig = 1 + log10(fabs(N));
        d = new int[nDig];
        for(int i = 0; i < nDig; i++){
            d[i] = fabs(N%10);
            N = N / 10;
        }
    }

}

// Destrutor
BigInt::~BigInt(){
    nDig = 0;
    //neg = false;
    delete[] d;
    d = nullptr;
}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//Sobrecarga de operadores
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//Atribuicao por copia
BigInt& BigInt::operator=(const BigInt& B){
    //Retorna se autoatribuicao
    if(this == &B) return *this;
    //Limpa conteudo anterior
    delete[] d;

    //Aloca nova área
    nDig = B.nDig;
    if(nDig > 0) d = new int[nDig];
    else d = nullptr;

    //Copiando valores
    for(int i = 0; i < nDig; i++){
        d[i] = B.d[i];
    }
    return *this;
}

//Atribuicao por movimento
BigInt& BigInt::operator=(BigInt&& B) noexcept{
    //Nao precisa testar autoatribuicao
    //Limpa conteudo anterior
    delete[] d;

    //Movendo conteudo
    neg = B.neg;
    nDig = B.nDig;
    d = B.d;

    //Zerando temporario
    B.nDig = 0;
    B.d = nullptr;

    return *this;
}

int BigInt::operator[](int i){
    //testando o valor de i para ver se é maior q size ou menor que 0
    if ((i >= size()) || (i < 0)){
        return 0;
    }
    return d[i];
}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//Funcoes de Consulta
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
bool BigInt::isNeg(){
    return neg;
}

int BigInt::size(){
    return nDig;
}

bool BigInt::isZero(){
    if ((nDig == 1) && (d[0] == 0)) return true;
    return false;
}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
