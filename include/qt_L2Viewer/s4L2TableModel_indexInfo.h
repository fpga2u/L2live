#pragma once

#include "common/s4time.h"
#include "types/s4type_precision.h"
#include "types/s4convertors.h"
#include "qt_common/sharedCharArray_ptr.h"
#include <QDateTime>

#include "sbe_ssz.h"
#include "sbe_ssh.h"
#include "qt_L2Viewer/s4L2TableModelUpdate.h"

namespace S4{
namespace QT{

class snapTableModel_indexInfo_L2 : public s4L2TableModelUpdate
{
    Q_OBJECT

public:
    snapTableModel_indexInfo_L2(QObject *parent = {}) : s4L2TableModelUpdate(parent)
    {
        init();
    }

    void refreshL2(const S4::sharedCharArray_ptr& l2data){
        size_t sbe_size = l2data->size();
        if (sbe_size < sizeof(SBE_SSH_header_t)){
            return;
        }
        std::map<std::pair<int, int>, QVariant> data;
        int r = 0;

        const SBE_SSH_header_t* pH = (SBE_SSH_header_t*)l2data->get();
        if (pH->SecurityIDSource == 101 && pH->MsgType == __MsgType_SSH_INDEX_SNAP__ && pH->MsgLen == sizeof(SBE_SSH_index_snap_t)){
            const SBE_SSH_index_snap_t* pSnap = (SBE_SSH_index_snap_t*)l2data->get();
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->TotalVolumeTrade, SSH_L2_INDEX_VOL_precision, true));  //手
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->TotalValueTrade, SSH_L2_INDEX_AMT_precision, true));   //元
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->PrevClosePx, SSH_L2_INDEX_PX_precision));
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->LastPx, SSH_L2_INDEX_PX_precision));
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->OpenPx, SSH_L2_INDEX_PX_precision));
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->HighPx, SSH_L2_INDEX_PX_precision));
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->LowPx, SSH_L2_INDEX_PX_precision));
            data[std::pair<int, int>(r++, 1)] = QStringLiteral("上海L2无此字段");
            data[std::pair<int, int>(r++, 1)] = (pSnap->DataTimeStamp);
            data[std::pair<int, int>(r++, 1)] = QStringLiteral("上海L2FAST此字段无意义");
        }else
        if (pH->SecurityIDSource == 101 && pH->MsgType == __MsgType_SSH_INDEX_SNAPx5__ && pH->MsgLen == sizeof(SBE_SSH_index_snapx5_t)) {
            const SBE_SSH_index_snapx5_t* pSnap = (SBE_SSH_index_snapx5_t*)l2data->get();
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->TotalVolumeTrade, SSH_L1Bin_VOL_precision, true));  //手
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->TotalValueTrade, SSH_L1Bin_AMT_precision, true));   //元
            data[std::pair<int, int>(r++, 1)] = QStringLiteral("上海L1Bin无此字段");
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->LastPx, SSH_L1Bin_PX_precision));
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->OpenPx, SSH_L1Bin_PX_precision));
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->HighPx, SSH_L1Bin_PX_precision));
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->LowPx, SSH_L1Bin_PX_precision));
            data[std::pair<int, int>(r++, 1)] = QStringLiteral("上海L1Bin TODO");
            data[std::pair<int, int>(r++, 1)] = ssh_L1Bin_timeString(pSnap->DataTimeStamp).c_str();
            data[std::pair<int, int>(r++, 1)] = QStringLiteral("上海L1Bin此字段无意义");    //SSH_TradingPhaseParse_header(pSnap->Header.TradingPhase); //解析也是得到无意义
        }
        else
        if (pH->SecurityIDSource == 102 && pH->MsgType == __MsgType_SSZ_INDEX_SNAP__ && pH->MsgLen == sizeof(SBE_SSZ_index_snap_t)){
            const SBE_SSZ_index_snap_t* pSnap = (SBE_SSZ_index_snap_t*)l2data->get();
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->TotalVolumeTrade, SSZ_L2_Qty_precision, true));    //股
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->TotalValueTrade, SSZ_L2_Amt_precision, true));     //元
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->PrevClosePx, SSZ_L2_iPrice_tick_precision));
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->LastPx, SSZ_L2_iPrice_snap_precision));
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->OpenPx, SSZ_L2_iPrice_snap_precision));
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->HighPx, SSZ_L2_iPrice_snap_precision));
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->LowPx, SSZ_L2_iPrice_snap_precision));
            data[std::pair<int, int>(r++, 1)] = (QString::number(pSnap->NumTrades));
            data[std::pair<int, int>(r++, 1)] = (ssz_L2_timeString(pSnap->TransactTime).c_str());
            data[std::pair<int, int>(r++, 1)] = SSZ_TradingPhaseCodeParse(pSnap->Header.TradingPhase);
        }
        
        updateDataAll(data);
    }

private:
    virtual void initNames() override
    {
        _row_names.clear();
        _row_names.push_back(QStringLiteral("成交总量"));
        _row_names.push_back(QStringLiteral("成交总金额"));
        _row_names.push_back(QStringLiteral("前盘指数"));
        _row_names.push_back(QStringLiteral("最新指数"));
        _row_names.push_back(QStringLiteral("开盘指数"));
        _row_names.push_back(QStringLiteral("最高指数"));
        _row_names.push_back(QStringLiteral("最低指数"));
        _row_names.push_back(QStringLiteral("成交笔数"));
        _row_names.push_back(QStringLiteral("时间"));
        _row_names.push_back(QStringLiteral("交易阶段"));

        _col_names.clear();
        _col_names.push_back(QStringLiteral("项"));
        _col_names.push_back(QStringLiteral("值"));
    }
    
    static
    QString SSZ_TradingPhaseCodeParse(SSZ_TradingPhaseCodePack_t code)
    {
        QString t0, t1;
        switch (code.unpack.Code0)
        {
            case 0: t0 = QStringLiteral("启动"); break;
            case 1: t0 = QStringLiteral("开盘集合竞价"); break;
            case 2: t0 = QStringLiteral("连续交易"); break;
            case 3: t0 = QStringLiteral("休市"); break;
            case 4: t0 = QStringLiteral("收盘集合竞价"); break;
            case 5: t0 = QStringLiteral("已闭市"); break;
            case 6: t0 = QStringLiteral("临时停牌"); break;
            case 7: t0 = QStringLiteral("盘后交易"); break;
            case 8: t0 = QStringLiteral("波动性中断"); break;
            default:t0 = QStringLiteral("无意义");
        };
        switch (code.unpack.Code1)
        {
            case 0: t1 = QStringLiteral("正常"); break;
            case 1: t1 = QStringLiteral("全天停牌"); break;
            default:t1 = QStringLiteral("无意义");
        }

        return t0 + ";" + t1;
    }
    
    static
    QString SSH_TradingPhaseParse_header(uint8_t header_TradingPhase)
    {
        switch (header_TradingPhase)
        {
            case 0  : return QStringLiteral("启动");
            case 1  : return QStringLiteral("开盘集合竞价");
            case 2  : return QStringLiteral("连续交易");
            case 5  : return QStringLiteral("闭市");
            case 6  : return QStringLiteral("产品停牌");
            case 9  : return QStringLiteral("可恢复交易的熔断（盘中集合竞价）");
            case 10 : return QStringLiteral("不可恢复交易的熔断（暂停交易至闭市）");
            case 4  : return QStringLiteral("收盘集合竞价");
            case 3  : return QStringLiteral("休市");
            case 8  : return QStringLiteral("波动性中断");
            default : return QStringLiteral("无意义");
        }
    }
};

}
}
