#ifndef _USER_SPP_H_
#define _USER_SPP_H_

#ifdef ENABLE_SPP
#include <spp_common.h>


typedef enum {
    serverInitialising = 0x00,
    serverStopped      = 0x80,
    serverUnconnected  = 0xC0,
    serverConnected    = 0xE0
} server_state;    

typedef struct sppTaskData
{
    TaskData        spp_task;
    bdaddr          bd_addr;
    server_state    state;
    SPP             *spp;
} sppTaskData;

//static APP_SPPS_T theApp;
extern void appSppInit(void);

extern void spps_handler(Task task, MessageId id, Message message);


#endif /* ENABLE_SPP */
#endif /* _USER_SPP_H_ */
