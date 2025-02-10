import threading
import time

from pyA20.gpio import gpio
from pyA20.gpio import port


def periodic_interrupt():
    # 
    global timer
    global clk
    global pwm
    timer = threading.Timer(0.0025, periodic_interrupt)  # interval 2 s
    timer.start()
    clk = clk + 1
    if(clk == 32):
        clk = 0
    if(pwm > clk):
        gpio.output(port.PA7, gpio.HIGH)
    else:
        gpio.output(port.PA7, gpio.LOW)


def main():
    gpio.setcfg(port.PA7, gpio.OUTPUT)

    global clk
    global pwm
    pwm = 0
    clk = 0
    print("Prog start point.")
    
    # Start first int
    global timer
    timer = threading.Timer(1, periodic_interrupt)  # interval 2 s
    timer.start()

    try:
        # Main loop
        num = 0
        while True:
            pwm = pwm + 1
            if(pwm == 32):
                pwm = 0
            time.sleep(1)
            pass
    except KeyboardInterrupt:
        print("Stoping programm.")
        timer.cancel()  # Stop timers

if __name__ == "__main__":
    main()