#include <iostream>
#include "bigint.h"

using namespace std;

int main(void)
{
  BigInt A,B;

  cout << "CONFIRA SE OS RESULTADOS CALCULADOS PELO PROGRAMA ESTAO CORRETOS\n\n";

  // Testando positivo e negativo
  cout << "\nPOSITIVO E NEGATIVO:\n";
  A = 0;
  cout << "I01:\t" << "+(" << A << ")=" << +A << " -(" << A << ")=" << -A << endl;
  A = 1;
  cout << "I02:\t" << "+(" << A << ")=" << +A << " -(" << A << ")=" << -A << endl;
  A = -1;
  cout << "I03:\t" << "+(" << A << ")=" << +A << " -(" << A << ")=" << -A << endl;

  // Testando adicao
  cout << "\nADICAO:\n";

  // Envolvendo nulos
  A = 0;
  B = 0;
  cout << "I04:\t" << "(" << A << ")+(" << B << ")="<< A+B << endl;
  A = 0;
  B = 123;
  cout << "I05:\t" << "(" << A << ")+(" << B << ")="<< A+B << endl;
  A = 123;
  B = 0;
  cout << "I06:\t" << "(" << A << ")+(" << B << ")="<< A+B << endl;
  A = 0;
  B = -123;
  cout << "I07:\t" << "(" << A << ")+(" << B << ")=" << A+B << endl;
  A = -123;
  B = 0;
  cout << "I08:\t" << "(" << A << ")+(" << B << ")="<< A+B << endl;

  // Dois numeros nao negativos
  // Mesmo numero de digitos, sem carry
  A = 234;
  B = 765;
  cout << "I09:\t" << "(" << A << ")+(" << B << ")="<< A+B << endl;
  // Mesmo numero de digitos, com carry
  A = 666;
  B = 345;
  cout << "I10:\t" << "(" << A << ")+(" << B << ")="<< A+B << endl;
  // Numero diferente de digitos, sem carry
  A = 1;
  B = 998;
  cout << "I11:\t" << "(" << A << ")+(" << B << ")="<< A+B << endl;
  // Numero diferente de digitos, com carry
  A = 998;
  B = 28;
  cout << "I12:\t" << "(" << A << ")+(" << B << ")="<< A+B << endl;

  // Dois numeros negativos
  // Mesmo numero de digitos, sem carry
  A = -234;
  B = -765;
  cout << "I13:\t" << "(" << A << ")+(" << B << ")="<< A+B << endl;
  // Mesmo numero de digitos, com carry
  A = -666;
  B = -345;
  cout << "I14:\t" << "(" << A << ")+(" << B << ")="<< A+B << endl;
  // Numero diferente de digitos, sem carry
  A = -1;
  B = -998;
  cout << "I15:\t" << "(" << A << ")+(" << B << ")="<< A+B << endl;
  // Numero diferente de digitos, com carry
  A = -998;
  B = -28;
  cout << "I16:\t" << "(" << A << ")+(" << B << ")="<< A+B << endl;

  // Primeiro numero nao negativo, segundo numero negativo
  // Modulo do primeiro maior ou igual que o do segundo
  // Mesmo numero de digitos, sem carry
  A = 765;
  B = -234;
  cout << "I17:\t" << "(" << A << ")+(" << B << ")="<< A+B << endl;
  // Mesmo numero de digitos, com carry
  A = 645;
  B = -366;
  cout << "I18:\t" << "(" << A << ")+(" << B << ")="<< A+B << endl;
  // Mesmo numero de digitos, iguais
  A = 765;
  B = -765;
  cout << "I19:\t" << "(" << A << ")+(" << B << ")="<< A+B << endl;
  // Numero diferente de digitos, sem carry
  A = 998;
  B = -1;
  cout << "I20:\t" << "(" << A << ")+(" << B << ")="<< A+B << endl;
  // Numero diferente de digitos, com carry
  A = 926;
  B = -68;
  cout << "I21:\t" << "(" << A << ")+(" << B << ")="<< A+B << endl;

  // Primeiro numero nao negativo, segundo numero negativo
  // Modulo do primeiro menor que o do segundo
  // Mesmo numero de digitos
  A = 265;
  B = -734;
  cout << "I22:\t" << "(" << A << ")+(" << B << ")="<< A+B << endl;
  // Numero diferente de digitos
  A = 98;
  B = -111;
  cout << "I23:\t" << "(" << A << ")+(" << B << ")="<< A+B << endl;

  // Primeiro numero negativo, segundo numero nao negativo
  // Modulo do primeiro maior ou igual que o do segundo
  // Mesmo numero de digitos
  A = -865;
  B = 734;
  cout << "I24:\t" << "(" << A << ")+(" << B << ")="<< A+B << endl;
  // Numero diferente de digitos
  A = -12398;
  B = 111;
  cout << "I25:\t" << "(" << A << ")+(" << B << ")="<< A+B << endl;

  // Primeiro numero negativo, segundo numero nao negativo
  // Modulo do primeiro menor que o do segundo
  // Mesmo numero de digitos
  A = -265;
  B = 734;
  cout << "I26:\t" << "(" << A << ")+(" << B << ")="<< A+B << endl;
  // Numero diferente de digitos
  A = -98;
  B = 111;
  cout << "I27:\t" << "(" << A << ")+(" << B << ")="<< A+B << endl;

  // Testando subtracao
  cout << "\nSUBTRACAO:\n";

  // Envolvendo nulos
  A = 0;
  B = 0;
  cout << "I28:\t" << "(" << A << ")-(" << B << ")="<< A-B << endl;
  A = 0;
  B = 123;
  cout << "I29:\t" << "(" << A << ")-(" << B << ")="<< A-B << endl;
  A = 123;
  B = 0;
  cout << "I30:\t" << "(" << A << ")-(" << B << ")="<< A-B << endl;
  A = 0;
  B = -123;
  cout << "I31:\t" << "(" << A << ")-(" << B << ")="<< A-B << endl;
  A = -123;
  B = 0;
  cout << "I32:\t" << "(" << A << ")-(" << B << ")="<< A-B << endl;

  // Dois numeros nao negativos
  // Mesmo numero de digitos, sem carry
  A = 234;
  B = 765;
  cout << "I33:\t" << "(" << A << ")-(" << B << ")="<< A-B << endl;
  // Mesmo numero de digitos, com carry
  A = 666;
  B = 345;
  cout << "I34:\t" << "(" << A << ")-(" << B << ")="<< A-B << endl;
  // Mesmo numero de digitos, iguais
  A = 666;
  B = 666;
  cout << "I35:\t" << "(" << A << ")-(" << B << ")="<< A-B << endl;
  // Numero diferente de digitos, sem carry
  A = 1;
  B = 998;
  cout << "I36:\t" << "(" << A << ")-(" << B << ")="<< A-B << endl;
  // Numero diferente de digitos, com carry
  A = 998;
  B = 28;
  cout << "I37:\t" << "(" << A << ")-(" << B << ")="<< A-B << endl;

  // Dois numeros negativos
  // Mesmo numero de digitos, sem carry
  A = -234;
  B = -765;
  cout << "I38:\t" << "(" << A << ")-(" << B << ")="<< A-B << endl;
  // Mesmo numero de digitos, com carry
  A = -666;
  B = -345;
  cout << "I39:\t" << "(" << A << ")-(" << B << ")="<< A-B << endl;
  // Mesmo numero de digitos, iguais
  A = -345;
  B = -345;
  cout << "I40:\t" << "(" << A << ")-(" << B << ")="<< A-B << endl;
  // Numero diferente de digitos, sem carry
  A = -1;
  B = -998;
  cout << "I41:\t" << "(" << A << ")-(" << B << ")="<< A-B << endl;
  // Numero diferente de digitos, com carry
  A = -998;
  B = -28;
  cout << "I42:\t" << "(" << A << ")-(" << B << ")="<< A-B << endl;

  // Primeiro numero nao negativo, segundo numero negativo
  // Modulo do primeiro maior ou igual que o do segundo
  // Mesmo numero de digitos, sem carry
  A = 765;
  B = -234;
  cout << "I43:\t" << "(" << A << ")-(" << B << ")="<< A-B << endl;
  // Mesmo numero de digitos, com carry
  A = 645;
  B = -366;
  cout << "I44:\t" << "(" << A << ")-(" << B << ")="<< A-B << endl;
  // Numero diferente de digitos, sem carry
  A = 998;
  B = -1;
  cout << "I45:\t" << "(" << A << ")-(" << B << ")="<< A-B << endl;
  // Numero diferente de digitos, com carry
  A = 926;
  B = -68;
  cout << "I46:\t" << "(" << A << ")-(" << B << ")="<< A-B << endl;

  // Primeiro numero nao negativo, segundo numero negativo
  // Modulo do primeiro menor que o do segundo
  // Mesmo numero de digitos
  A = 265;
  B = -734;
  cout << "I47:\t" << "(" << A << ")-(" << B << ")="<< A-B << endl;
  // Numero diferente de digitos
  A = 98;
  B = -111;
  cout << "I48:\t" << "(" << A << ")-(" << B << ")="<< A-B << endl;

  // Primeiro numero negativo, segundo numero nao negativo
  // Modulo do primeiro maior ou igual que o do segundo
  // Mesmo numero de digitos
  A = -865;
  B = 734;
  cout << "I49:\t" << "(" << A << ")-(" << B << ")="<< A-B << endl;
  // Numero diferente de digitos
  A = -12398;
  B = 111;
  cout << "I50:\t" << "(" << A << ")-(" << B << ")="<< A-B << endl;

  // Primeiro numero negativo, segundo numero nao negativo
  // Modulo do primeiro menor que o do segundo
  // Mesmo numero de digitos
  A = -265;
  B = 734;
  cout << "I51:\t" << "(" << A << ")-(" << B << ")="<< A-B << endl;
  // Numero diferente de digitos
  A = -98;
  B = 111;
  cout << "I52:\t" << "(" << A << ")-(" << B << ")="<< A-B << endl;

  return 0;
}

