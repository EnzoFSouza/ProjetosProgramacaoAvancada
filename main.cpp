#include <iostream>
#include <iomanip>
#include <string>
#include "bigint.h"

///
/// ESTE ARQUIVO NAO DEVE SER ALTERADO
///

using namespace std;

enum class Opcoes_t
{
  NUMERO_JA_DIGITADO,
  DIGITAR_NUMERO,
  SOMAR,
  SUBTRAIR,
  MULTIPLICAR,
  DIVIDIR_QUOCIENTE,
  DIVIDIR_RESTO,
  DIVIDIR_AMBOS,
  FATORIAL,
  ROTACIONAR_ESQUERDA,
  ROTACIONAR_DIREITA,
  INCREMENTAR,
  DECREMENTAR,
  INVERTER_SINAL,
  MODULO,
  TROCAR,
  AJUDA,
  TERMINAR,
  OPCAO_INVALIDA
};

void help()
{
  cout << "\nOPCOES:\n";
  cout << "Digite valor [novo Result <- BigInt(string)]\n";
  cout << "<   - Entrar um novo numero [novo Result <- operator>>]\n";
  cout << "+   - Somar os numeros [novo Result <- I3+Result]\n";
  cout << "-   - Subtrair os numeros [novo Result <- I3-Result]\n";
  cout << "*   - Multiplicar os numeros [novo Result <- I3*Result]\n";
  cout << "/   - Dividir os numeros [novo Result <- I3/Result]\n";
  cout << "%   - Dividir os numeros [novo Result <- I3%Result]\n";
  cout << "div - Dividir os numeros [novo I3 <- I3/Result; novo Result <- I3%Result]\n";
  cout << "!   - Fatorial do numero [novo Result <- !Result]\n";
  cout << "<<  - Rotacionar para esquerda [novo Result <- I3 << Result]\n";
  cout << ">>  - Rotacionar para direita [novo Result <- I3 >> Result]\n";
  cout << "++  - Incrementar numero [++Result]\n";
  cout << "--  - Decrementar numero [--Result]\n";
  cout << "inv - Inverter o sinal do numero [novo Result <- -Result]\n";
  cout << "abs - Calcular o modulo do numero [novo Result <- abs(Result)]\n";
  cout << "t   - Trocar os numeros [I1->I2  I2->I3  I3->Result  Result->I1]\n";
  cout << "h   - Imprimir ajuda\n";
  cout << "q   - Terminar\n";
}

const string tamanho(const BigInt& BI)
{
  string txt=" (";
  if (BI.isZero()) txt += "zero";
  else
  {
    txt += to_string(BI.size()) + " digito";
    if (BI.size()>1) txt += 's';
  }
  txt += ')';
  return move(txt);
}

