#ifndef _BIGINT_H_
#define _BIGINT_H_

#include <iostream>

class BigInt{
    private:
        bool neg; //se true entao negativo
        int nDig; //sempre >= 1
        int* d; //ponteiro q aponta pra int
        BigInt(bool isNeg, int tamanho); //Construtor específico 1

    public:
        //Construtor default
        BigInt();

        //Construtor por copia
        BigInt(const BigInt& B);

        //Construtor por movimento
        BigInt(BigInt&& Temp) noexcept;

        //Construtor específico 2
        //Pode servir como conversor de long long int para BigInt, logo nao possui explicit
        BigInt(long long int N);

        //Destrutor
        ~BigInt();

        //Sobrecarga de operadores
        //Atribuicao por copia
        BigInt& operator=(const BigInt& B);
        BigInt& operator=(BigInt&& B) noexcept;
        int operator[](int i) const;

        //Funcoes de consulta
        //o terceiro const indica que o metodo nao pode alterar o objeto no qual e chamado
        bool isNeg() const;
        int size() const;
        bool isZero() const;
};


#endif // _BIGINT_H_
