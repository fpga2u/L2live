#pragma once

#include "types/s4type_precision.h"
#include "types/s4convertors.h"
#include "qt_common/sharedCharArray_ptr.h"

#include "sbe_ssz.h"
#include "sbe_ssh.h"
#include "qt_L2Viewer/s4L2TableModelUpdate.h"

namespace S4{
namespace QT{

class snapTableModel_level : public s4L2TableModelUpdate
{
    Q_OBJECT
    const int _side_levels_nb;
public:
    snapTableModel_level(int side_levels_nb, QObject *parent = {}) : 
        s4L2TableModelUpdate(parent),
        _side_levels_nb(side_levels_nb)
    {
        init();
    }

    void refreshL2(const S4::sharedCharArray_ptr& l2data){
        size_t sbe_size = l2data->size();
        if (sbe_size < sizeof(SBE_SSH_header_t)){
            return;
        }
        const SBE_SSH_header_t* pH = (SBE_SSH_header_t*)l2data->get();
        std::map<std::pair<int, int>, QVariant> data;
        int r = 0;

        if (pH->SecurityIDSource == __SecurityIDSource_SSH_ && pH->MsgType == __MsgType_SSH_INSTRUMENT_SNAP__ && pH->MsgLen == sizeof(SBE_SSH_instrument_snap_t))
        {//数据有10档
            const int snap_lv_size = 10;
            const SBE_SSH_instrument_snap_t* pSnap = (SBE_SSH_instrument_snap_t*)l2data->get();
            r = _side_levels_nb - snap_lv_size;   //允许表格展示更多，如有11档则从#1行开始展示
            if (r < 0) r = 0;           //允许表格展示更少，如只展示9档，则从#0行开始展示
            for (int i=_side_levels_nb>snap_lv_size?(snap_lv_size-1):_side_levels_nb-1; i>=0; --i){  //从行数档开始展示，若行数超过10则从十档开始
                data[std::pair<int, int>(r, 1)] = SSH_L2_iPrice_snap_to_fPrice(pSnap->AskLevel[i].Price);
                data[std::pair<int, int>(r, 2)] = S4::DoubleConvertor::convert((float)pSnap->AskLevel[i].Qty/SSH_L2_Qty_precision).c_str();
                r++;
            }
            for (int i=0; i<snap_lv_size && i<_side_levels_nb; ++i){
                data[std::pair<int, int>(r, 1)] = SSH_L2_iPrice_snap_to_fPrice(pSnap->BidLevel[i].Price);
                data[std::pair<int, int>(r, 2)] = S4::DoubleConvertor::convert((float)pSnap->BidLevel[i].Qty/SSH_L2_Qty_precision).c_str();
                r++;
            }
        }else 
        if (pH->SecurityIDSource == __SecurityIDSource_SSZ_ && pH->MsgType == __MsgType_SSZ_INSTRUMENT_SNAP__ && pH->MsgLen == sizeof(SBE_SSZ_instrument_snap_t))
        {//数据有10档
            const int snap_lv_size = 10;
            const SBE_SSZ_instrument_snap_t* pSnap = (SBE_SSZ_instrument_snap_t*)l2data->get();
            r = _side_levels_nb - snap_lv_size;   //允许表格展示更多，如有11档则从#1行开始展示
            if (r < 0) r = 0;           //允许表格展示更少，如只展示9档，则从#0行开始展示
            for (int i=_side_levels_nb>snap_lv_size?(snap_lv_size-1):_side_levels_nb-1; i>=0; --i){  //从行数档开始展示，若行数超过10则从十档开始
                data[std::pair<int, int>(r, 1)] = SSZ_L2_iPrice_snap_to_fPrice(pSnap->AskLevel[i].Price);       //元
                data[std::pair<int, int>(r, 2)] = (float)pSnap->AskLevel[i].Qty/SSZ_L2_Qty_precision;           //股
                r++;
            }
            for (int i=0; i<snap_lv_size && i<_side_levels_nb; ++i){
                data[std::pair<int, int>(r, 1)] = SSZ_L2_iPrice_snap_to_fPrice(pSnap->BidLevel[i].Price);
                data[std::pair<int, int>(r, 2)] = (float)pSnap->BidLevel[i].Qty/SSZ_L2_Qty_precision;
                r++;
            }
        }else 
        if (pH->SecurityIDSource == __SecurityIDSource_SSH_ && pH->MsgType == __MsgType_SSH_INSTRUMENT_SNAPx5__ && pH->MsgLen == sizeof(SBE_SSH_instrument_snapx5_t))
        {//数据有5档
            const int snap_lv_size = 5;
            const SBE_SSH_instrument_snapx5_t* pSnap = (SBE_SSH_instrument_snapx5_t*)l2data->get();
            r = _side_levels_nb - snap_lv_size;   //允许表格展示更多，如有6档则从#1行开始展示
            if (r < 0) r = 0;           //允许表格展示更少，如只展示4档，则从#0行开始展示
            for (int i=_side_levels_nb>snap_lv_size?(snap_lv_size-1):_side_levels_nb-1; i>=0; --i){  //从行数档开始展示，若行数超过5则从五档开始
                data[std::pair<int, int>(r, 1)] = v2s(pSnap->AskLevel[i].Price, SSH_L1Bin_PX_precision);
                data[std::pair<int, int>(r, 2)] = (float)pSnap->AskLevel[i].Qty/SSH_L1Bin_VOL_precision;
                r++;
            }
            for (int i=0; i<snap_lv_size && i<_side_levels_nb; ++i){
                data[std::pair<int, int>(r, 1)] = v2s(pSnap->BidLevel[i].Price, SSH_L1Bin_PX_precision);
                data[std::pair<int, int>(r, 2)] = (float)pSnap->BidLevel[i].Qty/SSH_L1Bin_VOL_precision;
                r++;
            }
        }else 
        if (pH->SecurityIDSource == __SecurityIDSource_SSH_ && pH->MsgType == __MsgType_SSH_FUND_SNAPx5__ && pH->MsgLen == sizeof(SBE_SSH_fund_snapx5_t))
        {//数据有5档
            const int snap_lv_size = 5;
            const SBE_SSH_fund_snapx5_t* pSnap = (SBE_SSH_fund_snapx5_t*)l2data->get();
            r = _side_levels_nb - snap_lv_size;   //允许表格展示更多，如有6档则从#1行开始展示
            if (r < 0) r = 0;           //允许表格展示更少，如只展示4档，则从#0行开始展示
            for (int i=_side_levels_nb>snap_lv_size?(snap_lv_size-1):_side_levels_nb-1; i>=0; --i){  //从行数档开始展示，若行数超过5则从五档开始
                data[std::pair<int, int>(r, 1)] = v2s(pSnap->AskLevel[i].Price, SSH_L1Bin_PX_precision);
                data[std::pair<int, int>(r, 2)] = (float)pSnap->AskLevel[i].Qty/SSH_L1Bin_VOL_precision;
                r++;
            }
            for (int i=0; i<snap_lv_size && i<_side_levels_nb; ++i){
                data[std::pair<int, int>(r, 1)] = v2s(pSnap->BidLevel[i].Price, SSH_L1Bin_PX_precision);
                data[std::pair<int, int>(r, 2)] = (float)pSnap->BidLevel[i].Qty/SSH_L1Bin_VOL_precision;
                r++;
            }
        }else 
        if (pH->SecurityIDSource == __SecurityIDSource_SSH_ && pH->MsgType == __MsgType_SSH_OPTION_SNAPx5__ && pH->MsgLen == sizeof(SBE_SSH_option_snapx5_t))
        {//数据有5档
            const int snap_lv_size = 5;
            const SBE_SSH_option_snapx5_t* pSnap = (SBE_SSH_option_snapx5_t*)l2data->get();
            r = _side_levels_nb - snap_lv_size;   //允许表格展示更多，如有6档则从#1行开始展示
            if (r < 0) r = 0;           //允许表格展示更少，如只展示4档，则从#0行开始展示
            for (int i=_side_levels_nb>snap_lv_size?(snap_lv_size-1):_side_levels_nb-1; i>=0; --i){  //从行数档开始展示，若行数超过5则从五档开始
                data[std::pair<int, int>(r, 1)] = v2s(pSnap->AskLevel[i].Price, SSH_L1Bin_PX_precision);
                data[std::pair<int, int>(r, 2)] = v2s(pSnap->BidLevel[i].Qty, SSH_L1Bin_VOL_precision);
                r++;
            }
            for (int i=0; i<snap_lv_size && i<_side_levels_nb; ++i){
                data[std::pair<int, int>(r, 1)] = v2s(pSnap->BidLevel[i].Price, SSH_L1Bin_PX_precision);
                data[std::pair<int, int>(r, 2)] = v2s(pSnap->BidLevel[i].Qty, SSH_L1Bin_VOL_precision);
                r++;
            }
        }
        updateDataAll(data);
    }

private:
    virtual void initNames() override
    {
        _row_names.clear();
        if (_side_levels_nb>10){
            for (int i=0;i<_side_levels_nb;++i){
                _row_names.push_back(QString::number(_side_levels_nb-i));
            }
            for (int i=0;i<_side_levels_nb;++i){
                _row_names.push_back(QString::number(1+i));
            }
        }else{
            if (_side_levels_nb>=10)_row_names.push_back(QStringLiteral("卖十"));
            if (_side_levels_nb>= 9)_row_names.push_back(QStringLiteral("卖九"));
            if (_side_levels_nb>= 8)_row_names.push_back(QStringLiteral("卖八"));
            if (_side_levels_nb>= 7)_row_names.push_back(QStringLiteral("卖七"));
            if (_side_levels_nb>= 6)_row_names.push_back(QStringLiteral("卖六"));
            if (_side_levels_nb>= 5)_row_names.push_back(QStringLiteral("卖五"));
            if (_side_levels_nb>= 4)_row_names.push_back(QStringLiteral("卖四"));
            if (_side_levels_nb>= 3)_row_names.push_back(QStringLiteral("卖三"));
            if (_side_levels_nb>= 2)_row_names.push_back(QStringLiteral("卖二"));
            if (_side_levels_nb>= 1)_row_names.push_back(QStringLiteral("卖一"));
            if (_side_levels_nb>= 1)_row_names.push_back(QStringLiteral("买一"));
            if (_side_levels_nb>= 2)_row_names.push_back(QStringLiteral("买二"));
            if (_side_levels_nb>= 3)_row_names.push_back(QStringLiteral("买三"));
            if (_side_levels_nb>= 4)_row_names.push_back(QStringLiteral("买四"));
            if (_side_levels_nb>= 5)_row_names.push_back(QStringLiteral("买五"));
            if (_side_levels_nb>= 6)_row_names.push_back(QStringLiteral("买六"));
            if (_side_levels_nb>= 7)_row_names.push_back(QStringLiteral("买七"));
            if (_side_levels_nb>= 8)_row_names.push_back(QStringLiteral("买八"));
            if (_side_levels_nb>= 9)_row_names.push_back(QStringLiteral("买九"));
            if (_side_levels_nb>=10)_row_names.push_back(QStringLiteral("买十"));
        }
        
        _col_names.clear();
        _col_names.push_back(QStringLiteral("档位"));
        _col_names.push_back(QStringLiteral("价格"));
        _col_names.push_back(QStringLiteral("数量"));
    }

    virtual void initBackground() override
    {
        for (int i=0; i<_side_levels_nb; ++i){
            _background[std::pair<int, int>(i, 0)] = QColor(128, 255, 128);
            _background[std::pair<int, int>(i+_side_levels_nb, 0)] = QColor(255, 128, 128);
        }
    }

};

}
}