#ifndef LAYERMODEL_H
#define LAYERMODEL_H

#include <QAbstractTableModel>
struct LAYER;

class LayerModel : public QAbstractTableModel {
    Q_OBJECT

    QMap<QString, LAYER*> layers;
    const QStringList names;

public:
    explicit LayerModel(QMap<QString, LAYER*> layers, QObject* parent = nullptr);

signals:

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
};

#endif // LAYERMODEL_H
