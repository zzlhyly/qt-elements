#ifndef CODING_UICONTROLS_SRC_THEME_ICON_H_
#define CODING_UICONTROLS_SRC_THEME_ICON_H_

#include <QChar>

namespace theme {
namespace icon {

inline QChar close()       { return QChar(0x00D7); }  // ×
inline QChar success()     { return QChar(0x2713); }  // ✓
inline QChar info()        { return QChar(0x2139); }  // ℹ
inline QChar warning()     { return QChar(0x26A0); }  // ⚠
inline QChar error()       { return QChar(0x2715); }  // ✕
inline QChar arrowDown()   { return QChar(0x25BC); }  // ▼
inline QChar arrowUp()     { return QChar(0x25B2); }  // ▲
inline QChar arrowRight()  { return QChar(0x25B6); }  // ▶
inline QChar search()      { return QChar(0x1F50D); } // 🔍
inline QChar star()        { return QChar(0x2605); }  // ★
inline QChar starEmpty()   { return QChar(0x2606); }  // ☆
inline QChar eye()         { return QChar(0x25C9); }  // ◉
inline QChar eyeSlash()    { return QChar(0x25CB); }  // ○
inline QChar circle()      { return QChar(0x25CF); }  // ●
inline QChar plus()        { return QChar(0x002B); }  // +

} // namespace icon
} // namespace theme

#endif // CODING_UICONTROLS_SRC_THEME_ICON_H_
