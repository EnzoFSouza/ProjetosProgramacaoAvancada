#include <stdexcept>
#include <cmath>
#include <fstream>
#include <limits>
/* ACRESCENTE SE NECESSARIO */
#include <vector>

#include "planejador.h"

using namespace std;

/* *************************
   * CLASSE IDPONTO        *
   ************************* */

/// Atribuicao de string
/// NAO DEVE SER MODIFICADA
void IDPonto::set(string&& S)
{
  t=move(S);
  if (!valid()) t.clear();
}

/* *************************
   * CLASSE IDROTA         *
   ************************* */

/// Atribuicao de string
/// NAO DEVE SER MODIFICADA
void IDRota::set(string&& S)
{
  t=move(S);
  if (!valid()) t.clear();
}

/* *************************
   * CLASSE PONTO          *
   ************************* */

/// Impressao em console
/// NAO DEVE SER MODIFICADA
ostream& operator<<(ostream& X, const Ponto& P)
{
  X << P.id << '\t' << P.nome << " (" <<P.latitude << ',' << P.longitude << ')';
  return X;
}

/// Distancia entre 2 pontos (formula de haversine)
/// NAO DEVE SER MODIFICADA
double Ponto::distancia(const Ponto& P) const
{
  // Gera excecao se pontos invalidos
  if (!valid() || !P.valid())
    throw invalid_argument("distancia: ponto(s) invalido(s)");

  // Tratar logo pontos identicos
  if (id == P.id) return 0.0;
  // Constantes
  static const double MY_PI = 3.14159265358979323846;
  static const double R_EARTH = 6371.0;
  // Conversao para radianos
  double lat1 = MY_PI*this->latitude/180.0;
  double lat2 = MY_PI*P.latitude/180.0;
  double lon1 = MY_PI*this->longitude/180.0;
  double lon2 = MY_PI*P.longitude/180.0;
  // Seno das diferencas
  double sin_dlat2 = sin((lat2-lat1)/2.0);
  double sin_dlon2 = sin((lon2-lon1)/2.0);
  // Quadrado do seno do angulo entre os pontos
  double sin2_ang = sin_dlat2*sin_dlat2 + cos(lat1)*cos(lat2)*sin_dlon2*sin_dlon2;
  // Em vez de utilizar a funcao arcosseno, asin(sqrt(sin2_ang)),
  // vou utilizar a funcao arcotangente, menos sensivel a erros numericos.
  // Distancia entre os pontos
  return 2.0*R_EARTH*atan2(sqrt(sin2_ang),sqrt(1-sin2_ang));
}

/* *************************
   * CLASSE ROTA           *
   ************************* */

/// Impressao em console
/// NAO DEVE SER MODIFICADA
ostream& operator<<(ostream& X, const Rota& R)
{
  X << R.id << '\t' << R.nome << '\t' << R.comprimento << "km"
    << " [" << R.extremidade[0] << ',' << R.extremidade[1] << ']';
  return X;
}

/// Retorna a outra extremidade da rota, a que nao eh o parametro.
/// Gera excecao se o parametro nao for uma das extremidades da rota.
/// NAO DEVE SER MODIFICADA
IDPonto Rota::outraExtremidade(const IDPonto& ID) const
{
  if (extremidade[0]==ID) return extremidade[1];
  if (extremidade[1]==ID) return extremidade[0];
  throw invalid_argument("outraExtremidade: invalid IDPonto parameter");
}

/* *************************
   * CLASSE PLANEJADOR     *
   ************************* */

/// Torna o mapa vazio
/// NAO DEVE SER MODIFICADA
void Planejador::clear()
{
  pontos.clear();
  rotas.clear();
}

