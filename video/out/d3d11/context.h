#pragma once

#include "common/global.h"
#include "video/out/gpu/context.h"

bool d3d11_init(struct ra_ctx *ctx);
void d3d11_uninit(struct ra_ctx *ctx);
bool d3d11_start_frame(struct ra_swapchain *sw, struct ra_fbo *out_fbo);
bool d3d11_submit_frame(struct ra_swapchain *sw, const struct vo_frame *frame);
