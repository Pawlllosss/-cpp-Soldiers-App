#ifndef SOLDIERAPP_ADDSOLDIERDIALOG_H
#define SOLDIERAPP_ADDSOLDIERDIALOG_H

#include <QtCore/QtGlobal>
#include <QtCore/QArgument>
#include <QtWidgets/QDialog>
#include "Soldier.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AddSoldierDialog; }
QT_END_NAMESPACE

/**
 * Responsible for rendering dialog window for adding soldier.
 */
class AddSoldierDialog : public QDialog
{
    Q_OBJECT

public:
    AddSoldierDialog(QWidget *parent = nullptr);
    ~AddSoldierDialog();
    /**
     * Populates combobox with ranks
     * @param ranks
     */
    void setAvailableRanks(const std::list<RankDescription> &ranks);

signals:
    /**
    * Signal with information about added soldier
    * @param soldier added Soldier
    */
    void sendAddedSoldier(const Soldier &soldier);

private slots:
    void sendSoldierToMainWindow();

private:
    RankDescription getRankFromComboBox() const;
    void clearFields();

    Ui::AddSoldierDialog *ui;
};

#endif //SOLDIERAPP_ADDSOLDIERDIALOG_H
