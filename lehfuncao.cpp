#include "lehfuncao.h"
#include "ui_lehfuncao.h"

LehFuncao::LehFuncao(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LehFuncao)
    , cor(0, 0, 255)
{
    ui->setupUi(this);
}

LehFuncao::~LehFuncao()
{
    delete ui;
}

void LehFuncao::clear()
{
    ui->lineEdit->clear();
}

void LehFuncao::on_radioAzul_clicked()
{
    cor = QColor(0, 0, 255);
}


void LehFuncao::on_radioVermelho_clicked()
{
    cor = QColor(255, 0, 0);
}


void LehFuncao::on_radioVerd_clicked()
{
    cor = QColor(0, 255, 0);
}


void LehFuncao::on_radioPreto_clicked()
{
    cor = QColor(0, 0, 0);
}


void LehFuncao::on_buttonBox_accepted()
{
    signIncluirFuncao(ui->lineEdit->text, cor);
}

