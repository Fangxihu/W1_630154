/*!
    \copyright Copyright (c) 2019 Qualcomm Technologies International, Ltd.
        All Rights Reserved.
        Qualcomm Technologies International, Ltd. Confidential and Proprietary.
    \version Part of 6.3.0
    \file chain_micfwd_nb.c
    \brief The chain_micfwd_nb chain. This file is generated by C:/qtil/ADK_QCC512x_QCC302x_WIN_6.3.0.154/tools/chaingen/chaingen.py.
*/

#include <chain_micfwd_nb.h>
#include <cap_id_prim.h>
#include <opmsg_prim.h>
#include <hydra_macros.h>
#include <../av_headset_chain_roles.h>
static const operator_config_t operators[] =
{
    MAKE_OPERATOR_CONFIG_PRIORITY_MEDIUM(CAP_ID_SCO_RCV, OPR_SCO_RECEIVE),
    MAKE_OPERATOR_CONFIG_PRIORITY_HIGH(CAP_ID_SCO_SEND, OPR_SCO_SEND),
    MAKE_OPERATOR_CONFIG(CAP_ID_CVC_RECEIVE_NB, OPR_CVC_RECEIVE),
    MAKE_OPERATOR_CONFIG(CAP_ID_SPLITTER, OPR_SCOFWD_SPLITTER),
    MAKE_OPERATOR_CONFIG(CAP_ID_DOWNLOAD_SWITCHED_PASSTHROUGH_CONSUMER, OPR_SWITCHED_PASSTHROUGH_CONSUMER),
    MAKE_OPERATOR_CONFIG(CAP_ID_DOWNLOAD_ASYNC_WBS_ENC, OPR_SCOFWD_SEND),
    MAKE_OPERATOR_CONFIG(CAP_ID_CVCHS1MIC_SEND_NB, OPR_CVC_SEND),
    MAKE_OPERATOR_CONFIG(CAP_ID_IIR_RESAMPLER, OPR_SCO_UP_SAMPLE),
    MAKE_OPERATOR_CONFIG(CAP_ID_IIR_RESAMPLER, OPR_MIC_DOWN_SAMPLE),
    MAKE_OPERATOR_CONFIG(CAP_ID_SOURCE_SYNC, OPR_SOURCE_SYNC),
    MAKE_OPERATOR_CONFIG(CAP_ID_VOL_CTRL_VOL, OPR_VOLUME_CONTROL),
    MAKE_OPERATOR_CONFIG(CAP_ID_DOWNLOAD_AEC_REFERENCE, OPR_SCO_AEC),
    MAKE_OPERATOR_CONFIG(CAP_ID_DOWNLOAD_ASYNC_WBS_DEC, OPR_MICFWD_RECV),
    MAKE_OPERATOR_CONFIG(CAP_ID_DOWNLOAD_SWITCHED_PASSTHROUGH_CONSUMER, OPR_MICFWD_RECV_SPC),
    MAKE_OPERATOR_CONFIG(CAP_ID_DOWNLOAD_SWITCHED_PASSTHROUGH_CONSUMER, OPR_MICFWD_SPC_SWITCH)
};

static const operator_endpoint_t inputs[] =
{
    {OPR_SCO_RECEIVE, EPR_SCO_FROM_AIR, 0},
    {OPR_VOLUME_CONTROL, EPR_VOLUME_AUX, 1},
    {OPR_MICFWD_RECV_SPC, EPR_MICFWD_RX_OTA, 0},
    {OPR_SCO_AEC, EPR_SCO_MIC1, 2}
};

static const operator_endpoint_t outputs[] =
{
    {OPR_SCO_AEC, EPR_SCO_SPEAKER, 1},
    {OPR_SCO_SEND, EPR_SCO_TO_AIR, 0},
    {OPR_SWITCHED_PASSTHROUGH_CONSUMER, EPR_SCOFWD_TX_OTA, 0}
};

static const operator_connection_t connections[] =
{
    {OPR_SCO_RECEIVE, 0, OPR_CVC_RECEIVE, 0, 1},
    {OPR_CVC_RECEIVE, 0, OPR_SOURCE_SYNC, 0, 1},
    {OPR_SOURCE_SYNC, 0, OPR_SCOFWD_SPLITTER, 0, 1},
    {OPR_VOLUME_CONTROL, 0, OPR_SCO_AEC, 0, 1},
    {OPR_SCOFWD_SPLITTER, 0, OPR_VOLUME_CONTROL, 0, 1},
    {OPR_SCOFWD_SPLITTER, 1, OPR_SCO_UP_SAMPLE, 0, 1},
    {OPR_SCO_UP_SAMPLE, 0, OPR_SCOFWD_SEND, 0, 1},
    {OPR_SCOFWD_SEND, 0, OPR_SWITCHED_PASSTHROUGH_CONSUMER, 0, 1},
    {OPR_SCO_AEC, 3, OPR_CVC_SEND, 1, 1},
    {OPR_SCO_AEC, 0, OPR_CVC_SEND, 0, 1},
    {OPR_CVC_SEND, 0, OPR_MICFWD_SPC_SWITCH, 0, 1},
    {OPR_MICFWD_RECV_SPC, 0, OPR_MICFWD_RECV, 0, 1},
    {OPR_MICFWD_RECV, 0, OPR_MIC_DOWN_SAMPLE, 0, 1},
    {OPR_MIC_DOWN_SAMPLE, 0, OPR_MICFWD_SPC_SWITCH, 1, 1},
    {OPR_MICFWD_SPC_SWITCH, 0, OPR_SCO_SEND, 0, 1}
};

const chain_config_t chain_micfwd_nb_config = {1, 0, operators, 15, inputs, 4, outputs, 3, connections, 15};

