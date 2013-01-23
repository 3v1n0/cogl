/*
 * Cogl
 *
 * An object oriented GL/GLES Abstraction/Utility Layer
 *
 * Copyright (C) 2011 Intel Corporation.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 */

#ifndef __COGL_ONSCREEN_PRIVATE_H
#define __COGL_ONSCREEN_PRIVATE_H

#include "cogl-framebuffer-private.h"
#include "cogl-queue.h"

#include <glib.h>

#ifdef COGL_HAS_WIN32_SUPPORT
#include <windows.h>
#endif

#define COGL_ONSCREEN_MAX_FRAME_TIMINGS 16

typedef struct _CoglSwapBuffersNotifyEntry CoglSwapBuffersNotifyEntry;

COGL_TAILQ_HEAD (CoglSwapBuffersNotifyList, CoglSwapBuffersNotifyEntry);

struct _CoglSwapBuffersNotifyEntry
{
  COGL_TAILQ_ENTRY (CoglSwapBuffersNotifyEntry) list_node;

  CoglSwapBuffersNotify callback;
  void *user_data;
  unsigned int id;
};

typedef struct _CoglResizeNotifyEntry CoglResizeNotifyEntry;

COGL_TAILQ_HEAD (CoglResizeNotifyList, CoglResizeNotifyEntry);

struct _CoglResizeNotifyEntry
{
  COGL_TAILQ_ENTRY (CoglResizeNotifyEntry) list_node;

  CoglOnscreenResizeCallback callback;
  void *user_data;
  unsigned int id;
};

typedef struct _CoglFrameTimingsCallbackEntry CoglFrameTimingsCallbackEntry;

COGL_TAILQ_HEAD (CoglFrameTimingsCallbackList, CoglFrameTimingsCallbackEntry);

struct _CoglFrameTimingsCallbackEntry
{
  COGL_TAILQ_ENTRY (CoglFrameTimingsCallbackEntry) list_node;

  CoglFrameTimingsCallback callback;
  void *user_data;
  unsigned int id;
};

struct _CoglOnscreen
{
  CoglFramebuffer  _parent;

#ifdef COGL_HAS_X11_SUPPORT
  uint32_t foreign_xid;
  CoglOnscreenX11MaskCallback foreign_update_mask_callback;
  void *foreign_update_mask_data;
#endif

#ifdef COGL_HAS_WIN32_SUPPORT
  HWND foreign_hwnd;
#endif

  CoglBool swap_throttled;

  CoglSwapBuffersNotifyList swap_callbacks;

  CoglBool resizable;
  CoglResizeNotifyList resize_callbacks;

  CoglFrameTimingsCallbackList frame_timings_callbacks;

  int64_t frame_counter;
  int64_t swap_frame_counter; /* frame counter at last all to
                               * cogl_onscreen_swap_region() or
                               * cogl_onscreen_swap_buffers() */
  CoglFrameTimings *frame_timings[COGL_ONSCREEN_MAX_FRAME_TIMINGS];
  int current_frame_timings;
  int n_frame_timings;

  void *winsys;
};

CoglOnscreen *
_cogl_onscreen_new (void);

void
_cogl_framebuffer_winsys_update_size (CoglFramebuffer *framebuffer,
                                      int width, int height);

void
_cogl_onscreen_notify_swap_buffers (CoglOnscreen *onscreen);

void
_cogl_onscreen_notify_resize (CoglOnscreen *onscreen);

void
_cogl_onscreen_notify_frame_timings (CoglOnscreen *onscreen);

#endif /* __COGL_ONSCREEN_PRIVATE_H */
