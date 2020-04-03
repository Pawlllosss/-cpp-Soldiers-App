#include <QtCore/QDebug>
#include "SoldierModel.h"

SoldierModel::SoldierModel(QObject *parent) : QAbstractTableModel(parent) {
}

SoldierModel::SoldierModel(const SoldierModel &soldierModel, QObject *parent) : QAbstractTableModel(parent), soldiers(soldierModel.getSoldiers()) {

}

int SoldierModel::rowCount(const QModelIndex &parent) const {
    return soldiers.size();
}

int SoldierModel::columnCount(const QModelIndex &parent) const {
    return 3;
}

QVariant SoldierModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        return tryToGetFieldFromSoldier(index);
    }
    return QVariant();
}

bool SoldierModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (role == Qt::EditRole) {
        const int row = index.row();
        const int column = index.column();

        if (row >= soldiers.size()) {
            return false;
        }

        updateSoldierInModel(value, row, column);
    }
    return true;
}

QVariant SoldierModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
                case 0:
                    return QString("First name");
                case 1:
                    return QString("Last name");
                case 2:
                    return QString("Rank");
                default:
                    return QVariant();
            }
        }
    }
    return QVariant();
}

Qt::ItemFlags SoldierModel::flags(const QModelIndex &index) const {
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

void SoldierModel::addSoldier(const Soldier &soldier) {
    int newRow = rowCount() + 1;

    beginInsertRows(QModelIndex(), newRow, newRow);
    soldiers.emplace_back(soldier);
    endInsertRows();
}

void SoldierModel::deleteSoldier(const int row) {
    beginRemoveRows(QModelIndex(), row, row);
    soldiers.erase(soldiers.begin() + row);
    endRemoveRows();
}

QVariant SoldierModel::tryToGetFieldFromSoldier(const QModelIndex &index) const {
    const int row = index.row();
    const int column = index.column();

    if (row >= soldiers.size()) {
        return QVariant();
    } else {
        return getFieldFromSoldier(row, column);
    }
}

QVariant SoldierModel::getFieldFromSoldier(const int row, const int column) const {
    const Soldier &soldier = getSoldierByRow(row);

    switch (column) {
        case 0:
            return soldier.getFirstName();
        case 1:
            return soldier.getLastName();
        case 2: {
            const RankDescription &rank = soldier.getRank();
            return rank.name;
        }
        default:
            return QVariant();
    }
}

void SoldierModel::updateSoldierInModel(const QVariant &value, const int row, const int column) {
    Soldier& soldier = soldiers.at(row);
    QString newFieldValue = value.toString();

    switch (column) {
        case 0:
            soldier.setFirstName(newFieldValue);
            break;
        case 1:
            soldier.setLastName(newFieldValue);
            break;
        case 2:
            soldier.getRank();
            break;
    }
}

const std::vector<Soldier> &SoldierModel::getSoldiers() const {
    return soldiers;
}

const Soldier &SoldierModel::getSoldierByRow(const int row) const { return soldiers.at(row); }

void SoldierModel::clear() {
    int lastRow = rowCount() - 1;
    beginRemoveRows(QModelIndex(), 0, lastRow);
    soldiers.erase(soldiers.begin(), soldiers.end());
    endRemoveRows();
}
