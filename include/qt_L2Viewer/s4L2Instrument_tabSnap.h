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
    
//tabs, = [market]

//用于展示L1基金、期权快照，目前仅展示市场数据页面，可以增加基本面、K线图等页面
class L2Instrument_tabSnap: public QTabWidget
{
    Q_OBJECT
public:
    L2Instrument_tabSnap(instrument_type_t type, QWidget *parent = nullptr);

    void mouseMoveEvent(QMouseEvent* )
    {
        //qDebug() << "L2Instrument_tabSnap " << hasMouseTracking() << " " << event->pos().x() << ", " << event->pos().y();
    }
    
public slots:

    // void addOrders(const std::vector<ssz_sbe_order_t>&);
    // void addExecs(const std::vector<ssz_sbe_exec_t>&);

    
public slots:
    void onL2Data_instrument_snap(const S4::sharedCharArray_ptr&);
signals:
    void signal_L2Data_instrument_snap(const S4::sharedCharArray_ptr&);
    
private:

    const instrument_type_t _type;

    QWidget* _market;
    QWidget* _basic;

};


} // namespace QT
} // namespace S4
