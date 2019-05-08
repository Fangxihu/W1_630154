/*!
    \copyright Copyright (c) 2019 Qualcomm Technologies International, Ltd.
        All Rights Reserved.
        Qualcomm Technologies International, Ltd. Confidential and Proprietary.
    \version Part of 6.3.0
    \file chain_aptx_mono_no_autosync_decoder.c
    \brief The chain_aptx_mono_no_autosync_decoder chain. This file is generated by C:/qtil/ADK_QCC512x_QCC302x_WIN_6.3.0.154/tools/chaingen/chaingen.py.
*/

#include <chain_aptx_mono_no_autosync_decoder.h>
#include <cap_id_prim.h>
#include <opmsg_prim.h>
#include <hydra_macros.h>
#include <../av_headset_chain_roles.h>
static const operator_config_t operators[] =
{
    MAKE_OPERATOR_CONFIG(CAP_ID_DOWNLOAD_SWITCHED_PASSTHROUGH_CONSUMER, OPR_LATENCY_BUFFER),
    MAKE_OPERATOR_CONFIG(CAP_ID_APTX_CLASSIC_MONO_DECODER_NO_AUTOSYNC, OPR_APTX_CLASSIC_MONO_DECODER_NO_AUTOSYNC)
};

static const operator_endpoint_t inputs[] =
{
    {OPR_LATENCY_BUFFER, EPR_SINK_MEDIA, 0}
};

static const operator_endpoint_t outputs[] =
{
    {OPR_APTX_CLASSIC_MONO_DECODER_NO_AUTOSYNC, EPR_SOURCE_DECODED_PCM, 0}
};

static const operator_connection_t connections[] =
{
    {OPR_LATENCY_BUFFER, 0, OPR_APTX_CLASSIC_MONO_DECODER_NO_AUTOSYNC, 0, 1}
};

const chain_config_t chain_aptx_mono_no_autosync_decoder_config = {1, 0, operators, 2, inputs, 1, outputs, 1, connections, 1};

