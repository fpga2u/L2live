#pragma once

#include "qt_common/sharedCharArray_ptr.h"
#include "qt_L2Viewer/s4L2Instrument_def.h"

#include <QWidget>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QTabWidget>
#include <QDebug>
#include <QMouseEvent>


namespace S4{
namespace QT{
    
//view in instrument-tab, = [chart] + [table]
class L2Instrument: public QWidget
{
    Q_OBJECT

public:

public:
    L2Instrument(enum instrument_type_t type, int snapLevels_nb, QWidget *parent = nullptr);

    void mouseMoveEvent(QMouseEvent* )
    {
        //qDebug() << "L2Instrument " << hasMouseTracking() << " " << event->pos().x() << ", " << event->pos().y();
    }

    
public slots:

    // void addOrders(const std::vector<ssz_sbe_order_t>&);
    // void addExecs(const std::vector<ssz_sbe_exec_t>&);
    
public slots:
	void onL2Data_instrument_snap(const S4::sharedCharArray_ptr&);
	void onL2Data_index_snap(const S4::sharedCharArray_ptr&);
	void onL2Data_order(const S4::sharedCharArray_ptr&);
	void onL2Data_exec(const S4::sharedCharArray_ptr&);

signals:
	void signal_L2Data_instrument_snap(const S4::sharedCharArray_ptr&);
	void signal_L2Data_index_snap(const S4::sharedCharArray_ptr&);
	void signal_L2Data_order(const S4::sharedCharArray_ptr&);
	void signal_L2Data_exec(const S4::sharedCharArray_ptr&);

private:
    enum instrument_type_t _type;

    // K line tab
    // SnapInstrument_Kline_tab* _K_tab;

    // vol/indicator tab
    // SnapInstrument_indicator_tab* _indicator_tab;

    // cyc/... tab
    QTabWidget* _table;
    
private:

};


} // namespace QT
} // namespace S4
