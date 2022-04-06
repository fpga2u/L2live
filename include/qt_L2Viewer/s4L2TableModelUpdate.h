#pragma once

#include "common/s4time.h"
#include "common/s4string.h"
#include "types/s4convertors.h"
#include "network/L2_udp_recver_th.h"

#include <QTableView>
#include <QDateTime>
#include <QTimeLine>
#include <QDebug>


namespace S4{
namespace QT{

//表头、行列数、每行首列字符串固定、持续刷新值的表单。用于快照展示。
class s4L2TableModelUpdate : public QAbstractTableModel
{
public:
    //需要两步构造。
    explicit s4L2TableModelUpdate(QObject *parent = nullptr);
    void init();

    //QT类接口
    int rowCount(const QModelIndex &) const override { return (int)_row_names.size(); }
    int columnCount(const QModelIndex &) const override { return (int)_col_names.size();}
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QVariant data(const QModelIndex &index, int role) const override;

protected:/*需要派生实现*/
    /*在init()调用的初始化函数:initXXXX*/
    virtual void initNames() = 0;   //初始化 _row_names/ _col_names成员
    virtual void initBackground();  //初始化 _background

protected:
    //更新整个表单内容，显示new_data_matrix中的值，同时new_data_matrix将被置换成旧值。
    //new_data_matrix[row, col]的row从0开始，col从1开始；若某行列位置无值将显示空白。
    void updateDataAll(std::map<std::pair<int, int>, QVariant>& new_data_matrix);

    //更新单个单元值
    void updateData(int row, int col, QVariant& v);

    // inline static
    // QString v2s(double v, unsigned int precision) {
    //     return S4::DoubleConvertor::convert(v/ precision).c_str();
    // }
    inline static
    QString v2s(int64_t v, unsigned int precision, bool comma=false) {
        if (comma){
            return QString::fromStdString(S4::string_format_number_comma(S4::IntConvertor::convert(v/ precision) + "." + S4::IntConvertor::convert(v % precision)));
        }else{
            return QString::fromStdString(S4::IntConvertor::convert(v/ precision) + "." + S4::IntConvertor::convert(v % precision));
        }
    }
protected:
    std::vector<QString> _col_names;  //列名称，显示在表头，没名称则填入空字符串
    std::vector<QString> _row_names;  //行名称，显示在每行的首列

    std::map<std::pair<int, int>, QColor> _background;  //单元格背景色，某行列为空时默认填充白色

    //高亮配置，默认3000ms*5次，仅允许在构造函数中设置。
    int _highlight_duration_ms;     //高亮持续时间
    int _highlight_refresh_cnt;     //高亮刷新频率

private:
    QVariant itemFadeColor(const QModelIndex& index) const;

private:
    mutable  std::map<std::pair<int, int>, QDateTime> _data_changed_timing; //记录行列单元格数据变化时间点
    QTimeLine* _timeLine;
    std::map<std::pair<int, int>, QVariant> _data_mtx;  //(行号, 列号):数据；行号从0开始；列号从1开始(#0列用于显示行名称)
};



}
}
