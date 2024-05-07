#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "core/data/DValue.h"

#include <QMainWindow>
using namespace qtproject::data;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::shared_ptr<DValue> GetResult();

private slots:

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
