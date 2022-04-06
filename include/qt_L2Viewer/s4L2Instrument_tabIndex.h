#pragma once

#include "qt_common/sharedCharArray_ptr.h"

#include <QWidget>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QTabWidget>
#include <QDebug>
#include <QMouseEvent>


namespace S4{
namespace QT{
    
//tabs, = [market]

//用于展示指数，目前仅展示市场数据页面，可以增加基本面、K线图等页面
class L2Instrument_tabIndex: public QTabWidget
{
    Q_OBJECT
public:
    L2Instrument_tabIndex(int snapLeves_nb, QWidget *parent = nullptr);

    void mouseMoveEvent(QMouseEvent* )
    {
        //qDebug() << "L2Instrument_tabIndex " << hasMouseTracking() << " " << event->pos().x() << ", " << event->pos().y();
    }
    
public slots:

    // void addOrders(const std::vector<ssz_sbe_order_t>&);
    // void addExecs(const std::vector<ssz_sbe_exec_t>&);

    
public slots:
    void onL2Data_index_snap(const S4::sharedCharArray_ptr&);
signals:
    void signal_L2Data_index_snap(const S4::sharedCharArray_ptr&);
    
private:
    // std::map<int, Kinstrument_indicator_scene::indCtx_t> _tab_ctx;

    QWidget* _market;
    QWidget* _basic;

};


} // namespace QT
} // namespace S4
