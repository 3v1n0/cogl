/*
 * Cogl
 *
 * An object oriented GL/GLES Abstraction/Utility Layer
 *
 * Copyright (C) 2010 Intel Corporation.
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

#ifndef __COGL_PRIVATE_H__
#define __COGL_PRIVATE_H__

#include <cogl/cogl-pipeline.h>

#include "cogl-context.h"

G_BEGIN_DECLS

gboolean
_cogl_gl_update_features (CoglContext *context,
                          GError **error);

gboolean
_cogl_gles_update_features (CoglContext *context,
                            GError **error);

gboolean
_cogl_check_extension (const char *name, const char *ext);

void
_cogl_clear (const CoglColor *color, unsigned long buffers);

void
_cogl_read_pixels_with_rowstride (int x,
                                  int y,
                                  int width,
                                  int height,
                                  CoglReadPixelsFlags source,
                                  CoglPixelFormat format,
                                  guint8 *pixels,
                                  int rowstride);

void
_cogl_init (void);

void
_cogl_push_source (CoglPipeline *pipeline, gboolean enable_legacy);

gboolean
_cogl_get_enable_legacy_state (void);

/*
 * _cogl_pixel_format_get_bytes_per_pixel:
 * @format: a #CoglPixelFormat
 *
 * Queries how many bytes a pixel of the given @format takes.
 *
 * Return value: The number of bytes taken for a pixel of the given
 *               @format.
 */
int
_cogl_pixel_format_get_bytes_per_pixel (CoglPixelFormat format);

/*
 * _cogl_pixel_format_has_aligned_components:
 * @format: a #CoglPixelFormat
 *
 * Queries whether the ordering of the components for the given
 * @format depend on the endianness of the host CPU or if the
 * components can be accessed using bit shifting and bitmasking by
 * loading a whole pixel into a word.
 *
 * Return value: %TRUE if you need to consider the host CPU
 *               endianness when dealing with the given @format
 *               else %FALSE.
 */
gboolean
_cogl_pixel_format_is_endian_dependant (CoglPixelFormat format);

G_END_DECLS

#endif /* __COGL_PRIVATE_H__ */
