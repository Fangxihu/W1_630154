/*!
    \copyright Copyright (c) 2019 Qualcomm Technologies International, Ltd.
        All Rights Reserved.
        Qualcomm Technologies International, Ltd. Confidential and Proprietary.
    \version Part of 6.3.0
    \file chain_sbc_mono_no_autosync_decoder.h
    \brief The chain_sbc_mono_no_autosync_decoder chain. This file is generated by C:/qtil/ADK_QCC512x_QCC302x_WIN_6.3.0.154/tools/chaingen/chaingen.py.
*/

#ifndef _CHAIN_SBC_MONO_NO_AUTOSYNC_DECODER_H__
#define _CHAIN_SBC_MONO_NO_AUTOSYNC_DECODER_H__

/*!
    @startuml
        object OPR_LATENCY_BUFFER
        OPR_LATENCY_BUFFER : id = CAP_ID_DOWNLOAD_SWITCHED_PASSTHROUGH_CONSUMER
        object OPR_SBC_DECODER
        OPR_SBC_DECODER : id = CAP_ID_SBC_DECODER
        OPR_SBC_DECODER "IN(0)"<-- "OUT(0)" OPR_LATENCY_BUFFER
        object EPR_SINK_MEDIA #lightgreen
        OPR_LATENCY_BUFFER "IN(0)" <-- EPR_SINK_MEDIA
        object EPR_SOURCE_DECODED_PCM #lightblue
        EPR_SOURCE_DECODED_PCM <-- "OUT(0)" OPR_SBC_DECODER
    @enduml
*/

#include <chain.h>

extern const chain_config_t chain_sbc_mono_no_autosync_decoder_config;

#endif /* _CHAIN_SBC_MONO_NO_AUTOSYNC_DECODER_H__ */

