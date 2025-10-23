#ifndef MAINPLOTADOR_H
#define MAINPLOTADOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainPlotador;
}
QT_END_NAMESPACE

class MainPlotador : public QMainWindow
{
    Q_OBJECT

public:
    MainPlotador(QWidget *parent = nullptr);
    ~MainPlotador();

private slots:
    void on_actionFun_o_triggered();

    void on_actionApagar_triggered();

    void on_actionSair_triggered();

    void on_spinMinX_valueChanged(int arg1);

    void on_spinMaxX_valueChanged(int arg1);

    void on_spinMinY_valueChanged(int arg1);

    void on_spinMaxY_valueChanged(int arg1);

    void on_spinExpX_valueChanged(int arg1);

    void on_spinExpY_valueChanged(int arg1);

    void on_pushApagar_clicked();

private:
    Ui::MainPlotador *ui;
};
#endif // MAINPLOTADOR_H
