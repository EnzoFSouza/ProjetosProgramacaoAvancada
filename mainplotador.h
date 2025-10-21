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

private:
    Ui::MainPlotador *ui;
};
#endif // MAINPLOTADOR_H
