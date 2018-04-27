/*
 * muxing using libavformat
 *
 * Copyright (C) 2011 Rudolf Polzer <divVerent@xonotic.org>
 *
 * This file is part of mpv.
 *
 * mpv is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * mpv is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with mpv.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MPLAYER_ENCODE_LAVC_H
#define MPLAYER_ENCODE_LAVC_H

#include <pthread.h>

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avstring.h>
#include <libavutil/pixfmt.h>
#include <libavutil/opt.h>
#include <libavutil/mathematics.h>

#include "encode.h"
#include "video/csputils.h"

struct encode_lavc_context {
    struct mpv_global *global;
    struct encode_opts *options;
    struct mp_log *log;
    struct mp_tags *metadata;

    // All entry points must be guarded with the lock. Functions called by
    // the playback core lock this automatically, but ao_lavc.c and vo_lavc.c
    // must lock manually before accessing state.
    pthread_mutex_t lock;

    float vo_fps;

    // FFmpeg contexts.
    AVFormatContext *avc;
    AVStream *vst;
    AVStream *ast;
    AVCodecContext *vcc;
    AVCodecContext *acc;

    // these are processed from the options
    AVRational timebase;
    AVCodec *vc;
    AVCodec *ac;
    AVDictionary *foptions;
    AVDictionary *aoptions;
    AVDictionary *voptions;

    // values created during encoding
    int header_written; // -1 means currently writing

    // sync to audio mode
    double audio_pts_offset;
    double last_video_in_pts;

    double last_audio_in_pts;
    int64_t samples_since_last_pts;

    // anti discontinuity mode
    double next_in_pts;
    double discontinuity_pts_offset;

    long long abytes;
    long long vbytes;
    struct stream *twopass_bytebuffer_a;
    struct stream *twopass_bytebuffer_v;
    double t0;
    unsigned int frames;
    double audioseconds;

    bool expect_video;
    bool expect_audio;
    bool video_first;
    bool audio_first;

    // has encoding failed?
    bool failed;
    bool finished;
};

// interface for vo/ao drivers
int encode_lavc_alloc_stream(struct encode_lavc_context *ctx,
                             enum AVMediaType mt, AVStream **stream_out,
                             AVCodecContext **codec_out);
void encode_lavc_write_stats(struct encode_lavc_context *ctx,
                             AVCodecContext *stream);
int encode_lavc_write_frame(struct encode_lavc_context *ctx, AVStream *stream,
                            AVPacket *packet);
int encode_lavc_supports_pixfmt(struct encode_lavc_context *ctx, enum AVPixelFormat format);
int encode_lavc_open_codec(struct encode_lavc_context *ctx,
                           AVCodecContext *codec);
int encode_lavc_available(struct encode_lavc_context *ctx);
int encode_lavc_timesyncfailed(struct encode_lavc_context *ctx);
int encode_lavc_start(struct encode_lavc_context *ctx); // returns 1 on success
int encode_lavc_oformat_flags(struct encode_lavc_context *ctx);
double encode_lavc_getoffset(struct encode_lavc_context *ctx,
                             AVCodecContext *codec);
void encode_lavc_fail(struct encode_lavc_context *ctx, const char *format, ...); // report failure of encoding

#endif
