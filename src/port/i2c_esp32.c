#include "i2c_a7.h"
#include <driver/i2c.h>

#include "sm_timer.h"
#include <stdio.h>
#include "sci2c_cfg.h"
#include "sm_printf.h"

#define SDA_PIN                            21
#define SCL_PIN                            22
#define ACK_CHECK_EN                       0x1
#define ACK_CHECK_DIS                      0x0
#define ACK_VAL                            0x0
#define NACK_VAL                           0x1

i2c_config_t conf;

/* Handle NAK */
static int gBackoffDelay;

void ResetBackoffDelay() {
    gBackoffDelay = 0;
}

static void BackOffDelay_Wait() {
    if (gBackoffDelay < 200 )
        gBackoffDelay += 1;
    sm_sleep(gBackoffDelay);
}
#define I2C_LOG_PRINTF PRINTF

static i2c_port_t axSmDevice_port = I2C_NUM_1;
//static int axSmDevice_addr = 0x48;  

i2c_error_t axI2CInit(void)
{
    esp_err_t rc;

            conf.mode = I2C_MODE_MASTER;
            conf.sda_io_num = SDA_PIN;
            conf.scl_io_num = SCL_PIN;
            conf.sda_pullup_en = GPIO_PULLUP_DISABLE;
            conf.scl_pullup_en = GPIO_PULLUP_DISABLE;
            conf.master.clk_speed = 100000; 
            rc = i2c_param_config(axSmDevice_port, &conf);
            rc = i2c_driver_install(axSmDevice_port, I2C_MODE_MASTER, 0, 0, 0);

    if (rc == ESP_OK)
    {
        return I2C_OK;
    }
    else
    {
        return I2C_FAILED;
    }
    
}

/**
* Closes the communication channel to I2C device (not implemented)
*/
void axI2CTerm(int mode)
{
    AX_UNUSED_ARG(mode);
    i2c_driver_delete(axSmDevice_port);
    return;
}


i2c_error_t axI2CWrite(unsigned char bus, unsigned char addr, unsigned char * pTx, unsigned short txLen)
{

    if (bus != I2C_BUS_0)
    {
        return I2C_FAILED;
    }

    esp_err_t rc;

    i2c_cmd_handle_t cmdhandle = i2c_cmd_link_create();
    (void)i2c_master_start(cmdhandle);
    (void)i2c_master_write_byte(cmdhandle, addr | I2C_MASTER_WRITE, ACK_CHECK_EN);
    (void)i2c_master_write(cmdhandle, pTx, txLen, ACK_CHECK_EN);
    (void)i2c_master_stop(cmdhandle);
    rc = i2c_master_cmd_begin(axSmDevice_port, cmdhandle, 1000 / portTICK_RATE_MS);

    if (ESP_OK != rc)
    {

        if (ESP_FAIL == rc)
        {
            BackOffDelay_Wait();
            (void)i2c_cmd_link_delete(cmdhandle);
            return I2C_NACK_ON_ADDRESS;
        }


        printf("axi2cwrite (i2c_master_cmd_begin)failure");
        (void)i2c_cmd_link_delete(cmdhandle);
        return I2C_FAILED;
    }
    else
    {
        (void)i2c_cmd_link_delete(cmdhandle);
        ResetBackoffDelay();
        return I2C_OK;
    }
}


i2c_error_t axI2CRead(unsigned char bus, unsigned char addr, unsigned char * pRx, unsigned short rxLen)
{
    if (bus != I2C_BUS_0)
    {
        return I2C_FAILED;
    }

    esp_err_t rc;
    i2c_cmd_handle_t cmdhandle;

    

    cmdhandle = i2c_cmd_link_create();
    rc = i2c_master_start(cmdhandle);
    if (ESP_OK != rc)
    {
        printf("axi2cread (i2c_master_start)failure");
        return I2C_FAILED;
    }


    rc = i2c_master_write_byte(cmdhandle, (uint8_t)addr | I2C_MASTER_READ, ACK_CHECK_EN);
    if (ESP_OK != rc)
    {

        if (ESP_FAIL == rc)
        {
            BackOffDelay_Wait();
            return I2C_NACK_ON_ADDRESS;
        }

        printf("axi2cread (i2c_master_write_byte)failure");
        return I2C_FAILED;
    }

    if (rxLen > 1) {
        i2c_master_read(cmdhandle, pRx, rxLen - 1, ACK_VAL);
    }
    i2c_master_read_byte(cmdhandle, pRx + rxLen - 1, NACK_VAL);
	i2c_master_stop(cmdhandle);

    rc = i2c_master_cmd_begin(axSmDevice_port, cmdhandle, 1000 / portTICK_RATE_MS);
    if (ESP_OK != rc)
    {

        if (ESP_FAIL == rc)
        {
            BackOffDelay_Wait();
            (void)i2c_cmd_link_delete(cmdhandle);
            return I2C_NACK_ON_ADDRESS;
        }


        (void)i2c_cmd_link_delete(cmdhandle);
        return I2C_FAILED;
    }      
    
    (void)i2c_cmd_link_delete(cmdhandle);
    ResetBackoffDelay();
    return I2C_OK;
    
}
