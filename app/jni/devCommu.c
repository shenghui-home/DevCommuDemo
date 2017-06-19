//
// Created by beyond on 2017/5/6.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <android/log.h>

#include "utils.h"
#include "devCommu.h"
#include "commu_beyond_commudemo_DevCommuJni.h"

static int GetDevCommuVersion(char *inOutBuf, int dataLen, int inOutBufLen)
{
	int len = 0;

	len = snprintf(inOutBuf, inOutBufLen, "%s", LIB_DEV_COMMU_VERSION);

	return len;
}

static int DevCommuInit(char *inOutBuf, int dataLen, int inOutBufLen)
{
    int tmp = 0;
    int ret = 0;

    tmp = OpenI2cDev();
    if(tmp < 0)
    {
        ret = ERR_OPEN_I2C_DEV;
    }

    tmp = OpenSpiDev();
    if(tmp < 0)
    {
        ret = ERR_OPEN_SPI_DEV;
    }

    tmp = OpenSerialDev();
    if(tmp < 0)
    {
        ret = ERR_OPEN_SERIAL_DEV;
    }

    return ret;
}

static int DevCommuDeInit(char *inOutBuf, int dataLen, int inOutBufLen)
{
    int ret = 0;

    CloseI2cDev();
    CloseSpiDev();
    CloseSerialDev();

    return ret;
}

static int SendCmdMessage(int cmd, char *inOutBuf, int dataLen, int inOutBufLen)
{
	int ret = 0;

	switch(cmd)
    {
        case DEV_CMD_GET_VERSION:
            ret = GetDevCommuVersion(inOutBuf, dataLen, inOutBufLen);
            break;

        case DEV_CMD_DEV_INIT:
            ret = DevCommuInit(inOutBuf, dataLen, inOutBufLen);
            break;

        case DEV_CMD_DEV_DEINIT:
            ret = DevCommuDeInit(inOutBuf, dataLen, inOutBufLen);
            break;

        case DEV_CMD_SET_SERIAL_BAUD:
            ret = SetSerialParam(inOutBuf);
            break;

        case DEV_CMD_SET_SPI_MODE:
            ret = SetSpiMode(inOutBuf);
            break;

        case DEV_CMD_GET_SPI_MODE:
            ret = GetSpiMode(inOutBuf);
            break;

        case DEV_CMD_SET_SPI_SPEED:
            ret = SetSpiMaxSpeed(inOutBuf);
            break;

        case DEV_CMD_GET_SPI_SPEED:
            ret = GetSpiMaxSpeed(inOutBuf);
            break;

        case DEV_CMD_SET_SPI_BITS:
            ret = SetSpiCommuBits(inOutBuf);
            break;

        case DEV_CMD_GET_SPI_BITS:
            ret = GetSpiCommuBits(inOutBuf);
            break;

        case DEV_CMD_SET_SPI_DELAY:
            ret = SetSpiDevCommuDelay(inOutBuf);
            break;

        case DEV_CMD_SET_SPI_DEV_NO:
            ret = SetSpiDeviceNo(inOutBuf);
            break;

        case DEV_CMD_I2C_READ:
            ret = ReadI2cDev(inOutBuf, dataLen);
            break;

        case DEV_CMD_I2C_WRITE:
            ret = WriteI2cDev(inOutBuf, dataLen);
            break;

        case DEV_CMD_SPI_WRITE_READ:
            ret = WriteReadSpiDev(inOutBuf, dataLen);
            break;

        case DEV_CMD_SERIAL_READ:
            ret = ReadSerialDev(inOutBuf, dataLen);
            break;

        case DEV_CMD_SERIAL_WRITE:
            ret = WriteSerialDev(inOutBuf, dataLen);
            break;

        case DEV_CMD_GET_SPI_SENSOR_DAT:
            ret = GetSpiSensorData(inOutBuf);
            break;

        default:
            LOGD("Error, Not support this cmd.");
            break;
    }

    return ret;
}

JNIEXPORT jint JNICALL Java_commu_beyond_devcommudemo_DevCommuJni_SendCmdMessage
  (JNIEnv *env, jobject thiz, jint cmd, jbyteArray inOutBuf, jint dataLen, jint inOutBufLen)
{
	int ret = 0;
	char *pInOutBuf = NULL;

    if(inOutBufLen > 0)
	{
		pInOutBuf = (*env)->GetByteArrayElements(env, inOutBuf, NULL);
	}

    ret = SendCmdMessage(cmd, pInOutBuf, dataLen, inOutBufLen);

	if(inOutBufLen > 0)
    {
        if(ret > 0)
        {
            (*env)->SetByteArrayRegion(env, inOutBuf, 0, ret, pInOutBuf);
        }
    }

    return ret;
}

