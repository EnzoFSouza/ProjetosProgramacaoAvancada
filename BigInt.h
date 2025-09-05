#ifndef _BIGINT_H_
#define _BIGINT_H_

#include <iostream>

class BigInt{
    private:
        int N;
        double* x;

    public:
        // Construtor default
        BigInt(): N(0), x(nullptr) {};

        // Construtor por copia
        BigInt(const BigInt& I);

        // Construtor por movimento
        BigInt(BigInt&& I) noexcept;

        // Um construtor especifico, no qual o parametro de entrada indica a dimensao do vetor
        // Esse construtor NAO deve ser usado como conversor de int -> Vetor, pois seria incorreto.
        // Por isso, foi declarado como explicit
        explicit BigInt(int Num);

        // Destrutor
        ~BigInt();

        // Operador de atribuicao por copia
        BigInt& operator=(const BigInt& I);

        // Operador de atribuicao por movimento
        BigInt& operator=(BigInt&& I) noexcept;

        // Metodo de consulta que retorna a dimensao do vetor
        int size() const {return N;}

        // Metodo de consulta que retorna o valor de um elemento do vetor
        double operator[](int i) const;

        // Metodo de alteracao de valor de um elemento do vetor
        void set(int i, double valor);

        // Acrescenta um elemento ao final do vetor (aumenta de tamanho)
        void push_back(double valor);

        // As funcoes que implementam os operadores de entrada e saida de dados
        // Como nao sao metodos da classe (sao funcoes) mas precisam acessar dados privados
        // da classe, sao declaradas como friend
        friend std::ostream& operator<<(std::ostream& X, const BigInt& I);
        friend std::istream& operator>>(std::istream& X, BigInt& I);

        // Soma de vetores
        BigInt operator+(const BigInt& I) const;

        // Subtracao de vetores (- binario)
        BigInt operator-(const BigInt& I) const;

        // Negativo de um vetor (- unario)
        BigInt operator-() const;
};


#endif // _BIGINT_H_
