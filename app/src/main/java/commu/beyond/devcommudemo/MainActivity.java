package commu.beyond.devcommudemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import java.text.DecimalFormat;

public class MainActivity extends AppCompatActivity {

    public DevCommuJni devCommuJni;

    private EditText serialBaudEdit;
    private Button serialBaudBtn;
    private EditText serialSendEdit;
    private Button serialSendBtn;
    private Button serialReadBtn;
    private EditText i2cSendEdit;
    private Button i2cSendBtn;
    private Button i2cReadBtn;
    private EditText spiModeEdit;
    private Button spiModeSetBtn;
    private Button spiModeGetBtn;
    private EditText spiSpeedEdit;
    private Button spiSpeedSetBtn;
    private Button spiSpeedGetBtn;
    private EditText spiBitsEdit;
    private Button spiBitsSetBtn;
    private Button spiBitsGetBtn;
    private EditText spiCommuDelayEdit;
    private Button spiCommuDelayBtn;
    private EditText spiDevNoEdit;
    private Button spiDevNoBtn;
    private EditText spiSendDataEdit;
    private Button spiSendDataBtn;
    private Button spiReadDataBtn;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        serialBaudEdit = (EditText)findViewById(R.id.serialBaudEdit);
        serialBaudEdit.setText("115200");
        serialBaudBtn = (Button)findViewById(R.id.serialBaudBtn);
        serialBaudBtn.setOnClickListener(mylistener);

        serialSendEdit = (EditText)findViewById(R.id.serialSendEdit);
        serialSendBtn = (Button)findViewById(R.id.serialSendBtn);
        serialReadBtn = (Button)findViewById(R.id.serialReadBtn);
        serialSendBtn.setOnClickListener(mylistener);
        serialReadBtn.setOnClickListener(mylistener);

        i2cSendEdit = (EditText)findViewById(R.id.i2cSendEdit);
        i2cSendBtn = (Button)findViewById(R.id.i2cSendBtn);
        i2cReadBtn = (Button)findViewById(R.id.i2cReadBtn);
        i2cSendBtn.setOnClickListener(mylistener);
        i2cReadBtn.setOnClickListener(mylistener);

        spiModeEdit = (EditText)findViewById(R.id.spiModeEdit);
        spiModeEdit.setText("0");
        spiModeSetBtn = (Button)findViewById(R.id.spiModeSetBtn);
        spiModeGetBtn = (Button)findViewById(R.id.spiModeGetBtn);
        spiModeSetBtn.setOnClickListener(mylistener);
        spiModeGetBtn.setOnClickListener(mylistener);

        spiSpeedEdit = (EditText)findViewById(R.id.spiSpeedEdit);
        spiSpeedEdit.setText("9600");
        spiSpeedSetBtn = (Button)findViewById(R.id.spiSpeedSetBtn);
        spiSpeedGetBtn = (Button)findViewById(R.id.spiSpeedGetBtn);
        spiSpeedSetBtn.setOnClickListener(mylistener);
        spiSpeedGetBtn.setOnClickListener(mylistener);

        spiBitsEdit = (EditText)findViewById(R.id.spiBitsEdit);
        spiBitsEdit.setText("8");
        spiBitsSetBtn = (Button)findViewById(R.id.spiBitsSetBtn);
        spiBitsGetBtn = (Button)findViewById(R.id.spiBitsGetBtn);
        spiBitsSetBtn.setOnClickListener(mylistener);
        spiBitsGetBtn.setOnClickListener(mylistener);

        spiCommuDelayEdit = (EditText)findViewById(R.id.spiCommuDelayEdit);
        spiCommuDelayEdit.setText("2000");
        spiCommuDelayBtn = (Button)findViewById(R.id.spiCommuDelayBtn);
        spiCommuDelayBtn.setOnClickListener(mylistener);

        spiDevNoEdit = (EditText)findViewById(R.id.spiDevNoEdit);
        spiDevNoEdit.setText("1");
        spiDevNoBtn = (Button)findViewById(R.id.spiDevNoBtn);
        spiDevNoBtn.setOnClickListener(mylistener);

        spiSendDataEdit = (EditText)findViewById(R.id.spiSendDataEdit);
        spiSendDataBtn = (Button)findViewById(R.id.spiSendDataBtn);
        spiReadDataBtn = (Button)findViewById(R.id.spiReadDataBtn);
        spiSendDataBtn.setOnClickListener(mylistener);
        spiReadDataBtn.setOnClickListener(mylistener);

