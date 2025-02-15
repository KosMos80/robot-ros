import threading
import time

from pyA20.gpio import gpio
from pyA20.gpio import port

timer_const = 0.0001

def periodic_interrupt():
    #
    global timer
    global clk
    global pwm
    timer = threading.Timer(timer_const, periodic_interrupt)  # interval 2 s
    timer.start()
    clk = clk + 1
    if(clk == 32):
        clk = 0
    if(pwm > clk):
        gpio.output(port.PA7, gpio.HIGH)
    else:
        gpio.output(port.PA7, gpio.LOW)


def main():
    gpio.init()
    gpio.setcfg(port.PA7, gpio.OUTPUT)
    gpio.setcfg(port.PA9, gpio.OUTPUT)

    global clk
    global pwm
    pwm = 0
    clk = 0
    print("Prog start point.")

    # Start first int
    global timer
    timer = threading.Timer(timer_const, periodic_interrupt)  # interval 2 s
    timer.start()

    try:
        # Main loop
        num = 0
        while True:
            pwm = pwm + 1
            if(pwm == 32):
                pwm = 0
            print("PWM = ", pwm)
            gpio.output(port.PA9, gpio.HIGH)
            time.sleep(0.1)
            gpio.output(port.PA9, gpio.LOW)
            time.sleep(0.9)
            pass
    except KeyboardInterrupt:
        print("Stoping programm.")
        timer.cancel()  # Stop timers

if __name__ == "__main__":
    main()
