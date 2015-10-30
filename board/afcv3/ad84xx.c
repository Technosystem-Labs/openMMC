#include "port.h"
#include "pin_mapping.h"
#include "ad84xx.h"

void dac_vadj_init( void )
{
    gpio_set_pin_dir( GPIO_DAC_VADJ_RST_PORT, GPIO_DAC_VADJ_RST_PIN, OUTPUT);
    gpio_set_pin_dir( GPIO_DAC_VADJ_CSN_PORT, GPIO_DAC_VADJ_CSN_PIN, OUTPUT);
    gpio_set_pin_state( GPIO_DAC_VADJ_RST_PORT, GPIO_DAC_VADJ_RST_PIN, LOW);

    ssp_config( DAC_VADJ_SPI, DAC_VADJ_SPI_SPEED, DAC_VADJ_FRAME_SIZE, MASTER_MODE, POLLING );

    gpio_set_pin_state( GPIO_DAC_VADJ_RST_PORT, GPIO_DAC_VADJ_RST_PIN, HIGH);
}

void dac_vadj_config( uint8_t addr, uint8_t val )
{
    uint8_t data[2] = { addr, val };
    ssp_write( DAC_VADJ_SPI, &data[0], sizeof(data)/sizeof(data[0]) );
}