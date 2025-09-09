#include <iostream>
#include "bigint.h"

using namespace std;

// Funcao que imprime algumas caracteristicas de um BigInt.
// Usa metodos de consulta: isNeg, size e isZero
void imprimir(const string& S, const BigInt& P)
{
  cout << S << '=';
  if (P.isNeg()) cout << '-';
  for (int i=P.size()-1; i>=0; --i)
  {
    cout << P[i];
  }
  cout << " (";
  if (P.isZero()) cout << "zero";
  else cout << P.size() << " digitos";
  cout << ')' << endl;
}

int main(void)
{
  // Testando o construtor especifico a partir de string

  BigInt P8("");
  // deve imprimir msg de erro e valor 0
  cout << "I01: Deve imprimir msg de erro e 0 -> ";
  imprimir("P8",P8);

  BigInt P9("-");
  // deve imprimir msg de erro e valor 0
  cout << "I02: Deve imprimir msg de erro e 0 -> ";
  imprimir("P9",P9);

  BigInt P10(" 1");
  // deve imprimir msg de erro e valor 0
  cout << "I03: Deve imprimir msg de erro e 0 -> ";
  imprimir("P10",P10);

  BigInt P11("1 2");
  // deve imprimir msg de erro e valor 0
  cout << "I04: Deve imprimir msg de erro e 0 -> ";
  imprimir("P11",P11);

  BigInt P12("1 ");
  // deve imprimir msg de erro e valor 0
  cout << "I05: Deve imprimir msg de erro e 0 -> ";
  imprimir("P12",P12);

  BigInt P13("123z");
  // deve imprimir msg de erro e valor 0
  cout << "I06: Deve imprimir msg de erro e 0 -> ";
  imprimir("P13",P13);

  BigInt P14("123456789012345678901234567890");
  // deve imprimir NUMERO_GRANDE
  cout << "I07: Deve imprimir 123456789012345678901234567890 -> ";
  imprimir("P14",P14);

  BigInt P15("-123456789012345678901234567890");
  // deve imprimir -NUMERO_GRANDE
  cout << "I08: Deve imprimir -123456789012345678901234567890 -> ";
  imprimir("P15",P15);

  // Testando a funcao correct

  BigInt P16("-0");
  // deve imprimir valor 0
  cout << "I09: Deve imprimir 0 -> ";
  imprimir("P16",P16);

  BigInt P17("0075");
  // deve imprimir valor 75
  cout << "I10: Deve imprimir 75 -> ";
  imprimir("P17",P17);

  return 0;
}

