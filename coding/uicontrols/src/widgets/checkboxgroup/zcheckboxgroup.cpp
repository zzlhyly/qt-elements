#include "zcheckboxgroup.h"
#include "widgets/checkbox/zcheckbox.h"
#include "theme/theme.h"

#include <QVariant>
#include <QVBoxLayout>

ZCheckboxGroup::ZCheckboxGroup(QWidget* parent)
    : QWidget(parent)
{
    layout_ = new QVBoxLayout(this);
    layout_->setContentsMargins(0, 0, 0, 0);
    layout_->setSpacing(8);
}

void ZCheckboxGroup::setValue(const QList<int>& v) {
    if (value_ == v) return;
    value_ = v;
    rebuildChecks();
    emit valueChanged(value_);
}

void ZCheckboxGroup::setType(GroupType t) { type_ = t; rebuildChecks(); }
void ZCheckboxGroup::setBorder(bool b) { border_ = b; rebuildChecks(); }
void ZCheckboxGroup::setMin(int m) { min_ = m; }
void ZCheckboxGroup::setMax(int m) { max_ = m; }
void ZCheckboxGroup::setDisabled(bool d) { disabled_ = d; rebuildChecks(); }
void ZCheckboxGroup::setSize(Size s) { size_ = s; rebuildChecks(); }

void ZCheckboxGroup::addCheckbox(ZCheckbox* cb, int val) {
    checkboxes_.append(cb);
    checkbox_values_.append(val);
    rebuildChecks();
}

void ZCheckboxGroup::rebuildChecks() {
    // Remove all children from layout
    while (layout_->count() > 0) {
        auto* item = layout_->takeAt(0);
        if (item->widget()) item->widget()->setParent(nullptr);
        delete item;
    }

    for (int i = 0; i < checkboxes_.size(); ++i) {
        auto* cb = checkboxes_[i];
        int val = checkbox_values_[i];

        bool checked = value_.contains(val);
        cb->setChecked(checked);

        if (type_ == GroupType::kButton) {
            cb->setProperty("checkboxGroupButton", QVariant(true));
            cb->setStyleSheet(QString());
        } else {
            cb->setProperty("checkboxGroupButton", QVariant());
        }

        cb->setEnabled(!disabled_);
        cb->setParent(this);

        disconnect(cb, nullptr, this, nullptr);
        connect(cb, &QAbstractButton::toggled, this, [this, cb, val](bool checked) {
            QList<int> newValue = value_;
            if (checked) {
                if (!newValue.contains(val)) newValue.append(val);
                if (max_ > 0 && newValue.size() > max_) { newValue.removeAll(val); cb->setChecked(false); return; }
            } else {
                if (min_ > 0 && newValue.size() <= min_) { cb->setChecked(true); return; }
                newValue.removeAll(val);
            }
            if (newValue != value_) {
                value_ = newValue;
                emit valueChanged(value_);
            }
        });

        layout_->addWidget(cb);
    }
}
