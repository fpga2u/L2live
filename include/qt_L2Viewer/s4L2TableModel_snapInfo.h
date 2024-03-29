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

class snapTableModel_snapInfo_L2 : public s4L2TableModelUpdate
{
    Q_OBJECT

public:
    snapTableModel_snapInfo_L2(QObject *parent = {}) : s4L2TableModelUpdate(parent)
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

        if (pH->SecurityIDSource == __SecurityIDSource_SSH_ && pH->MsgType == __MsgType_SSH_INSTRUMENT_SNAP__ && pH->MsgLen == sizeof(SBE_SSH_instrument_snap_t)){
            const SBE_SSH_instrument_snap_t* pSnap = (SBE_SSH_instrument_snap_t*)l2data->get();
            data[std::pair<int, int>(r++, 1)] = (priceString(SSH_L2_iPrice_snap_to_fPrice(pSnap->LastPx)).c_str());
            data[std::pair<int, int>(r++, 1)] = QStringLiteral("上海L2FAST无此字段");
            data[std::pair<int, int>(r++, 1)] = (priceString(SSH_L2_iPrice_tick_to_fPrice(pSnap->PrevClosePx)).c_str());
            data[std::pair<int, int>(r++, 1)] = (priceString(SSH_L2_iPrice_snap_to_fPrice(pSnap->OpenPx)).c_str());
            data[std::pair<int, int>(r++, 1)] = (priceString(SSH_L2_iPrice_snap_to_fPrice(pSnap->HighPx)).c_str());
            data[std::pair<int, int>(r++, 1)] = (priceString(SSH_L2_iPrice_snap_to_fPrice(pSnap->LowPx)).c_str());
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->TotalVolumeTrade, SSH_L2_Qty_precision, true));     //股
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->TotalValueTrade, SSH_L2_Amt_precision, true));      //元
            data[std::pair<int, int>(r++, 1)] = (pSnap->NumTrades);
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->AskWeightPx, SSZ_L2_iPrice_snap_precision));
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->AskWeightSize, SSZ_L2_Qty_precision));   //股
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->BidWeightPx, SSZ_L2_iPrice_snap_precision));
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->BidWeightSize, SSZ_L2_Qty_precision));   //股
            data[std::pair<int, int>(r++, 1)] = QStringLiteral("上海L2FAST无此字段");
            data[std::pair<int, int>(r++, 1)] = QStringLiteral("上海L2FAST无此字段");
            data[std::pair<int, int>(r++, 1)] = (pSnap->DataTimeStamp);
            data[std::pair<int, int>(r++, 1)] = SSH_TradingPhaseParse_header(pSnap->Header.TradingPhase) + 
                                                "\n" +
                                                SSH_TradingPhaseParse_body(pSnap->TradingPhaseCodePack);
        }else 
        if (pH->SecurityIDSource == __SecurityIDSource_SSH_ && pH->MsgType == __MsgType_SSH_INSTRUMENT_SNAPx5__ && pH->MsgLen == sizeof(SBE_SSH_instrument_snapx5_t)){
            const SBE_SSH_instrument_snapx5_t* pSnap = (SBE_SSH_instrument_snapx5_t*)l2data->get();
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->LastPx, SSH_L1Bin_PX_precision));
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->LastQty, SSH_L1Bin_VOL_precision, true));               //股
            data[std::pair<int, int>(r++, 1)] = QStringLiteral("上海L1Binary未转换此字段");
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->OpenPx, SSH_L1Bin_PX_precision));
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->HighPx, SSH_L1Bin_PX_precision));
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->LowPx, SSH_L1Bin_PX_precision));
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->TotalVolumeTrade, SSH_L1Bin_VOL_precision, true));      //股
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->TotalValueTrade, SSH_L1Bin_AMT_precision, true));       //元
            data[std::pair<int, int>(r++, 1)] = QString::number(pSnap->NumTrades);
            data[std::pair<int, int>(r++, 1)] = QStringLiteral("上海L1Binary无此字段");
            data[std::pair<int, int>(r++, 1)] = QStringLiteral("上海L1Binary无此字段");
            data[std::pair<int, int>(r++, 1)] = QStringLiteral("上海L1Binary无此字段");
            data[std::pair<int, int>(r++, 1)] = QStringLiteral("上海L1Binary无此字段");
            data[std::pair<int, int>(r++, 1)] = QStringLiteral("上海L1Binary无此字段");
            data[std::pair<int, int>(r++, 1)] = QStringLiteral("上海L1Binary无此字段");
            data[std::pair<int, int>(r++, 1)] = ssh_L1Bin_timeString(pSnap->DataTimeStamp).c_str();
            data[std::pair<int, int>(r++, 1)] = SSH_TradingPhaseParse_header(pSnap->Header.TradingPhase) + 
                                                "\n" +
                                                SSH_TradingPhaseParse_body(pSnap->TradingPhaseCodePack);
        }else 
        if (pH->SecurityIDSource == __SecurityIDSource_SSZ_ && pH->MsgType == __MsgType_SSZ_INSTRUMENT_SNAP__ && pH->MsgLen == sizeof(SBE_SSZ_instrument_snap_t)){
            const SBE_SSZ_instrument_snap_t* pSnap = (SBE_SSZ_instrument_snap_t*)l2data->get();
            data[std::pair<int, int>(r++, 1)] = (priceString(SSZ_L2_iPrice_snap_to_fPrice(pSnap->LastPx)).c_str());
            data[std::pair<int, int>(r++, 1)] = QStringLiteral("深圳L2Binary无此字段");
            data[std::pair<int, int>(r++, 1)] = (priceString(SSZ_L2_iPrice_tick_to_fPrice(pSnap->PrevClosePx)).c_str());
            data[std::pair<int, int>(r++, 1)] = (priceString(SSZ_L2_iPrice_snap_to_fPrice(pSnap->OpenPx)).c_str());
            data[std::pair<int, int>(r++, 1)] = (priceString(SSZ_L2_iPrice_snap_to_fPrice(pSnap->HighPx)).c_str());
            data[std::pair<int, int>(r++, 1)] = (priceString(SSZ_L2_iPrice_snap_to_fPrice(pSnap->LowPx)).c_str());
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->TotalVolumeTrade, SSZ_L2_Qty_precision, true));     //股
            data[std::pair<int, int>(r++, 1)] = (v2s(pSnap->TotalValueTrade, SSZ_L2_Amt_precision, true));      //元
            data[std::pair<int, int>(r++, 1)] = (QString::number(pSnap->NumTrades));
            data[std::pair<int, int>(r++, 1)] = (priceString(SSZ_L2_iPrice_snap_to_fPrice(pSnap->AskWeightPx)).c_str());
            data[std::pair<int, int>(r++, 1)] = (QString::number(pSnap->AskWeightSize/SSZ_L2_Qty_precision));   //股
            data[std::pair<int, int>(r++, 1)] = (priceString(SSZ_L2_iPrice_snap_to_fPrice(pSnap->BidWeightPx)).c_str());
            data[std::pair<int, int>(r++, 1)] = (QString::number(pSnap->BidWeightSize/SSZ_L2_Qty_precision));   //股
            data[std::pair<int, int>(r++, 1)] = (priceString(SSZ_L2_iPrice_snap_to_fPrice(pSnap->UpLimitPx)).c_str());
            data[std::pair<int, int>(r++, 1)] = (priceString(SSZ_L2_iPrice_snap_to_fPrice(pSnap->DnLimitPx)).c_str());
            data[std::pair<int, int>(r++, 1)] = (ssz_L2_timeString(pSnap->TransactTime).c_str());
            data[std::pair<int, int>(r++, 1)] = SSZ_TradingPhaseCodeParse(pSnap->Header.TradingPhase);
        }
        
        updateDataAll(data);
    }

