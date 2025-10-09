#include <stdexcept>
#include <cmath>
#include <fstream>
#include <limits>
/* ACRESCENTE SE NECESSARIO */
#include <algorithm>
#include <vector>
#include <list>
#include <exception>

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

//Sobrecarga de operadores
bool Ponto::operator==(const Ponto& P) const{
    //if (P.id != id) return false;
    //if (P.nome != nome) return false;
    //if ((P.latitude != latitude) || (P.longitude != longitude)) return false;
    if (id != P.id) return false;
    return true;
}

bool Ponto::operator==(const IDPonto& idP) const{
    if(id != idP) return false;
    return true;
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

//Sobrecarga de operadores
bool Rota::operator==(const Rota& R) const{
    //if (nome != R.nome) return false;
    //if (comprimento != R.comprimento) return false;
    //for(int i = 0; i < 2; i++){
    //    if (R.extremidade[i] != extremidade[i]) return false;
    //}
    if (id != R.id) return false;
    return true;
}

bool Rota::operator==(const IDRota& idR) const{
    if (id != idR) return false;
    return true;
}

bool Rota::operator==(const IDPonto& idP) const{
    if (extremidade[0] == idP || extremidade[1] == idP) return true;
    return false;
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
        if(!I.is_open()) throw 1;

        string cabecalho;

        // Leitura da primeira linha do arquivo
        getline(I, cabecalho); //Leh ateh \n
        if(I.fail() || cabecalho!="ID;Nome;Latitude;Longitude") throw 2;

        bool leitura_ok;

        do{
            string id;
            Ponto prov;
            IDPonto id_prov;

            I >> ws;

            getline(I, id, ';');
            prov.id.set(move(id));
            if (!I) throw 3;

            getline(I, prov.nome, ';');
            if (!I) throw 4;

            I >> prov.latitude;
            if (!I) throw 5;

            getline(I, id, ';'); //Na leitura da latitude, cin nao consome o ; e o cin da longitude da erro pois consome
            //o ; mas longitude eh double

            I >> prov.longitude;
            if (!I) throw 6;

            I >> ws;
            leitura_ok = I.good();

            //Testa se ponto eh valido
            if (!prov.valid()) throw 7;

            //Testa se ponto jah existe
            if (find(pontos_temp.begin(), pontos_temp.end(), prov) != pontos_temp.end()) throw 8;

            //Adiciona ponto ao vetor temporario
            pontos_temp.push_back(prov);

        }while (leitura_ok);
    }

    catch(int i){
        string msg_error = "Erro " + to_string(i) + " na leitura do arquivo de pontos";
        throw ios_base::failure(msg_error);
    }

    I.close();

    I.open(arq_rotas, fstream::in);

    try{
        if(!I.is_open()) throw 1;

        string cabecalho;

        // Leitura da primeira linha do arquivo
        getline(I, cabecalho);  // Leh ateh \n
        if(I.fail() || cabecalho!="ID;Nome;Extremidade 1;Extremidade 2;Comprimento") throw 2;

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
            if (!I) throw 3;

            getline(I, prov.nome, ';');
            if (!I) throw 4;

            getline(I, id1, ';');
            prov.extremidade[0].set(move(id1));
            if (!I) throw 5;

            getline(I, id2, ';');
            prov.extremidade[1].set(move(id2));
            if (!I) throw 6;

            I >> prov.comprimento;
            if (!I) throw 7;

            I >> ws;
            leitura_ok = I.good();

            //Testa se rota eh valida
            if (!prov.valid()) throw 8;

            if (find(pontos_temp.begin(), pontos_temp.end(), prov.extremidade[0]) == pontos_temp.end()) throw 9;

            if (find(pontos_temp.begin(), pontos_temp.end(), prov.extremidade[1]) == pontos_temp.end()) throw 10;

            //Testa se rota jah existe
            if (find(rotas_temp.begin(), rotas_temp.end(), prov) != rotas_temp.end()) throw 11;

            //Adiciona rota ao vetor temporario
            rotas_temp.push_back(prov);

        }while (leitura_ok);
    }

    catch(int i){
        if (i == 11) cout << "rota ja existe" << endl;
        string msg_error = "Erro " + to_string(i) + " na leitura do arquivo de rotas";
        throw ios_base::failure(msg_error);
    }

    I.close();
    pontos = move(pontos_temp);
    rotas = move(rotas_temp);
}

