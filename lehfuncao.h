#ifndef LEHFUNCAO_H
#define LEHFUNCAO_H

#include <QDialog>

namespace Ui {
class LehFuncao;
}

class LehFuncao : public QDialog
{
    Q_OBJECT

public:
    explicit LehFuncao(QWidget *parent = nullptr);
    ~LehFuncao();
    void clear();

signals:
    void signIncluirFuncao(QString Funcao, QColor Cor);

private slots:
    void on_radioAzul_clicked();

    void on_radioVermelho_clicked();

    void on_radioVerd_clicked();

    void on_radioPreto_clicked();

    void on_buttonBox_accepted();

private:
    Ui::LehFuncao *ui;
    QColor cor;
};

#endif // LEHFUNCAO_H
