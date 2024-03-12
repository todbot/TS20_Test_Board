#ifndef TS20_H
#define TS20_H

#include "Arduino.h"
#include <Wire.h>

// Register definitions
#define Sensitivity_PWM1 0x00   //ch2,ch1
#define Sensitivity_PWM2 0x01   //ch4,ch3
#define Sensitivity_PWM3 0x02   //ch6,ch5
#define Sensitivity_PWM4 0x03   //ch21,ch7
#define Sensitivity_PWM5 0x04   //ch9,ch8
#define Sensitivity_PWM6 0x05   //ch11,ch10
#define Sensitivity_PWM7 0x06   //ch13,ch12
#define Sensitivity_PWM8 0x07   //ch15,ch14
#define Sensitivity_PWM9 0x08   //ch17,ch16
#define Sensitivity_PWM10 0x09  //ch19,ch18
#define Sensitivity_PWM11 0x0A  //ch20
#define GTRL1 0x0B
#define GTRL2 0x0C
#define Cal_CTRL 0x0D

#define Port_CTRL1 0x0E
#define Port_CTRL2 0x0F
#define Port_CTRL3 0x10
#define Port_CTRL4 0x11
#define Port_CTRL5 0x12
#define Port_CTRL6 0x13

#define Cal_HOLD1 0x14
#define Cal_HOLD2 0x15
#define Cal_HOLD3 0x16

#define Err_CTRL 0x17  // "Err_Percent" in datasheet

#define Output1 0x20
#define Output2 0x21
#define Output3 0x22

#define Ref_wr_H 0x23
#define Ref_wr_L 0x24
#define Ref_wr_CH1 0x25
#define Ref_wr_CH2 0x26
#define Ref_wr_CH3 0x27

#define Sen_RD_CTRL 0x28
#define Sensitivity_RD 0x29

#define Rd_CH1 0x30
#define Rd_CH2 0x31
#define Rd_CH3 0x32
#define Sen_H 0x33
#define Sen_L 0x34
#define Ref_H 0x35
#define Ref_L 0x36
// FIXME: these need redefintion (same as above)
// #define Rd_CH1			0x37
// #define Rd_CH2			0x38
// #define Rd_CH3			0x39

#define TS20_ADDR_GND 0x6A       //0xD4>>1 //ADD Pin = GND
#define TS20_ADDR_VDD 0x7A       //0xF4>>1 //ADD Pin = VDD
#define TS20_ADDR_DEFAULT TS20_ADDR_GND  // choose how you have board configured

//#define PADSENS 0b0101  // 0x55
#define PADSENS 0b1111    // 0x00
//#define PADSENS 0b0000  // 0x00
#define PADSENS2 ((PADSENS<<4)|PADSENS)

class TS20 {
public:
  TS20();
  bool begin(uint8_t i2caddr = TS20_ADDR_GND, TwoWire *theWire = &Wire);
  uint32_t getTouches();

private:
  TwoWire *_wire;
  uint8_t _i2caddr;
};


#endif
