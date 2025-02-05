from pyA20.gpio import gpio
from pyA20.gpio import port
from time import sleep

#initialize the gpio module
gpio.init()

#setup the port (same as raspberry pi's gpio.setup() function)

gpio.setcfg(port.PA7, gpio.OUTPUT)
gpio.setcfg(port.PA8, gpio.OUTPUT)
gpio.setcfg(port.PA9, gpio.OUTPUT)
gpio.setcfg(port.PA10, gpio.OUTPUT)

try:
    while True:
        for i in range(16):
            print(i)
            dd = i
            if((dd % 2) == 1):
                print("ON pin PA7")
                gpio.output(port.PA7, gpio.HIGH)
            else:
                print("OFF pin PA7")
                gpio.output(port.PA7, gpio.LOW)
            dd = int(dd / 2)

            if((dd % 2) == 1):
                print("ON pin PA8")
                gpio.output(port.PA8, gpio.HIGH)
            else:
                print("OFF pin PA8")
                gpio.output(port.PA8, gpio.LOW)
            sleep(1)

except KeyboardInterrupt:
    print("--")
    gpio.output(port.PA7, gpio.LOW)
