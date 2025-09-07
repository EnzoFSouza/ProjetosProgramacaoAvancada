#include <iostream>
#include <limits>
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

// Funcao que inicializa e retorna um BigInt sem nome.
// Ao retornar, pode usar o construtor por movimento.
BigInt inicializa()
{
  return BigInt(666);
}

int main(void)
{
  // Testando o construtor default;

  cout << "==========\n";
  BigInt P0;
  // deve imprimir 0
  cout << "I01: Deve imprimir 0 -> ";
  imprimir("P0",P0);

  // Testando o construtor especifico a partir de inteiros

  cout << "==========\n";
  BigInt P1(LLONG_MIN);
  // deve imprimir -NUMERO_GRANDE
  cout << "I02: Deve imprimir " << LLONG_MIN << " -> ";
  imprimir("P1",P1);

  BigInt P2(0);
  // deve imprimir 0
  cout << "I03: Deve imprimir 0 -> ";
  imprimir("P2",P2);

  BigInt P3(LLONG_MAX);
  // deve imprimir NUMERO_GRANDE
  cout << "I04: Deve imprimir " << LLONG_MAX << " -> ";
  imprimir("P3",P3);

  // Testando o construtor por cópia

  cout << "==========\n";
  BigInt P4(P1);
  // deve imprimir -NUMERO_GRANDE
  cout << "I05: Deve imprimir " << LLONG_MIN << " -> ";
  imprimir("P1",P1);
  // deve imprimir -NUMERO_GRANDE
  cout << "I06: Deve imprimir " << LLONG_MIN << " -> ";
  imprimir("P4",P4);

  BigInt P5(P2);
  // deve imprimir 0
  cout << "I07: Deve imprimir 0 -> ";
  imprimir("P2",P2);
  // deve imprimir 0
  cout << "I08: Deve imprimir 0 -> ";
  imprimir("P5",P5);

  BigInt P6(P3);
  // deve imprimir NUMERO_GRANDE
  cout << "I09: Deve imprimir " << LLONG_MAX << " -> ";
  imprimir("P3",P3);
  // deve imprimir NUMERO_GRANDE
  cout << "I10: Deve imprimir " << LLONG_MAX << " -> ";
  imprimir("P6",P6);

  // Testando o construtor por movimento
  // Pode chamar esse construtor 2 vezes:
  // - Para retornar o valor de inicializa() para uma variavel sem nome
  // - Para criar P7 a partir da variavel sem nome

  cout << "==========\n";
  BigInt P7(inicializa());
  // deve imprimir 666
  cout << "I11: Deve imprimir 666 -> ";
  imprimir("P7",P7);

  // Testando o operador de atribuicao por copia

  cout << "==========\n";
  P1 = P7;
  // deve imprimir 666
  cout << "I12: Deve imprimir 666 -> ";
  imprimir("P7",P7);
  cout << "I13: Deve imprimir 666 -> ";
  imprimir("P1",P1);

  P2 = P6;
  // deve imprimir NUMERO_GRANDE
  cout << "I14: Deve imprimir " << LLONG_MAX << " -> ";
  imprimir("P6",P6);
  cout << "I15: Deve imprimir " << LLONG_MAX << " -> ";
  imprimir("P2",P2);

  P3 = P4 = P5;
  // deve imprimir 0
  cout << "I16: Deve imprimir 0 -> ";
  imprimir("P5",P5);
  cout << "I17: Deve imprimir 0 -> ";
  imprimir("P4",P4);
  cout << "I18: Deve imprimir 0 -> ";
  imprimir("P3",P3);

  // Testando o operador de atribuicao por movimento

  cout << "==========\n";

  P1 = BigInt(-3);
  // deve imprimir -3
  cout << "I19: Deve imprimir -3 -> ";
  imprimir("P1",P1);

  P5 = inicializa();
  // deve imprimir 666
  cout << "I20: Deve imprimir 666 -> ";
  imprimir("P5",P5);

  cout << "==========\n";

  // Testando operator[] com parametros dentro e fora de faixa
  // P5 = 666, digitos de 0 a 2
  cout << "I21 a I25: Deve imprimir 0,6,6,6,0:\n";
  for (int i=-1; i<=3; ++i)
  {
    cout << "P[" << i << "]=" << P5[i] << endl;
  }

  return 0;
}
