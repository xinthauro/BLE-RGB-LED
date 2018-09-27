#include <rgbs.h>
#include <rgb.h>

/* Local-scope ---------------------------------------------------------------*/
#define RGB_VALUE_LENGHT    3u
#define RGB_CHANNEL_RED     0u
#define RGB_CHANNEL_GREEN   1u
#define RGB_CHANNEL_BLUE    2u

/*............................................................................*/
void RGBS_start(void)
{
    RGB_start();
}
/*............................................................................*/
void RGBS_valueWriteRequest(CYBLE_GATTS_WRITE_REQ_PARAM_T *wrParameter)
{
    if (wrParameter->handleValPair.value.len == 3u) {
        /* Write to RGB led received value */
        RGBValue value;
        value.red = wrParameter->handleValPair.value.val[RGB_CHANNEL_RED];
        value.green = wrParameter->handleValPair.value.val[RGB_CHANNEL_GREEN];
        value.blue = wrParameter->handleValPair.value.val[RGB_CHANNEL_BLUE];
        RGB_write(&value);
        /* Update GATT DB with lastest request */
        CyBle_GattsWriteAttributeValue(&wrParameter->handleValPair, 0u, &wrParameter->connHandle, CYBLE_GATT_DB_PEER_INITIATED);
        /* Send response to write request */
        CyBle_GattsWriteRsp(wrParameter->connHandle);
    } else {
        /* Send error response */
        CYBLE_GATTS_ERR_PARAM_T error;
        error.opcode = CYBLE_GATT_WRITE_REQ;
        error.attrHandle = wrParameter->handleValPair.attrHandle;
        error.errorCode = CYBLE_GATT_ERR_OUT_OF_RANGE;
        CyBle_GattsErrorRsp(cyBle_connHandle, &error);
    }
}

