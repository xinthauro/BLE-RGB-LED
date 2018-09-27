/*******************************************************************************
* main.c
* Last updapted 2018-09-27
*
* Carlos Silva
*******************************************************************************/
#include <project.h>
#include <rgbs.h>
#include <dis.h>

/* Local-scope ---------------------------------------------------------------*/
static void bleStart(void);
static void bleDisconnected(void);
static void bleStackCallback(uint32 eventCode, void *eventParameter);

/*............................................................................*/
int main(void)
{
    /* Enable global interrupts */
    CyGlobalIntEnable;
    /* Initializes BLE Stack */
    CyBle_Start(bleStackCallback);
    CyBle_ProcessEvents();
    for (;;) {
        CyBle_ProcessEvents();
    }
}
/*............................................................................*/
static void bleStart(void)
{
    RGBS_start();
    DIS_start();
}
/*............................................................................*/
static void bleDisconnected(void)
{
}
/*............................................................................*/
static void bleStackCallback(uint32 eventCode, void *eventParameter)
{
    switch (eventCode) {
        case CYBLE_EVT_STACK_ON:
            bleStart();
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            break;
        case CYBLE_EVT_HARDWARE_ERROR:
            break;
        case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
            if (CYBLE_STATE_DISCONNECTED == CyBle_GetState()) {
                bleDisconnected();
                CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_SLOW);
            }
            break;
        case CYBLE_EVT_TIMEOUT:
            if (CYBLE_STATE_DISCONNECTED == CyBle_GetState()) {
                bleDisconnected();
                CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_SLOW);
            }
            break;
        case CYBLE_EVT_GAP_DEVICE_CONNECTED:
            bleDisconnected();
            break;
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            bleDisconnected();
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            break;
        case CYBLE_EVT_GATTS_WRITE_REQ: {
            CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReqParam = (CYBLE_GATTS_WRITE_REQ_PARAM_T *)eventParameter;
            switch (wrReqParam->handleValPair.attrHandle) {
                case CYBLE_RGB_LED_VALUE_CHAR_HANDLE:
                    RGBS_valueWriteRequest(wrReqParam);
                    break;
                default:
                    break;
            }
            break;
        }
        default:
            break;
    }
}

