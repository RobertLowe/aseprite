// ASEPRITE gui library
// Copyright (C) 2001-2013  David Capello
//
// This source file is distributed under a BSD-like license, please
// read LICENSE.txt for more information.

#ifndef UI_SCROLL_BAR_H_INCLUDED
#define UI_SCROLL_BAR_H_INCLUDED

#include "base/compiler_specific.h"
#include "ui/widget.h"

namespace ui {

  class ScrollBar : public Widget
  {
  public:
    ScrollBar(int align);

    int getPos() const { return m_pos; }
    void setPos(int pos);

    int getSize() const { return m_size; }
    void setSize(int size);

    // For themes
    void getScrollBarThemeInfo(int* pos, int* len);

  protected:
    // Events
    bool onProcessMessage(Message* msg) OVERRIDE;
    void onPaint(PaintEvent& ev) OVERRIDE;

  private:
    void getScrollBarInfo(int* _pos, int* _len, int* _bar_size, int* _viewport_size);

    int m_pos;
    int m_size;

    static int m_wherepos;
    static int m_whereclick;
  };

} // namespace ui

#endif
