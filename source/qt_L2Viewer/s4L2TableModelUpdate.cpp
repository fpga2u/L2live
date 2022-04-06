#include "qt_L2Viewer/s4L2TableModelUpdate.h"
#include "qt_common/s4qt_itemFormatDelegate.h"
#include "qdebug.h"

#define DEF_HIGHLIGHT_DURATION_MS 2000
#define DEF_HIGHLIGHT_REFRESH_CNT 5

namespace S4{
namespace QT{
    
s4L2TableModelUpdate::s4L2TableModelUpdate(QObject *parent) : 
    QAbstractTableModel{parent},
    _highlight_duration_ms(DEF_HIGHLIGHT_DURATION_MS),
    _highlight_refresh_cnt(DEF_HIGHLIGHT_REFRESH_CNT)
{
}

void s4L2TableModelUpdate::initBackground()
{
    //默认空
}

void s4L2TableModelUpdate::init()
{
    initNames();
    initBackground();

    //初始化成空数据
    for (int r=0; r<rowCount(QModelIndex()); ++r){
        for (int c=1; c<columnCount(QModelIndex()); ++c){
            _data_mtx[std::pair<int, int>(r, c)] = {};
        }
    }
    
    //TODO: 派生类是否需要改高亮周期和刷新频率？
    _timeLine = new QTimeLine(_highlight_duration_ms * 1.1, this);
    _timeLine->setFrameRange(0, _highlight_refresh_cnt);
    _timeLine->stop();
    connect(_timeLine, &QTimeLine::frameChanged, this, [=](int) {   //触发单元格刷新信号，View类需要将setItemDelegate(itemFormatDelegate())以发送刷新role
        beginResetModel();
        endResetModel();
    });
}


QVariant s4L2TableModelUpdate::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
        return {};
    if ((size_t)section >= _col_names.size()){
        return {};
    }else{
        return _col_names.at(section);
    }
}

// void s4L2TableModelUpdate::set_highlight_duration_ms(int ms)
// {
//     if (ms<0) _highlight_duration_ms = DEF_HIGHLIGHT_DURATION_MS;
//     else _highlight_duration_ms = ms;
// }
// void s4L2TableModelUpdate::set_highlight_refresh_cnt(int cnt)
// {
//     if (cnt<0) cnt = 0;
//     else _highlight_refresh_cnt = cnt;
// }

//高亮颜色渐变
QVariant s4L2TableModelUpdate::itemFadeColor(const QModelIndex& index) const
{
    auto idx = std::pair<int, int>(index.row(), index.column());
    std::map<std::pair<int, int>, QDateTime>::iterator it = _data_changed_timing.find(idx);
    QColor default_bg(Qt::white);
    if (_background.count(idx)){
        default_bg = _background.at(idx);
    }

    if (it == _data_changed_timing.end()) return default_bg;
    float time_passed = it->second.msecsTo(QDateTime::currentDateTime());
    if (time_passed < _highlight_duration_ms) {
        float fct = time_passed / _highlight_duration_ms;   //0->1
        if (fct>1) fct = 1;
        QColor bg(Qt::cyan);
        uint8_t r = (255 - bg.red()) * (fct)+bg.red();
        uint8_t g = (255 - bg.green()) * (fct)+bg.green();
        uint8_t b = (255 - bg.blue()) * (fct)+bg.blue();
        return QColor(r, g, b);
    }
    _data_changed_timing.erase(it);
    return  default_bg;
}

QVariant s4L2TableModelUpdate::data(const QModelIndex &index, int role) const
{
    if (role == itemFormatDelegateRole) {   //自定义的刷新信号
        return itemFadeColor(index);
    }

    if (role != Qt::DisplayRole)
        return {}; // && role != Qt::EditRole

    if (index.column() == 0){
        return _row_names.at(index.row());
    } else if (index.column() < (int)_col_names.size() && _data_mtx.count(std::pair<int, int>(index.row(), index.column()))) {
        return _data_mtx.at(std::pair<int, int>(index.row(), index.column()));
    }else{
        return {};
    }
}

void s4L2TableModelUpdate::updateDataAll(std::map<std::pair<int, int>, QVariant>& new_data)
{
    //backup
    beginResetModel();
    std::swap(new_data, _data_mtx);
    endResetModel();

    //高亮变动
    // _data_changed_timing.clear();
    auto now_timing = QDateTime::currentDateTime();
    for (int r=0; r<rowCount(QModelIndex()); ++r){
        for (int c=1; c<columnCount(QModelIndex()); ++c){
            auto idx = std::pair<int, int>(r, c);
            bool exits_changed = (new_data.count(idx) != _data_mtx.count(idx));
            bool value_changed = new_data.count(idx) && _data_mtx.count(idx) && new_data.at(idx) != _data_mtx.at(idx);
            if (exits_changed || value_changed)
            {
                _data_changed_timing[idx] = now_timing;    //单元刷新时间
            }
        }
    }
    _timeLine->stop();
    if (_data_changed_timing.size())
        _timeLine->start();
}

void s4L2TableModelUpdate::updateData(int row, int col, QVariant& v)
{
    auto idx = std::pair<int, int>(row, col);
    beginResetModel();
    if (!_data_mtx.count(idx)){
        _data_mtx[idx] = v;
        v.clear();
    }else{
        std::swap(v, _data_mtx[idx]);
    }
    endResetModel();

    if (v != _data_mtx[idx]){
        _data_changed_timing[idx] = QDateTime::currentDateTime();    //单元刷新时间
    }
    _timeLine->stop();
    if (_data_changed_timing.size())
        _timeLine->start();
}


} // namespace QT
} // namespace S4
