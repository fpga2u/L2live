#pragma once

#include "common/s4time.h"
#include "types/s4convertors.h"
#include "qt_common/s4qt_itemFormatDelegate.h"

#include "qt_L2Viewer/s4L2TableModelUpdate.h"


namespace S4{
namespace QT{

class snapTableModel_L2Stats : public s4L2TableModelUpdate
{
    Q_OBJECT

public:
    snapTableModel_L2Stats(QObject *parent = {}) : s4L2TableModelUpdate(parent)
    {
        init();
    }

public slots:
    void refresh(const struct S4::NW::L2Stats_t &stats)
    {
        std::map<std::pair<int, int>, QVariant> data;
        int r = 0;
        data[std::pair<int, int>(r++, 1)] = ((long long)stats.recv_frame_cnt);
        data[std::pair<int, int>(r++, 1)] = ((long long)stats.recv_heartbeat_cnt);
        data[std::pair<int, int>(r++, 1)] = ((long long)stats.recv_instrument_snap_cnt);
        data[std::pair<int, int>(r++, 1)] = ((long long)stats.recv_index_snap_cnt);
        data[std::pair<int, int>(r++, 1)] = ((long long)stats.recv_order_cnt);
        data[std::pair<int, int>(r++, 1)] = ((long long)stats.recv_exec_cnt);
        data[std::pair<int, int>(r++, 1)] = ((long long)stats.recv_instrument_snapx5_cnt);
        data[std::pair<int, int>(r++, 1)] = ((long long)stats.recv_fund_snapx5_cnt);
        data[std::pair<int, int>(r++, 1)] = ((long long)stats.recv_index_snapx5_cnt);
        data[std::pair<int, int>(r++, 1)] = ((long long)stats.recv_option_snapx5_cnt);
        data[std::pair<int, int>(r++, 1)] = ((long long)stats.recv_unknown_cnt);
        data[std::pair<int, int>(r++, 1)] = ((long long)stats.live_code_nb);
        data[std::pair<int, int>(r++, 1)] = ((long long)stats.live_instrument_snap_cnt);
        data[std::pair<int, int>(r++, 1)] = ((long long)stats.live_index_snap_cnt);
        data[std::pair<int, int>(r++, 1)] = ((long long)stats.live_order_cnt);
        data[std::pair<int, int>(r++, 1)] = ((long long)stats.live_exec_cnt);
        data[std::pair<int, int>(r++, 1)] = ((long long)stats.live_instrument_snapx5_cnt);
        data[std::pair<int, int>(r++, 1)] = ((long long)stats.live_fund_snapx5_cnt);
        data[std::pair<int, int>(r++, 1)] = ((long long)stats.live_index_snapx5_cnt);
        data[std::pair<int, int>(r++, 1)] = ((long long)stats.live_option_snapx5_cnt);
        data[std::pair<int, int>(r++, 1)] = (ms_to_str_r(stats.last_frame_time_ms).c_str());

        updateDataAll(data);
    }

private:
    virtual void initNames() override
    {
        _row_names.clear();
        _row_names.push_back(QStringLiteral("L2消息"));
        _row_names.push_back(QStringLiteral("心跳"));
        _row_names.push_back(QStringLiteral("行情快照"));
        _row_names.push_back(QStringLiteral("指数快照"));
        _row_names.push_back(QStringLiteral("逐笔委托"));
        _row_names.push_back(QStringLiteral("逐笔成交"));
        _row_names.push_back(QStringLiteral("L1股票行情快照"));
        _row_names.push_back(QStringLiteral("L1基金行情快照"));
        _row_names.push_back(QStringLiteral("L1指数行情快照"));
        _row_names.push_back(QStringLiteral("L1期权行情快照"));
        _row_names.push_back(QStringLiteral("其它"));
        _row_names.push_back(QStringLiteral("关注标的数目"));
        _row_names.push_back(QStringLiteral("关注标的行情快照"));
        _row_names.push_back(QStringLiteral("关注标的指数快照"));
        _row_names.push_back(QStringLiteral("关注标的逐笔委托"));
        _row_names.push_back(QStringLiteral("关注标的逐笔成交"));
        _row_names.push_back(QStringLiteral("关注标的L1股票行情快照"));
        _row_names.push_back(QStringLiteral("关注标的L1基金行情快照"));
        _row_names.push_back(QStringLiteral("关注标的L1指数行情快照"));
        _row_names.push_back(QStringLiteral("关注标的L1期权行情快照"));
        _row_names.push_back(QStringLiteral("本地最后接收时间"));

        _col_names.clear();
        _col_names.push_back(QStringLiteral("项"));
        _col_names.push_back(QStringLiteral("值"));
    }
};

}
}
