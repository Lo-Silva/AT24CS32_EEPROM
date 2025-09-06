// AT24CS32.h
// Header file for AT24C32 EEPROM driver
#include <Wire.h>
#include <stdint.h>
#include <Arduino.h>

#ifndef AT24CS32_H
#define AT24CS32_H

#define PAGE_SIZE 32                // Page Size
#define SN_START 0x800              // First byte in 16 byte SN 
#define EEPROM_ADDRESS 0x50         // EEPROM address (replace with configured address)
#define SERIAL_NUMBER_ADDRESS 0x58  // SN address (replace with configured address)

class AT24CS32
{
    private:
        uint8_t* eepromPtr;
        uint8_t* pageDataPtr;
        uint8_t* serialNumberPtr;
        void dummyWrite(uint16_t address, uint8_t deviceAddress);
        
        public:
        AT24CS32();
        ~AT24CS32();
        uint8_t* readSerialNumber();
        uint8_t readByte(uint16_t address);
        uint8_t* readPage (uint16_t address);
        uint8_t writeByte(uint16_t address, const uint8_t data);
        uint8_t writePage (uint16_t address, const uint8_t* data) ;
        uint8_t* dumpEEPROM(uint16_t startAddress = 0x0000, uint16_t endAddress = 0x0FFF)
}
#endif // AT24CS32_H