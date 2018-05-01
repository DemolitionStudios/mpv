/* Copyright (C) 2018 the mpv developers
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef MPV_CLIENT_API_RENDER_D3D11_H_
#define MPV_CLIENT_API_RENDER_D3D11_H_

#include "render.h"

#ifdef __cplusplus
extern "C" {
#endif
                             
/**
 * For initializing the mpv D3D11 state via MPV_RENDER_PARAM_D3D11_INIT_PARAMS.
 */
typedef struct mpv_d3d11_init_params {
    int fake;
} mpv_d3d11_init_params;

