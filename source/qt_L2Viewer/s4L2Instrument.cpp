#include "common/s4logger.h"
#include "qt_L2Viewer/s4L2Instrument.h"
#include "qt_L2Viewer/s4L2Instrument_tabStock.h"
#include "qt_L2Viewer/s4L2Instrument_tabIndex.h"
#include "qt_L2Viewer/s4L2Instrument_tabSnap.h"
#include <QGridLayout>

namespace S4{
namespace QT{
    
L2Instrument::L2Instrument(enum instrument_type_t type, int snapLevels_nb, QWidget *parent) :
    QWidget(parent),
    _type(type)
{
	this->setMouseTracking(true);
	//int i;
	// _K_tab = new SnapInstrument_Kline_tab(this);

	// _indicator_tab = new SnapInstrument_indicator_tab(this);

	// connect(_K_tab, SIGNAL(paint_indicator(SnapInstrument_indicator_scene::ind_type, timeMode_t)),
	// 	_indicator_tab, SLOT(paint(SnapInstrument_indicator_scene::ind_type, timeMode_t)));

	// connect(_K_tab, SIGNAL(signalViewEvent(std::shared_ptr<view_event>)), _indicator_tab, SLOT(slotViewEvent(std::shared_ptr<view_event>)));

	if (type == instrument_type_t::STOCK) {
		_table = new L2Instrument_tabStock(type, snapLevels_nb, this);
		connect(this, &L2Instrument::signal_L2Data_instrument_snap, (L2Instrument_tabStock*)_table, &L2Instrument_tabStock::onL2Data_instrument_snap);
		// connect(this, &L2Instrument::signal_L2Data_index_snap, (L2Instrument_tabStock*)_table, &L2Instrument_tabStock::onL2Data_index_snap);
		connect(this, &L2Instrument::signal_L2Data_order, (L2Instrument_tabStock*)_table, &L2Instrument_tabStock::onL2Data_order);
		connect(this, &L2Instrument::signal_L2Data_exec, (L2Instrument_tabStock*)_table, &L2Instrument_tabStock::onL2Data_exec);
	}
	else if (type == instrument_type_t::INDEX) {
		_table = new L2Instrument_tabIndex(snapLevels_nb, this);
		connect(this, &L2Instrument::signal_L2Data_index_snap, (L2Instrument_tabIndex*)_table, &L2Instrument_tabIndex::onL2Data_index_snap);
	}
	else if (type == instrument_type_t::FUND || type == instrument_type_t::OPTION) {
		// _table = new L2Instrument_tabSnap(type, this);
		// connect(this, &L2Instrument::signal_L2Data_instrument_snap, (L2Instrument_tabSnap*)_table, &L2Instrument_tabSnap::onL2Data_instrument_snap);
		_table = new L2Instrument_tabStock(type, snapLevels_nb, this);
		connect(this, &L2Instrument::signal_L2Data_instrument_snap, (L2Instrument_tabStock*)_table, &L2Instrument_tabStock::onL2Data_instrument_snap);
		// connect(this, &L2Instrument::signal_L2Data_index_snap, (L2Instrument_tabStock*)_table, &L2Instrument_tabStock::onL2Data_index_snap);
		connect(this, &L2Instrument::signal_L2Data_order, (L2Instrument_tabStock*)_table, &L2Instrument_tabStock::onL2Data_order);
		connect(this, &L2Instrument::signal_L2Data_exec, (L2Instrument_tabStock*)_table, &L2Instrument_tabStock::onL2Data_exec);
	}
    else{
        ERR("Illegal instrument_type_t={} take as STOCK", (int)type);   //
		_table = new L2Instrument_tabStock(type, snapLevels_nb, this);
		connect(this, &L2Instrument::signal_L2Data_instrument_snap, (L2Instrument_tabStock*)_table, &L2Instrument_tabStock::onL2Data_instrument_snap);
		// connect(this, &L2Instrument::signal_L2Data_index_snap, (L2Instrument_tabStock*)_table, &L2Instrument_tabStock::onL2Data_index_snap);
		connect(this, &L2Instrument::signal_L2Data_order, (L2Instrument_tabStock*)_table, &L2Instrument_tabStock::onL2Data_order);
		connect(this, &L2Instrument::signal_L2Data_exec, (L2Instrument_tabStock*)_table, &L2Instrument_tabStock::onL2Data_exec);
    }
	//网格分割
	QGridLayout *pLayout = new QGridLayout();
    pLayout->addWidget(_table, 0, 0);

	setLayout(pLayout);
}


void L2Instrument::onL2Data_instrument_snap(const S4::sharedCharArray_ptr& s)
{
	emit signal_L2Data_instrument_snap(s);
}
void L2Instrument::onL2Data_index_snap(const S4::sharedCharArray_ptr& s)
{
	emit signal_L2Data_index_snap(s);
}
void L2Instrument::onL2Data_order(const S4::sharedCharArray_ptr& s)
{
	emit signal_L2Data_order(s);
}
void L2Instrument::onL2Data_exec(const S4::sharedCharArray_ptr& s)
{
	emit signal_L2Data_exec(s);
}


} // namespace QT
} // namespace S4
