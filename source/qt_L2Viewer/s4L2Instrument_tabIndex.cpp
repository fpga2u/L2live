#include "qt_L2Viewer/s4L2Instrument_tabIndex.h"
#include "qt_L2Viewer/s4L2Instrument_tabIndex_MD.h"
namespace S4{
namespace QT{
    
L2Instrument_tabIndex::L2Instrument_tabIndex(int snapLeves_nb, QWidget *parent):
    QTabWidget(parent)
{
    setMouseTracking(true);

    _market = new L2Instrument_tabIndex_MD(snapLeves_nb, this);

	addTab(_market, QStringLiteral("L1/L2指数快照"));
	setCurrentIndex(0);

	connect(this, &L2Instrument_tabIndex::signal_L2Data_index_snap, (L2Instrument_tabIndex_MD*)_market, &L2Instrument_tabIndex_MD::onL2Data_index_snap);
}


void L2Instrument_tabIndex::onL2Data_index_snap(const S4::sharedCharArray_ptr& s)
{
	emit signal_L2Data_index_snap(s);
}




} // namespace QT
} // namespace S4
