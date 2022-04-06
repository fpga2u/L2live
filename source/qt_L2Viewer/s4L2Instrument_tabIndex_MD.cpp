﻿#include "qt_L2Viewer/s4L2Instrument_tabIndex_MD.h"
#include "qt_L2Viewer/s4L2TableModel_indexInfo.h"
#include "qt_common/s4qt_itemFormatDelegate.h"

#include <QGridLayout>
#include <QHeaderView>
#include <QSplitter>
#include <QLineEdit>
#include <QLabel>

namespace S4{
namespace QT{
    
L2Instrument_tabIndex_MD::L2Instrument_tabIndex_MD(int snapLeves_nb, QWidget *parent):
    QWidget(parent)
{
    setMouseTracking(true);
    itemFormatDelegate* delegate = new itemFormatDelegate(this);

 //   _level_tv = new QTableView(this);
 //   _level_tv->setItemDelegate(delegate);
 //   snapTableModel_level* levels = new snapTableModel_level(snapLeves_nb, _level_tv);
 //   _level_tv->setModel(levels);
 //   _level_tv->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
 //   _level_tv->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
 //   // _level_tv->verticalHeader()->setMaximumHeight(24);
 //   // _level_tv->verticalHeader()->setMinimumHeight(5);
 //   _level_tv->setSelectionBehavior(QAbstractItemView::SelectRows);
	//_level_tv->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);	//限制选择
	//_level_tv->setMaximumWidth(250);
 //   connect(this, &L2Instrument_tabIndex_MD::signal_L2Data_instrument_snap, levels, &snapTableModel_level::refreshL2);
 //   {
 //       const int nNumRows = levels->rowCount(QModelIndex());
 //       _level_tv->resizeRowsToContents();
 //       _level_tv->resizeColumnsToContents();
 //       int nRowHeight = _level_tv->rowHeight(0);
 //       int nTableHeight = (nNumRows * nRowHeight) + _level_tv->horizontalHeader()->height() + 2 * _level_tv->frameWidth();
 //       _level_tv->setMinimumHeight(nTableHeight);
 //       _level_tv->setMaximumHeight(nTableHeight);

 //   }

    _info_tv = new QTableView(this);
    _info_tv->setItemDelegate(delegate);
    snapTableModel_indexInfo_L2* infos = new snapTableModel_indexInfo_L2(_info_tv);
    _info_tv->setModel(infos);
    _info_tv->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    _info_tv->horizontalHeader()->setVisible(false);
    _info_tv->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // _info_tv->verticalHeader()->setMaximumHeight(24);
    // _info_tv->verticalHeader()->setMinimumHeight(5);
    _info_tv->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    
    _info_tv->setSelectionBehavior(QAbstractItemView::SelectRows);
	_info_tv->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);	//限制选择
	_info_tv->setMaximumWidth(450);
    connect(this, &L2Instrument_tabIndex_MD::signal_L2Data_index_snap, infos, &snapTableModel_indexInfo_L2::refreshL2);
    {
        const int nNumRows = infos->rowCount(QModelIndex());
        _info_tv->resizeRowsToContents();
        _info_tv->resizeColumnsToContents();
        int nRowHeight = _info_tv->rowHeight(0);
        int nTableHeight = (nNumRows * nRowHeight) + _info_tv->horizontalHeader()->height() + 2 * _info_tv->frameWidth();
        _info_tv->setMinimumHeight(nTableHeight);
        _info_tv->setMaximumHeight(nTableHeight);
    }
 //   
 //   _order_tv = new QTableView(this);
 //   _order_tv->setItemDelegate(delegate);
 //   snapTableModel_order* orders = new snapTableModel_order(_order_tv);
 //   _order_tv->setModel(orders);
 //   _order_tv->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
 //   _order_tv->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
 //   // _order_tv->verticalHeader()->setMaximumHeight(24);
 //   // _order_tv->verticalHeader()->setMinimumHeight(5);
 //   _order_tv->setSelectionBehavior(QAbstractItemView::SelectRows);
	//_order_tv->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);	//限制选择
	//_order_tv->setMaximumWidth(750);
 //   connect(this, &L2Instrument_tabIndex_MD::signal_L2Data_order, orders, &snapTableModel_order::refreshL2);

 //   QLabel* orderLabel = new QLabel(QStringLiteral("逐笔订单："), this);
 //   _order_info = new QLabel(this);
 //   _order_info->setMaximumHeight(26);
	//QSplitter* splitterOrderSt = new QSplitter(this);
 //   splitterOrderSt->addWidget(orderLabel);
 //   splitterOrderSt->addWidget(_order_info);
	//splitterOrderSt->setSizes({ 50, 100 });
 //   _order_cnt = 0;

	//_exec_tv = new QTableView(this);
	//_exec_tv->setItemDelegate(delegate);
	//snapTableModel_exec* execs = new snapTableModel_exec(_exec_tv);
	//_exec_tv->setModel(execs);
	//_exec_tv->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//_exec_tv->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//// _exec_tv->verticalHeader()->setMaximumHeight(24);
	//// _exec_tv->verticalHeader()->setMinimumHeight(5);
	//_exec_tv->setSelectionBehavior(QAbstractItemView::SelectRows);
	//_exec_tv->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);	//限制选择
	//_exec_tv->setMaximumWidth(750);
	//connect(this, &L2Instrument_tabIndex_MD::signal_L2Data_exec, execs, &snapTableModel_exec::refreshL2);
 //   QLabel* execLabel = new QLabel(QStringLiteral("逐笔成交："), this);
 //   _exec_info = new QLabel(this);
 //   _exec_info->setMaximumHeight(26);
	//QSplitter* splitterExecSt = new QSplitter(this);
 //   splitterExecSt->addWidget(execLabel);
 //   splitterExecSt->addWidget(_exec_info);
	//splitterExecSt->setSizes({ 50, 100 });
 //   _exec_cnt = 0;

	////整体布局
	QSplitter* splitter = new QSplitter(this);	//横排
	//splitter->addWidget(_level_tv);
	splitter->addWidget(_info_tv);

	// QSplitter* splitterV = new QSplitter(Qt::Orientation::Vertical, this);	//竖排
	// splitterV->addWidget(splitterOrderSt);
	// splitterV->addWidget(_order_tv);
	// splitterV->addWidget(splitterExecSt);
	// splitterV->addWidget(_exec_tv);
	// splitterV->setSizes({ 26, 150, 26, 150 });


	// splitter->addWidget(splitterV);
    // splitter->setSizes({50, 50, 150});

   //布局放进网格，使填充满
	QGridLayout *pLayout = new QGridLayout(this);
    pLayout->addWidget(splitter);
	setLayout(pLayout);

}


void L2Instrument_tabIndex_MD::onL2Data_index_snap(const S4::sharedCharArray_ptr& s)
{
	emit signal_L2Data_index_snap(s);
}



} // namespace QT
} // namespace S4
