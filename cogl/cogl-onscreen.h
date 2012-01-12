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
 * License along with this library. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 *
 *
 * Authors:
 *   Robert Bragg <robert@linux.intel.com>
 */

#if !defined(__COGL_H_INSIDE__) && !defined(CLUTTER_COMPILATION)
#error "Only <cogl/cogl.h> can be included directly."
#endif

#ifndef __COGL_ONSCREEN_H
#define __COGL_ONSCREEN_H

#include <cogl/cogl-context.h>
#include <cogl/cogl-framebuffer.h>
#include <glib.h>

G_BEGIN_DECLS

typedef struct _CoglOnscreen CoglOnscreen;
#define COGL_ONSCREEN(X) ((CoglOnscreen *)(X))

CoglOnscreen *
cogl_onscreen_new (CoglContext *context, int width, int height);

#ifdef COGL_HAS_X11
typedef void (*CoglOnscreenX11MaskCallback) (CoglOnscreen *onscreen,
                                             guint32 event_mask,
                                             void *user_data);

/**
 * cogl_x11_onscreen_set_foreign_window_xid:
 * @onscreen: The unallocated framebuffer to associated with an X
 *            window.
 * @xid: The XID of an existing X window
 * @update: A callback that notifies of updates to what Cogl requires
 *          to be in the core X protocol event mask.
 *
 * Ideally we would recommend that you let Cogl be responsible for
 * creating any X window required to back an onscreen framebuffer but
 * if you really need to target a window created manually this
 * function can be called before @onscreen has been allocated to set a
 * foreign XID for your existing X window.
 *
 * Since Cogl needs, for example, to track changes to the size of an X
 * window it requires that certain events be selected for via the core
 * X protocol. This requirement may also be changed asynchronously so
 * you must pass in an @update callback to inform you of Cogl's
 * required event mask.
 *
 * For example if you are using Xlib you could use this API roughly
 * as follows:
 * [{
 * static void
 * my_update_cogl_x11_event_mask (CoglOnscreen *onscreen,
 *                                guint32 event_mask,
 *                                void *user_data)
 * {
 *   XSetWindowAttributes attrs;
 *   MyData *data = user_data;
 *   attrs.event_mask = event_mask | data->my_event_mask;
 *   XChangeWindowAttributes (data->xdpy,
 *                            data->xwin,
 *                            CWEventMask,
 *                            &attrs);
 * }
 *
 * {
 *   *snip*
 *   cogl_x11_onscreen_set_foreign_window_xid (onscreen,
 *                                             data->xwin,
 *                                             my_update_cogl_x11_event_mask,
 *                                             data);
 *   *snip*
 * }
 * }]
 *
 * Since: 2.0
 * Stability: Unstable
 */
#define cogl_x11_onscreen_set_foreign_window_xid \
  cogl_x11_onscreen_set_foreign_window_xid_EXP
void
cogl_x11_onscreen_set_foreign_window_xid (CoglOnscreen *onscreen,
                                          guint32 xid,
                                          CoglOnscreenX11MaskCallback update,
                                          void *user_data);

#define cogl_x11_onscreen_get_window_xid cogl_x11_onscreen_get_window_xid_EXP
guint32
cogl_x11_onscreen_get_window_xid (CoglOnscreen *onscreen);

#define cogl_x11_onscreen_get_visual_xid cogl_x11_onscreen_get_visual_xid_EXP
guint32
cogl_x11_onscreen_get_visual_xid (CoglOnscreen *onscreen);
#endif /* COGL_HAS_X11 */

#ifdef COGL_HAS_WIN32_SUPPORT
#define cogl_win32_onscreen_set_foreign_window \
  cogl_win32_onscreen_set_foreign_window_EXP
void
cogl_win32_onscreen_set_foreign_window (CoglOnscreen *onscreen,
                                        HWND hwnd);

#define cogl_win32_onscreen_get_window cogl_win32_onscreen_get_window_EXP
HWND
cogl_win32_onscreen_get_window (CoglOnscreen *onscreen);
#endif /* COGL_HAS_WIN32_SUPPORT */

#if defined (COGL_HAS_EGL_PLATFORM_WAYLAND_SUPPORT)
struct wl_surface *
cogl_wayland_onscreen_get_surface (CoglOnscreen *onscreen);
struct wl_shell_surface *
cogl_wayland_onscreen_get_shell_surface (CoglOnscreen *onscreen);

void
cogl_wayland_onscreen_resize (CoglOnscreen *onscreen,
                              gint          width,
                              gint          height,
                              gint          offset_x,
                              gint          offset_y);
#endif /* COGL_HAS_EGL_PLATFORM_WAYLAND_SUPPORT */

