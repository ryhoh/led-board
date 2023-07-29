#include "LEDControllers.h"

Max7219::Max7219(uint8_t dat, uint8_t lat, uint8_t clk, uint8_t brightness)
{
#ifdef ARDUINO

  this->dat = dat;
  this->lat = lat;
  this->clk = clk;

  call_pinMode(dat, OUTPUT);
  call_pinMode(lat, OUTPUT);
  call_pinMode(clk, OUTPUT);

  this->send(0x0c, 0x01);  // シャットダウン -> オペレート
  this->send(0x0b, 0x07);  // スキャンリミット設定 -> 8桁
  this->send(0x09, 0x00);  // デコードモード -> No decodeモード

  // 残留表示を消去
  for (uint8_t addr_i = 1; addr_i < 9; ++addr_i) {
    this->send(addr_i, 0x0F);  // 文字blankを送信
  }

  // 輝度設定
  if (9 < brightness)
    brightness = 9;
  this->send(0x0a, brightness);

#endif  /* SIMULATOR */
}

void Max7219::testRun(uint8_t step)
{
#ifndef SIMULATOR  // シミュレータでは設定不要

  switch (step) {
  case 0:
    // ディスプレイテストモード（全点灯）
    this->send(0x0f, 0x01);
    break;
  case 1:
    // テストモード終了
    this->send(0x0f, 0x00);
    break;
  case 2:
    // リセット
    for (uint8_t addr_i = 1; addr_i < 9; ++addr_i) {
      this->send(addr_i, 0x00);
    }
    break;
  default:
    break;
  }

#endif  /* SIMULATOR */
}

void Max7219::flushMatrixLED(MatrixLED &matrixLED)
{
#ifdef SIMULATOR
  Mock_Max7219_flushMatrixLED(matrixLED);
#else  /* SIMULATOR */

  call_digitalWrite(this->lat, LOW);
  for (uint8_t row_i = 0; row_i < 8; ++row_i) {
    this->shiftOut(row_i + 1, *(matrixLED.buffer + row_i));
  }
  call_digitalWrite(this->lat, HIGH);
  call_digitalWrite(this->lat, LOW);

#endif  /* SIMULATOR */
}

void Max7219::flushMatrixLEDs(MatrixLED *matrixLEDs, uint8_t length)
{
#ifdef SIMULATOR
  Mock_Max7219_flushMatrixLEDs(matrixLEDs, length);
#else  /* SIMULATOR */

  for (uint8_t row_i = 0; row_i < 8; ++row_i) {
    call_digitalWrite(this->lat, LOW);
    for (uint8_t matrix_i = 0; matrix_i < length; ++matrix_i) {
        this->shiftOut(row_i + 1, *((matrixLEDs + matrix_i)->buffer + row_i));
    }
    call_digitalWrite(this->lat, HIGH);
    call_digitalWrite(this->lat, LOW);
  }

#endif  /* SIMULATOR */
}

inline void Max7219::shiftOut(uint8_t addr, uint8_t data)
{
  call_shiftOut(this->dat, this->clk, MSBFIRST, addr);
  call_shiftOut(this->dat, this->clk, MSBFIRST, data);
}

inline void Max7219::send(uint8_t addr, uint8_t data)
{
  call_digitalWrite(this->lat, LOW);
  this->shiftOut(addr, data);
  call_digitalWrite(this->lat, HIGH);
  call_digitalWrite(this->lat, LOW);
}