#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   MainWindow(QObject *WebSocketObj, QWidget *parent = nullptr);
   ~MainWindow();

public slots:
   void ShowHelloBack();

protected:
   void showEvent(QShowEvent *ev);

private:
   QObject *m_WebSocketObj;
private:
   Ui::MainWindow *ui;

   void ShowLoginDialog();

};
#endif // MAINWINDOW_H
