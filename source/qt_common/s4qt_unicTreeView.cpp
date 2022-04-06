#include "qt_common/s4qt_unicTreeView.h"
#include <QDebug>
#include <QMouseEvent>
#include <QStandardItem>
#include <QLineEdit>
#include <QShortcut>

namespace S4
{
namespace QT
{


unicTreeView::unicTreeView(QWidget* parent):
    QTreeView(parent)
{
	QShortcut* shortCut = new QShortcut(Qt::Key_Delete, this);
	connect(shortCut, &QShortcut::activated, this, &unicTreeView::onDelkey);
	connect(this, &unicTreeView::signal_blankDoubleClick, this, &unicTreeView::onBlankDoubleClick);
	// connect(this, &QTreeView::clicked, this, &unicTreeView::onMouseClick);
}
void unicTreeView::onSetCurrentRoot(QStandardItem* root)
{
	_current_root = root;
	//connect((QStandardItemModel*)model(), &QStandardItemModel::itemChanged, this, &unicTreeView::onItemChanged);
}

void unicTreeView::onSelectItem(const QString& text)
{
    int idx = findChild(text);
    if (idx < 0) return;
    this->setCurrentIndex(_current_root->child(idx)->index());
}


void unicTreeView::onSetTextFormater(unicTreeView::textFormater_t* textFormater)
{
	_textFormater = textFormater;
}

void unicTreeView::mouseDoubleClickEvent(QMouseEvent* event)
{
	QTreeView::mouseDoubleClickEvent(event);

	QModelIndex index = this->indexAt(event->pos());
	//QAbstractItemModel *model = this->model();
	//QMap<int, QVariant> ItemData = model->itemData(index);

	if (index.row() < 0) {
		qDebug() << "onBlankDoubleClick";
		emit signal_blankDoubleClick();
	}
}

void unicTreeView::onDelkey()
{
	if (!this->currentIndex().parent().isValid())
		return;
	qDebug() << "onDelkey " << this->currentIndex();
    emit signal_delItem(this->currentIndex().data().toString());
	_current_root->removeRow(this->currentIndex().row());
}

void unicTreeView::onDelItem(const QString& text)
{
	int i = findChild(text);
	if (i >= 0) {
		_current_root->removeRow(i);
	}
}

// void unicTreeView::onMouseClick(const QModelIndex& index) {
// 	if (!this->currentIndex().parent().isValid())
// 		return;
// 	emit signal_selectItem(this->currentIndex().data().toString());
// }

void unicTreeView::currentChanged(const QModelIndex &current, const QModelIndex &previous) {
	emit signal_selectItem(this->currentIndex().data().toString());
}

void unicTreeView::onBlankDoubleClick() {
	//if (!index.parent().isValid())
	//	return;
	//if (!index.parent().parent().isValid()) return;

    QStandardItem * item = new QStandardItem;
	item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
	_current_root->appendRow(item);

	this->expandAll();
	this->setCurrentIndex(item->index());
	this->edit(item->index());
}

void unicTreeView::onItemChanged(QWidget* editor, int hint)
{
    if (QLineEdit* le = qobject_cast<QLineEdit*>(editor)) {
		int row = findChild(le->text());
        if (row < 0){
            qDebug() << "item not found:" << le->text() << " " << currentIndex();
            _current_root->removeRow(this->currentIndex().row());
            return;
        }
		if (_textFormater) {
			QString fmt_text;
			if (!(*_textFormater)(le->text(), fmt_text)) {
				_current_root->removeRow(row);
				qDebug() << "error format, please retry!";
				return;
			}
			_current_root->child(row)->setText(fmt_text);
		}
        QString text = _current_root->child(row)->text();
        int count = countChild(text);
		if (count>1) {
			_current_root->removeRow(row);
			qDebug() << "dual input, please change!";
		    int existing_row = findChild(text);
			this->setCurrentIndex(_current_root->child(existing_row)->index());
			return;
		}
		_current_root->child(row)->setFlags(_current_root->child(row)->flags() & (~Qt::ItemIsEditable));
		emit signal_newItem(text);
	}
}

int unicTreeView::findChild(const QString& text)
{
	for (int i = 0; i < _current_root->rowCount(); ++i)
	{
		if (_current_root->child(i)->text() == text)
		{
			return i;
		}
	}
	return -1;
}

int unicTreeView::countChild(const QString& text)
{
    int c=0;
	for (int i = 0; i < _current_root->rowCount(); ++i)
	{
		if (_current_root->child(i)->text() == text)
		{
			++c;
		}
	}
	return c;
}

void unicTreeView::forceAddChild(const QString& text)
{
	QStandardItem* item = new QStandardItem;
	item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
	item->setText(text);
	_current_root->appendRow(item);

	this->expandAll();
	this->setCurrentIndex(item->index());
	//this->edit(item->index());
	//this->closePersistentEditor(item->index());
}

} // namespace QT
} // namespace S4
