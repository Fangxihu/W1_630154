/*!
    \copyright Copyright (c) 2019 Qualcomm Technologies International, Ltd.
        All Rights Reserved.
        Qualcomm Technologies International, Ltd. Confidential and Proprietary.
    \version Part of 6.3.0
    \file chain_prompt_pcm.h
    \brief The chain_prompt_pcm chain. This file is generated by E:/qtil/ADK_QCC512x_QCC302x_WIN_6.3.0.154/tools/chaingen/chaingen.py.
*/

#ifndef _CHAIN_PROMPT_PCM_H__
#define _CHAIN_PROMPT_PCM_H__

/*!
    @startuml
        object OPR_TONE_PROMPT_RESAMPLER
        OPR_TONE_PROMPT_RESAMPLER : id = CAP_ID_IIR_RESAMPLER
        object EPR_PROMPT_IN #lightgreen
        OPR_TONE_PROMPT_RESAMPLER "IN(0)" <-- EPR_PROMPT_IN
        object EPR_TONE_PROMPT_CHAIN_OUT #lightblue
        EPR_TONE_PROMPT_CHAIN_OUT <-- "OUT(0)" OPR_TONE_PROMPT_RESAMPLER
    @enduml
*/

#include <chain.h>

extern const chain_config_t chain_prompt_pcm_config;

#endif /* _CHAIN_PROMPT_PCM_H__ */

