/*!
    \copyright Copyright (c) 2019 Qualcomm Technologies International, Ltd.
        All Rights Reserved.
        Qualcomm Technologies International, Ltd. Confidential and Proprietary.
    \version Part of 6.3.0
    \file chain_tone_gen_no_iir.h
    \brief The chain_tone_gen_no_iir chain. This file is generated by C:/qtil/ADK_QCC512x_QCC302x_WIN_6.3.0.154/tools/chaingen/chaingen.py.
*/

#ifndef _CHAIN_TONE_GEN_NO_IIR_H__
#define _CHAIN_TONE_GEN_NO_IIR_H__

/*!
    @startuml
        object OPR_TONE_GEN
        OPR_TONE_GEN : id = CAP_ID_RINGTONE_GENERATOR
        object EPR_TONE_PROMPT_CHAIN_OUT #lightblue
        EPR_TONE_PROMPT_CHAIN_OUT <-- "OUT(0)" OPR_TONE_GEN
    @enduml
*/

#include <chain.h>

extern const chain_config_t chain_tone_gen_no_iir_config;

#endif /* _CHAIN_TONE_GEN_NO_IIR_H__ */
