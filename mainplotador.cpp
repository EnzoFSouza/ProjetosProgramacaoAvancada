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
    , grafico(new Grafico(this))
{
    ui->setupUi(this);

    connect(lehFuncao, LehFuncao::signIncluirFuncao, this, MainPlotador::slotIncluirFuncao);

    connect(grafico, Grafico::signGraficoClicked, this, MainPlotador::slotGraficoClicked);

    ui->tableFuncoes->setStyleSheet("QHeaderView::section{background-color:lightgray}");

    ui->tableFuncoes->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    ui->tableFuncoes->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    ui->tableFuncoes->setHorizontalHeaderLabels(QStringList() << "COR" << "FUNCAO");

    grafico->setLimites(ui->spinMinX->value(), ui->spinMaxX->value(),
                        ui->spinExpX->value(), ui->spinMinY->value(),
                        ui->spinMaxY->value(), ui->spinExpY->value());

    ui->horizontalLayout->insertWidget(0, grafico);

    /*
    minX = ui->spinMinX->value() * pow(10.0, ui->spinExpX->value());
    maxX = ui->spinMaxX->value() * pow(10.0, ui->spinExpX->value());

    minY = ui->spinMinY->value() * pow(10.0, ui->spinExpY->value());
    maxY = ui->spinMaxY->value() * pow(10.0, ui->spinExpY->value());

    nMarcX = 1 + ui->spinMaxX->value() - ui->spinMinX->value();
    nMarcY = 1 + ui->spinMaxY->value() - ui->spinMinY->value();
    */

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

    grafico->setLimites(ui->spinMinX->value(), ui->spinMaxX->value(),
                        ui->spinExpX->value(), ui->spinMinY->value(),
                        ui->spinMaxY->value(), ui->spinExpY->value());

    ui->spinMaxX->setMinimum(1+arg1);

    desenharGrafico();
}


void MainPlotador::on_spinMaxX_valueChanged(int arg1)
{
    grafico->setLimites(ui->spinMinX->value(), ui->spinMaxX->value(),
                        ui->spinExpX->value(), ui->spinMinY->value(),
                        ui->spinMaxY->value(), ui->spinExpY->value());

    ui->spinMinX->setMaximum(arg1 - 1);

    desenharGrafico();
}


void MainPlotador::on_spinMinY_valueChanged(int arg1)
{
    grafico->setLimites(ui->spinMinX->value(), ui->spinMaxX->value(),
                        ui->spinExpX->value(), ui->spinMinY->value(),
                        ui->spinMaxY->value(), ui->spinExpY->value());

    ui->spinMaxY->setMinimum(1+arg1);

    desenharGrafico();
}


void MainPlotador::on_spinMaxY_valueChanged(int arg1)
{
    grafico->setLimites(ui->spinMinX->value(), ui->spinMaxX->value(),
                        ui->spinExpX->value(), ui->spinMinY->value(),
                        ui->spinMaxY->value(), ui->spinExpY->value());

    ui->spinMinY->setMaximum(arg1 - 1);

    desenharGrafico();
}


void MainPlotador::on_spinExpX_valueChanged(int arg1)
{
    //maxX = ui->spinMaxX->value() * pow(10.0, arg1);
    //minX = ui->spinMinX->value() * pow(10.0, arg1);
    grafico->setLimites(ui->spinMinX->value(), ui->spinMaxX->value(),
                        ui->spinExpX->value(), ui->spinMinY->value(),
                        ui->spinMaxY->value(), ui->spinExpY->value());

    desenharGrafico();
}


void MainPlotador::on_spinExpY_valueChanged(int arg1)
{
    //maxY = ui->spinMaxY->value() * pow(10.0, arg1);
    //minY = ui->spinMinY->value() * pow(10.0, arg1);
    grafico->setLimites(ui->spinMinX->value(), ui->spinMaxX->value(),
                        ui->spinExpX->value(), ui->spinMinY->value(),
                        ui->spinMaxY->value(), ui->spinExpY->value());

    desenharGrafico();
}


void MainPlotador::on_pushApagar_clicked()
{
    grafico->clearFuncoes();
    exibirFuncoes();
    desenharGrafico();
}

/*
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
*/

void MainPlotador::slotIncluirFuncao(QString Funcao, QColor Cor)
{
    try{
        grafico->pushFuncao(Funcao, Cor);
    }
    catch(const std::invalid_argument &E){
        QMessageBox::critical(this, "Funcao Invalida", "Erro na funcao: " + QString::fromStdString(E.what()));
    }
}

void MainPlotador::slotGraficoClicked(double X, double Y)
{
    QString msg = QString("X=%1  Y=%2").arg(X).arg(Y);
    ui->statusbar->showMessage(msg, 2000);
}

void MainPlotador::exibirFuncoes()
{
    ui->tableFuncoes->clearContents();
    ui->tableFuncoes->setRowCount(grafico->size());

    QLabel* prov;
    QPixmap img(20,20);

    for(int k = 0; k < grafico->size(); ++k){
        img.fill(grafico->getCor(k));
        prov = new QLabel(this);
        prov->setAlignment(Qt::AlignCenter);
        prov->setPixmap(img);
        ui->tableFuncoes->setCellWidget(k, 0, prov);

        prov = new QLabel(this);
        prov->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
        prov->setWordWrap(true);
        prov->setText(QString::fromStdString(grafico->getEval(k).getText()));
        ui->tableFuncoes->setCellWidget(k, 1, prov);
    }
}

void MainPlotador::desenharGrafico()
{
    grafico->desenharGrafico();
}

