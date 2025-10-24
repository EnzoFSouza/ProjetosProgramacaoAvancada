#ifndef MAINPLOTADOR_H
#define MAINPLOTADOR_H

#include <QMainWindow>
#include <vector>
#include <QMessageBox>
#include "lehfuncao.h"
#include "evaluator.h"
#include "grafico.h"

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

    void slotGraficoClicked(double X, double Y);

private:
    Ui::MainPlotador *ui;

    void exibirFuncoes(); //exibe lista de funcoes a serem plotadas
    void desenharGrafico(); //desenha gráfico com as funções

    LehFuncao* lehFuncao;
    Grafico* grafico;
};
#endif // MAINPLOTADOR_H
