#include <stdexcept>
#include <cmath>
#include <fstream>
#include <limits>
#include <algorithm>
#include <vector>
#include <exception>

#include "planejador.h"

using namespace std;

/// Atribuicao de string
/// NAO DEVE SER MODIFICADA
void IDPonto::set(string&& S)
{
  t=move(S);
  if (!valid()) t.clear();
}

/// Atribuicao de string
/// NAO DEVE SER MODIFICADA
void IDRota::set(string&& S)
{
  t=move(S);
  if (!valid()) t.clear();
}

/// Impressao em console
/// NAO DEVE SER MODIFICADA
ostream& operator<<(ostream& X, const Ponto& P)
{
  X << P.id << '\t' << P.nome << " (" <<P.latitude << ',' << P.longitude << ')';
  return X;
}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//Posso modificar
//Sobrecarga de operadores
bool Ponto::operator==(const Ponto& P) const{
    if (P.id != id) return false;
    if (P.nome != nome) return false;
    if ((P.latitude != latitude) || (P.longitude != longitude)) return false;

    return true;
}

bool Ponto::operator==(const IDPonto& idP) const{
    if (idP != id) return false;
    return true;
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
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

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//Posso modificar
//Sobrecarga de operadores
bool Rota::operator==(const Rota& R) const{
    //Com a mesma id?
    if (R.id != id) return false;
    /*if (R.nome != nome) return false;
    if (R.comprimento != comprimento) return false;
    for(int i = 0; i < 2; i++){
        if (R.extremidade[i] != extremidade[i]) return false;
    }*/
    return true;
}

bool Rota::operator==(const IDRota& idR) const{
    if (id != idR) return false;
    return true;
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

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

    vector<Ponto> pontos_temp;
    vector<Rota> rotas_temp;

    I.open(arq_pontos, fstream::in);

    try{
        if(!I.is_open()) throw ios_base::failure("Erro 1 na leitura do arquivo de pontos ");

        string cabecalho;

        // Leitura da primeira linha do arquivo
        getline(I, cabecalho); //Leh ateh \n
        if(I.fail() || cabecalho!="ID;Nome;Latitude;Longitude") throw ios_base::failure("Erro 2 na leitura do arquivo de pontos ");

        bool leitura_ok;

        do{
            string id;
            Ponto prov;
            IDPonto id_prov;

            I >> ws;

            getline(I, id, ';');
            prov.id.set(move(id));
            if (!I) throw ios_base::failure("Erro 3 na leitura do arquivo de pontos ");

            getline(I, prov.nome, ';');
            if (!I) throw ios_base::failure("Erro 4 na leitura do arquivo de pontos ");

            I >> prov.latitude;
            if (!I) throw ios_base::failure("Erro 5 na leitura do arquivo de pontos ");

            getline(I, id, ';'); //Na leitura da latitude, cin nao consome o ; e o cin da longitude da erro pois consome
            //o ; mas longitude eh double

            I >> prov.longitude;
            if (!I) throw ios_base::failure("Erro 6 na leitura do arquivo de pontos ");

            I >> ws;
            leitura_ok = I.good();

            //Testa se ponto eh valido
            if (!prov.valid()) throw ios_base::failure("Erro 7 na leitura do arquivo de pontos ");

            //Testa se ponto jah existe
            if (find(pontos_temp.begin(), pontos_temp.end(), prov) != pontos_temp.end()) throw ios_base::failure("Erro 8 na leitura do arquivo de pontos ");

            //Adiciona ponto ao vetor temporario
            pontos_temp.push_back(prov);

        }while (leitura_ok);
    }

    catch(const ios_base::failure& e){
        //I.setstate(ios_base::failure);
        cerr << e.what() << arq_pontos;
    }

    I.close();

    I.open(arq_rotas, fstream::in);

    try{
        if(!I.is_open()) throw ios_base::failure("Erro 1 na leitura do arquivo de rotas ");

        string cabecalho;

        // Leitura da primeira linha do arquivo
        getline(I, cabecalho);  // Leh ateh \n
        if(I.fail() || cabecalho!="ID;Nome;Extremidade 1;Extremidade 2;Comprimento") throw ios_base::failure("Erro 2 na leitura do arquivo de rotas ");

        bool leitura_ok;

        do{
            string id;
            string id1;
            string id2;
            Rota prov;
            IDRota id_prov;

            I >> ws;

            getline(I, id, ';');
            prov.id.set(move(id));
            if (!I) throw ios_base::failure("Erro 3 na leitura do arquivo de rotas ");

            getline(I, prov.nome, ';');
            if (!I) throw ios_base::failure("Erro 4 na leitura do arquivo de rotas ");

            getline(I, id1, ';');
            prov.extremidade[0].set(move(id1));
            if (!I) throw ios_base::failure("Erro 5 na leitura do arquivo de rotas ");

            getline(I, id2, ';');
            prov.extremidade[1].set(move(id2));
            if (!I) throw ios_base::failure("Erro 6 na leitura do arquivo de rotas ");

            I >> prov.comprimento;
            if (!I) throw ios_base::failure("Erro 7 na leitura do arquivo de rotas ");

            I >> ws;
            leitura_ok = I.good();

            //Testa se rota eh valida
            if (!prov.valid()) throw ios_base::failure("Erro 8 na leitura do arquivo de rotas ");

            if (find(pontos_temp.begin(), pontos_temp.end(), prov.extremidade[0]) == pontos_temp.end()) throw ios_base::failure("Erro 9 na leitura do arquivo de rotas ");

            if (find(pontos_temp.begin(), pontos_temp.end(), prov.extremidade[1]) == pontos_temp.end()) throw ios_base::failure("Erro 10 na leitura do arquivo de rotas ");

            if (find(rotas_temp.begin(), rotas_temp.end(), prov) != rotas_temp.end()) throw ios_base::failure("Erro 11 na leitura do arquivo de rotas ");

            //Adiciona rota ao vetor temporario
            rotas_temp.push_back(prov);

        }while (leitura_ok);
    }

    catch(const ios_base::failure& e){
        //I.setstate(ios_base::failure);
        cerr << e.what() << arq_rotas;
    }

    I.close();
    pontos = move(pontos_temp);
    rotas = move(rotas_temp);
}

/// Retorna um Ponto do mapa, passando a id como parametro.
/// Se a id for inexistente, gera excecao.
/// Deve receber ACRESCIMOS
Ponto Planejador::getPonto(const IDPonto& Id) const{

    //Procura um ponto que corresponde aa Id do parametro
    vector<Ponto>::const_iterator iter;
    iter = find(pontos.begin(), pontos.end(), Id);

    // Em caso de sucesso, retorna o ponto encontrado
    if (iter != pontos.end()) return *iter;

    // Se nao encontrou, gera excecao
    throw invalid_argument("getPonto: invalid IDPonto parameter");
}

/// Retorna um Rota do mapa, passando a id como parametro.
/// Se a id for inexistente, gera excecao.
/// Deve receber ACRESCIMOS
Rota Planejador::getRota(const IDRota& Id) const{
    // Procura uma rota que corresponde aa Id do parametro
    vector<Rota>::const_iterator iter;
    iter = find(rotas.begin(), rotas.end(), Id);

    // Em caso de sucesso, retorna o ponto encontrado
    if (iter != rotas.end()) return *iter;

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
    /*Noh atual;
    atual.id_pt = id_origem;
    atual.id_rt = IDRota();
    atual.g = 0.0;
    atual.h = pt_origem.distancia(pt_destino);
*/

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
