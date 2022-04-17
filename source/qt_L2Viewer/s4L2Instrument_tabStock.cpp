#include "qt_L2Viewer/s4L2Instrument_tabStock.h"
#include "qt_L2Viewer/s4L2Instrument_tabStock_MD.h"
namespace S4{
namespace QT{
    
L2Instrument_tabStock::L2Instrument_tabStock(instrument_type_t type, int snapLeves_nb, QWidget *parent):
    QTabWidget(parent)
{
    setMouseTracking(true);

    _market = new L2Instrument_tabStock_MD(type, snapLeves_nb, this);

    if (type==instrument_type_t::STOCK){
	    addTab(_market, QStringLiteral("L1/L2股票数据"));
    }else if (type==instrument_type_t::FUND){
	    addTab(_market, QStringLiteral("L1/L2基金数据"));
    }else if (type==instrument_type_t::OPTION){
	    addTab(_market, QStringLiteral("L1/L2期权数据"));
    }else{
	    addTab(_market, QStringLiteral("错误类型"));
    }
	setCurrentIndex(0);

	connect(this, &L2Instrument_tabStock::signal_L2Data_instrument_snap, (L2Instrument_tabStock_MD*)_market, &L2Instrument_tabStock_MD::onL2Data_instrument_snap);
	connect(this, &L2Instrument_tabStock::signal_L2Data_order, (L2Instrument_tabStock_MD*)_market, &L2Instrument_tabStock_MD::onL2Data_order);
	connect(this, &L2Instrument_tabStock::signal_L2Data_exec, (L2Instrument_tabStock_MD*)_market, &L2Instrument_tabStock_MD::onL2Data_exec);
}


void L2Instrument_tabStock::onL2Data_instrument_snap(const S4::sharedCharArray_ptr& s)
{
	emit signal_L2Data_instrument_snap(s);
}
void L2Instrument_tabStock::onL2Data_order(const S4::sharedCharArray_ptr& s)
{
	emit signal_L2Data_order(s);
}
void L2Instrument_tabStock::onL2Data_exec(const S4::sharedCharArray_ptr& s)
{
	emit signal_L2Data_exec(s);
}




} // namespace QT
} // namespace S4
