/*******************************************************************************
* main.c
* Last updapted 2018-09-27
*
* Carlos Silva
*******************************************************************************/
#include <project.h>
#include <rgbs.h>
#include <rgb.h>
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
    /* RGB_process is called every 7.8ms */
    CySysWdtSetInterruptCallback(CY_SYS_WDT_COUNTER0, RGB_process);
    for (;;) {
        CyBle_ProcessEvents();
    }
}
/*............................................................................*/
static void bleStart(void)
{
    RGBS_start();
    DIS_start();
    RGB_setBreathe(RGB_BREATHE_CYAN);
    CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
}
/*............................................................................*/
static void bleDisconnected(void)
{
    RGB_setBreathe(RGB_BREATHE_CYAN);
    CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
}
/*............................................................................*/
static void bleStackCallback(uint32 eventCode, void *eventParameter)
{
    switch (eventCode) {
        case CYBLE_EVT_STACK_ON:
            bleStart();
            break;
        case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
            if (CYBLE_STATE_DISCONNECTED == CyBle_GetState()) {
                bleDisconnected();
            }
            break;
        case CYBLE_EVT_GAP_DEVICE_CONNECTED:
            RGB_setBreathe(RGB_BREATHE_MAGENTA);
            break;
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            bleDisconnected();
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

