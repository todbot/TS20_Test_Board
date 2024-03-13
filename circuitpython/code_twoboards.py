import time
import board
import busio 
import neopixel

from ts20 import TS20

leds = neopixel.NeoPixel(board.GP22, 64, brightness=0.2, auto_write=False)

i2c = busio.I2C(scl=board.GP5, sda=board.GP4)
ts20A = TS20(i2c, 0x6a)
ts20B = TS20(i2c, 0x7a)

print("hi")
padA_to_led = [
    0, 15, 16, 31, 32,
    1, 14, 17, 30, 33,
    2, 13, 18, 29, 34,
    3, 12, 19, 28, 35,
    63,
]

padB_to_led = [
    4, 11, 20, 27, 36,
    5, 10, 21, 26, 37,
    6,  9, 22, 25, 38,
    7,  8, 23, 24, 39,
    63,
]

time.sleep(1)

print("setting pad sensitivties")
senses = [15] * 20
#senses[4] = 0  # make pad #5 a proximity sensor
#ts20.set_pad_sensitivities(senses)

last_print_time = 0
#dim_by = 15
while True:
    touchesA = ts20A.read_touches()
    touchesB = ts20B.read_touches()
    
    if time.monotonic() - last_print_time > 0.1:
        last_print_time = time.monotonic()
        print(touchesB, touchesA)
        
    leds.fill(0)
    for i,t in enumerate(touchesA):
        if t:
            leds[padA_to_led[i]] = 0xff00ff
    for i,t in enumerate(touchesB):
        if t:
            leds[padB_to_led[i]] = 0xff00ff
    leds.show()
    
    time.sleep(0.005)
