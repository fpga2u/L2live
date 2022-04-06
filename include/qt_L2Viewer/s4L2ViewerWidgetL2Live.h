﻿#pragma once


#include "qt_L2Viewer/s4SnapViewerWidget.h"
#include "qt_L2Viewer/s4L2TableModel_L2Stats.h"
#include "network/L2_udp_recver_th.h"
#include "qt_common/s4qt_unicTreeView.h"

#include "qt_market/s4MarketDataAgent.h"
#include "qt_market/s4MarketDataSource.h"

#include <QTableView>
#include <QStandardItem>
#include <QStringListModel>

namespace S4{
namespace QT{

//    void updateTableList();


class snapViewerWidgetL2Live : public s4SnapViewerWidget
{
    Q_OBJECT

public:
    explicit snapViewerWidgetL2Live(QWidget *parent = nullptr);
    virtual ~snapViewerWidgetL2Live();

public slots:
	void slot_startMDSource();
	void slot_stopMDSource();
	
	void setCurrentInstrument(const QString& code);
	void openInstrumentTab(const QString& code);
	void closeInstrumentTab(const QString& code);

	virtual void closeSnapTab(int index) override;
signals:
	void signal_status(const QString&);
protected:

	struct snap_info_t
	{
		mktCodeI_t code;
	};
	std::map<QString, snap_info_t> _instrument_info_cargo;

protected:
	void mouseMoveEvent(QMouseEvent* )
	{
		//qDebug() << "Kview " << hasMouseTracking() << " " << event->pos().x() << ", " << event->pos().y();
	}

protected:
	QTableView* _stats_tv;
	snapTableModel_L2Stats* _stats_model;
	QStandardItem* _aim_security_root;
protected:
	std::shared_ptr<NW::L2DataQ_t> _pL2DataQ;
	std::shared_ptr<NW::L2CmdQ_t> _pL2CmdQ;

	std::shared_ptr<NW::L2_udp_recver_th> _udp_recver_th;
	marketDataAgent* _snapMarketDataLive;

	marketDataSource* _marketDataSource;


	std::vector<std::string> _dynamicSS_L2 = 
	{
		"L2Data_instrument_snap",
		"L2Data_index_snap",
		"L2Data_order",
		"L2Data_exec",
	};
protected:

	void startMDAgent();

	void applyDynamicSS_L2(const QString& code, QWidget*, bool doConnect);
};


}
}