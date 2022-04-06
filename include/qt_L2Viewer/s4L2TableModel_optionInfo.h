﻿#pragma once

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

//上海L1基金
class snapTableModel_optionInfo_L2 : public s4L2TableModelUpdate
{
    Q_OBJECT

public:
    snapTableModel_optionInfo_L2(QObject *parent = {}) : s4L2TableModelUpdate(parent)
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
        if (pH->SecurityIDSource == __SecurityIDSource_SSH_ && pH->MsgType == __MsgType_SSH_OPTION_SNAPx5__ && pH->MsgLen == sizeof(SBE_SSH_option_snapx5_t)){
            const SBE_SSH_option_snapx5_t* pSnap = (SBE_SSH_option_snapx5_t*)l2data->get();
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->LastPx, SSH_L1Bin_PX_precision));                       //
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->LastQty, SSH_L1Bin_VOL_precision, true));               //
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->OpenPx, SSH_L1Bin_PX_precision));
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->HighPx, SSH_L1Bin_PX_precision));
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->LowPx, SSH_L1Bin_PX_precision));
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->SettlPx, SSH_L1Bin_PX_precision));
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->TotalLongPosition, SSH_L1Bin_VOL_precision));
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->RefPx, SSH_L1Bin_PX_precision));
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->QuantityMatching, SSH_L1Bin_VOL_precision));
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->TotalVolumeTrade, SSH_L1Bin_VOL_precision, true));      //
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->TotalValueTrade, SSH_L1Bin_AMT_precision, true));       //
            data[std::pair<int, int>(r++, 1)] = QString::number(pSnap->NumTrades);
            data[std::pair<int, int>(r++, 1)] = ssz_L2_timeString(pSnap->DataTimeStamp).c_str();
            data[std::pair<int, int>(r++, 1)] = SSH_TradingPhaseParse_header(pSnap->Header.TradingPhase) + 
                                                "\n" +
                                                SSH_TradingPhaseParse_body_option(pSnap->TradingPhaseCodePack);
        }

        updateDataAll(data);
    }

private:
    virtual void initNames() override
    {
        _row_names.clear();
        _row_names.push_back(QStringLiteral("最新成交价"));
        _row_names.push_back(QStringLiteral("最新成交量"));
        _row_names.push_back(QStringLiteral("开盘价"));
        _row_names.push_back(QStringLiteral("最高"));
        _row_names.push_back(QStringLiteral("最低"));
        _row_names.push_back(QStringLiteral("结算价"));
        _row_names.push_back(QStringLiteral("总持仓量"));
        _row_names.push_back(QStringLiteral("动态参考价格"));
        _row_names.push_back(QStringLiteral("虚拟匹配数量"));
        _row_names.push_back(QStringLiteral("成交总量"));
        _row_names.push_back(QStringLiteral("成交总金额"));
        _row_names.push_back(QStringLiteral("成交订单数"));
        _row_names.push_back(QStringLiteral("时间戳"));
        _row_names.push_back(QStringLiteral("\n\n交易阶段\n\n\n"));

        _col_names.clear();
        _col_names.push_back(QStringLiteral("项"));
        _col_names.push_back(QStringLiteral("值"));
    }

    virtual void initBackground() override
    {
        _background.clear();
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
            default : return QStringLiteral("无意义:") + QString::number(header_TradingPhase);
        }
    }
    
    static
    QString SSH_TradingPhaseParse_body_option(TradingPhaseCodePack_t body_TradingPhaseCodePack)
    {
        QString b1, b2, b3;
        switch (body_TradingPhaseCodePack.unpack.B1)
        {
            case 0: b1 = QStringLiteral("未连续停牌"); break;
            case 1: b1 = QStringLiteral("连续停牌"); break;
            default:b1 = QStringLiteral("预留");
        }
        switch (body_TradingPhaseCodePack.unpack.B2)
        {
            case 0: b2 = QStringLiteral("不限制开仓"); break;
            case 1: b2 = QStringLiteral("限制备兑开仓"); break;
            case 2: b2 = QStringLiteral("卖出开仓"); break;
            case 3: b2 = QStringLiteral("限制卖出开仓、备兑开仓"); break;
            case 4: b2 = QStringLiteral("限制买入开仓"); break;
            case 5: b2 = QStringLiteral("限制买入开仓、备兑开仓"); break;
            case 6: b2 = QStringLiteral("限制买入开仓、卖出开仓"); break;
            case 7: b2 = QStringLiteral("限制买入开仓、卖出开仓、备兑开仓"); break;
            default:b2 = QStringLiteral("无意义:") + QString::number(body_TradingPhaseCodePack.unpack.B2);
        }
        switch (body_TradingPhaseCodePack.unpack.B3)
        {
            case 0: b3 = QStringLiteral("不接受订单申报"); break;
            case 1: b3 = QStringLiteral("可接受订单申报"); break;
            default:b3 = QStringLiteral("无意义:") + QString::number(body_TradingPhaseCodePack.unpack.B3);
        }
        return b1 + "\n" + b2 + "\n" + b3;
    }
};

}
}
