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

bool BigInt::operator==(const BigInt& B) const{
    if (B.size() != size()) return false;

    if (B.neg != neg) return false;

    for(int i = 0; i < size(); i ++){
        if (B.d[i] != d[i]) return false;
    }
    return true;
}

bool BigInt::operator!=(const BigInt& B) const{
    return !(*this == B);
}

bool BigInt::operator<(const BigInt& B) const{
    if (isNeg() != B.isNeg()) return isNeg();

    //Ambos negativos
    if (isNeg()){
        if (size() != B.size()) return (size() > B.size());
        for (int i = size() - 1; i >= 0; i--){
            if (d[i] != B.d[i]) return d[i] > B.d[i];
        }
    }

    //ambos positivos ou nulos
    if (size() != B.size()) return size() < B.size();

    //mesmo numero de digitos
    for (int i = size() - 1; i >= 0; i--){
        if (d[i] != B.d[i]) return d[i] < B.d[i];
    }

    //numeros identicos
    return false;
}

bool BigInt::operator>(const BigInt& B) const{
    return B < *this;
}

bool BigInt::operator<=(const BigInt& B) const{
    return !(B < *this);
}

bool BigInt::operator>=(const BigInt& B) const{
    return !(*this < B);
}

BigInt& BigInt::operator++(){
    if(!isNeg()) increment();
    else decrement();
    return *this;
}

BigInt& BigInt::operator--(){
    if(isNeg()) increment();
    else decrement();
    return *this;
}

BigInt BigInt::operator++(int){
    BigInt prov = *this; //criando copia
    //*this++; //incrementando o this
    if(!isNeg()) increment();
    else decrement();
    return prov; //retorna o prov
}

BigInt BigInt::operator--(int){
    BigInt prov = *this; //criando copia
    //*this--; //decrementando o this
    if(isNeg()) increment();
    else decrement();
    return prov; //retorna o prov
}

const BigInt& BigInt::operator+() const{
    return *this;
}

BigInt BigInt::operator-() const{
    if((isNeg() == false) && (size() == 1) && (d[0] == 0)){
        return BigInt(0); //criando um bigint q vale 0 e retornando ele
    }

    BigInt prov = *this; //criando copia
    prov.neg = !isNeg(); //alterando sinal
    return prov;
}

BigInt BigInt::operator+(const BigInt& B) const{
    BigInt prov = *this;

    if(isNeg() == B.isNeg()){
        BigInt C(isNeg(), 1 + max(size(), B.size()));
        int carry = 0;
        for (int i = 0; i <= C.size() - 1; i++){
            C.d[i] = prov[i] + B[i] + carry;
            if(C.d[i] > 9){
                C.d[i] -= 10;
                carry = 1;
            }
            else{
                carry = 0;
            }
        }
        C.correct();
        return C;
    }
    else{ //sinais diferentes
        if(abs(*this) >= abs(B)){
            BigInt C(isNeg(), size());
            int borrow = 0;
            for (int i = 0; i <= C.size() - 1; i++){
                C.d[i] = prov[i] - B[i] - borrow;
                if (C.d[i] < 0){
                    C.d[i] += 10;
                    borrow = 1;
                }
                else{
                    borrow = 0;
                }
            }
            C.correct();
            return C;
        }
        else{
            return B + *this;
        }
    }
}

BigInt BigInt::operator-(const BigInt& B) const{
    return *this + (-B);
}

BigInt BigInt::operator*(const BigInt& B) const{
    if ((isZero()) || (B.isZero())) return BigInt(0);

    BigInt C(!(isNeg() == B.isNeg()), size() + B.size());

    for (int i = 0; i <= size() - 1; i++){
        if (d[i] != 0){
            for (int j = 0; j <= B.size() - 1; j++){
                if (B.d[j] != 0){
                    int k = i + j;
                    C.d[k] = C.d[k] + (d[i] * B.d[j]);
                    while (C.d[k] > 9){
                        int carry = C.d[k] / 10;
                        C.d[k] = C.d[k] % 10;
                        k = k + 1;
                        C.d[k] = C.d[k] + carry;
                    }
                }
            }
        }
    }
    C.correct();
    return C;
}

