#include "tablemodeldefectivepixel.h"

TableModelDefectivePixel::TableModelDefectivePixel(CDefectivePixelManager *pDefectivePixelManager, QObject * /*parent*/):
    m_pDefectivePixelManager(pDefectivePixelManager)
{
}

TableModelDefectivePixel::~TableModelDefectivePixel()
{

}

int TableModelDefectivePixel::rowCount(const QModelIndex & /*parent*/) const
{
    return m_vecData.size();
}

int TableModelDefectivePixel::columnCount(const QModelIndex & /*parent*/) const
{
    //1. Status
    //2. X
    //3. Y
    //4. Evaluation
    //5. Reference
    //6. Difference(%)
    return 6;
}

QVariant TableModelDefectivePixel::data(const QModelIndex &index, int role) const
{
    switch(role)
    {
    case Qt::DisplayRole:
        switch(index.column())
        {
        case 0: return m_vecData[index.row()].strRegistrationStatus;
        case 1: return m_vecData[index.row()].x;
        case 2: return m_vecData[index.row()].y;
        case 3: return m_vecData[index.row()].coordinateOnly ? "": QString::asprintf("%.2f", m_vecData[index.row()].evaluation);
        case 4: return m_vecData[index.row()].coordinateOnly ? "": QString::asprintf("%.2f", m_vecData[index.row()].reference);
        case 5: return m_vecData[index.row()].coordinateOnly ? "": QString::asprintf("%.2f", m_vecData[index.row()].difference);
        }
	break;
    case Qt::InitialSortOrderRole:
	switch(index.column())
        {
        case 0: return m_vecData[index.row()].registered;	//status
        case 1: return m_vecData[index.row()].x;	//x
        case 2: return m_vecData[index.row()].y;	//y
        case 3: return m_vecData[index.row()].coordinateOnly ? "": QString::asprintf("%.2f", m_vecData[index.row()].evaluation);	//evaluation
        case 4: return m_vecData[index.row()].coordinateOnly ? "": QString::asprintf("%.2f", m_vecData[index.row()].reference);		//reference
        case 5: return m_vecData[index.row()].coordinateOnly ? "": QString::asprintf("%.2f", m_vecData[index.row()].difference);	//difference
        }
        break;

	break;
    case Qt::UserRole:
        return m_vecData[index.row()].index;
    }

    return QVariant();
}

QVariant TableModelDefectivePixel::headerData(int section, Qt::Orientation /*orientation*/, int role) const
{
    switch(role)
    {
    case Qt::DisplayRole:
        switch(section)
        {
        case 0: return "Status";
        case 1: return "X";
        case 2: return "Y";
        case 3: return "Evaluation";
        case 4: return "Reference";
        case 5: return "Difference(%)";
        }
    }
    return QVariant();
}

bool TableModelDefectivePixel::removeRows(int row, int count, const QModelIndex & /*parent*/)
{
	if (0 < count)
	{
		beginRemoveRows(QModelIndex(), row, row + count - 1);
		for (int i = 0; i < count; i++)
		{
			m_vecData.erase(m_vecData.begin() + row);
		}
		endRemoveRows();
	}
    return true;
}

void TableModelDefectivePixel::SetSelectedList(std::vector<size_t> selectedRows)
{
    m_vecSelectedRows = selectedRows;

    std::vector<std::pair<size_t, size_t>> vecPixelList;
    for (size_t index = 0; index < m_vecSelectedRows.size(); index++)
    {
        const uint32_t dataIndex = m_vecData[m_vecSelectedRows[index]].index;
    	vecPixelList.push_back(std::make_pair(dataIndex >> 16, dataIndex & 0xFFFF));
    }
	m_pDefectivePixelManager->SetSelectedPixelInformation(vecPixelList);
}

