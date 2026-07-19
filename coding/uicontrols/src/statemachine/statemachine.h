// statemachine.h — Unified state resolution for all interactive components.
//
// Components set boolean flags (hovered, pressed, focused, etc.) from event
// handlers, then call Update() to compute the effective ComponentState.
// Priority: Disabled > Loading > Pressed > Hovered > Focused > Selected > Checked > Idle.
//
// StateTracker emits StateChanged(old, new) so components can react to transitions.

#ifndef CODING_UICONTROLS_SRC_STATEMACHINE_STATEMACHINE_H_
#define CODING_UICONTROLS_SRC_STATEMACHINE_STATEMACHINE_H_

#include <QObject>

namespace statemachine {

// Effective visual state after priority-based resolution.
enum class ComponentState {
    kIdle,
    kHover,
    kPressed,
    kFocused,
    kDisabled,
    kLoading,
    kSelected,
    kChecked,
    kIndeterminate,
    kError,
    kWarning,
    kSuccess
};

class StateTracker : public QObject {
    Q_OBJECT

public:
    explicit StateTracker(QObject* parent = nullptr);

    // Input flag setters — call these from event handlers.
    void SetEnabled(bool enabled);
    void SetHovered(bool hovered);
    void SetPressed(bool pressed);
    void SetFocused(bool focused);
    void SetLoading(bool loading);
    void SetSelected(bool selected);
    void SetChecked(bool checked);

    // Compute and return effective state. Returns true if state actually changed.
    bool Update();

    // Get current effective state without recomputing.
    ComponentState CurrentState() const;

    // Convenience: returns true if state prevents interaction.
    bool IsInteractive() const;

signals:
    void StateChanged(ComponentState oldState, ComponentState newState);

private:
    bool enabled_ = true;
    bool hovered_ = false;
    bool pressed_ = false;
    bool focused_ = false;
    bool loading_ = false;
    bool selected_ = false;
    bool checked_ = false;
    ComponentState current_state_ = ComponentState::kIdle;
};

}  // namespace statemachine

#endif  // CODING_UICONTROLS_SRC_STATEMACHINE_STATEMACHINE_H_
