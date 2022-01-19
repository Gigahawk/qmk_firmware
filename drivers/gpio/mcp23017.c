#include "i2c_master.h"
#include "mcp23017.h"

#include "debug.h"

#define SLAVE_TO_ADDR(n) (n << 1)
#define TIMEOUT 100

void mcp23017_init(uint8_t slave_addr) {
    static uint8_t s_init = 0;
    uint8_t        addr   = SLAVE_TO_ADDR(slave_addr);
    uint8_t        reg;
    i2c_status_t   ret;
    uint8_t        conf = 0;

    if (!s_init) {
        i2c_init();

        s_init = 1;
    }

    // In the event that IOCON.BANK is set, the address of IOCON changes to
    // BANK1_IOCON == GPINTENB.
    // Since both registers default to 0 on POR, it is assumed to be safe to
    // set either register to 0 ensure that IOCON is at the expected address
    reg = MCP23017_BANK1_IOCON;
    ret = i2c_writeReg(addr, reg, &conf, sizeof(conf), TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        print("mcp23017_init: failed to set BANK1_IOCON to 0\n");
        return;
    }
    reg = MCP23017_IOCON;
    ret = i2c_writeReg(addr, reg, &conf, sizeof(conf), TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        print("mcp23017_init: failed to set IOCON\n");
    }
}

void mcp23017_set_config(uint8_t slave_addr, uint8_t port, uint8_t conf) {
    uint8_t addr = SLAVE_TO_ADDR(slave_addr);
    uint8_t reg  = port ? MCP23017_IODIRB : MCP23017_IODIRA;

    i2c_status_t ret = i2c_writeReg(addr, reg, &conf, sizeof(conf), TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        print("mcp23017_set_config: failed to set IODIR");
    }
}

void mcp23017_set_output(uint8_t slave_addr, uint8_t port, uint8_t conf) {
    uint8_t addr = SLAVE_TO_ADDR(slave_addr);
    uint8_t reg  = port ? MCP23017_GPIOB : MCP23017_GPIOA;

    i2c_status_t ret = i2c_writeReg(addr, reg, &conf, sizeof(conf), TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        print("mcp23017_set_output: failed to set GPIO");
    }
}

uint8_t mcp23017_read_pins(uint8_t slave_addr, uint8_t port) {
    uint8_t addr = SLAVE_TO_ADDR(slave_addr);
    uint8_t reg  = port ? MCP23017_GPIOB : MCP23017_GPIOA;
    uint8_t data = 0;

    i2c_status_t ret = i2c_readReg(addr, reg, &data, sizeof(data), TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        print("mcp23017_read_pins: failed to read GPIO");
    }
    return data;
}

uint16_t mcp23017_read_all_pins(uint8_t slave_addr) {
    uint8_t addr = SLAVE_TO_ADDR(slave_addr);
    uint8_t reg  = MCP23017_GPIOA;

    typedef union {
        uint8_t  u8[2];
        uint16_t u16;
    } data16;

    data16 data;

    i2c_status_t ret = i2c_readReg(addr, reg, &data.u8[0], sizeof(data), TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        print("mcp23017_read_all_pins: failed to read GPIO");
    }
    return data.u16;
}
