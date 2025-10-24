#include "mainplotador.h"
#include "ui_mainplotador.h"
#include "evaluator.h"
#include <stdexcept>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QPen>

MainPlotador::MainPlotador(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainPlotador)
    , lehFuncao(new LehFuncao(this))
    //, eval(std::vector<Evaluator>)
    //, cor(std::vector<QColor>)
    , largura(0)
    , altura(0)
    , minX(0.0)
    , maxX(0.0)
    , minY(0.0)
    , maxY(0.0)
    , nMarcX(0)
    , nMarcY(0)
{
    ui->setupUi(this);
    connect(lehFuncao, LehFuncao::signIncluirFuncao, this, MainPlotador::slotIncluirFuncao);

    ui->tableFuncoes->setStyleSheet("QHeaderView::section{background-color:lightgray}");

    ui->tableFuncoes->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    ui->tableFuncoes->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    ui->tableFuncoes->setHorizontalHeaderLabels(QStringList() << "COR" << "FUNCAO");

    minX = ui->spinMinX->value() * pow(10.0, ui->spinExpX->value());
    maxX = ui->spinMaxX->value() * pow(10.0, ui->spinExpX->value());

    minY = ui->spinMinY->value() * pow(10.0, ui->spinExpY->value());
    maxY = ui->spinMaxY->value() * pow(10.0, ui->spinExpY->value());

    nMarcX = 1 + ui->spinMaxX->value() - ui->spinMinX->value();
    nMarcY = 1 + ui->spinMaxY->value() - ui->spinMinY->value();

    desenharGrafico();
}

MainPlotador::~MainPlotador()
{
    delete ui;
}

void MainPlotador::on_actionFun_o_triggered()
{
    lehFuncao->clear();
    lehFuncao->show();
}


void MainPlotador::on_actionApagar_triggered()
{
    on_pushApagar_clicked();
}


void MainPlotador::on_actionSair_triggered()
{
    QCoreApplication::quit();
}


void MainPlotador::on_spinMinX_valueChanged(int arg1)
{
    minX = arg1 * pow(10.0, ui->spinExpX->value());
    nMarcX = 1 + ui->spinMaxX->value() - ui->spinMinX->value();

    ui->spinMaxX->setMinimum(1+arg1);

    desenharGrafico();
}


void MainPlotador::on_spinMaxX_valueChanged(int arg1)
{
    maxX = arg1 * pow(10.0, ui->spinExpX->value());
    nMarcX = 1 + ui->spinMaxX->value() - ui->spinMinX->value();

    ui->spinMinX->setMaximum(arg1 - 1);

    desenharGrafico();
}


void MainPlotador::on_spinMinY_valueChanged(int arg1)
{
    minY = arg1 * pow(10.0, ui->spinExpY->value());
    nMarcY = 1 + ui->spinMaxY->value() - ui->spinMinY->value();

    ui->spinMaxY->setMinimum(1+arg1);

    desenharGrafico();
}


void MainPlotador::on_spinMaxY_valueChanged(int arg1)
{
    maxY = arg1 * pow(10.0, ui->spinExpY->value());
    nMarcY = 1 + ui->spinMaxY->value() - ui->spinMinY->value();

    ui->spinMinY->setMaximum(arg1 - 1);

    desenharGrafico();
}


void MainPlotador::on_spinExpX_valueChanged(int arg1)
{
    maxX = ui->spinMaxX->value() * pow(10.0, arg1);
    minX = ui->spinMinX->value() * pow(10.0, arg1);
    desenharGrafico();
}


void MainPlotador::on_spinExpY_valueChanged(int arg1)
{
    maxY = ui->spinMaxY->value() * pow(10.0, arg1);
    minY = ui->spinMinY->value() * pow(10.0, arg1);
    desenharGrafico();
}


void MainPlotador::on_pushApagar_clicked()
{
    eval.clear();
    cor.clear();
    exibirFuncoes();
    desenharGrafico();
}

double MainPlotador::convXtoJ(double X) const
{
    return (largura-1) * (X-minX)/(maxX-minX);
}

double MainPlotador::convYtoI(double Y) const
{
    return (altura-1) * (maxY - Y)/(maxY-minY);
}

double MainPlotador::convJtoX(double J) const
{
    return minX + (maxX-minX)*J/(largura-1);
}

double MainPlotador::convItoY(double I) const
{
    return maxY-(maxY-minY)*I/(altura-1);
}

void MainPlotador::slotIncluirFuncao(QString Funcao, QColor Cor)
{
    try{
        Evaluator new_eval;
        new_eval.set(Funcao.toStdString());
        eval.push_back(new_eval);
        cor.push_back(Cor);
        exibirFuncoes();
        desenharGrafico();
    }
    catch(const std::invalid_argument &E){
        QMessageBox::critical(this, "Funcao Invalida", "Erro na funcao: " + QString::fromStdString(E.what()));
    }
}

void MainPlotador::exibirFuncoes()
{
    ui->tableFuncoes->clearContents();
    ui->tableFuncoes->setRowCount(eval.size());

    QLabel* prov;
    QPixmap img(20,20);

    for(int k = 0; k < eval.size(); ++k){
        img.fill(cor.at(k));
        prov = new QLabel(this);
        prov->setAlignment(Qt::AlignCenter);
        prov->setPixmap(img);
        ui->tableFuncoes->setCellWidget(k, 0, prov);

        prov = new QLabel(this);
        prov->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
        prov->setWordWrap(true);
        prov->setText(QString::fromStdString(eval.at(k).getText()));
        ui->tableFuncoes->setCellWidget(k, 1, prov);
    }
}

void MainPlotador::desenharGrafico()
{
    QPen pen;
    QPainter painter;

    largura = ui->grafico->width();
    altura = ui->grafico->height();

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
        ui->grafico->setPixmap(img);
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

    ui->grafico->setPixmap(img);
}

