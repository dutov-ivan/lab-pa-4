//
// Created by ivan on 11/7/25.
////
// Created by ivan on 11/7/25.
//

#ifndef LAB4_PA_QT_INDEXMainRecordModel_H
#define LAB4_PA_QT_INDEXMainRecordModel_H
#include <QAbstractTableModel>
#include "main_area.h"

class MainRecordModel : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit MainRecordModel(QObject *parent = nullptr)
        : QAbstractTableModel(parent) {
    }

    QList<MainRecord> records;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return records.size();
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return 2; // Index, record number
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || role != Qt::DisplayRole)
            return {};

        const auto &r = records[index.row()];
        switch (index.column()) {
            case 0: return r.key;
            case 1: return r.name;
        }
        return {};
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
            return {};
        switch (section) {
            case 0: return "Key";
            case 1: return "String (up to 50 chars)";
        }
        return {};
    }

    // // Optional: make it editable
    // Qt::ItemFlags flags(const QModelIndex &index) const override {
    //     return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
    // }
    //
    // bool setData(const QModelIndex &index, const QVariant &value, int role) override {
    //     if (role != Qt::EditRole) return false;
    //     auto &r = records[index.row()];
    //     switch (index.column()) {
    //         case 0: r.id = value.toInt();
    //             break;
    //         case 1: r.name = value.toString();
    //             break;
    //         case 2: r.value = value.toDouble();
    //             break;
    //     }
    //     emit dataChanged(index, index);
    //     return true;
    // }

    void addRecord(const MainRecord &r) {
        beginInsertRows(QModelIndex(), records.size(), records.size());
        records.append(r);
        endInsertRows();
    }
};


#endif //LAB4_PA_QT_INDEXMainRecordModel_H
