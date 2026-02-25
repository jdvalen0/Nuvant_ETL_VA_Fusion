#ifndef TABLEMODELDEFECTIVEPIXEL_H
#define TABLEMODELDEFECTIVEPIXEL_H

#include <QtGlobal>
#include <QAbstractTableModel>
#include <QSortFilterProxyModel>
#include "cdefectivepixelmanager.h"

typedef struct SDefectivePixels_
{
    quint64 index;
    QString strRegistrationStatus;
    uint32_t x;
    uint32_t y;
    double evaluation;
    double reference;
    double difference;
    bool coordinateOnly;
    uint32_t registered;
} DefectivePixels;

class TableModelDefectivePixel final : public QAbstractTableModel, public IDefectivePixelListCtrl
{
    Q_OBJECT

public:
    TableModelDefectivePixel(CDefectivePixelManager *pDefectivePixelManager, QObject *parent = nullptr);
    ~TableModelDefectivePixel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    void SetSelectedList(std::vector<size_t> selectedRows);

    void RegisterSelectedPixel();
    void DeregisterSelectedPixel();
    void UpdateDefectivePixelList();
    size_t GetSelectedRegisteredItemCount();
    size_t GetSelectedNotRegisteredItemCount();

protected:
    CDefectivePixelManager *m_pDefectivePixelManager;

    // Implementation of IDefectivePixel
    void AddDefectivePixel(StApi::PSStDefectivePixelInformation_t pInfo, int32_t nRegistered = -1) override;
    void AddDefectivePixel(size_t x, size_t y, int32_t nRegistered = -1) override;

    std::vector<DefectivePixels> m_vecData;
    std::vector<size_t> m_vecSelectedRows;

};

#endif // TABLEMODELDEFECTIVEPIXEL_H
