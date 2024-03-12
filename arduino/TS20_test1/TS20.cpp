

#include "TS20.h"


byte config_info[] = {
  // register name, register data
  // RB_SEL=Noram, Sleep Mode=Disable, S/W Reset=Enable, IMP_SEL=High Imp. S/M_Mode=Multi, VPM=0
  GTRL2, 0x1A, // put chip into reset, so we can change parameters? 
  // set all ports to capsense (as opposed to LED driver or tact switch)
  Port_CTRL1, 0x00,  // Port Control  
  Port_CTRL2, 0x00,
  Port_CTRL3, 0x00,
  Port_CTRL4, 0x00,
  Port_CTRL5, 0x00,
  Port_CTRL6, 0x00,
  // Sensitivty
  // if SSC bit =1(Normal Step) , (Data Value x 0.2%)+0.15%
  // if SSC bit =0(Fine Stemp) , (Data Value x 0.1%)+0.05%  
  Sensitivity_PWM1,  PADSENS2,  // Sensitivty control,(threshold level), ch2,1
  Sensitivity_PWM2,  PADSENS2,  // Sensitivty control,(threshold level), ch4,3
  Sensitivity_PWM3,  PADSENS2,  // Sensitivty control,(threshold level), ch6,5
  Sensitivity_PWM4,  PADSENS2,  // Sensitivty control,(threshold level), ch7
  Sensitivity_PWM5,  PADSENS2,  // Sensitivty control,(threshold level), ch9,8
  Sensitivity_PWM6,  PADSENS2,  // Sensitivty control,(threshold level), ch11,10
  Sensitivity_PWM7,  PADSENS2,  // Sensitivty control,(threshold level), ch13,12
  Sensitivity_PWM8,  PADSENS2,  // Sensitivty control,(threshold level), ch15,14
  Sensitivity_PWM9,  PADSENS2,  // Sensitivty control,(threshold level), ch17,16
  Sensitivity_PWM10, PADSENS2,  // Sensitivty control,(threshold level), ch19,18
  Sensitivity_PWM11, PADSENS2,  // Sensitivty control,(threshold level), ch20
  // General Ctrl1: SSC= Normal Step, MS=Auto Mode, FTC=5sec, Respons Time Control(RTC)= 011b + 1 = 4 times
  GTRL1, 0x4B,      // 0x4A is reset default, 0x4B  // general control, 
  Cal_HOLD1, 0x00,  // Calibration On, ch 1-7
  Cal_HOLD2, 0x00,  // Calibration On, ch 8-14
  Cal_HOLD2, 0x00,  // Calibration On, ch 9-20
  Err_CTRL, 0x0D,    // what
  Cal_CTRL, 0xFA,   // are these
  // General Ctrl2: RB_SEL=Noram, Sleep Mode=Disable, S/W Reset=Disable, IMP_SEL=Low Imp. S/M_Mode=Multi, VPM=0
  //GTRL2, 0x12,     // Software Reset Disable (Clear)
  // General Ctrl2: RB_SEL=Noram, Sleep Mode=Disable, S/W Reset=Disable, IMP_SEL=Low Imp. S/M_Mode=Multi, VPM=0
  GTRL2, 0x02,     // Software Reset Disable (Clear)
};


/*!
 *  @brief      Default constructor
 */
TS20::TS20() {}

/*!
 *  @brief    Begin a TS20 object on a given I2C bus. This function resets
 *            the device and writes the default settings.
 *  @param    i2caddr
 *            the i2c address the device can be found on. Defaults to 0x6A.
 *  @param    *theWire
 *            Wire object
 *  @param    touchThreshold
 *            touch detection threshold value
 *  @param    releaseThreshold
 *            release detection threshold value
 *  @returns  true on success, false otherwise
 */
bool TS20::begin(uint8_t i2caddr, TwoWire *theWire ) {
                //  uint8_t touchThreshold, uint8_t releaseThreshold) {
  _wire = theWire;
  _i2caddr = i2caddr;
  _wire->begin();

  int config_len = sizeof(config_info);
  for (int i = 0; i < config_len; i += 2) {
    byte reg_addr = config_info[i];
    byte reg_val = config_info[i + 1];
    _wire->beginTransmission(_i2caddr);  // send ic peripheral address
    _wire->write(reg_addr);               // sends register address
    _wire->write(reg_val);                // sends register data
    _wire->endTransmission();             // stop transmitting
  }
  return true;   // FIXME: check to see if there's actually a device
}

/*!
 *  @brief    Rreturn bit field of which pads have been touched 
 **/
uint32_t TS20::getTouches() {
  _wire->beginTransmission(_i2caddr);  // send i2c peripheral address
  _wire->write(byte(Output1));          // send ts20 register address
  _wire->endTransmission();             // stop transmitting
  _wire->requestFrom(_i2caddr, 3);     // ask for data read (3 byte)
  byte d0 = Wire.read();
  byte d1 = Wire.read();
  byte d2 = Wire.read();
  uint32_t touches = d0 | (d1<<7) | (d2<<15);
  return touches;
}


