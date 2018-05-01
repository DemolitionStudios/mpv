#pragma once

#include "common/global.h"
#include "video/out/gpu/context.h"

static bool d3d11_init(struct ra_ctx *ctx);
static void d3d11_uninit(struct ra_ctx *ctx);
static bool d3d11_start_frame(struct ra_swapchain *sw, struct ra_fbo *out_fbo);
static bool d3d11_submit_frame(struct ra_swapchain *sw, const struct vo_frame *frame);
