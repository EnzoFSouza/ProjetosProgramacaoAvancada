#ifndef _BIGINT_H_
#define _BIGINT_H_

#include <iostream>

class BigInt{
    private:
        bool neg; //true --> negativo
        int nDig; //sempre >= 1
        int8_t* d; //aponta para array com nDig e já inicializado como nullptr
        BigInt(bool isNeg, int tamanho);

    public:
        // Construtor default (0 parametros)
        BigInt();

        // Destrutor
        ~BigInt();
};


#endif // _BIGINT_H_