private:
    virtual void initNames() override
    {
        _row_names.clear();
        _row_names.push_back(QStringLiteral("最新成交价"));
        _row_names.push_back(QStringLiteral("最新成交量"));
        _row_names.push_back(QStringLiteral("昨收"));
        _row_names.push_back(QStringLiteral("开盘价"));
        _row_names.push_back(QStringLiteral("最高"));
        _row_names.push_back(QStringLiteral("最低"));
        _row_names.push_back(QStringLiteral("成交总量"));
        _row_names.push_back(QStringLiteral("成交总金额"));
        _row_names.push_back(QStringLiteral("成交笔数"));
        _row_names.push_back(QStringLiteral("委卖加权价格"));
        _row_names.push_back(QStringLiteral("委卖量"));
        _row_names.push_back(QStringLiteral("委买加权价格"));
        _row_names.push_back(QStringLiteral("委买量"));
        _row_names.push_back(QStringLiteral("涨停价"));
        _row_names.push_back(QStringLiteral("跌停价"));
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

        return t0 + "\n" + t1;
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
    
    static
    QString SSH_TradingPhaseParse_body(TradingPhaseCodePack_t body_TradingPhaseCodePack)
    {
        QString b1, b2, b3;
        switch (body_TradingPhaseCodePack.unpack.B1)
        {
            case 0: b1 = QStringLiteral("产品不可正常交易"); break;
            case 1: b1 = QStringLiteral("产品可正常交易"); break;
            default:b1 = QStringLiteral("无意义");
        }
        switch (body_TradingPhaseCodePack.unpack.B2)
        {
            case 0: b2 = QStringLiteral("未上市"); break;
            case 1: b2 = QStringLiteral("已上市"); break;
            default:b2 = QStringLiteral("无意义");
        }
        switch (body_TradingPhaseCodePack.unpack.B3)
        {
            case 0: b3 = QStringLiteral("不接受订单申报"); break;
            case 1: b3 = QStringLiteral("可接受订单申报"); break;
            default:b3 = QStringLiteral("无意义");
        }
        return b1 + "\n" + b2 + "\n" + b3;
    }
};

}
}
