#include "qt_L2Viewer/s4L2Instrument_tabSnap.h"
#include "qt_L2Viewer/s4L2Instrument_tabSnap_MD.h"
namespace S4{
namespace QT{
    
L2Instrument_tabSnap::L2Instrument_tabSnap(instrument_type_t type, QWidget *parent):
    QTabWidget(parent),
    _type(type)
{
    setMouseTracking(true);

    _market = new L2Instrument_tabSnap_MD(type, 5, this);

    if (type==instrument_type_t::FUND){
	    addTab(_market, QStringLiteral("L1基金数据"));
    }else if (type==instrument_type_t::OPTION){
	    addTab(_market, QStringLiteral("L1期权数据"));
    }else{
	    addTab(_market, QStringLiteral("错误类型"));
    }
	setCurrentIndex(0);

	connect(this, &L2Instrument_tabSnap::signal_L2Data_instrument_snap, (L2Instrument_tabSnap_MD*)_market, &L2Instrument_tabSnap_MD::onL2Data_instrument_snap);
}


void L2Instrument_tabSnap::onL2Data_instrument_snap(const S4::sharedCharArray_ptr& s)
{
	emit signal_L2Data_instrument_snap(s);
}

} // namespace QT
} // namespace S4
