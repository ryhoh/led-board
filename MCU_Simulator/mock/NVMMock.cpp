#include "NVMMock.h"

static char mock_rom[MOCK_EEPROM_SIZE] = {
  // Reference: NVM.h

  /* [0x00] - [0x1F] : SSID */
  0x53, 0x53, 0x49, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // "SSID"
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  /* [0x20] - [0x3F] : Password */
  0x50, 0x61, 0x73, 0x73, 0x77, 0x6f, 0x72, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // "Password"
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  /* [0x40] - [0x5F] : Device Name */
  0x53, 0x69, 0x6d, 0x75, 0x6c, 0x61, 0x74, 0x6f, 0x72, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // "Simulator"
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  /* [0x60] - [0x60] : Variant Index */
  0x01,
};

void NVM_Mock_Read(int32_t begin_addr, char buf[], uint32_t size) {
  for (int32_t i = 0; i < (int32_t)size; i++) {
    const int32_t from_addr = begin_addr + i;
    if (from_addr < 0 || from_addr >= MOCK_EEPROM_SIZE) {
      buf[i] = 0;
    } else {
      buf[i] = mock_rom[from_addr];
    }
  }
}

void NVM_Mock_Write(int32_t begin_addr, const char buf[], uint32_t size) {
  for (int32_t i = 0; i < (int32_t)size; i++) {
    const int32_t to_addr = begin_addr + i;
    if (to_addr >= 0 && to_addr < MOCK_EEPROM_SIZE) {
      mock_rom[to_addr] = buf[i];
    }
  }
}
