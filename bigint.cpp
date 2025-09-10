#include <iostream>
#include <cmath>
#include <cstdint>

#include "bigint.h"

using namespace std;

//Construtores e Destrutores
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//Construtor default
BigInt::BigInt(){
    neg = false;
    nDig = 1;
    d = new int8_t[1]; //Alocando espaco para 1 digito, ponteiro passa a apontar para local válido
    d[0] = 0;
}

//Construtor por cópia
BigInt::BigInt(const BigInt& B) : neg(B.neg), nDig(B.nDig), d(nullptr){
    if (nDig > 0) d = new int8_t[nDig];

    //Copiando elementos de B para atual
    for (int i = 0; i < nDig; ++i) d[i] = B.d[i];
}

//Construtor por movimento
BigInt::BigInt(BigInt&& Temp) noexcept: neg(Temp.neg), nDig(Temp.nDig), d(Temp.d){
    //Zerando o temporário
    Temp.nDig = 0;
    Temp.neg = false;
    Temp.d = nullptr;
}

//Construtor específico 1: a partir de bool e int
BigInt::BigInt(bool isNeg, int tamanho){
    neg = isNeg;
    if (tamanho > 0){
        nDig = tamanho;
        d = new int8_t[nDig]; //alocando espaco para N digitos

        //preenchendo com zeros
        for(int i = 0; i < nDig; ++i){
            d[i] = 0;
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
        d = new int8_t[1]; //Alocando espaco para 1 digito, ponteiro passa a apontar para local válido
        d[0] = 0;
        //Se usar BigInt() dá bug
    }

    else if(N < 0){
        neg = true;
        nDig = 1 + log10(fabs(N));
        d = new int8_t[nDig];
        for(int i = 0; i < nDig; i++){
            d[i] = fabs(N%10);
            N = N / 10;
        }
    }

    else{
        neg = false;
        nDig = 1 + log10(fabs(N));
        d = new int8_t[nDig];
        for(int i = 0; i < nDig; i++){
            d[i] = fabs(N%10);
            N = N / 10;
        }
    }

}

//Construtor específico 3: a partir de string
BigInt::BigInt(string S){
    neg = false;
    nDig = 1;
    d = new int8_t[1];
    d[0] = 0;

    //string invalida
    if (S.empty()) {
        cerr << "Erro na string";
        return;
    }

    int inicio = 0;
    if((S[0] == '+') || (S[0] == '-')){
        if(S.size() == 1){ //Só tem o sinal
            cerr << "Erro na string";
            return;
        }
        if(S[0] == '-') neg = true;
        else neg = false;
        inicio = 1;
    }

    neg = isNeg();
    nDig = S.size() - inicio;
    //BigInt(neg, nDig);
    d = new int8_t[nDig];

    for(int i = 0; i <= size() - 1; ++i){
        char c = S[S.size() - 1 - i];
        //cout << "ISDIGIT: " << isdigit(c);

        if(!isdigit(c)){
           delete[] d;

           neg = false;
           nDig = 1;
           d = new int8_t[1];
           d[0] = 0;
           cerr << "Erro na string";
           return;
        }

        d[i] = static_cast<int8_t>(c - '0');
    }
    correct();
}

// Destrutor
BigInt::~BigInt(){
    nDig = 0;
    neg = false;
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

    //Caso as dimensoes sejam diferentes, desaloca a area anterior e aloca uma nova area
    if (nDig != B.nDig){
        //Limpa conteudo anterior
        delete[] d;

        nDig = B.nDig;
        neg = B.neg;
        //Aloca nova área
        if(nDig > 0) d = new int8_t[nDig];
        else d = nullptr;
    }

    //Copiando valores
    for(int i = 0; i < nDig; ++i) d[i] = B.d[i];
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
    B.neg = false;
    B.d = nullptr;

    return *this;
}

int BigInt::operator[](int i) const{
    //testando o valor de i para ver se é maior q size ou menor que 0
    if ((i >= size()) || (i < 0)){
        return 0;
    }
    return d[i];
}

//Imprimindo BigInt
ostream& operator<<(ostream& O, const BigInt& B){
    if (B.isNeg()){
        O << '-';
    }

    for (int i = B.size() - 1; i >= 0; i--){
        O << B[i];
    }
    return O;
}

//Digitando BigInt
istream& operator>>(istream& I, BigInt& B){
    B.neg = false;
    B.nDig = 0;
    istream::sentry s(I);
    if(s){ //stream OK
        char c = I.peek();
        if ((c = '+') || (c = '-')){
            c = I.get();
            B.neg = (c == '-');
            c = I.peek();
        }
        while(isdigit(c)){
            c = I.get();
            B.nDig = B.size() + 1;
            int8_t* prov = new int8_t[B.nDig];

            for(int i = B.nDig - 1; i > 0; i--) prov[i] = B.d[i];
            prov[0] = static_cast<int8_t>(c - '0');

            delete[] B.d;

            B.d = prov;

            //Verificando o proximo char
            c = I.peek();
        }
        if(B.size() == 0) ios::failbit;
    }
    B.correct();
    return I;
}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//Funcoes de Consulta
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
bool BigInt::isNeg() const{
    return neg;
}

int BigInt::size() const{
    return nDig;
}

bool BigInt::isZero() const{
    if ((nDig == 1) && (d[0] == 0)) return true;
    return false;
}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//Funcoes Suporte
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void BigInt::correct(){
    if((size() <= 0) || (d == nullptr)){
        neg = false;
        nDig = 1;
        d = new int8_t[nDig];
        d[0] = 0;
        return;
    }

    int newSize = size();
    while((newSize > 1) && (d[newSize - 1] == 0)) newSize = newSize - 1;

    if (newSize != size()){
        neg = isNeg();
        nDig = newSize;
        BigInt prov(isNeg(), nDig);
        for(int i = 0; i < nDig; i++) prov.d[i] = d[i];
        *this = move(prov);
    }

    if (size() == 1){
        if(d[0] < 0){
            neg = !isNeg();
            d[0] = fabs(d[0]);
        }
        if(d[0] == 0) neg = false;
    }
}

long long int BigInt::toInt(){
    long long int val = 0;
    for(int i = size() - 1; i >= 0; i--){
        val = 10 * val + d[i];
        if(val < 0){
            cerr << "Erro na conversao para long long int";
            return 0;
        }
    }
    if (isNeg()) val = val * -1;
    return val;
}
