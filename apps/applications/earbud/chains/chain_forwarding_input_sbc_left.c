/*!
    \copyright Copyright (c) 2019 Qualcomm Technologies International, Ltd.
        All Rights Reserved.
        Qualcomm Technologies International, Ltd. Confidential and Proprietary.
    \version Part of 6.3.0
    \file chain_forwarding_input_sbc_left.c
    \brief The chain_forwarding_input_sbc_left chain. This file is generated by C:/qtil/ADK_QCC512x_QCC302x_WIN_6.3.0.154/tools/chaingen/chaingen.py.
*/

#include <chain_forwarding_input_sbc_left.h>
#include <cap_id_prim.h>
#include <opmsg_prim.h>
#include <hydra_macros.h>
#include <../av_headset_chain_roles.h>
static const operator_config_t operators[] =
{
    MAKE_OPERATOR_CONFIG(CAP_ID_RTP_DECODE, OPR_RTP_DECODER),
    MAKE_OPERATOR_CONFIG(CAP_ID_DOWNLOAD_SWITCHED_PASSTHROUGH_CONSUMER, OPR_SWITCHED_PASSTHROUGH_CONSUMER),
    MAKE_OPERATOR_CONFIG(CAP_ID_SBC_DECODER, OPR_SBC_DECODER),
    MAKE_OPERATOR_CONFIG(CAP_ID_SBC_ENCODER, OPR_SBC_ENCODER)
};

static const operator_endpoint_t inputs[] =
{
    {OPR_RTP_DECODER, EPR_SINK_MEDIA, 0}
};

static const operator_endpoint_t outputs[] =
{
    {OPR_SWITCHED_PASSTHROUGH_CONSUMER, EPR_SOURCE_FORWARDING_MEDIA, 0},
    {OPR_SBC_DECODER, EPR_SOURCE_DECODED_PCM, 0}
};

static const operator_connection_t connections[] =
{
    {OPR_RTP_DECODER, 0, OPR_SBC_DECODER, 0, 1},
    {OPR_SBC_DECODER, 1, OPR_SBC_ENCODER, 0, 1},
    {OPR_SBC_ENCODER, 0, OPR_SWITCHED_PASSTHROUGH_CONSUMER, 0, 1}
};

const chain_config_t chain_forwarding_input_sbc_left_config = {0, 0, operators, 4, inputs, 1, outputs, 2, connections, 3};