        devCommuJni = DevCommuJni.getInstance();
        devCommuJni.SendCmdMessage(DevCommuJni.DEV_CMD_DEV_INIT, null, 0, 0);
    }

    Button.OnClickListener mylistener = new Button.OnClickListener() {

        @Override
        public void onClick(View v) {
            int ret = 0;
            String toastStr = null;
            byte[] inOutBuf = new byte[1024];

            switch (v.getId()) {
                case R.id.serialBaudBtn:
                    System.out.println("beyond.zuo---->>>serialBaudBtn clicked");
                    byte[] baudBuf = serialBaudEdit.getText().toString().getBytes();
                    System.arraycopy(baudBuf, 0, inOutBuf, 0, baudBuf.length);
                    ret = devCommuJni.SendCmdMessage(DevCommuJni.DEV_CMD_SET_SERIAL_BAUD, inOutBuf,
                            baudBuf.length, inOutBuf.length);
                    if(ret >= 0) {
                        toastStr = "Serial Baudrate Set Success";
                    } else {
                        toastStr = "Serial Baudrate Set Fail";
                    }
                    break;

                case R.id.serialSendBtn:
                    System.out.println("beyond.zuo---->>>serialSendBtn clicked");
                    byte[] serialDat = new byte[] {(byte)0xFE, 0x04, 0x00, 0x03, 0x00, 0x01, (byte)0xD5, (byte)0xC5};
                    ret = devCommuJni.SendCmdMessage(DevCommuJni.DEV_CMD_SERIAL_WRITE, inOutBuf,
                            serialDat.length, inOutBuf.length);
                    if(ret >= 0) {
                        toastStr = "Serial Data Send Success";
                    } else {
                        toastStr = "Serial Data Send Fail";
                    }
                    break;

                case R.id.serialReadBtn:
                    System.out.println("beyond.zuo---->>>serialReadBtn clicked");
                    ret = devCommuJni.SendCmdMessage(DevCommuJni.DEV_CMD_SERIAL_READ, inOutBuf,
                            8, inOutBuf.length);
                    if(ret >= 8) {
                        int co2value = (inOutBuf[3] << 8) + inOutBuf[4];
                        toastStr = "CO2 Value is : " + co2value;
                    } else {
                        toastStr = "Serial Data Read Fail";
                    }
                    break;

                case R.id.i2cSendBtn:
                    toastStr = "Need Support";
                    break;

                case R.id.i2cReadBtn:
                    DecimalFormat df = new DecimalFormat("######0.00");
                    ret = devCommuJni.SendCmdMessage(DevCommuJni.DEV_CMD_I2C_READ, inOutBuf,
                            6, inOutBuf.length);
                    if(ret >= 6) {
                        int temp = (inOutBuf[0] * 256 + inOutBuf[1]);
                        double cTemp = -45 + (175 * temp / 65535.0);
                        double fTemp = -49 + (315 * temp / 65535.0);
                        double humidity = 100 * (inOutBuf[3] * 256 + inOutBuf[4]) / 65535.0;

                        toastStr = "Temperature in Celsius:" + df.format(cTemp) + " C,  Temperature in Fahrenheit:" + df.format(fTemp) + " F,  Relative Humidity:" + df.format(humidity) + " RH";
                        i2cSendEdit.setText(toastStr);
                    } else {
                        toastStr = "I2C Data Read Fail";
                    }
                    break;

                case R.id.spiModeSetBtn:
                    byte[] modeBuf = spiModeEdit.getText().toString().getBytes();
                    System.arraycopy(modeBuf, 0, inOutBuf, 0, modeBuf.length);
                    ret = devCommuJni.SendCmdMessage(DevCommuJni.DEV_CMD_SET_SPI_MODE, inOutBuf,
                            modeBuf.length, inOutBuf.length);
                    if(ret >= 0) {
                        toastStr = "SPI Mode Set Success";
                    } else {
                        toastStr = "SPI Mode Set Fail";
                    }
                    break;

                case R.id.spiModeGetBtn:
                    ret = devCommuJni.SendCmdMessage(DevCommuJni.DEV_CMD_GET_SPI_MODE, inOutBuf,
                            5, inOutBuf.length);
                    if(ret > 0) {
                        toastStr = "SPI Mode:" + new String(inOutBuf);
                    } else {
                        toastStr = "SPI Mode Get Fail";
                    }
                    break;

                case R.id.spiSpeedSetBtn:
                    byte[] speedBuf = spiSpeedEdit.getText().toString().getBytes();
                    System.arraycopy(speedBuf, 0, inOutBuf, 0, speedBuf.length);
                    ret = devCommuJni.SendCmdMessage(DevCommuJni.DEV_CMD_SET_SPI_SPEED, inOutBuf,
                            speedBuf.length, inOutBuf.length);
                    if(ret >= 0) {
                        toastStr = "SPI Speed Set Success";
                    } else {
                        toastStr = "SPI Speed Set Fail";
                    }
                    break;

                case R.id.spiSpeedGetBtn:
                    ret = devCommuJni.SendCmdMessage(DevCommuJni.DEV_CMD_GET_SPI_SPEED, inOutBuf,
                            10, inOutBuf.length);
                    if(ret > 0) {
                        toastStr = "SPI Speed:" + new String(inOutBuf);
                    } else {
                        toastStr = "SPI Speed Get Fail";
                    }
                    break;

                case R.id.spiBitsSetBtn:
                    byte[] bitsBuf = spiBitsEdit.getText().toString().getBytes();
                    System.arraycopy(bitsBuf, 0, inOutBuf, 0, bitsBuf.length);
                    ret = devCommuJni.SendCmdMessage(DevCommuJni.DEV_CMD_SET_SPI_BITS, inOutBuf,
                            bitsBuf.length, inOutBuf.length);
                    if(ret >= 0) {
                        toastStr = "SPI Bits Set Success";
                    } else {
                        toastStr = "SPI Bits Set Fail";
                    }
                    break;

                case R.id.spiBitsGetBtn:
                    ret = devCommuJni.SendCmdMessage(DevCommuJni.DEV_CMD_GET_SPI_BITS, inOutBuf,
                            10, inOutBuf.length);
                    if(ret > 0) {
                        toastStr = "SPI Bits:" + new String(inOutBuf);
                    } else {
                        toastStr = "SPI Bits Get Fail";
                    }
                    break;

                case R.id.spiCommuDelayBtn:
                    byte[] delayBuf = spiCommuDelayEdit.getText().toString().getBytes();
                    System.arraycopy(delayBuf, 0, inOutBuf, 0, delayBuf.length);
                    ret = devCommuJni.SendCmdMessage(DevCommuJni.DEV_CMD_SET_SPI_DELAY, inOutBuf,
                            delayBuf.length, inOutBuf.length);
                    if(ret >= 0) {
                        toastStr = "SPI Commu Delay Set Success";
                    } else {
                        toastStr = "SPI Commu Delay Set Fail";
                    }
                    break;

                case R.id.spiDevNoBtn:
                    byte[] devNoBuf = spiDevNoEdit.getText().toString().getBytes();
                    System.arraycopy(devNoBuf, 0, inOutBuf, 0, devNoBuf.length);
                    ret = devCommuJni.SendCmdMessage(DevCommuJni.DEV_CMD_SET_SPI_DEV_NO, inOutBuf,
                            devNoBuf.length, inOutBuf.length);
                    if(ret >= 0) {
                        toastStr = "SPI Dev No Set Success";
                    } else {
                        toastStr = "SPI Dev No Set Fail";
                    }
                    break;

                case R.id.spiReadDataBtn:
                case R.id.spiSendDataBtn:
                    /*byte[] spiDat = new byte[] {
                            0x06, 0x1C, 0x12, 0x34, 0x00, 0x04, (byte)0xA3, 0x51,
                            0x00, 0x00, 0x01, 0x60
                    };
                    System.arraycopy(spiDat, 0, inOutBuf, 0, spiDat.length);
                    ret = devCommuJni.SendCmdMessage(DevCommuJni.DEV_CMD_SPI_WRITE_READ, inOutBuf,
                            spiDat.length, inOutBuf.length);
                            if(ret > 0) {
                        toastStr = "SPI Read Success, Show to EditText";
                        String recvStr = inOutBuf[0] + ", ";
                        for(int i = 1; i < ret; i++) {
                            recvStr += (inOutBuf[i] + ", ");
                        }
                        spiSendDataEdit.setText(recvStr);
                    } else {
                        toastStr = "SPI Data Send Fail";
                    }*/

                    short cmd = 849;

                    shortToBytes(cmd, inOutBuf, 0);
                    ret = devCommuJni.SendCmdMessage(DevCommuJni.DEV_CMD_GET_SPI_SENSOR_DAT, inOutBuf,
                            2, inOutBuf.length);

                    if(ret >= 0) {
                        toastStr = "SPI Get Sensor Data:" + ret;
                    } else {
                        toastStr = "SPI Get Sensor Data Fail";
                    }
                    break;

                default:
                    break;
            }
            if(null != toastStr) {
                Toast.makeText(getApplicationContext(), toastStr,
                        Toast.LENGTH_SHORT).show();
            }
        }
    };

    @Override
    protected void onDestroy() {
        super.onDestroy();
        devCommuJni.SendCmdMessage(DevCommuJni.DEV_CMD_DEV_DEINIT, null, 0, 0);
    }

    public static int shortToBytes(short value, byte[] bytes, int offset) {
        int idx = offset;

        bytes[idx++] = (byte) (value & 0xFF);
        bytes[idx++] = (byte) ((value>>8) & 0xFF);

        return idx;
    }
}
