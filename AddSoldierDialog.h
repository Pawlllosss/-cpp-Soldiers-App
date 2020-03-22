#ifndef SOLDIERAPP_ADDSOLDIERDIALOG_H
#define SOLDIERAPP_ADDSOLDIERDIALOG_H

#include <QtCore/QtGlobal>
#include <QtCore/QArgument>
#include <QtWidgets/QDialog>
#include "Soldier.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AddSoldierDialog; }
QT_END_NAMESPACE

class AddSoldierDialog : public QDialog
{
    Q_OBJECT

public:
    AddSoldierDialog(QWidget *parent = nullptr);
    ~AddSoldierDialog();
    void setAvailableRanks(const std::list<Rank> &ranks);

signals:
    void sendAddedSoldier(const Soldier &soldier);

private slots:
    void sendSoldierToMainWindow();

private:
    Ui::AddSoldierDialog *ui;
};

#endif //SOLDIERAPP_ADDSOLDIERDIALOG_H
