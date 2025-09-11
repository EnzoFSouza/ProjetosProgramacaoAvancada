#ifndef _BIGINT_H_
#define _BIGINT_H_

#include <iostream>
#include <cstdint>
#include <string>

class BigInt{
    private:
        bool neg; //se true entao negativo
        int nDig; //sempre >= 1
        int8_t* d; //ponteiro q aponta pra int

        //Construtor específico 1
        BigInt(bool isNeg, int tamanho);

        void correct(); //corrigir bigint se necessario
        void increment(); //aumentar digitos do bigint
        void decrement(); //diminuir digitos do bigint


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

        //Construtor específico 3
        explicit BigInt(std::string S);

        //Destrutor
        ~BigInt();

        //Sobrecarga de operadores
        BigInt& operator=(const BigInt& B); //Atribuicao por copia
        BigInt& operator=(BigInt&& B) noexcept;
        int operator[](int i) const;
        bool operator==(const BigInt& B) const;
        bool operator!=(const BigInt& B) const;
        bool operator<(const BigInt& B) const;
        bool operator>(const BigInt& B) const;
        bool operator<=(const BigInt& B) const;
        bool operator>=(const BigInt& B) const;
        BigInt& operator++();
        BigInt& operator--();
        BigInt operator++(int);
        BigInt operator--(int);
        const BigInt& operator+() const; //operator + unario
        BigInt operator-() const; //operator - unario
        BigInt operator+(const BigInt& B) const; //operator + binario
        BigInt operator-(const BigInt& B) const; //operator - binario

        friend std::ostream& operator<<(std::ostream& O, const BigInt& B);
        friend std::istream& operator>>(std::istream& I, BigInt& B);

        //Funcoes de consulta
        //o terceiro const indica que o metodo nao pode alterar o objeto no qual e chamado
        bool isNeg() const;
        int size() const;
        bool isZero() const;

        long long int toInt();
        friend BigInt abs(const BigInt& B);
};


#endif // _BIGINT_H_
