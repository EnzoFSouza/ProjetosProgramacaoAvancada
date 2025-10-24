#ifndef GRAFICO_H
#define GRAFICO_H

#include <QLabel>
#include <QColor>
#include <QPixmap>
#include "evaluator.h"


class Grafico : public QLabel
{
    Q_OBJECT
public:
    Grafico(QWidget *parent = nullptr);

    bool empty() {return eval.empty();};

    size_t size() {return eval.size();};

    const Evaluator& getEval(int i) {return eval.at(i);};

    const QColor& getCor(int i) {return cor.at(i);};

    void pushFuncao(QString Funcao, QColor Cor);

    void clearFuncoes();

    void setLimites(int MinX, int MaxX, int ExpX, int MinY, int MaxY, int ExpY);

    void desenharGrafico();

signals:
    void signGraficoClicked(double X, double Y);

private:
    double convXtoJ(double X) const; //converte valor X para coordenada (coluna) J
    double convYtoI(double Y) const; //converte valor Y para coordenada (linha) I
    double convJtoX(double J) const; //converte coordenada (coluna) J para valor X
    double convItoY(double I) const; //converte coordenada (linha) I para valor Y

    void resizeEvent(QResizeEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    std::vector<Evaluator> eval;
    std::vector<QColor> cor;
    QPixmap img;
    int largura, altura;
    double minX, maxX, minY, maxY;
    int nMarcX, nMarcY;

};

#endif // GRAFICO_H