/// Leh um mapa dos arquivos arq_pontos e arq_rotas.
/// Caso nao consiga ler dos arquivos, deixa o mapa inalterado e gera excecao ios_base::failure.
/// Deve receber ACRESCIMOS
void Planejador::ler(const std::string& arq_pontos,
                     const std::string& arq_rotas)
{

    ifstream I;
    // Vetores temporarios para armazenamento dos Pontos e Rotas lidos.
    vector<Ponto> pontos_temp;
    vector<Ponto>::iterator j;

    try{
        //Abre arquivo
        I.open(arq_pontos, fstream::in);
        if(!I.is_open()) throw 1;

        string cabecalho;

        // Leitura da primeira linha do arquivo
        getline(I, cabecalho);  // Leh ateh \n
        if(I.fail() || cabecalho!="ID;Nome;Latitude;Longitude") throw 2;

        bool leitura_ok;

        do{
            string id;
            Ponto prov;
            IDPonto id_prov;

            getline(I, id, ';');
            prov.id.set(move(id));
            if (!I || prov.id==id_prov) throw 3;
            cout << prov.id;

            getline(I, prov.nome, ';');
            if (!I || prov.nome=="") throw 4;
            cout << prov.nome;

            I >> prov.latitude;
            if (!I || prov.latitude==0) throw 5;
            cout << prov.latitude;

            getline(I, id, ';'); //Na leitura da latitude, cin nao consome o ; e o cin da longitude da erro pois consome
            //o ; mas longitude eh double

            I >> prov.longitude;
            if (!I || prov.longitude==0) throw 6;
            cout << prov.longitude;

            I >> ws;
            leitura_ok = I.good();

            pontos_temp.push_back(prov);

        }while (leitura_ok);
    }

    catch(int i){
        I.setstate(ios::failbit);
        cerr << "Erro " << i << " na leitura do arquivo de pontos " << arq_pontos;
    }

    for(j = pontos_temp.begin(); j != pontos_temp.end(); j++) cout << *j << "Vetor";

  // Leh os Pontos do arquivo e armazena no vetor temporario de Pontos.
  // 1) Abre o arquivo de Pontos (Em caso de erro, codigo 1)
  // 2) Leh e testa o cabecalho do arquivo: "ID;Nome;Latitude;Longitude"
  //    (Em caso de erro, codigo 2)
  //3) Repita a leitura de cada um dos Pontos:
  //    | 3.1) Leh a ID (Em caso de erro na leitura, codigo 3)
  //    | 3.2) Leh o nome (Em caso de erro, codigo 4)
  //    | 3.3) Leh a latitude (Em caso de erro na leitura, codigo 5)
  //    | 3.4) Leh a longitude (Em caso de erro na leitura, codigo 6)
  //    | 3.5) Consome todos os eventuais separadores ateh o inicio do proximo dado
  //    | 3.6) Testa se o Ponto com esses parametros lidos eh valido
  //    |      (Em caso de erro, codigo 7)
  //    | 3.7) Testa que nao existe Ponto com a mesma ID no vetor temporario
  //    |      de Pontos lidos ateh agora (Em caso de erro, codigo 8)
  //    | 3.8) Insere o Ponto lido no vetor temporario de Pontos
  //    enquanto o arquivo não acabar (eof)
  //    Em caso de qualquer erro, gera excecao ios_base::failure com mensagem:
  //      "Erro <CODIGO> na leitura do arquivo de pontos <ARQ_PONTOS>"


  // 4) Fecha o arquivo de Pontos
  /* ***********  /
  /  FALTA FAZER  /
  /  *********** */

  // Leh as Rotas do arquivo e armazena no vetor temporario de Rotas.
  // 1) Abre o arquivo de Rotas (Em caso de erro, codigo 1)
  // 2) Leh e testa o cabecalho do arquivo: "ID;Nome;Extremidade 1;Extremidade 2;Comprimento"
  //    (Em caso de erro, codigo 2)
  // 3) Repita a leitura de cada uma das Rotas:
  //    | 3.1) Leh a ID (Em caso de erro na leitura, codigo 3)
  //    | 3.2) Leh o nome (Em caso de erro na leitura, codigo 4)
  //    | 3.3) Leh a ID da extremidade[0] (Em caso de erro na leitura, codigo 5)
  //    | 3.4) Leh a ID da extremidade[1] (Em caso de erro na leitura, codigo 6)
  //    | 3.5) Leh o comprimento (Em caso de erro na leitura, codigo 7)
  //    | 3.6) Consome todos os eventuais separadores ateh o inicio do proximo dado
  //    | 3.7) Testa se a Rota com esses parametros lidos eh valida
  //    |      (Em caso de erro, codigo 8)
  //    | 3.8) Testa que a Id da extremidade[0] corresponde a um ponto lido
  //    |      no vetor temporario de Pontos (Em caso de erro, codigo 9)
  //    | 3.9) Testa que a Id da extremidade[1] corresponde a um ponto lido
  //    |      no vetor temporario de Pontos (Em caso de erro, codigo 10)
  //    | 3.10) Testa que nao existe Rota com a mesma ID no vetor temporario
  //    |      de Rotas lidas ateh agora (Em caso de erro, codigo 11)
  //    | 3.11) Insere a Rota lida no vetor temporario de Rotas
  //    enquanto o arquivo não acabar (eof)
  //    Em caso de qualquer erro, gera excecao ios_base::failure com mensagem:
  //      "Erro <CODIGO> na leitura do arquivo de rotas <ARQ_ROTAS>"
  // 4) Fecha o arquivo de Rotas
  /* ***********  /
  /  FALTA FAZER  /
  /  *********** */

  // Faz os vetores temporarios de Pontos e Rotas passarem a ser
  // os vetores de Pontos e Rotas do planejador.
  /* ***********  /
  /  FALTA FAZER  /
  /  *********** */
}

