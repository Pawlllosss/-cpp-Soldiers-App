#ifndef SOLDIERAPP_SOLDIERMODEL_H
#define SOLDIERAPP_SOLDIERMODEL_H

#include <QtCore/QAbstractTableModel>
#include "Soldier.h"

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
    void addSoldier(const Soldier &soldier);
    void deleteSoldier(const int row);
    const std::vector<Soldier> &getSoldiers() const;
    const Soldier &getSoldierByRow(const int row) const;
    void clear();

private:
    QVariant getFieldFromSoldier(const int row, const int column) const;
    QVariant tryToGetFieldFromSoldier(const QModelIndex &index) const;
    void updateSoldierInModel(const QVariant &value, const int row, const int column);

    std::vector<Soldier> soldiers;};

#endif //SOLDIERAPP_SOLDIERMODEL_H
