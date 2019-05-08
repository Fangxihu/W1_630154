/*
user spp
fang 20190505
*/

#ifdef ENABLE_SPP
#include "av_headset.h"
#include "av_headset_log.h"

#include "user_spp.h"

#include <panic.h>
#include <spps.h>
#include <stream.h>

#define USER_DEBUG_SPP

#ifdef USER_DEBUG_SPP
#define SPP_LOG(x)         DEBUG_LOG(x)
#define SPP_LOGF(x, ...)   DEBUG_LOGF(x, __VA_ARGS__)
#else
#define SPP_LOG(x)
#define SPP_LOGF(x)
#endif

static void setServerState(server_state new_state);

static void setServerState(server_state new_state)
{
    sppTaskData *theSpp = appGetSpp();

    theSpp->state = new_state;
}

/*! Initialise the SPP Module */
void appSppInit(void)
{
    appGetSpp()->spp_task.handler = spps_handler;
	
	SPP_LOG("appSppInit\n");
	
	setServerState(serverStopped);	 
	
	/* Start the SPP Server  */
	SppStartService(appGetSppTask());
}

#if 0
void spp_handler(Task task, MessageId id, Message message)
{
    switch(id)
    {
   
            case SPP_START_SERVICE_CFM:
            {
                SPP_START_SERVICE_CFM_T *sssc = (SPP_START_SERVICE_CFM_T *)message;
                SPP_DEBUG(("SPP_START_SERVICE_CFM :-"));
                uart_print("+SPPSTAT=0\r\n");
                if (sssc->status == spp_start_success)
                {
                    SPP_DEBUG(("success\n"));
                    SPP_DEBUG(("Memory Slots: %d\n", VmGetAvailableAllocations()));
                    /* Now wait for an SPP_CONNECT_IND */
                    setServerState(serverUnconnected);
                }
                else
                {
                    SPP_DEBUG(("failure: %d\n", sssc->status));
                    Panic();
                }
            }
            break;
            
        case SPP_STOP_SERVICE_CFM:
            {
                SPP_STOP_SERVICE_CFM_T *sssc = (SPP_STOP_SERVICE_CFM_T *)message;
                SPP_DEBUG(("SPP_STOP_SERVICE_CFM :-"));
                if (sssc->status == spp_stop_success)
                {
                    SPP_DEBUG(("success\n"));
                    SPP_DEBUG(("Memory Slots: %d\n", VmGetAvailableAllocations()));

                    setServerState(serverStopped);
                }
                else
                {
                    SPP_DEBUG(("failure: %d\n", sssc->status));
                    Panic();
                }
            }
            break;
       
        case SPP_CONNECT_IND:
            {
                SPP_CONNECT_IND_T *ind = (SPP_CONNECT_IND_T *)message; 
                SPP_DEBUG(("SPP_CONNECT_IND\n"));
                
               
                /* Respond to accept the connection.*/
                SppConnectResponse(
                        task, 
                        &theSink.local_bd_addr, 
                        1,                      /* Accept the connection */
                        ind->sink,
                        ind->server_channel,
                        0                       /* Use default payload size */
                        );
            }
            break;                
    
        case SPP_SERVER_CONNECT_CFM:
            {
                SPP_SERVER_CONNECT_CFM_T *sscc = (SPP_SERVER_CONNECT_CFM_T *)message;
                SPP_DEBUG(("SPP_SERVER_CONNECT_CFM_T\n"));
                uart_print("+SPPSTAT=2\r\n");
                if (spp_connect_success == sscc->status)
                {

                    theSink.spp   = sscc->spp;

                    PanicNull(sscc->sink);
            
                    theSink.rfcommSink = sscc->sink;
                    if(stateManagerGetState() == deviceConnected) 
                    ConnectionWriteScanEnable(hci_scan_enable_off);
                    
                    /* Connect the SPP Sink to the Uart Source and visa-versa */                    

                    setServerState(serverConnected);
                   /* MessageSendLater( &theSink.task , Event_SppNotify , 0,1000 ) ;*/
                }
                else
                {
                    SPP_DEBUG(("failure: %d\n", sscc->status));
                    Panic();
                }
            }
            break;

        case SPP_DISCONNECT_CFM:
            {
                SPP_DISCONNECT_CFM_T *sdc = (SPP_DISCONNECT_CFM_T *)message;
                SPP_DEBUG(("SPP_DISCONNECT_CFM :-"));
                if (sdc->status == spp_disconnect_success)
                {
                    SPP_DEBUG(("Success!\n"));
                }
                else
                {
                    SPP_DEBUG(("reason %d\n", sdc->status));
                }
                

                setServerState(serverUnconnected);
                ConnectionWriteScanEnable(hci_scan_enable_page);
                SPP_DEBUG(("SPP Server is now unconnected\n"));
            }
            break;
            
        case SPP_MESSAGE_MORE_DATA:
         {
            uint8 i;
            Source src = ((SPP_MESSAGE_MORE_DATA_T*)message)->source;
            const uint8 *s = SourceMap(src);
            uint16 len = SourceBoundary(src);
            char buff[20];
            
            SPP_DEBUG(("\n=============\n"));
            sprintf(buff,"+SPPDATA=%d\r\n",len);
            uart_send(buff, strlen(buff));
            
            for(i=0;i<len;i++)
            {
                SPP_DEBUG((" 0x%x",*(s+i)));                
            }   
            
            uart_send(s, len);
            uart_print("\r\n");
            SourceDrop(src, len);
            
         }
            break;
            
        case SPP_DISCONNECT_IND:
            {
                SPP_DISCONNECT_IND_T *sdi = (SPP_DISCONNECT_IND_T *)message;
                SPP_DEBUG(("SPP_DISCONNECT_IND - status %d ", sdi->status));
                SPP_DEBUG(("The SPP Client disconnected!\n"));
                uart_print("+SPPSTAT=0\r\n");
                SppDisconnectResponse(sdi->spp);

                setServerState(serverUnconnected);
            }
            break;            
            
            
 
        
        default:
            SPP_DEBUG(("Unhandled Message: %d, 0x%0X\n", id, id));
            break;        
    }
}
#endif