/// Retorna um Ponto do mapa, passando a id como parametro.
/// Se a id for inexistente, gera excecao.
/// Deve receber ACRESCIMOS
Ponto Planejador::getPonto(const IDPonto& Id) const
{
  // Procura um ponto que corresponde aa Id do parametro
  /* ***********  /
  /  FALTA FAZER  /
  /  *********** */
  // Em caso de sucesso, retorna o ponto encontrado
  /* ***********  /
  /  FALTA FAZER  /
  /  *********** */
  // Se nao encontrou, gera excecao
  throw invalid_argument("getPonto: invalid IDPonto parameter");
}

/// Retorna um Rota do mapa, passando a id como parametro.
/// Se a id for inexistente, gera excecao.
/// Deve receber ACRESCIMOS
Rota Planejador::getRota(const IDRota& Id) const
{
  // Procura uma rota que corresponde aa Id do parametro
  /* ***********  /
  /  FALTA FAZER  /
  /  *********** */
  // Em caso de sucesso, retorna a rota encontrada
  /* ***********  /
  /  FALTA FAZER  /
  /  *********** */
  // Se nao encontrou, gera excecao
  throw invalid_argument("getRota: invalid IDRota parameter");
}

/// *******************************************************************************
/// Calcula o caminho entre a origem e o destino do planejador usando o algoritmo A*
/// *******************************************************************************

/// Noh: os elementos dos conjuntos de busca do algoritmo A*.
/// Deve ser DECLARADA E IMPLEMENTADA inteiramente.
/* ***********  /
/  FALTA FAZER  /
/  *********** */

/// Calcula o caminho mais curto no mapa entre origem e destino, usando o algoritmo A*
/// Retorna o comprimento do caminho encontrado (<0 se nao existe caminho).
/// O parametro C retorna o caminho encontrado (vazio se nao existe caminho).
/// O parametro NumAberto retorna o numero de nos (>=0) em Aberto ao termino do algoritmo A*,
/// mesmo quando nao existe caminho.
/// O parametro NumFechado retorna o numero de nos (>=0) em Fechado ao termino do algoritmo A*,
/// mesmo quando nao existe caminho.
/// Em caso de parametros de entrada invalidos ou de erro no algoritmo, gera excecao.
/// Deve receber ACRESCIMOS.
double Planejador::calculaCaminho(const IDPonto& id_origem,
                                  const IDPonto& id_destino,
                                  Caminho& C, int& NumAberto, int& NumFechado)
{
  try
  {
    // Mapa vazio
    if (empty()) throw 1;

    Ponto pt_origem, pt_destino;
    // Calcula os pontos que correspondem a id_origem e id_destino.
    // Se algum nao existir, throw 2
    try
    {
      pt_origem = getPonto(id_origem);
      pt_destino = getPonto(id_destino);
    }
    catch(...)
    {
      throw 2;
    }

    /* *****************************  /
    /  IMPLEMENTACAO DO ALGORITMO A*  /
    /  ***************************** */

    /* ***********  /
    /  FALTA FAZER  /
    /  *********** */

    // Substitua pelo caminho correto
    C = Caminho();

    // Substitua pelo valor correto
    return -1.0;
  }
  catch(int i)
  {
    string msg_err = "Erro " + to_string(i) + " no calculo do caminho\n";
    throw invalid_argument(msg_err);
  }

  // Zera o caminho resultado em caso de erro
  C = Caminho();

  // Retorna -1 em caso de erro
  return -1.0;
}
