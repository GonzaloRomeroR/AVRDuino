import machine
from machine import Pin, I2C
import time

i2c = I2C(scl=Pin(14), sda=Pin(12), freq=100000)

while True:
        cadenaRecibida = "D50-----"
        if len (cadenaRecibida) == 8:
                for i in range( len(cadenaRecibida) ):
                        if cadenaRecibida[i] != '-':
                                i2c.writeto(8, cadenaRecibida[i])
                                time.sleep_ms(20)
                i2c.writeto(8, 'F')
                time.sleep_ms(20)

        print (cadenaRecibida)
        time.sleep_ms(5000)
