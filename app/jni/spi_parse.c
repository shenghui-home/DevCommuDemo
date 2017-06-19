#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <android/log.h>

#include "utils.h"
#include "devspi.h"

static int gSerialNo = 0;
static char gSensorDat[256];

static unsigned short ExchangeShortData(unsigned short *data)
{
    unsigned short exDat = 0;
    unsigned short inDat = *data & 0xffff;

    exDat = (inDat << 8) | (inDat >> 8);

    *data = exDat;

    return exDat;
}

static int ExchangeByteOrder(char *buf, int len)
{
    int i = 0;
    int tmp = 0;

    for(i = 0; i < len / 2; i++)
    {
        tmp = buf[i];
        buf[i] = buf[len - 1 - i];
        buf[len - 1 - i] = tmp;
    }

    return i;
}

static int PrepareSpiData(char *sendBuf, int bufLen, PSensorData pSensorData)
{
	int i = 0;
	int offset = 0;
	int tmpLen = 0;
	TProtoData protoData;
	
	memset(sendBuf, 0, bufLen);
	
	protoData.header = 0x061C;
	protoData.serialNo = gSerialNo++;
	protoData.len = pSensorData->len + 4;
	protoData.data = (char *)pSensorData;

	ExchangeShortData(&protoData.header);
	memcpy(sendBuf + offset, &protoData.header, sizeof(short));
	offset += sizeof(short);

	ExchangeShortData(&protoData.serialNo);
	memcpy(sendBuf + offset, &protoData.serialNo, sizeof(short));
	offset += sizeof(short);

	ExchangeShortData(&protoData.len);
	memcpy(sendBuf + offset, &protoData.len, sizeof(short));
	offset += sizeof(short);

	ExchangeShortData(&pSensorData->type);
	LOGD("beyond.zuo----22------>>>>>pSensorData->type:0x%x", pSensorData->type);
	memcpy(sendBuf + offset, &pSensorData->type, sizeof(short));
	offset += sizeof(short);

    tmpLen = pSensorData->len;
	ExchangeShortData(&pSensorData->len);
	memcpy(sendBuf + offset, &pSensorData->len, sizeof(short));
	offset += sizeof(short);

	ExchangeByteOrder(pSensorData->value, tmpLen);
	memcpy(sendBuf + offset, pSensorData->value, tmpLen);
	offset += tmpLen;
	
	for(i = 0; i < offset; i++)
	{
		protoData.crc += sendBuf[i];
	}

	ExchangeShortData(&protoData.crc);
	memcpy(sendBuf + offset, &protoData.crc, sizeof(short));
	offset += sizeof(short);
	
	return offset;
}

static int ParseSensorData(char *recvBuf, int len, PSensorData pSensorData)
{
	int i = 0;
	int crc = 0;
	int offset = 0;
	
	TProtoData protoData;
	
	memcpy(&protoData.header, recvBuf + offset, sizeof(short));
	ExchangeShortData(&protoData.header);
	offset += sizeof(short);
	
	memcpy(&protoData.serialNo, recvBuf + offset, sizeof(short));
	ExchangeShortData(&protoData.serialNo);
	offset += sizeof(short);
	
	memcpy(&protoData.len, recvBuf + offset, sizeof(short));
	ExchangeShortData(&protoData.len);
	offset += sizeof(short);
	
	memcpy(&pSensorData->type, recvBuf + offset, sizeof(short));
	ExchangeShortData(&pSensorData->type);
	offset += sizeof(short);
	
	memcpy(&pSensorData->len, recvBuf + offset, sizeof(short));
	ExchangeShortData(&pSensorData->len);
	offset += sizeof(short);

	if (pSensorData->len > sizeof(gSensorDat))
	{
	    pSensorData->len = sizeof(gSensorDat);
	}
	memcpy(pSensorData->value, recvBuf + offset, pSensorData->len);
	ExchangeByteOrder(pSensorData->value, pSensorData->len);
	offset += pSensorData->len;
	
	for(i = 0; i < offset; i++)
	{
		crc += recvBuf[i];
	}
	
	memcpy(&protoData.crc, recvBuf + offset, sizeof(short));
	ExchangeShortData(&protoData.crc);
	offset += sizeof(short);
	
	if(crc == protoData.crc)
	{
		return offset;
	}
	
	return 0;
}

static int ProcSpiData(int cmd, PSensorData pSensorData)
{
    int i = 0;
	int ret = 0;
	int len = 0;
	char sendBuf[512];
	
	memset(gSensorDat, 0, sizeof(gSensorDat));
	
	pSensorData->type = 0xA000 | (0x0FFF & cmd);
	LOGD("beyond.zuo---------->>>>>pSensorData->type:0x%x", pSensorData->type);
	pSensorData->len = 0;
	pSensorData->value = gSensorDat;
	
	len = PrepareSpiData(sendBuf, sizeof(sendBuf), pSensorData);

	for(i = 0; i < len; i++)
	{
	    LOGD("Prepare Send Spi Data[%d]=0x%02x", i, sendBuf[i]);
	}

	len = WriteReadSpiDev(sendBuf, len);

	for(i = 0; i < len; i++)
    {
        LOGD("Recv Spi Data[%d]=0x%02x", i, sendBuf[i]);
    }

	if(len > 0)
	{
	    ret = ParseSensorData(sendBuf, len, pSensorData);
	}

	return ret;
}

int GetSpiSensorData(char *inOutBuf)
{
	int ret = 0;
	int len = 0;
	int cmd = 0;
	int sensorInfo = 0;
	TSensorData sensorData;

	memcpy(&cmd, inOutBuf, sizeof(short));
	LOGD("beyond.zuo---------->>>>>cmd:%d", cmd);
	
	ret = ProcSpiData(cmd, &sensorData);
	
	if(ret > 0)
	{
	    len = sensorData.len > sizeof(int) ? sizeof(int) : sensorData.len;
		memcpy(&sensorInfo, sensorData.value, len);
	}
	
	return sensorInfo;
}