#define cogl_onscreen_set_swap_throttled cogl_onscreen_set_swap_throttled_EXP
void
cogl_onscreen_set_swap_throttled (CoglOnscreen *onscreen,
                                  gboolean throttled);

/**
 * cogl_onscreen_show:
 * @onscreen: The onscreen framebuffer to make visible
 *
 * This requests to make @onscreen visible to the user.
 *
 * Actually the precise semantics of this function depend on the
 * window system currently in use, and if you don't have a
 * multi-windowining system this function may in-fact do nothing.
 *
 * This function will implicitly allocate the given @onscreen
 * framebuffer before showing it if it hasn't already been allocated.
 *
 * <note>Since Cogl doesn't explicitly track the visibility status of
 * onscreen framebuffers it wont try to avoid redundant window system
 * requests e.g. to show an already visible window. This also means
 * that it's acceptable to alternatively use native APIs to show and
 * hide windows without confusing Cogl.</note>
 *
 * Since: 2.0
 * Stability: Unstable
 */
#define cogl_onscreen_show cogl_onscreen_show_EXP
void
cogl_onscreen_show (CoglOnscreen *onscreen);

/**
 * cogl_onscreen_hide:
 * @onscreen: The onscreen framebuffer to make invisible
 *
 * This requests to make @onscreen invisible to the user.
 *
 * Actually the precise semantics of this function depend on the
 * window system currently in use, and if you don't have a
 * multi-windowining system this function may in-fact do nothing.
 *
 * This function does not implicitly allocate the given @onscreen
 * framebuffer before hiding it.
 *
 * <note>Since Cogl doesn't explicitly track the visibility status of
 * onscreen framebuffers it wont try to avoid redundant window system
 * requests e.g. to show an already visible window. This also means
 * that it's acceptable to alternatively use native APIs to show and
 * hide windows without confusing Cogl.</note>
 *
 * Since: 2.0
 * Stability: Unstable
 */
#define cogl_onscreen_hide cogl_onscreen_hide_EXP
void
cogl_onscreen_hide (CoglOnscreen *onscreen);

/* XXX: Actually should this be renamed too cogl_onscreen_swap_buffers()? */
#define cogl_framebuffer_swap_buffers cogl_framebuffer_swap_buffers_EXP
/**
 * cogl_framebuffer_swap_buffers:
 * @framebuffer: A #CoglFramebuffer
 *
 * Swaps the current back buffer being rendered too, to the front for display.
 *
 * This function also implicitly discards the contents of the color, depth and
 * stencil buffers as if cogl_framebuffer_discard_buffers() were used. The
 * significance of the discard is that you should not expect to be able to
 * start a new frame that incrementally builds on the contents of the previous
 * frame.
 *
 * Since: 1.8
 * Stability: unstable
 */
void
cogl_framebuffer_swap_buffers (CoglFramebuffer *framebuffer);

#define cogl_framebuffer_swap_region cogl_framebuffer_swap_region_EXP
/**
 * cogl_framebuffer_swap_region:
 * @framebuffer: A #CoglFramebuffer
 * @rectangles: An array of integer 4-tuples representing rectangles as
 *              (x, y, width, height) tuples.
 * @n_rectangles: The number of 4-tuples to be read from @rectangles
 *
 * Swaps a region of the back buffer being rendered too, to the front for
 * display.  @rectangles represents the region as array of @n_rectangles each
 * defined by 4 sequential (x, y, width, height) integers.
 *
 * This function also implicitly discards the contents of the color, depth and
 * stencil buffers as if cogl_framebuffer_discard_buffers() were used. The
 * significance of the discard is that you should not expect to be able to
 * start a new frame that incrementally builds on the contents of the previous
 * frame.
 *
 * Since: 1.8
 * Stability: unstable
 */
void
cogl_framebuffer_swap_region (CoglFramebuffer *framebuffer,
                              const int *rectangles,
                              int n_rectangles);


typedef void (*CoglSwapBuffersNotify) (CoglFramebuffer *framebuffer,
                                       void *user_data);

#define cogl_framebuffer_add_swap_buffers_callback \
  cogl_framebuffer_add_swap_buffers_callback_EXP
unsigned int
cogl_framebuffer_add_swap_buffers_callback (CoglFramebuffer *framebuffer,
                                            CoglSwapBuffersNotify callback,
                                            void *user_data);

#define cogl_framebuffer_remove_swap_buffers_callback \
  cogl_framebuffer_remove_swap_buffers_callback_EXP
void
cogl_framebuffer_remove_swap_buffers_callback (CoglFramebuffer *framebuffer,
                                               unsigned int id);

G_END_DECLS

#endif /* __COGL_ONSCREEN_H */
