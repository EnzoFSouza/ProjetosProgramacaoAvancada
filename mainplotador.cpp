#include "mainplotador.h"
#include "ui_mainplotador.h"
#include "evaluator.h"

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

}


void MainPlotador::on_spinMaxX_valueChanged(int arg1)
{

}


void MainPlotador::on_spinMinY_valueChanged(int arg1)
{

}


void MainPlotador::on_spinMaxY_valueChanged(int arg1)
{

}


void MainPlotador::on_spinExpX_valueChanged(int arg1)
{

}


void MainPlotador::on_spinExpY_valueChanged(int arg1)
{

}


void MainPlotador::on_pushApagar_clicked()
{

}

void MainPlotador::slotIncluirFuncao(QString Funcao, QColor Cor)
{

}

double MainPlotador::convXtoJ(double X) const
{

}

double MainPlotador::convYtoI(double Y) const
{

}

double MainPlotador::convJtoX(double J) const
{

}

double MainPlotador::convItoY(double Y) const
{

}

void MainPlotador::exibirFuncoes()
{

}

void MainPlotador::desenharGrafico()
{

}

