#include "lehfuncao.h"
#include "ui_lehfuncao.h"

LehFuncao::LehFuncao(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LehFuncao)
{
    ui->setupUi(this);
}

LehFuncao::~LehFuncao()
{
    delete ui;
}

void LehFuncao::on_radioAzul_clicked()
{

}


void LehFuncao::on_radioVermelho_clicked()
{

}


void LehFuncao::on_radioVerd_clicked()
{

}


void LehFuncao::on_radioPreto_clicked()
{

}


void LehFuncao::on_buttonBox_accepted()
{

}

