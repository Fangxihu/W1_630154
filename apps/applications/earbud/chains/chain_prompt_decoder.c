/*!
    \copyright Copyright (c) 2019 Qualcomm Technologies International, Ltd.
        All Rights Reserved.
        Qualcomm Technologies International, Ltd. Confidential and Proprietary.
    \version Part of 6.3.0
    \file chain_prompt_decoder.c
    \brief The chain_prompt_decoder chain. This file is generated by C:/qtil/ADK_QCC512x_QCC302x_WIN_6.3.0.154/tools/chaingen/chaingen.py.
*/

#include <chain_prompt_decoder.h>
#include <cap_id_prim.h>
#include <opmsg_prim.h>
#include <hydra_macros.h>
#include <../av_headset_chain_roles.h>
static const operator_config_t operators[] =
{
    MAKE_OPERATOR_CONFIG(CAP_ID_SBC_DECODER, OPR_PROMPT_DECODER),
    MAKE_OPERATOR_CONFIG(CAP_ID_IIR_RESAMPLER, OPR_TONE_PROMPT_RESAMPLER)
};

static const operator_endpoint_t inputs[] =
{
    {OPR_PROMPT_DECODER, EPR_PROMPT_IN, 0}
};

static const operator_endpoint_t outputs[] =
{
    {OPR_TONE_PROMPT_RESAMPLER, EPR_TONE_PROMPT_CHAIN_OUT, 0}
};

static const operator_connection_t connections[] =
{
    {OPR_PROMPT_DECODER, 0, OPR_TONE_PROMPT_RESAMPLER, 0, 1}
};

const chain_config_t chain_prompt_decoder_config = {0, 0, operators, 2, inputs, 1, outputs, 1, connections, 1};

