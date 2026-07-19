#ifndef WIDGETS_CHECKBOXGROUP_ZCHECKBOXGROUP_H_
#define WIDGETS_CHECKBOXGROUP_ZCHECKBOXGROUP_H_

#include <QWidget>
#include <QList>

class ZCheckbox;
class QVBoxLayout;

// ZCheckboxGroup — Element Plus checkbox group container.
// Manages a list of ZCheckbox children, tracks selected values, and supports
// min/max selection constraints and button-style rendering.

class ZCheckboxGroup : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QList<int> value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(GroupType type READ type WRITE setType)
    Q_PROPERTY(bool border READ border WRITE setBorder)
    Q_PROPERTY(int min READ min WRITE setMin)
    Q_PROPERTY(int max READ max WRITE setMax)
    Q_PROPERTY(bool disabled READ isDisabled WRITE setDisabled)

public:
    enum class GroupType { kDefault, kButton };
    enum class Size { kDefault, kLarge, kSmall };

    explicit ZCheckboxGroup(QWidget* parent = nullptr);

    void setValue(const QList<int>& value);
    QList<int> value() const { return value_; }

    void setType(GroupType type);
    GroupType type() const { return type_; }

    void setBorder(bool border);
    bool border() const { return border_; }

    void setMin(int m);
    int min() const { return min_; }

    void setMax(int m);
    int max() const { return max_; }

    void setDisabled(bool disabled);
    bool isDisabled() const { return disabled_; }

    void setSize(Size size);
    Size size() const { return size_; }

    void addCheckbox(ZCheckbox* checkbox, int checkboxValue);

signals:
    void valueChanged(const QList<int>& value);

private:
    void rebuildChecks();

    QList<int> value_;
    GroupType type_ = GroupType::kDefault;
    bool border_ = false;
    int min_ = 0;
    int max_ = 0;
    bool disabled_ = false;
    Size size_ = Size::kDefault;
    QVBoxLayout* layout_ = nullptr;
    QList<ZCheckbox*> checkboxes_;
    QList<int> checkbox_values_;
};

#endif // WIDGETS_CHECKBOXGROUP_ZCHECKBOXGROUP_H_