int main()
{
  BigInt I1, I2, I3, Result;
  string opcao_txt("");
  Opcoes_t opcao = Opcoes_t::OPCAO_INVALIDA;

  cout << "CALCULADORA DE INTEIROS SEM LIMITE\n";
  help();

  do
  {
    cout << "\nI1:     " << I1 << tamanho(I1) << endl;
    cout << "I2:     " << I2 << tamanho(I2) << endl;
    if (opcao == Opcoes_t::DIVIDIR_AMBOS) cout << setw(7) << opcao_txt << " =====\n";
    cout << "I3:     " << I3 << tamanho(I3) << endl;
    if (opcao != Opcoes_t::NUMERO_JA_DIGITADO &&
        opcao != Opcoes_t::DIGITAR_NUMERO &&
        opcao != Opcoes_t::DIVIDIR_AMBOS &&
        opcao != Opcoes_t::TROCAR &&
        opcao != Opcoes_t::AJUDA &&
        opcao != Opcoes_t::OPCAO_INVALIDA) cout << setw(7) << opcao_txt << " =====\n";
    cout << "Result: " << Result << tamanho(Result) << endl;

    // Solicita a opcao
    do
    {
      cout << "Digite sua opcao [h para ajuda]: ";
      cin >> opcao_txt;
    }
    while (opcao_txt.empty());

    // Converte caracteres para minusculas
    for (auto& c : opcao_txt) c = tolower(c);
    // Inicialmente, supoe opcao invalida;
    opcao = Opcoes_t::OPCAO_INVALIDA;
    // Determina a opcao digitada
    if (opcao_txt=="<") opcao = Opcoes_t::DIGITAR_NUMERO;
    else if (opcao_txt=="+") opcao = Opcoes_t::SOMAR;
    else if (opcao_txt=="-") opcao = Opcoes_t::SUBTRAIR;
    else if (opcao_txt=="*") opcao = Opcoes_t::MULTIPLICAR;
    else if (opcao_txt=="/") opcao = Opcoes_t::DIVIDIR_QUOCIENTE;
    else if (opcao_txt=="%") opcao = Opcoes_t::DIVIDIR_RESTO;
    else if (opcao_txt=="div") opcao = Opcoes_t::DIVIDIR_AMBOS;
    else if (opcao_txt=="!") opcao = Opcoes_t::FATORIAL;
    else if (opcao_txt=="<<") opcao = Opcoes_t::ROTACIONAR_ESQUERDA;
    else if (opcao_txt==">>") opcao = Opcoes_t::ROTACIONAR_DIREITA;
    else if (opcao_txt=="++") opcao = Opcoes_t::INCREMENTAR;
    else if (opcao_txt=="--") opcao = Opcoes_t::DECREMENTAR;
    else if (opcao_txt=="inv") opcao = Opcoes_t::INVERTER_SINAL;
    else if (opcao_txt=="abs") opcao = Opcoes_t::MODULO;
    else if (opcao_txt=="t") opcao = Opcoes_t::TROCAR;
    else if (opcao_txt=="h") opcao = Opcoes_t::AJUDA;
    else if (opcao_txt=="q") opcao = Opcoes_t::TERMINAR;

    // Testa se foi digitado um numero em potencial
    if (opcao == Opcoes_t::OPCAO_INVALIDA)
    {
      if (isdigit(opcao_txt[0]) ||
          ((opcao_txt[0]=='+' || opcao_txt[0]=='-') && opcao_txt.size()>1 && isdigit(opcao_txt[1])))
      {
        opcao = Opcoes_t::NUMERO_JA_DIGITADO;
      }
    }

    // Nao rotaciona nada se for incrementar, decrementar, ajuda, sair ou opcao desconhecida
    if (opcao!=Opcoes_t::INCREMENTAR &&
        opcao!=Opcoes_t::DECREMENTAR &&
        opcao!=Opcoes_t::AJUDA &&
        opcao!=Opcoes_t::TERMINAR &&
        opcao!=Opcoes_t::OPCAO_INVALIDA)
    {
      // Rotaciona os numeros no buffer
      if (opcao==Opcoes_t::TROCAR)
      {
        // Rotaciona no sentido inverso
        BigInt prov(move(Result));
        Result = move(I3);
        I3 = move(I2);
        I2 = move(I1);
        I1 = move(prov);
      }
      else
      {
        // Todas as demais opcoes: rotaciona normalmente
        I1 = move(I2);
        I2 = move(I3);
        I3 = move(Result);
        // Novo resultado entra em result
      }
    }

    // Executa a opcao escolhida
    switch(opcao)
    {
    case Opcoes_t::NUMERO_JA_DIGITADO:
      // Usa construtor a partir de string.
      // Se string invalida, imprime msg de erro e faz ser zero.
      Result = BigInt(opcao_txt);
      break;
    case Opcoes_t::DIGITAR_NUMERO:
      // Usa operador de extracao operator>>
      cout << "Valor: ";
      cin >> Result;
      if (cin.fail())
      {
        cerr << "Valor digitado invalido\n";
        cin.clear();
      }
      break;
    case Opcoes_t::SOMAR:
      Result = I2+I3;
      break;
    case Opcoes_t::SUBTRAIR:
      Result = I2-I3;
      break;
    case Opcoes_t::MULTIPLICAR:
      Result = I2*I3;
      break;
    case Opcoes_t::DIVIDIR_QUOCIENTE:
      Result = I2/I3;
      break;
    case Opcoes_t::DIVIDIR_RESTO:
      Result = I2%I3;
      break;
    case Opcoes_t::DIVIDIR_AMBOS:
      // Roda mais uma vez
      I1 = move(I2);
      I2 = move(I3);
      // Resultados da divisao em I3 e Result
      I1.division(I2,I3,Result);
      break;
    case Opcoes_t::FATORIAL:
      Result = !I3;
      break;
    case Opcoes_t::ROTACIONAR_ESQUERDA:
      Result = I2 << I3.toInt();
      break;
    case Opcoes_t::ROTACIONAR_DIREITA:
      Result = I2 >> I3.toInt();
      break;
    case Opcoes_t::INCREMENTAR:
      ++Result;
      break;
    case Opcoes_t::DECREMENTAR:
      --Result;
      break;
    case Opcoes_t::INVERTER_SINAL:
      Result = -I3;
      break;
    case Opcoes_t::MODULO:
      Result = abs(I3);
      break;
    case Opcoes_t::AJUDA:
      help();
      break;
    case Opcoes_t::TROCAR:
    case Opcoes_t::TERMINAR:
      break;
    case Opcoes_t::OPCAO_INVALIDA:
    default:
      cerr << "Opcao (" << opcao_txt << ") desconhecida\n";
      break;
    }
  }
  while (opcao != Opcoes_t::TERMINAR);

  return 0;
}
