#include <iostream>
#include <cstdlib>
#include <ctime>
#include "bigint.h"

using namespace std;

int main(void)
{
  BigInt BI0(0), BI1(1), BIm1(-1),
         BIbig(1234567890), BImbig(-1234567890), BIbig1(1234567891);

  cout << "CONFIRA SE OS DESLOCAMENTOS CALCULADOS PELO PROGRAMA ESTAO CORRETOS\n\n";

  // Teste do deslocamento aa esquerda
  cout << "\nTESTE DO DESLOCAMENTO AA ESQUERDA:\n";
  cout << "I01:\t" << "BI=" << BI0 << "\tBI<<3=" << (BI0<<3) << endl;
  cout << "I02:\t" << "BI=" << BI1 << "\tBI<<3=" << (BI1<<3) << endl;
  cout << "I03:\t" << "BI=" << BIm1 << "\tBI<<3=" << (BIm1<<3) << endl;
  cout << "I04:\t" << "BI=" << BIbig << "\tBI<<-1=" << (BIbig<<-1) << endl;
  cout << "I05:\t" << "BI=" << BIbig << "\tBI<<0=" << (BIbig<<0) << endl;
  cout << "I06:\t" << "BI=" << BIbig << "\tBI<<3=" << (BIbig<<3) << endl;
  cout << "I07:\t" << "BI=" << BImbig << "\tBI<<3=" << (BImbig<<3) << endl;

  // Teste do deslocamento aa direita
  cout << "\nTESTE DO DESLOCAMENTO AA DIREITA:\n";
  cout << "I08:\t" << "BI=" << BI0 << "\tBI>>3=" << (BI0>>3) << endl;
  cout << "I09:\t" << "BI=" << BI1 << "\tBI>>3=" << (BI1>>3) << endl;
  cout << "I10:\t" << "BI=" << BIm1 << "\tBI>>3=" << (BIm1>>3) << endl;
  cout << "I11:\t" << "BI=" << BIbig << "\tBI>>-1=" << (BIbig>>-1) << endl;
  cout << "I12:\t" << "BI=" << BIbig << "\tBI>>0=" << (BIbig>>0) << endl;
  cout << "I13:\t" << "BI=" << BIbig << "\tBI>>3=" << (BIbig>>3) << endl;
  cout << "I14:\t" << "BI=" << BIbig << "\tBI>>10=" << (BIbig>>10) << endl;
  cout << "I15:\t" << "BI=" << BImbig << "\tBI>>3=" << (BImbig>>3) << endl;

  BigInt A,B,Q,R;

  cout << "\n\nCONFIRA SE AS DIVISOES CALCULADAS PELO PROGRAMA ESTAO CORRETAS\n\n";

  // Testando funcao de divisao
  cout << "\nFUNCAO DIVISION:\n";
  A = 1;
  srand(time(nullptr));
  for (int i=0; i<15; ++i)
  {
    A = (A<<1) + rand()%10;
    B = rand();
    A.division(B,Q,R);
    cout << "I" << 16+i << ":\t" << A << '/' << B << " = " << Q << " resto " << R
         << '\t' << ((Q*B+R == A) ? "OK" : "ERRO") << endl;
  }

  // Testando operadores de divisao
  cout << "\nOPERADORES DE DIVISAO:\n";

  // Envolvendo nulos
  A = 0;
  B = 0;
  cout << "I31:\t" << "(" << A << ")/(" << B << ")="<< A/B << " resto=" << A%B << endl;
  A = 0;
  B = 123;
  cout << "I32:\t" << "(" << A << ")/(" << B << ")="<< A/B << " resto=" << A%B << endl;
  A = 123;
  B = 0;
  cout << "I33:\t" << "(" << A << ")/(" << B << ")="<< A/B << " resto=" << A%B << endl;
  A = 0;
  B = -123;
  cout << "I34:\t" << "(" << A << ")/(" << B << ")="<< A/B << " resto=" << A%B << endl;
  A = -123;
  B = 0;
  cout << "I35:\t" << "(" << A << ")/(" << B << ")="<< A/B << " resto=" << A%B << endl;

  // Dois numeros nao negativos, dividendo modulo menor que o divisor
  A = 10000;
  B = 98765;
  cout << "I36:\t" << "(" << A << ")/(" << B << ")="<< A/B << " resto=" << A%B << endl;
  // Dois numeros nao negativos, dividendo modulo maior que o divisor
  A = 1000000000000;
  B = 98765;
  cout << "I37:\t" << "(" << A << ")/(" << B << ")="<< A/B << " resto=" << A%B << endl;
  // Dois numeros negativos
  A = -123456700;
  B = -12345;
  cout << "I38:\t" << "(" << A << ")/(" << B << ")="<< A/B << " resto=" << A%B << endl;
  // Primeiro numero nao negativo, segundo negativo
  A = 123456;
  B = -1234;
  cout << "I39:\t" << "(" << A << ")/(" << B << ")="<< A/B << " resto=" << A%B << endl;
  // Primeiro numero negativo, segundo nao negativo
  A = -123450000;
  B = 12345;
  cout << "I40:\t" << "(" << A << ")/(" << B << ")="<< A/B << " resto=" << A%B << endl;

  return 0;
}

