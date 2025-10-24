#include "mainplotador.h"
#include "ui_mainplotador.h"
#include "evaluator.h"
#include <stdexcept>

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
    nMarcX = 1 + ui->spinMaxY->value() - ui->spinMinY->value();

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

}

void MainPlotador::desenharGrafico()
{

}

