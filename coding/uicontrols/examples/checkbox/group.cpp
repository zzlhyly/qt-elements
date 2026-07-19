#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include "widgets/checkboxgroup/zcheckboxgroup.h"
#include "widgets/checkbox/zcheckbox.h"

QWidget* ZCheckboxDemoGroup() {
    auto* w = new QWidget();
    auto* layout = new QVBoxLayout(w);
    layout->setSpacing(12);

    auto* group = new ZCheckboxGroup();
    group->addCheckbox(new ZCheckbox("Option A"), 1);
    group->addCheckbox(new ZCheckbox("Option B"), 2);
    group->addCheckbox(new ZCheckbox("Option C"), 3);
    group->setMin(1);
    group->setMax(2);

    auto* label = new QLabel("Checked: ");
    QObject::connect(group, &ZCheckboxGroup::valueChanged,
        [label](const QList<int>& values) {
            QStringList parts;
            for (int v : values)
                parts << QString::number(v);
            label->setText("Checked: " + parts.join(", "));
        });

    layout->addWidget(group);
    layout->addWidget(label);
    layout->addStretch();
    return w;
}
