
# for install:  pip install pyserial-asyncio

import asyncio
import serial_asyncio

# config UART3
UART_PORT = "/dev/ttyS3"  # nomer porta uart (sample, /dev/serial0)
BAUDRATE = 9600  # speed
BYTESIZE = 8  # bit
PARITY = 'N'  # parytet
STOPBITS = 1  # stop bit

class UARTProtocol(asyncio.Protocol):
    def connection_made(self, transport):
        """Called in by setup conection with UART"""
        self.transport = transport
        print(f"Connect with : {UART_PORT}")

    def data_received(self, data):
        """Вызывается при получении данных"""
        print(f"Получено: {data.decode(errors='ignore')}")
        self.transport.write(b"ACK")  # Отправка подтверждения

    def connection_lost(self, exc):
        """Вызывается при потере соединения"""
        print("Соединение потеряно")
        if exc:
            print(f"Ошибка: {exc}")

async def main():
    """Основная асинхронная функция"""
    loop = asyncio.get_running_loop()
    transport, protocol = await serial_asyncio.create_serial_connection(
        loop, UARTProtocol, UART_PORT, baudrate=BAUDRATE, bytesize=BYTESIZE, parity=PARITY, stopbits=STOPBITS
    )

    try:
        while True:
            await asyncio.sleep(1)  # Рабочий цикл
    except KeyboardInterrupt:
        print("Выход...")
        transport.close()

# Запуск программы
asyncio.run(main())

