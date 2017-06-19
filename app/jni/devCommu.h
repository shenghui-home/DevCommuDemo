//
// Created by beyond on 2017/5/6.
//

#ifndef COMMUDEMO_DEVCOMMU_H
#define COMMUDEMO_DEVCOMMU_H

#define LIB_DEV_COMMU_VERSION	"devcommu_ver1.0.0"

#define DEV_CMD_BASE    0
#define DEV_CMD_GET_VERSION         DEV_CMD_BASE + 1
#define DEV_CMD_DEV_INIT            DEV_CMD_BASE + 2
#define DEV_CMD_DEV_DEINIT          DEV_CMD_BASE + 3

#define DEV_CMD_SET_SERIAL_BAUD     DEV_CMD_BASE + 4

#define DEV_CMD_SET_SPI_MODE        DEV_CMD_BASE + 5
#define DEV_CMD_GET_SPI_MODE        DEV_CMD_BASE + 6

#define DEV_CMD_SET_SPI_SPEED       DEV_CMD_BASE + 7
#define DEV_CMD_GET_SPI_SPEED       DEV_CMD_BASE + 8

#define DEV_CMD_SET_SPI_BITS        DEV_CMD_BASE + 9
#define DEV_CMD_GET_SPI_BITS        DEV_CMD_BASE + 10

#define DEV_CMD_SET_SPI_DELAY       DEV_CMD_BASE + 11

#define DEV_CMD_SET_SPI_DEV_NO      DEV_CMD_BASE + 12

#define DEV_CMD_I2C_READ            DEV_CMD_BASE + 13
#define DEV_CMD_I2C_WRITE           DEV_CMD_BASE + 14

#define DEV_CMD_SPI_WRITE_READ      DEV_CMD_BASE + 15

#define DEV_CMD_SERIAL_READ         DEV_CMD_BASE + 16
#define DEV_CMD_SERIAL_WRITE        DEV_CMD_BASE + 17

#define DEV_CMD_GET_SPI_SENSOR_DAT  DEV_CMD_BASE + 18

#define ERR_OPEN_I2C_DEV            -1
#define ERR_OPEN_SPI_DEV            -2
#define ERR_OPEN_SERIAL_DEV         -3

#endif //COMMUDEMO_DEVCOMMU_H
