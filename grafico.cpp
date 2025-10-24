#include "grafico.h"

Grafico::Grafico(QWidget *parent = nullptr):
    QLabel(parent)
    //,eval(std::vector<Evaluator>)
    //, cor(std::vector<QColor>)
    , img(QPixmap())
    , largura(0)
    , altura(0)
    , minX(0.0)
    , maxX(0.0)
    , minY(0.0)
    , maxY(0.0)
    , nMarcX(0)
    , nMarcY(0)
{
    QSizePolicy::Expanding(setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    setMinimumSize(540, 540);
    setFrameShape(QFrame::Box);
    setFrameShadow(QFrame::Plain);
    setAlignment(Qt::AlignCenter);
}

void Grafico::pushFuncao(QString Funcao, QColor Cor)
{
    try{
        Evaluator new_eval;
        new_eval.set(Funcao.toStdString());
        eval.push_back(new_eval);
        cor.push_back(Cor);
    }
    catch(const std::invalid_argument &E){
        QMessageBox::critical(this, "Funcao Invalida", "Erro na funcao: " + QString::fromStdString(E.what()));
    }
}

void Grafico::clearFuncoes()
{
    eval.clear();
    cor.clear();
}

void Grafico::setLimites(int MinX, int MaxX, int ExpX, int MinY, int MaxY, int ExpY)
{
    minX = MinX * pow(10.0, ExpX);

    maxX = MaxX * pow(10.0, ExpX);

    minY = MinY * pow(10.0, ExpY);

    maxY = MaxX * pow(10.0, ExpY);

    nMarcX = 1 + MaxX - MinX;

    nMarcY = 1 + MaxY - MinY;

    //minX = ui->spinMinX->value() * pow(10.0, ui->spinExpX->value());
    //maxX = ui->spinMaxX->value() * pow(10.0, ui->spinExpX->value());

    //minY = ui->spinMinY->value() * pow(10.0, ui->spinExpY->value());
    //maxY = ui->spinMaxY->value() * pow(10.0, ui->spinExpY->value());

    //nMarcX = 1 + ui->spinMaxX->value() - ui->spinMinX->value();
    //nMarcY = 1 + ui->spinMaxY->value() - ui->spinMinY->value();
}

void Grafico::desenharGrafico()
{
    QPen pen;
    QPainter painter;

    largura = this->width();
    altura = this->height();

    QPixmap img(largura, altura);
    img.fill(Qt::white);

    pen.setWidth(3);
    pen.setColor(Qt::black);
    painter.begin(&img);
    painter.setPen(pen);

    //Eixo X
    double Izero = convYtoI(0.0);
    if ((Izero >= 0.0) && (Izero <= altura - 1.0)){
        QLineF eixoX(0.0, Izero, largura - 1.0, Izero);
        painter.drawLine(eixoX);

        for(int i = 0; i < nMarcX; ++i){
            double Jmarc = convXtoJ(minX + (maxX - minX) * i / (nMarcX - 1.0));
            QLineF marcacao(Jmarc, Izero - 3.0, Jmarc, Izero + 3.0);
            painter.drawLine(marcacao);
        }
    }

    //Eixo Y
    double Jzero = convXtoJ(0.0);
    if (Jzero >= 0.0 && Jzero <= largura - 1.0)
    {
        QLineF eixoY(Jzero, 0.0, Jzero, altura - 1.0);
        painter.drawLine(eixoY);

        for (int i = 0; i < nMarcY; ++i)
        {
            double Imarc = convYtoI(minY + (maxY - minY) * i / (nMarcY - 1.0));
            QLineF marcacao(Jzero - 3.0, Imarc, Jzero + 3.0, Imarc);
            painter.drawLine(marcacao);
        }
    }

    if(eval.empty()){
        painter.end();
        this->setPixmap(img);
        return;
    }

    double X, Y;
    double I, Iant;

    pen.setWidth(1);

    for(int k = 0; k < eval.size(); ++k){
        pen.setColor(cor.at(k));
        painter.setPen(pen);

        Iant = -1.0;

        for(int J = 0; J <= largura - 1; J++){
            X = convJtoX(J);
            Y = eval.at(k)(X);
            I = convYtoI(Y);

            if (I >= 0.0 && I <= altura - 1.0 && Iant >= 0.0 && Iant <= altura - 1.0){
                QLineF linha(J - 1, Iant, J, I);
                painter.drawLine(linha); // conecta ponto anterior ao atual
            }

            Iant = I;
        }
    }

    painter.end();

    this->setPixmap(img);
}

double Grafico::convXtoJ(double X) const
{
    return (largura-1) * (X-minX)/(maxX-minX);
}

double Grafico::convYtoI(double Y) const
{
    return (altura-1) * (maxY - Y)/(maxY-minY);
}

double Grafico::convJtoX(double J) const
{
    return minX + (maxX-minX)*J/(largura-1);
}

double Grafico::convItoY(double I) const
{
    return maxY-(maxY-minY)*I/(altura-1);
}
