/* ASEPRITE
 * Copyright (C) 2001-2013  David Capello
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "config.h"

#include "commands/filters/filter_preview.h"

#include "commands/filters/filter_manager_impl.h"
#include "raster/sprite.h"
#include "ui/manager.h"
#include "ui/message.h"
#include "ui/widget.h"
#include "util/render.h"

using namespace ui;

FilterPreview::FilterPreview(FilterManagerImpl* filterMgr)
  : Widget(JI_WIDGET)
  , m_filterMgr(filterMgr)
  , m_timer(1, this)
{
  setVisible(false);
}

FilterPreview::~FilterPreview()
{
  stop();
}

void FilterPreview::stop()
{
  m_filterMgr = NULL;
  m_timer.stop();
}

void FilterPreview::restartPreview()
{
  m_filterMgr->beginForPreview();
  m_timer.start();
}

FilterManagerImpl* FilterPreview::getFilterManager() const
{
  return m_filterMgr;
}

bool FilterPreview::onProcessMessage(Message* msg)
{
  switch (msg->type) {

    case JM_OPEN:
      RenderEngine::setPreviewImage(m_filterMgr->getLayer(),
                                    m_filterMgr->getDestinationImage());
      break;

    case JM_CLOSE:
      RenderEngine::setPreviewImage(NULL, NULL);

      // Stop the preview timer.
      m_timer.stop();
      break;

    case JM_TIMER:
      if (m_filterMgr) {
        if (m_filterMgr->applyStep())
          m_filterMgr->flush();
        else
          m_timer.stop();
      }
      break;
  }

  return Widget::onProcessMessage(msg);
}
