#include <iostream>
#include "bigint.h"

using namespace std;

int main(void)
{
  BigInt A,B;

  cout << "CONFIRA SE OS RESULTADOS CALCULADOS PELO PROGRAMA ESTAO CORRETOS\n\n";

  // Testando multiplicacao
  cout << "\nMULTIPLICACAO:\n";

  // Envolvendo nulos
  A = 0;
  B = 0;
  cout << "I01:\t" << "(" << A << ")*(" << B << ")="<< A*B << endl;
  A = 0;
  B = 123;
  cout << "I02:\t" << "(" << A << ")*(" << B << ")="<< A*B << endl;
  A = 123;
  B = 0;
  cout << "I03:\t" << "(" << A << ")*(" << B << ")="<< A*B << endl;
  A = 0;
  B = -123;
  cout << "I04:\t" << "(" << A << ")*(" << B << ")="<< A*B << endl;
  A = -123;
  B = 0;
  cout << "I05:\t" << "(" << A << ")*(" << B << ")="<< A*B << endl;

  // Dois numeros nao negativos, sem carry
  A = 1000;
  B = 98765;
  cout << "I06:\t" << "(" << A << ")*(" << B << ")="<< A*B << endl;
  // Dois numeros nao negativos, com carry
  A = 1234;
  B = 98765;
  cout << "I07:\t" << "(" << A << ")*(" << B << ")="<< A*B << endl;
  // Dois numeros negativos
  A = -1234;
  B = -98765;
  cout << "I08:\t" << "(" << A << ")*(" << B << ")="<< A*B << endl;
  // Primeiro numero nao negativo, segundo negativo
  A = 1234;
  B = -98765;
  cout << "I09:\t" << "(" << A << ")*(" << B << ")="<< A*B << endl;
  // Primeiro numero negativo, segundo nao negativo
  A = -1234;
  B = 98765;
  cout << "I10:\t" << "(" << A << ")*(" << B << ")="<< A*B << endl;

  // Testando fatorial
  cout << "\nFATORIAL:\n";

  A = -100;
  cout << "I11:\t" << "(" << A << ")!=" << !A << endl;
  A = -1;
  cout << "I12:\t" << "(" << A << ")!=" << !A << endl;
  A = 0;
  cout << "I13:\t" << "(" << A << ")!=" << !A << endl;
  A = 1;
  cout << "I14:\t" << "(" << A << ")!=" << !A << endl;
  A = 10;
  cout << "I15:\t" << "(" << A << ")!=" << !A << endl;
  A = 100;
  cout << "I16:\t" << "(" << A << ")!=" << !A << endl;
  A = 1000;
  cout << "I17:\t" << "(" << A << ")!=" << !A << endl;

  return 0;
}

