#ifndef _BIGINT_H_
#define _BIGINT_H_

#include <iostream>

class BigInt{
    private:
        bool neg; //se true entao negativo
        int nDig; //sempre >= 1
        BigInt(bool isNeg, int tamanho); //Construtor específico 1
        int8_t* d; //ponteiro q aponta pra int8_t

    public:
        //Construtor default
        BigInt();

        //Construtor por copia
        BigInt(const BigInt& B);

        //Construtor por movimento
        BigInt::BigInt(BigInt&& Temp)

        //Construtor específico 2
        BigInt::BigInt(long long int N);

        //Destrutor
        ~BigInt();

        //Sobrecarga de operadores
        //Atribuicao por copia
        BigInt& operator=(const BigInt& B);
        BigInt& operator=(BigInt&& B) noexcept;
        BigInt operator[](int i);

        //Funcoes de consulta
        isNeg();
        size();
        isZero();
};


#endif // _BIGINT_H_