void TableModelDefectivePixel::RegisterSelectedPixel()
{
    std::vector<std::pair<size_t, size_t>> vecPixelList;
    for (size_t index = 0; index < m_vecSelectedRows.size(); index++)
    {
        if (!((QString)m_vecData[m_vecSelectedRows[index]].strRegistrationStatus).contains(
                    "Register", Qt::CaseInsensitive))
        {
            const uint32_t dataIndex = m_vecData[m_vecSelectedRows[index]].index;
            vecPixelList.push_back(std::make_pair(dataIndex >> 16, dataIndex & 0xFFFF));
        }
    }
    if (vecPixelList.size() == 0) return;

    m_pDefectivePixelManager->RegisterSelectedPixel(vecPixelList);
    UpdateDefectivePixelList();
}

void TableModelDefectivePixel::DeregisterSelectedPixel()
{
    std::vector<std::pair<size_t, size_t>> vecPixelList;
    for (size_t index = 0; index < m_vecSelectedRows.size(); index++)
    {
        if (((QString)m_vecData[m_vecSelectedRows[index]].strRegistrationStatus).contains(
                    "Register", Qt::CaseInsensitive))
        {
            const uint32_t dataIndex = m_vecData[m_vecSelectedRows[index]].index;
            vecPixelList.push_back(std::make_pair(dataIndex >> 16, dataIndex & 0xFFFF));
        }
    }
    if (vecPixelList.size() == 0) return;

    m_pDefectivePixelManager->DeregisterSelectedPixel(vecPixelList);
    UpdateDefectivePixelList();
}

void TableModelDefectivePixel::UpdateDefectivePixelList()
{
    m_vecSelectedRows.clear();
    this->removeRows(0, m_vecData.size());
    m_pDefectivePixelManager->UpdateDefectivePixelList(this);
}

void TableModelDefectivePixel::AddDefectivePixel(StApi::PSStDefectivePixelInformation_t pInfo, int32_t nRegistered)
{
    DefectivePixels data;
    data.strRegistrationStatus = nRegistered < 0 ? "" : QString::asprintf("Registered[%d]", nRegistered);
    data.x = pInfo->x;
    data.y = pInfo->y;
    data.evaluation = pInfo->dblEvaluationValue;
    data.reference = pInfo->dblReferenceValue;
    data.difference = pInfo->dblDeltaRatio * 100;
    data.coordinateOnly = false;
    data.index = (((pInfo->x & 0xFFFF) << 16) | (pInfo->y & 0xFFFF));
    data.registered = nRegistered < 0 ? UINT32_MAX : (uint32_t)nRegistered;;
    m_vecData.push_back(data);
    emit layoutChanged();
}

void TableModelDefectivePixel::AddDefectivePixel(size_t x, size_t y, int32_t nRegistered)
{
    DefectivePixels data;
    data.strRegistrationStatus = QString::asprintf("Registered[%d]", nRegistered);
    data.x = x;
    data.y = y;
    data.coordinateOnly = true;
    data.index = (((x & 0xFFFF) << 16) | (y & 0xFFFF));
    data.registered = (uint32_t)nRegistered;
    m_vecData.push_back(data);
    emit layoutChanged();
}

size_t TableModelDefectivePixel::GetSelectedRegisteredItemCount()
{
	size_t nCount = 0;
	for (size_t index = 0; index < m_vecSelectedRows.size(); index++)
	{
		if (((QString)m_vecData[m_vecSelectedRows[index]].strRegistrationStatus).contains("Register", Qt::CaseInsensitive))
		{
			++nCount;
		}
	}
	return(nCount);
}
size_t TableModelDefectivePixel::GetSelectedNotRegisteredItemCount()
{
        size_t nCount = 0;
        for (size_t index = 0; index < m_vecSelectedRows.size(); index++)
        {
                if (!((QString)m_vecData[m_vecSelectedRows[index]].strRegistrationStatus).contains("Register", Qt::CaseInsensitive))
                {
                        ++nCount;
                }
        }
        return(nCount);
}

