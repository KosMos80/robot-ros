import threading
import time


def periodic_interrupt():
    # Повторный вызов функции с тем же интервалом
    global timer
    global clk
    timer = threading.Timer(0.1, periodic_interrupt)  # Устанавливаем интервал в 2 секунды
    timer.start()
    #print("Сработало прерывание!", clk)
    st = "+"
    for i in range(clk):
        st =  st + "+"
    print(st)
    clk = clk + 1


def main():
    global clk
    clk = 0
    print("Программа начала выполнение.")
    
    # Запускаем первый вызов прерывания
    global timer
    timer = threading.Timer(0.1, periodic_interrupt)  # Устанавливаем интервал в 2 секунды
    timer.start()

    try:
        # Основной цикл программы
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
