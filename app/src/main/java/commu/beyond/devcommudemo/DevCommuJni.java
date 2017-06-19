package commu.beyond.devcommudemo;

/**
 * Created by beyond on 2017/5/5.
 */

public class DevCommuJni {

    public static final int DEV_CMD_GET_VERSION = 1;
    public static final int DEV_CMD_DEV_INIT = 2;
    public static final int DEV_CMD_DEV_DEINIT = 3;
    public static final int DEV_CMD_SET_SERIAL_BAUD = 4;
    public static final int DEV_CMD_SET_SPI_MODE = 5;
    public static final int DEV_CMD_GET_SPI_MODE = 6;
    public static final int DEV_CMD_SET_SPI_SPEED = 7;
    public static final int DEV_CMD_GET_SPI_SPEED = 8;
    public static final int DEV_CMD_SET_SPI_BITS = 9;
    public static final int DEV_CMD_GET_SPI_BITS = 10;
    public static final int DEV_CMD_SET_SPI_DELAY = 11;
    public static final int DEV_CMD_SET_SPI_DEV_NO = 12;
    public static final int DEV_CMD_I2C_READ = 13;
    public static final int DEV_CMD_I2C_WRITE = 14;
    public static final int DEV_CMD_SPI_WRITE_READ = 15;
    public static final int DEV_CMD_SERIAL_READ = 16;
    public static final int DEV_CMD_SERIAL_WRITE = 17;
    public static final int DEV_CMD_GET_SPI_SENSOR_DAT = 18;

    private DevCommuJni() {

    }

    private static class LazyHolder {
        private static final DevCommuJni INSTANCE = new DevCommuJni();
    }

    public static final DevCommuJni getInstance() {
        return LazyHolder.INSTANCE;
    }

    public native int SendCmdMessage(int cmd, byte[] inOutBuf, int dataLen, int inOutBufLen);

    static {
        System.loadLibrary("DevCommuJni");
    }
}