BigInt BigInt::operator!() const{
    if(isNeg()){
        cerr << "Nao pode calcular fatorial de numero negativo";
        return BigInt(0);
    }

    BigInt prov = *this;
    BigInt C(1);

    for (BigInt N(2); N <= prov; N++){
        C = C * N;
    }

    return C;
}

BigInt BigInt::operator<<(int n) const{
    if((n <= 0) || (isZero())) return *this;

    BigInt C(isNeg(), size() + n);

    for (int i = 0; i <= C.size() - 1; i++){
        if (i < n) C.d[i] = 0;
        else C.d[i] = d[i - n];
    }

    return C;
}

BigInt BigInt::operator>>(int n) const{
    if ((n <= 0) || (isZero())) return *this;
    if (n >= size()) return BigInt(0);

    BigInt C(isNeg(), size() - n);

    for (int i = 0; i <= C.size() - 1; i++) C.d[i] = d[i + n];
    return C;
}

const BigInt BigInt::operator/(BigInt& D) const{
    BigInt Q, R;
    division(D, Q, R);
    return Q;
}

const BigInt BigInt::operator%(BigInt& D) const{
    BigInt Q, R;
    division(D, Q, R);
    return R;
}

//Imprimindo BigInt
ostream& operator<<(ostream& O, const BigInt& B){
    if (B.isNeg()){
        O << '-';
    }

    for (int i = B.size() - 1; i >= 0; --i){
        O << B[i];
    }
    return O;
}

//Digitando BigInt
istream& operator>>(istream& I, BigInt& B){

    istream::sentry s(I);

    B = BigInt(false, 0);

    if(s){ //stream OK
        char c = I.peek();
        if ((c == '+') || (c == '-')){
            c = I.get();
            B.neg = (c == '-');
            c = I.peek();
        }
        while(isdigit(c)){
            c = I.get();

            BigInt prov(B.isNeg(), B.size() + 1);

            for (int i = 0; i < B.size(); i++) prov.d[i+1] = B.d[i];

            prov.d[0] = static_cast<int8_t>(c - '0');

            B = move(prov);

            //Verificando o proximo char
            c = I.peek();
        }
        if(B.size() == 0) I.setstate(ios::failbit);
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

void BigInt::increment(){
    int k = 0;
    d[k] = d[k] + 1;
    while((k < size() - 1) && (d[k] > 9)){
        d[k] = 0;
        k = k + 1;
        d[k] = d[k] + 1;
    }
    if((k == size() - 1) && (d[k] > 9)){
        BigInt prov(isNeg(), size() + 1);

        //passando os digitos do atual para prov
        for (int i = 0; i < size(); i++) prov.d[i] = d[i];

        prov.d[size() - 1] = 0;
        prov.d[size()] = 1;

        *this = move(prov);
    }
}

void BigInt::decrement(){
    int k = 0;
    d[k] = d[k] - 1;
    while((k < size() - 1) && (d[k] < 0)){
        d[k] = 9;
        k = k + 1;
        d[k] = d[k] - 1;
    }
    if((k == size() - 1) && (d[k] <= 0)){
        //digito mais significativo se tornou zero ou negativo
        correct();
    }
}

void BigInt::division(const BigInt& D, BigInt& Q, BigInt& R) const{
    Q = BigInt(0);
    if ((isZero()) || (D.isZero())){
        if (D.isZero()) cerr << "Erro: Divisao por zero";
        R = BigInt(0);
        return;
    }
    if (abs(*this) < abs(D)){
        R = *this;
        return;
    }

    R = BigInt(0);

    for (int i = size() - 1; i >= 0; i--){
        if (!(R.isZero())) R = R<<1;
        R.d[0] = d[i];

        int div = 0;
        while (R >= abs(D)){
            R = R - abs(D);
            div = div + 1;
        }

        if (!(Q.isZero())) Q = Q<<1;
        Q.d[0] = div;
    }

    Q.neg = (isNeg() != D.isNeg());
    if (!(R.isZero())) R.neg = isNeg();
}

BigInt abs(const BigInt& B){
    BigInt modulo(false, B.size());
    for (int i = 0; i < B.size(); i++) modulo.d[i] = B.d[i];
    return modulo;
}