/// Retorna um Ponto do mapa, passando a id como parametro.
/// Se a id for inexistente, gera excecao.
/// Deve receber ACRESCIMOS
Ponto Planejador::getPonto(const IDPonto& Id) const
{
  //Procura um ponto que corresponde aa Id do parametro
    auto iter = find(pontos.begin(), pontos.end(), Id);

    // Em caso de sucesso, retorna o ponto encontrado
    if (iter != pontos.end()) return *iter;

    // Se nao encontrou, gera excecao
    throw invalid_argument("getPonto: invalid IDPonto parameter");
}

/// Retorna um Rota do mapa, passando a id como parametro.
/// Se a id for inexistente, gera excecao.
/// Deve receber ACRESCIMOS
Rota Planejador::getRota(const IDRota& Id) const
{
    // Procura uma rota que corresponde aa Id do parametro
    auto iter = find(rotas.begin(), rotas.end(), Id);

    //cout << "Procurei";
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
bool Noh::operator==(const IDPonto& idP) const{
    return (id_pt == idP);
}

bool Noh::operator<(const Noh& N) const{
    if(f() > N.f()) return false;
    return true;
}

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
  try{

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
    Noh atual;
    atual.id_pt = id_origem;
    atual.id_rt = IDRota();
    atual.g = 0.0;
    atual.h = pt_origem.distancia(pt_destino);

    list<Noh> Aberto;
    vector<Noh> Fechado;

    Aberto.push_front(atual);

    //Enquanto nao encontrou solucao e existem nohs em aberto
    while((!Aberto.empty()) && (atual.id_pt != id_destino)) {

        //Le e excluiu o 1 noh (de menor custo) de aberto
        atual = Aberto.front();
        Aberto.pop_front();

        // Adiciona noh atual ao final de dechado
        Fechado.push_back(atual);

        // Verifica se é destino
        if(atual.id_pt == id_destino) break;

        // Gera sucessores
        // Iterando pelo vetor de rotas
        for(const auto& rota_suc : rotas) {
            if(!(rota_suc == atual.id_pt)) continue; //pular as rotas que nao partem do ponto atual

            //Criando noh suc
            Noh suc;
            suc.id_pt = rota_suc.outraExtremidade(atual.id_pt);
            suc.id_rt = rota_suc.id;
            suc.g = atual.g + rota_suc.comprimento;
            Ponto pt_suc = getPonto(suc.id_pt);
            suc.h = pt_suc.distancia(pt_destino);

            bool eh_inedito = true;

            // Procura noh igual a suc em fechado
            for(const auto& nohF : Fechado) {
                if(nohF.id_pt == suc.id_pt) {
                    eh_inedito = false; //noh ja existe
                    break;
                }
            }

            // Procura noh igual a suc em aberto
            if(eh_inedito) {
                for(auto itA = Aberto.begin(); itA != Aberto.end(); ++itA) {
                    if(itA->id_pt == suc.id_pt) { //se encontrou noh
                        if(suc.f() < itA->f()) { //menor custo total
                            Aberto.erase(itA); // exclui anterior, remove nó mais caro
                        } else {
                            eh_inedito = false; // noh já existe com custo melhor
                        }
                        break;
                    }
                }
            }

            // Insere suc na posição correta de aberto
            if(eh_inedito) {
                auto it = Aberto.begin();
                while(it != Aberto.end() && it->f() < suc.f()) ++it;
                Aberto.insert(it, suc);
            }
        }
    }


    NumAberto = Aberto.size();
    NumFechado = Fechado.size();

    // Inicializa caminho vazio
    C = Caminho();
    double Compr;

    if(atual.id_pt != id_destino) {
            // Não encontrou caminho
            Compr = -1.0;
    } else {
        // Caminho encontrado
        Compr = atual.g;
        IDPonto id_atual = atual.id_pt;

        while(id_atual.valid()) {
            // Encontra rota que levou até id_atual
            auto it = find(Fechado.begin(), Fechado.end(), id_atual);
            if(it == Fechado.end()) break;

            C.push(Trecho(it->id_rt, it->id_pt));

            // Rota anterior
            Rota rota_ant = getRota(it->id_rt);
            id_atual = rota_ant.outraExtremidade(it->id_pt);

            // Se chegou na origem, insere trecho final e sai
            if(id_atual == id_origem) {
                C.push(Trecho(rota_ant.id, id_atual));
                break;
            }
        }
    }

    return Compr;
  }

  catch(int i){
    string msg_err = "Erro " + to_string(i) + " no calculo do caminho\n";
    throw invalid_argument(msg_err);
  }

  // Zera o caminho resultado em caso de erro
  C = Caminho();

  // Retorna -1 em caso de erro
  return -1.0;
}
