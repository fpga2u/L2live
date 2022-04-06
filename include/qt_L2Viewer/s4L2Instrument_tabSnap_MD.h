#pragma once

#include "qt_common/sharedCharArray_ptr.h"
#include "qt_L2Viewer/s4L2Instrument_def.h"

#include <QWidget>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QTabWidget>
#include <QDebug>
#include <QMouseEvent>
#include <QTableView>
#include <QLabel>


namespace S4{
namespace QT{
    
//view of tables = [level] + [info] + [order] + [exec]
//用于展示基金、期权市场数据，仅快照
class L2Instrument_tabSnap_MD: public QWidget
{
    Q_OBJECT
public:
    L2Instrument_tabSnap_MD(instrument_type_t type, int snapLeves_nb,QWidget *parent = nullptr);

    void mouseMoveEvent(QMouseEvent* )
    {
        //qDebug() << "L2Instrument_tabSnap_MD " << hasMouseTracking() << " " << event->pos().x() << ", " << event->pos().y();
    }

public slots:

    // void addOrders(const std::vector<ssz_sbe_order_t>&);
    // void addExecs(const std::vector<ssz_sbe_exec_t>&);
    
public slots:
    void onL2Data_instrument_snap(const S4::sharedCharArray_ptr&);

signals:
    void signal_L2Data_instrument_snap(const S4::sharedCharArray_ptr&);
    
private:
    // 
    QTableView* _level_tv;

    //
    QTableView* _info_tv;

    const instrument_type_t _type;
private:


};


} // namespace QT
} // namespace S4
