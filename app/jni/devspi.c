//
// Created by beyond on 2017/5/6.
//

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

static int gSpiFd = -1;
static TSpiParam gSpiParam;

int OpenSpiDev()
{
    int fd = -1;

    fd = open(SPI_DEV_NAME, O_RDWR);
    if(fd < 0)
    {
        LOGD("Open %s file fail! Please check driver", SPI_DEV_NAME);
        return fd;
    }
    LOGD("Open %s Success.", SPI_DEV_NAME);

    gSpiFd = fd;

    memset(&gSpiParam, 0, sizeof(TSpiParam));
    gSpiParam.bits = 8;
    gSpiParam.speed = 9600;
    gSpiParam.delayUs = 0;

    return fd;
}

int SetSpiMode(char *mode)
{
    int ret = 0;
    int mod = atoi(mode);

    if(gSpiFd <= 0)
    {
        return gSpiFd;
    }

    ret = ioctl(gSpiFd, SPI_IOC_WR_MODE, &mod);
    LOGD("Set SPI Mode Ret:%d, mode:%d", ret, mod);

    return ret;
}

int GetSpiMode(char *mode)
{
    int ret = 0;
    int mod = 0;

    if(gSpiFd <= 0)
    {
        return gSpiFd;
    }

    ret = ioctl(gSpiFd, SPI_IOC_RD_MODE, &mod);
    LOGD("Get SPI Mode Ret:%d, mode:%d", ret, mod);
    if(ret < 0)
    {
        return ret;
    }
    ret = sprintf(mode, "%d", mod);

    return ret;
}

int SetSpiCommuBits(char *bits)
{
    int ret = 0;
    int bit = atoi(bits);

    if(gSpiFd <= 0)
    {
        return gSpiFd;
    }

    gSpiParam.bits = bit;

    ret = ioctl(gSpiFd, SPI_IOC_WR_BITS_PER_WORD, &bit);
    LOGD("Set SPI Commu Bits Ret:%d, bit:%d", ret, bit);

    return ret;
}

int GetSpiCommuBits(char *bits)
{
    int ret = 0;
    int bit = 0;

    if(gSpiFd <= 0)
    {
        return gSpiFd;
    }

    ret = ioctl(gSpiFd, SPI_IOC_RD_BITS_PER_WORD, &bit);
    LOGD("Get SPI Commu Bits Ret:%d, bit:%d", ret, bit);
    if(ret < 0)
    {
        return ret;
    }
    ret = sprintf(bits, "%d", bit);

    return ret;
}

int SetSpiMaxSpeed(char *speeds)
{
    int ret = 0;
    int speed = atoi(speeds);

    if(gSpiFd <= 0)
    {
        return gSpiFd;
    }

    gSpiParam.speed = speed;

    ret = ioctl(gSpiFd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    LOGD("Set SPI Speed Ret:%d, speed:%d", ret, speed);

    return ret;
}

int GetSpiMaxSpeed(char *speeds)
{
    int ret = 0;
    int speed = 0;

    if(gSpiFd <= 0)
    {
        return gSpiFd;
    }

    ret = ioctl(gSpiFd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
    LOGD("Get SPI Speed Ret:%d, speed:%d", ret, speed);
    if(ret < 0)
    {
        return ret;
    }
    ret = sprintf(speeds, "%d", speed);

    return ret;
}

int SetSpiDevCommuDelay(char *delays)
{
    int delay = atoi(delays);

    gSpiParam.delayUs = delay;

    return TRUE;
}

int SetSpiDeviceNo(char *devNo)
{
    //TODO
    int ret = 0;
    int no = atoi(devNo);

    if(SPI_DEV_NUM_1 == no)
    {
        system("echo 1,0>/sys/class/inet_gpio/inet_gpio");
        system("echo 2,1>/sys/class/inet_gpio/inet_gpio");
    }
    else if(SPI_DEV_NUM_2 == no)
    {
        system("echo 1,1>/sys/class/inet_gpio/inet_gpio");
        system("echo 2,0>/sys/class/inet_gpio/inet_gpio");
    }
    else
    {
        ret = -1;
    }


    return ret;
}

int WriteReadSpiDev(char *buf, int len)
{
    int i = 0;
    int ret = 0;
    char txBuf[SPI_SEND_MAX_LEN];
    char rxBuf[SPI_SEND_MAX_LEN];
    struct spi_ioc_transfer transfer;

    if(gSpiFd <= 0 || len > (SPI_SEND_MAX_LEN - 1))
    {
        LOGD("SPI Data Send Fail!");
        return -1;
    }
    memset(txBuf, 0, sizeof(txBuf));
    memset(rxBuf, 0, sizeof(rxBuf));

    memcpy(txBuf, buf, len);

    /*for(i = 0; i < len+1; i++)
    {
        LOGD("beyond.zuo---------->>>>txBuf[%d]=%d", i, txBuf[i]);
    }*/

    transfer.tx_buf = (unsigned long)txBuf;
    transfer.rx_buf = (unsigned long)rxBuf;
    transfer.len = len+1;
    transfer.delay_usecs = gSpiParam.delayUs;
    transfer.speed_hz = gSpiParam.speed;
    transfer.bits_per_word = gSpiParam.bits;

    ret = ioctl(gSpiFd, SPI_IOC_MESSAGE(1), &transfer);
    if(ret > 0)
    {
        memset(buf, 0, len);
        memcpy(buf, rxBuf + 1, len);
        /*for(i = 0; i < ret; i++)
        {
            LOGD("beyond.zuo---------->>>>rxBuf[%d]=%d", i, rxBuf[i]);
        }*/
    }

    LOGD("Write SPI Ret:%d, transfer.len:%d", ret, transfer.len);

    return (ret - 1);
}

int CloseSpiDev()
{
    if(gSpiFd <= 0)
    {
        return gSpiFd;
    }
    close(gSpiFd);
    gSpiFd = -1;

    return TRUE;
}