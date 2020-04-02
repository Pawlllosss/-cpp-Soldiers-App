#ifndef SOLDIERAPP_SOLDIERMODEL_H
#define SOLDIERAPP_SOLDIERMODEL_H

#include <QtCore/QAbstractTableModel>
#include "Soldier.h"

/**
 * Model representing information about soldier ready to populate view widget (for example QTableView)
 */
class SoldierModel: public QAbstractTableModel {
    Q_OBJECT

public:
    SoldierModel(QObject *parent = nullptr);
    SoldierModel(const SoldierModel &soldierModel, QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    /**
     * Adds Soldier to model
     * @param Soldier to add to model
     */
    void addSoldier(const Soldier &soldier);
    /**
     * Deletes Soldier from given row in model
     * @param row to remove from model
     */
    void deleteSoldier(const int row);
    /**
     * Returns vector of soldiers stored in model
     * @return vector of Soldiers
     */
    const std::vector<Soldier> &getSoldiers() const;
    /**
     * Returns soldier from row
     * @param row
     * @return soldier stored in row
     */
    const Soldier &getSoldierByRow(const int row) const;
    /**
     * Clears data in model
     */
    void clear();

private:
    QVariant getFieldFromSoldier(const int row, const int column) const;
    QVariant tryToGetFieldFromSoldier(const QModelIndex &index) const;
    void updateSoldierInModel(const QVariant &value, const int row, const int column);

    std::vector<Soldier> soldiers;
};

#endif //SOLDIERAPP_SOLDIERMODEL_H
