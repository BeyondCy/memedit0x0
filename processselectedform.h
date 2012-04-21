#ifndef PROCESSSELECTEDFORM_H
#define PROCESSSELECTEDFORM_H

#include <QWidget>

namespace Ui {
class ProcessSelectedForm;
}

class ProcessSelectedForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit ProcessSelectedForm(QWidget *parent = 0);
    ~ProcessSelectedForm();
    
private:
    Ui::ProcessSelectedForm *ui;
};

#endif // PROCESSSELECTEDFORM_H
