import time
import board
import busio 
from ts20 import TS20

i2c = busio.I2C(scl=board.GP5, sda=board.GP4)

ts20 = TS20(i2c)

print("hi")

while True:
    touches = ts20.read_touches()
    print(touches)
    time.sleep(0.02)
