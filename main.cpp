#include <iostream>
#include <limits>
#include "bigint.h"

using namespace std;

int main(void)
{
  // Testando toInt
  cout << "I1: Nao deve imprimir nenhuma msg de erro de conversao\n";
  long long int V,W;
  for (V=-1000000; V<=1000000; ++V)
  {
    BigInt BI(V);
    W = BI.toInt();
    if (V!=W) cerr << "Erro na conversao int/BigInt/int: " << V << ',' << W << endl;
  }

  // Conversao de BigInt fora de faixa para inteiro.
  // Deve emitir erro e retornar 0.
  BigInt P12("123456789012345678901234567890");
  BigInt P13("-123456789012345678901234567890");
  cout << "I2: Deve imprimir msg de erro e valor 0\n";
  cout << "Valor convertido de P12=" << P12.toInt() << endl;
  cout << "I3: Deve imprimir msg de erro e valor 0\n";
  cout << "Valor convertido de P13=" << P13.toInt() << endl;

  BigInt BI;
  string msg[] = {
    "<ENTER><ENTER><TAB><TAB><espaco><espaco>12",
    "z",
    "-",
    "+",
    "-0",
    "0000",
    "0075",
    "-0075",
    "123z",
    "Nao vai esperar digitar, pois vai processar o que ficou da digitacao anterior",
    "32-16",
    "Nao vai esperar digitar, pois vai processar o que ficou da digitacao anterior",
    "1 2 3",
    "Nao vai esperar digitar, pois vai processar o que ficou da digitacao anterior",
    "Nao vai esperar digitar, pois vai processar o que ficou da digitacao anterior",
    "+123456789012345678901234567890",
    "-123456789012345678901234567890"
  };
  string result[] = {
    "12",
    "msg de erro e 0",
    "msg de erro e 0",
    "msg de erro e 0",
    "0",
    "0",
    "75",
    "-75",
    "123",
    "msg de erro e 0",
    "32",
    "-16",
    "1",
    "2",
    "3",
    "+123456789012345678901234567890",
    "-123456789012345678901234567890"
  };

  string nada;
  for (int i=0; i<17; ++i)
  {
    cout << "\nDigite " << msg[i] << endl;
    cout << "> ";
    cin >> BI;
    cout << "I" << i+4 << ": Deve imprimir " << result[i] << endl;
    if (cin.fail())
    {
      cin.clear(); // Limpa o estado de erro
      cout << "Erro na leitura! ";
      // Para ler tudo que foi digitado ateh o proximo ENTER, incluindo o que gerou erro
      getline(cin,nada);
    }
    cout << "BI=" << BI << endl;
  }

  return 0;
}

