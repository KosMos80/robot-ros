import threading
import time


def periodic_interrupt():
    # 
    global timer
    global clk
    timer = threading.Timer(0.1, periodic_interrupt)  # interval 2 s
    timer.start()
    print("work INT!", clk)
    st = "+"
    for i in range(clk):
        st =  st + "+"
    print(st)
    clk = clk + 1


def main():
    global clk
    clk = 0
    print("Prog start point.")
    
    # Start first int
    global timer
    timer = threading.Timer(0.1, periodic_interrupt)  # interval 2 s
    timer.start()

    try:
        # Main loop
        num = 0
        while True:
            print("Выполнение программы:",  num , "   +++++++++++++++++   ")
            num = num + 1
            clk = 0
            time.sleep(5)
            pass
    except KeyboardInterrupt:
        print("Остановка программы.")
        timer.cancel()  # Останавливаем таймер при завершении программы

if __name__ == "__main__":
    main()
