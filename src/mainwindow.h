#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
// include keyboard files
#include "../keyboard/widgetKeyBoard.h"

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

    // to focus on lineEdit object
    void setExternalLineEdit(QLineEdit* focusOnLineEdit);
    QLineEdit* externalLineEditPointer; // external pointer to the main APP

private slots:
    void on_btnOk_Clicked();
    void on_btnCancel_Clicked();
    void returnWidgetSignalReceived();

    

private:
    Ui::MainWindow *ui;
    widgetKeyBoard  *keyboard;
};
#endif // MAINWINDOW_H