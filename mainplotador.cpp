#include "mainplotador.h"
#include "ui_mainplotador.h"

MainPlotador::MainPlotador(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainPlotador)
{
    ui->setupUi(this);
}

MainPlotador::~MainPlotador()
{
    delete ui;
}
