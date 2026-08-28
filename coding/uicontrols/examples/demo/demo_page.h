// demo_page.h - Builds the scrollable gallery page for one component group.
//
// Every demo is rendered as a titled section, so individual demo files only
// have to return their own content widget.

#ifndef UICONTROLS_EXAMPLES_DEMO_DEMO_PAGE_H_
#define UICONTROLS_EXAMPLES_DEMO_DEMO_PAGE_H_

class QWidget;

namespace demo {

class DemoGroup;

// Creates a scroll area listing every entry of |group|, each preceded by its
// section title. The returned widget has no parent.
QWidget* CreateDemoPage(const DemoGroup& group);

}  // namespace demo

#endif  // UICONTROLS_EXAMPLES_DEMO_DEMO_PAGE_H_
