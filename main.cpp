#include <iostream>
#include "bigint.h"

using namespace std;

int main(void)
{
  BigInt BI;
  int i;

  cout << "CONFIRA SE AS SEQUENCIAS GERADAS PELO PROGRAMA ESTAO CORRETAS\n\n";

  //
  // OPERADORES PRE-FIXADOS
  //

  cout << "Incremento pre-fixado:\n";

  // Incremento nao negativo
  cout << "I01 (de 1 a 20):\t";
  BI = 0;
  for (i=0; i<20; i++)
  {
    cout << ++BI << ' ';
  }
  cout << endl;

  // Incremento negativo
  cout << "I02 (de -29 a -10):\t";
  BI = -30;
  for (i=0; i<20; i++)
  {
    cout << ++BI << ' ';
  }
  cout << endl;

  // Incremento negativo -> nao negativo
  cout << "I03 (de -9 a 10):\t";
  BI = -10;
  for (i=0; i<20; i++)
  {
    cout << ++BI << ' ';
  }
  cout << endl;

  cout << "Decremento pre-fixado:\n";

  // Decremento nao negativo
  cout << "I04 (de 29 a 10):\t";
  BI = 30;
  for (i=0; i<20; i++)
  {
    cout << --BI << ' ';
  }
  cout << endl;

  // Decremento negativo
  cout << "I05 (de -2 a -21):\t";
  BI = -1;
  for (i=0; i<20; i++)
  {
    cout << --BI << ' ';
  }
  cout << endl;

  // Decremento nao negativo -> negativo
  cout << "I06 (de 9 a -10):\t";
  BI = 10;
  for (i=0; i<20; i++)
  {
    cout << --BI << ' ';
  }
  cout << endl;

  //
  // OPERADORES POS-FIXADOS
  //

  cout << "Incremento pos-fixado:\n";

  // Incremento nao negativo
  cout << "I07 (de 0 a 19):\t";
  BI = 0;
  for (i=0; i<20; i++)
  {
    cout << BI++ << ' ';
  }
  cout << endl;

  // Incremento negativo
  cout << "I08 (de -30 a -11):\t";
  BI = -30;
  for (i=0; i<20; i++)
  {
    cout << BI++ << ' ';
  }
  cout << endl;

  // Incremento negativo -> nao negativo
  cout << "I09 (de -10 a 9):\t";
  BI = -10;
  for (i=0; i<20; i++)
  {
    cout << BI++ << ' ';
  }
  cout << endl;

  cout << "Decremento pos-fixado:\n";

  // Decremento nao negativo
  cout << "I10 (de 30 a 11):\t";
  BI = 30;
  for (i=0; i<20; i++)
  {
    cout << BI-- << ' ';
  }
  cout << endl;

  // Decremento negativo
  cout << "I11 (de -1 a -20):\t";
  BI = -1;
  for (i=0; i<20; i++)
  {
    cout << BI-- << ' ';
  }
  cout << endl;

  // Decremento nao negativo -> negativo
  cout << "I12 (de 10 a -9):\t";
  BI = 10;
  for (i=0; i<20; i++)
  {
    cout << BI-- << ' ';
  }
  cout << endl;

  return 0;
}

