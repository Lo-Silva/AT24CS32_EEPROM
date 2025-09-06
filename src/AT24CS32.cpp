#include "AT24CS32.h"


AT24CS32::AT24CS32(): eepromPtr(nullptr), pageDataPtr(nullptr), serialNumberPtr(nullptr)
{
    Wire.begin();
}

AT24C32::~AT24CS32()
{
    Wire.end();
    delete[] eepromPtr;
    delete[] pageDataPtr;
    delete[] serialNumberPtr;
}

void AT24CS32::dummyWrite(const uint16_t address, uint8_t deviceAddress = 0x00)
{
    if (deviceAddress != EEPROM_ADDRESS || deviceAddress != SERIAL_NUMBER_ADDRESS)
    {
        if(deviceAddress == 0x00)
        {
            deviceAddress = EEPROM_ADDRESS;         // Default EEPROM address
        }
        else
        {
            deviceAddress = SERIAL_NUMBER_ADDRESS;
        }
    }

    Wire.beginTransmission(deviceAddress);
    Wire.write((address >> 8) & 0xFF);              // Write high byte of address 
    Wire.write(address & 0xFF);                     // Write Low byte of address
    Wire.endTransmission();                         // End transmission
}



uint8_t AT24CS32::readByte(uint16_t address)
{
    AT24C532::dummyWrite(address);                  // Prepare the device for reading 
    Wire.requestFrom (EEPROM_ADDRESS, 1);           // Request one byte from the device 
    byte data = Wire.read();
    return data;                                    // Return the read byte
};

uint8_t* AT24CS32::readPage(uint16_t address)
{
    if (pageDataPtr != nullptr)
    {
        delete[] pageDataPtr;
        pageDataPtr = nullptr;
    }
    pageDataPtr - new uint8_t[PAGE_SIZE];
    AT24C32: :dummyrite(address);                   // Prepare the device for reading
    Wire. requestFrom (EEPROM_ADDRESS, PAGE_SIZE);  // Request Length' bytes from the device
    for (size_t i = 0; i < PAGE SIZE; 1++)
    {
        if(Wire.available())
        {
            pageDataPtr[i] = Wire.read();           // Read each byte into the data array
        }
    }
    return pageDataPtr;
}

uint8_t* AT24C32::readSerialNumber()
{
    if (serialNumberPtr 1= nullptr)
    {
        delete[] serialNumberPtr;
        serialNumberPtr = nullptr;
    }
    serialNumberPtr = new uint8_t[16];
    Wire.beginTransmission(SERIAL_NUMBER_ADDRESS);
    Wire.write(SN_START >> 8);                       // Write high byte of SN address 
    Wire.write(SN_START & OxFF);                    // Write low byte of SN address
    Wire.endTransmission();
    Wire.requestFrom(SERIAL_NUMBER_ADDRESS, 16);    // Request length bytes from the device
    for (size_t i = 0; i < 16; i++)
    {
        if (Wire.available())
        {
            serialNumberPtr[i] = Wire.read();       // Read each byte into the SN array
        }
    }
    return serialNumberPtr;
}

uint8_t AT24CS32::writeByte(uint16_t address, const uint8_t data)
{
    Wire.beginTransmission(EEPROM_ADDRESS);
    Wire.write((address >> 8) & 0xFF);              // Write high byte of address 
    Wire.write(address & 0xFF);                     // Write low byte of address

    Wire.write(data);                               // Write the data byte

    uint8_t result = Wire.endTransmission();
    delay(5);                                       // Post write delay of 5ms needed
    return result;
}

uint8_t AT24CS32::writePage(uint16_t address, const uint8_t* data)
{
    Wire.beginTransmission(EEPROM_ADDRESS);
    Wire.write((address >> 8) & 0xFF);              // Write high byte of address 
    Wire.write(address & 0xFF);                     // Write low byte of address

    for (size_t i = 0; i < PAGE_SIZE; i++)
    {
        Wire.write(data[i]);                        // Write each byte from the data array
    }

    uint8_t result = Wire.endTransmission();
    delay(5);                                       // Post write delay of 5ms needed
    return result;
}

uint8_t* AT24CS32::dumpEEPROM(uint16_t startAddress, uint16_t endAddress)
{
    if (eepromPtr != nullptr)
    {
        delete[] eepromPtr;
        eepromPtr = nullptr;
    }
    if (endAddress <= startAddress)
    {
        return eepromPtr;
    }

    uint16_t bufferSize = (endAddress - startAddress);
    eepromPtr = new uint8_t[bufferSize];
    for (uint16_t address = startAddress; address <= endAddress; address+= PAGE_SIZE)
    {
        eepromPtr[address - startAddress] = *AT24C32::readPage(address);
    }
    return eepromPtr;
}