#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCloseEvent>
// QMap contains better functionality than std::map
#include <QMap>

#include "processlistwidget.h"
#include "MemoryScanner.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void closeEvent(QCloseEvent *);
    void on_action_Quit_triggered();

    void on_actionAbout_triggered();

    void on_tabWidget_tabCloseRequested(int index);
    void on_tabWidget_destroyed();
    void on_tabWidget_currentChanged(int index);

    void on_actionNew_Scan_triggered();

    void on_ProcessSelected(int pid, QString name);

private:
    Ui::MainWindow *ui;

    QMap<int, MemoryScanner*> scanners;
    int currentScanner; // updated when user switches tabs..
};

#endif // MAINWINDOW_H
