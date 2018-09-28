/*******************************************************************************
* dis.c
* Last updapted 2018-09-28
*
* Carlos Silva
*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <project.h>
#include <dis.h>
#include <config.h>

/* Local-scope ---------------------------------------------------------------*/
#define MODEL_NUMBER        DIS_MODEL_NUMBER
#define HARDWARE_REVISION   DIS_HARDWARE_REVISION
#define FIRMWARE_REVISION   DIS_FIRMWARE_REVISION

static void setModelNumber(void);
static void setSerialNumber(void);
static void setHardwareRevision(void);
static void setFirmwareRevision(void);

/*............................................................................*/
void DIS_start(void)
{
    setModelNumber();
    setSerialNumber();
    setHardwareRevision();
    setFirmwareRevision();
}
/*............................................................................*/
static void setModelNumber(void)
{
    CyBle_DissSetCharacteristicValue(CYBLE_DIS_MODEL_NUMBER, strlen(MODEL_NUMBER), (uint8 *)MODEL_NUMBER);
}
/*............................................................................*/
static void setSerialNumber(void)
{
    char dummy[20];
    uint32 id[2];
    
    CyGetUniqueId(id);
    snprintf(dummy, sizeof(dummy), "%.4X:%.4X:%.4X:%.4X", (uint16)(id[1] >> 8), (uint16)id[1], (uint16)(id[0] >> 8), (uint16)id[0]);
    CyBle_DissSetCharacteristicValue(CYBLE_DIS_SERIAL_NUMBER, strlen(dummy), (uint8 *)dummy);
}
/*............................................................................*/
static void setHardwareRevision(void)
{
    CyBle_DissSetCharacteristicValue(CYBLE_DIS_HARDWARE_REV, strlen(HARDWARE_REVISION), (uint8 *)HARDWARE_REVISION);
}
/*............................................................................*/
static void setFirmwareRevision(void)
{
    CyBle_DissSetCharacteristicValue(CYBLE_DIS_FIRMWARE_REV, strlen(FIRMWARE_REVISION), (uint8 *)FIRMWARE_REVISION);
}