void spps_handler(Task task, MessageId id, Message message)
{
    sppTaskData *theSpp = appGetSpp();

    switch(id)
    {
#if 0
        case SERVER_DISCONNECT:
            if (theSpp->state == serverConnected)
            {
                PRINT("Disconnecting from the SPP Client.\n");
                SppDisconnectRequest(theSpp->state);
            }
            else 
                PRINT("Can not Disconnect in this state: %d\n", theSpp->state);
            break;
            
        case START_STOP_SERVICE:
            switch (theSpp->state)
            {
                case serverStopped:
                    PRINT("Starting the SPP server service.\n");
                    SppStartService(task);
                    break;
                case serverUnconnected:
                    PRINT("Stopping the SPP server service.\n");
                    SppStopService(task);
                    break;
                default:
                    PRINT("Cannot start or stop the SPP server in this state: %d\n", theSpp->state);
                    break;
            }
            break;
#endif

#if 0
        case CL_INIT_CFM:
            {
                CL_INIT_CFM_T *cic = (CL_INIT_CFM_T*)message;
                
                PRINT(("CL_INIT_CFM :- "));
                if (success == cic->status)
                {
                    PRINT(("success\n"));
                    PRINT(("Memory Slots: %d\n", VmGetAvailableAllocations()));
                
                    /* Make this device discoverable for inquiries and pages */
                    ConnectionWriteScanEnable(hci_scan_enable_inq_and_page);
                                  
                    setServerState(serverStopped);   
                    
                    /* Start the SPP Server  */
                    SppStartService(task);
                }
                else
                {
                    PRINT(("failure: %d\n", cic->status));
                    Panic();
                }
            }
            break;            
#endif
        case SPP_START_SERVICE_CFM:
            {
                SPP_START_SERVICE_CFM_T *sssc = (SPP_START_SERVICE_CFM_T *)message;
                SPP_LOG("SPP_START_SERVICE_CFM :-");
                if (sssc->status == spp_start_success)
                {
                    SPP_LOG("success\n");
                    SPP_LOGF("Memory Slots: %d\n", VmGetAvailableAllocations());
                    /* Now wait for an SPP_CONNECT_IND */
                    setServerState(serverUnconnected);
                }
                else
                {
                    SPP_LOGF("failure: %d\n", sssc->status);
                    Panic();
                }
            }
            break;
            
        case SPP_STOP_SERVICE_CFM:
            {
                SPP_STOP_SERVICE_CFM_T *sssc = (SPP_STOP_SERVICE_CFM_T *)message;
                SPP_LOG("SPP_STOP_SERVICE_CFM :-");
                if (sssc->status == spp_stop_success)
                {
                    SPP_LOG("success\n");
                    SPP_LOGF("Memory Slots: %d\n", VmGetAvailableAllocations());

                    setServerState(serverStopped);
                }
                else
                {
                    SPP_LOGF("failure: %d\n", sssc->status);
                    Panic();
                }
            }
            break;
       
        case SPP_CONNECT_IND:
            {
                SPP_CONNECT_IND_T *sci = (SPP_CONNECT_IND_T *)message; 
                SPP_LOG("SPP_CONNECT_IND\n");
                
                theSpp->bd_addr.lap = sci->addr.lap;
                theSpp->bd_addr.uap = sci->addr.uap;
                theSpp->bd_addr.nap = sci->addr.nap; 
                
                /* Respond to accept the connection.*/
                SppConnectResponse(
                        task, 
                        &theSpp->bd_addr,
                        1,                      /* Accept the connection */
                        sci->sink,
                        sci->server_channel,
                        0                       /* Use default payload size */
                        );
            }
            break;                
    
        case SPP_SERVER_CONNECT_CFM:
            {
                SPP_SERVER_CONNECT_CFM_T *sscc = (SPP_SERVER_CONNECT_CFM_T *)message;
                SPP_LOG("SPP_SERVER_CONNECT_CFM_T :-");
                if (spp_connect_success == sscc->status)
                {
                    Source uartSource = (Source) PanicZero( StreamUartSource() );
                    Sink   uartSink   = (Sink)   PanicZero( StreamUartSink() );
                    
                    SPP_LOG("Success\n");
                    SPP_LOGF("Memory Slots: %d\n", VmGetAvailableAllocations());

                    theSpp->spp   = sscc->spp;

                    PanicNull(sscc->sink);
            
                    /* Connect the SPP Sink to the Uart Source and visa-versa */                    
                    
                    PanicZero( 
                         StreamConnect(
                                 StreamSourceFromSink( sscc->sink ),
                                 uartSink
                                 )
                         );
                        
                    PanicZero( StreamConnect( uartSource, sscc->sink ) );

                    setServerState(serverConnected);
                }
                else
                {
                    SPP_LOGF("failure: %d\n", sscc->status);
                    Panic();
                }
            }
            break;

        case SPP_DISCONNECT_CFM:
            {
                SPP_DISCONNECT_CFM_T *sdc = (SPP_DISCONNECT_CFM_T *)message;
                SPP_LOG("SPP_DISCONNECT_CFM :-");
                if (sdc->status == spp_disconnect_success)
                    SPP_LOG("Success!\n");
                else
                    SPP_LOGF("reason %d\n", sdc->status);
                
                setServerState(serverUnconnected);

                SPP_LOG("SPP Server is now unconnected\n");
            }
            break;
            
        case SPP_DISCONNECT_IND:
            {
                SPP_DISCONNECT_IND_T *sdi = (SPP_DISCONNECT_IND_T *)message;
                SPP_LOGF("SPP_DISCONNECT_IND - status %d ", sdi->status);
                SPP_LOG("The SPP Client disconnected!\n");

                SppDisconnectResponse(sdi->spp);

                setServerState(serverUnconnected);
            }
            break;            
                      
        case CL_RFCOMM_CONTROL_IND:  
            SPP_LOG("CL_RFCOMM_CONTROL_IND\n");
            break;
        
        default:
            SPP_LOGF("Unhandled Message: %d, 0x%0X\n", id, id);
            break;        
    }
}


#endif/*ENABLE_SPP*/
