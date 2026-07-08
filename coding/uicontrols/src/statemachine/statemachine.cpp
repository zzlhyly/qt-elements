#include "statemachine/statemachine.h"

namespace statemachine {

StateTracker::StateTracker(QObject* parent)
    : QObject(parent)
{
}

void StateTracker::SetEnabled(bool enabled)
{
    enabled_ = enabled;
}

void StateTracker::SetHovered(bool hovered)
{
    hovered_ = hovered;
}

void StateTracker::SetPressed(bool pressed)
{
    pressed_ = pressed;
}

void StateTracker::SetFocused(bool focused)
{
    focused_ = focused;
}

void StateTracker::SetLoading(bool loading)
{
    loading_ = loading;
}

void StateTracker::SetSelected(bool selected)
{
    selected_ = selected;
}

void StateTracker::SetChecked(bool checked)
{
    checked_ = checked;
}

bool StateTracker::Update()
{
    ComponentState new_state = ComponentState::kIdle;

    // Priority-based resolution: highest priority first.
    if (!enabled_) {
        new_state = ComponentState::kDisabled;
    } else if (loading_) {
        new_state = ComponentState::kLoading;
    } else if (pressed_) {
        new_state = ComponentState::kPressed;
    } else if (hovered_) {
        new_state = ComponentState::kHover;
    } else if (focused_) {
        new_state = ComponentState::kFocused;
    } else if (selected_) {
        new_state = ComponentState::kSelected;
    } else if (checked_) {
        new_state = ComponentState::kChecked;
    } else {
        new_state = ComponentState::kIdle;
    }

    if (new_state == current_state_) {
        return false;
    }

    ComponentState old_state = current_state_;
    current_state_ = new_state;
    emit StateChanged(old_state, current_state_);
    return true;
}

ComponentState StateTracker::CurrentState() const
{
    return current_state_;
}

bool StateTracker::IsInteractive() const
{
    return current_state_ != ComponentState::kDisabled &&
           current_state_ != ComponentState::kLoading;
}

}  // namespace statemachine
