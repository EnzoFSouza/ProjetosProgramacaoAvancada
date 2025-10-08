#include <stdexcept>
#include <cmath>
#include <fstream>
#include <limits>
#include <algorithm>
#include <vector>
#include <list>
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
    if (R.nome != nome) return false;
    if (R.comprimento != comprimento) return false;
    for(int i = 0; i < 2; i++){
        if (R.extremidade[i] != extremidade[i]) return false;
    }
    return true;
}

bool Rota::operator==(const IDRota& idR) const{
    if (id != idR) return false;
    return true;
}

bool Rota::operator==(const IDPonto& idP) const{
    if (idP != extremidade[0] && idP != extremidade[1]) return false;
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

            if (find(rotas_temp.begin(), rotas_temp.end(), prov) != rotas_temp.end()) throw 11;

            //Adiciona rota ao vetor temporario
            rotas_temp.push_back(prov);

        }while (leitura_ok);
    }

    catch(int i){
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
Ponto Planejador::getPonto(const IDPonto& Id) const{

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
Rota Planejador::getRota(const IDRota& Id) const{
    // Procura uma rota que corresponde aa Id do parametro
    auto iter = find(rotas.begin(), rotas.end(), Id);

    cout << "Procurei";
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

bool Noh::operator==(const Noh& N) const{
    if (id_pt != N.id_pt) return false;
    if (id_rt != N.id_rt) return false;
    return true;
}

bool Noh::operator<(double d){
    if (f() > d) return false;
    return true;
}

bool buscarRotaByIDPonto(const IDPonto& idP, const Rota& R){
    return R.extremidade[0] == idP || R.extremidade[1] == idP;
}
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
    Noh atual;
    atual.id_pt = id_origem;
    atual.id_rt = IDRota();
    atual.g = 0.0;
    atual.h = pt_origem.distancia(pt_destino);

    list<Noh> Aberto; //nohs ainda nao analisados
    vector<Noh> Fechado; //nohs ja analisados

    Aberto.push_front(atual);

    //Laco principal do algoritmo
    do{
        // Lê e exclui o 1º Noh (o de
        // menor custo) de Aberto
        atual = Aberto.front();
        Aberto.pop_front();

        //Inclui atual no final de fechado
        Fechado.push_back(atual);

        Rota rota_suc;

        //Expande se nao eh solucao
        if(atual.id_pt != id_destino){
            //Gera sucessores de atual
            do{
                //busca rota_suc, proxima rota conectada a atual
                auto iter = find_if(rotas.begin(), rotas.end(), buscarRotaByIDPonto(atual.id_pt));
                //auto iter = find(rotas.begin(), rotas.end(), Id);

                //cout << "Procurei";
                // Em caso de sucesso, retorna o ponto encontrado
                //if (iter != rotas.end()) return *iter;

                rota_suc = *iter;
                //rota_suc = getRota(outraExtremidade(atual.id_pt));

                //find no vetor de rotas, se nao existe é end
                //if(EXISTE(rota_suc)){
                if(find(rotas.begin(), rotas.end(), rota_suc) != rotas.end()){
                    //gera noh sucessor suc
                    Noh suc;

                    //cout << suc.id_pt;
                    suc.id_pt = rota_suc.outraExtremidade(atual.id_pt);
                    suc.id_rt = rota_suc.id;
                    suc.g = atual.g + rota_suc.comprimento;

                    //Ponto do noh suc
                    Ponto pt_suc = getPonto(suc.id_pt);
                    suc.h = pt_suc.distancia(pt_destino);

                    //assume que nao existe igual a suc
                    bool eh_inedito = true;

                    //procura noh igual a suc e fechado
                    Noh oldF;
                    auto itr = find(Fechado.begin(), Fechado.end(), suc.id_pt);
                    oldF = *itr;

                    //Achou algum noh
                    //if(EXISTE(oldF)){
                    if(find(Fechado.begin(), Fechado.end(), oldF) != Fechado.end()) eh_inedito = false; //noh ja existe

                    else{
                        //procura noh igual a suc em aberto
                        Noh oldA;
                        auto itr = find(Aberto.begin(), Aberto.end(), suc.id_pt);
                        oldA = *itr;

                        //achou algum noh
                        //if(EXISTE(oldA)){
                        if(find(Aberto.begin(), Aberto.end(), oldA) != Aberto.end()){
                            //Menor custo total
                            if(suc.f() <  oldA.f()) Aberto.erase(itr); //exclui anterior
                            else eh_inedito = false; //Noh ja exitse
                        }
                    }
                    //nao existe igual
                    if(eh_inedito){
                        //Noh big = lower_bound(suc.f(), Aberto);
                        //Acha big, primeiro noh de aberto com custo total f() maior que f() de suc
                        auto iter = lower_bound(Aberto.begin(), Aberto.end(), suc.f());
                        Noh big = *iter;

                        //insere suc em aberto antes de big
                        Aberto.insert(iter, suc);
                    }
                }
            }while(find(rotas.begin(), rotas.end(), rota_suc) != rotas.end()); //Existe rota suc
        }
    }while(!Aberto.empty() && (atual.id_pt != id_destino));

    NumAberto = size(Aberto);
    NumFechado = size(Fechado);

    // Inicialmente, caminho "C" vazio
    C = Caminho();

    double Compr;
    // Encontrou solução ou nao?
    if(atual.id_pt != id_destino){
        Compr = -1.0;
    }
    else{
        Compr = atual.g;

        while(atual.id_pt.valid()){
            // Acrescenta Trecho atual no
            // topo do caminho "C"
            C.push(Trecho(atual.id_rt, atual.id_pt));

            // Recupera o antecessor.
            // Obtém "rota_ant", Rota que
            // levou até "atual".
            Rota rota_ant = getRota(atual.id_rt);

            //Calcula id do antecessor
            IDPonto id_pt_ant = rota_ant.outraExtremidade(atual.id_pt);

            //Procura noh igual a "id_pt_ant" em fechado
            auto iter = find(Fechado.begin(), Fechado.end(), id_pt_ant);

            atual = *iter;

        }
         // Acrescenta Trecho da origem no
        // topo do caminho "C"
        C.push(Trecho(atual.id_rt, atual.id_pt));
    }
    /* ***********  /
    /  FALTA FAZER  /
    /  *********** */

    // Substitua pelo caminho correto

    // Substitua pelo valor correto
    return Compr;
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
