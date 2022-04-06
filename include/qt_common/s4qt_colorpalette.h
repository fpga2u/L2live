#pragma once

#include <QColor>
#include <vector>

namespace S4{

//psitive color box index    
#define S4_K_RISE_CN 0
#define S4_K_OPEN_CN 1


//negtive color box index    
#define S4_K_FALL_CN 0
#define S4_K_CLOSE_CN 1



struct color_pair_t
{
    QColor back;
    QColor front;
};

struct color_box_t
{
    QColor body;
    QColor skin;
};

class qt_colorpalette_t
{
public:
    QColor background = QColor("#FFFFE0");
    QColor crosshair = Qt::red;
    color_pair_t grid = { QColor("#FF80FF"), QColor("#000000") };   //line, text
    std::vector<color_pair_t> curve = {  //back=line, front=dot
        {QColor("#00f9ff"), QColor("#0004ff")},
        {QColor("#ff5f29"), QColor("#215553")},
        {QColor("#666D91"), QColor("#F0A750")},
        {QColor("#126663"), QColor("#B15A58")},
        {QColor("#783C35"), QColor("#44A274")},
        {QColor("#34431B"), QColor("#6A5B7D")},
        {QColor("#216470"), QColor("#C4704B")},

        //{QColor("#783C35"), QColor("#1E958E")},
        //{QColor("#844555"), QColor("#44A274")},
        //{QColor("#7F5677"), QColor("#7BAB56")},
        //{QColor("#666D91"), QColor("#B6AC44")},
        //{QColor("#3D8399"), QColor("#F0A750")}
    };
    std::vector<color_box_t> positive_boxes = {
        {QColor("#F11227"), QColor("#A13026")},
        {QColor("#D52627"), QColor("#892F24")},
        {QColor("#ec4488"), QColor("#8b1d4e")},
    };
    std::vector<color_box_t> negtive_boxes = {
        {QColor("#005aff"), QColor("#0000FF")},
        {QColor("#8080FF"), QColor("#8080FF")},
        {QColor("#7c00ff"), QColor("#6300ff")},
    };
    std::vector<QColor> front_crv = {
        QColor("#4080AF"),
        QColor("#FF80FF"),
        QColor("#80c0FF")
    };
    std::vector<color_pair_t> labels = {
        {Qt::darkBlue, Qt::white},
        {Qt::darkGray, Qt::red},
        {Qt::darkGreen, Qt::white},

        {QColor("#5F2F28"), QColor("#1B7060")},
        {QColor("#673542"), QColor("#427848")},
        {QColor("#5E435D"), QColor("#707B32")},
        {QColor("#45556F"), QColor("#9D7731")},
        {QColor("#216470"), QColor("#C4704B")},
    };
};



} // namespace S4
