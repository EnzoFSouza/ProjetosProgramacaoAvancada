#ifndef MAINPLOTADOR_H
#define MAINPLOTADOR_H

#include <QMainWindow>
#include <vector>
#include <QMessageBox>
#include "lehfuncao.h"
#include "evaluator.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainPlotador;
}
QT_END_NAMESPACE

class MainPlotador : public QMainWindow
{
    Q_OBJECT

public:
    MainPlotador(QWidget *parent = nullptr);
    ~MainPlotador();

private slots:
    void on_actionFun_o_triggered();

    void on_actionApagar_triggered();

    void on_actionSair_triggered();

    void on_spinMinX_valueChanged(int arg1);

    void on_spinMaxX_valueChanged(int arg1);

    void on_spinMinY_valueChanged(int arg1);

    void on_spinMaxY_valueChanged(int arg1);

    void on_spinExpX_valueChanged(int arg1);

    void on_spinExpY_valueChanged(int arg1);

    void on_pushApagar_clicked();

    void slotIncluirFuncao(QString Funcao, QColor Cor);

private:
    Ui::MainPlotador *ui;

    double convXtoJ(double X) const; //converte valor X para coordenada (coluna) J
    double convYtoI(double Y) const; //converte valor Y para coordenada (linha) I
    double convJtoX(double J) const; //converte coordenada (coluna) J para valor X
    double convItoY(double I) const; //converte coordenada (linha) I para valor Y
    void exibirFuncoes(); //exibe lista de funcoes a serem plotadas
    void desenharGrafico(); //desenha gráfico com as funções

    LehFuncao* lehFuncao;
    std::vector<Evaluator> eval;
    std::vector<QColor> cor;
    int largura, altura;
    double minX, maxX, minY, maxY;
    int nMarcX, nMarcY;
};
#endif // MAINPLOTADOR_H
