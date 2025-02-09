#!/usr/bin/env python3
import rospy
from geometry_msgs.msg import Twist
import sys, select, termios, tty

# Управляющие клавиши
MOVE_BINDINGS = {
    'w': (1, 0),  # Forward
    's': (-1, 0), # Revers
    'a': (0, 1),  # Left
    'd': (0, -1), # Right
    'x': (0, 0)   # Stop
}

# Speed
LINEAR_SPEED = 0.5  # Line speed
ANGULAR_SPEED = 1.0  # ang speed

def get_key():
    """ reading pressed key """
    tty.setraw(sys.stdin.fileno())  # off buffers
    select.select([sys.stdin], [], [], 0)
    key = sys.stdin.read(1)
    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)  # restore terminal
    return key

if __name__ == '__main__':
    settings = termios.tcgetattr(sys.stdin)  # Сохраняем настройки терминала

    rospy.init_node('teleop_keyboard')  # Инициализируем узел
    pub = rospy.Publisher('/cmd_vel', Twist, queue_size=10)  # Публикуем в топик /cmd_vel

    print("Управление:\nW - Вперёд\nS - Назад\nA - Влево\nD - Вправо\nX - Стоп\nCtrl+C - Выход")

    try:
        while not rospy.is_shutdown():
            key = get_key()
            if key in MOVE_BINDINGS:
                linear, angular = MOVE_BINDINGS[key]
                
                twist = Twist()
                twist.linear.x = linear * LINEAR_SPEED
                twist.angular.z = angular * ANGULAR_SPEED
                pub.publish(twist)  # Отправляем сообщение
                
                rospy.loginfo(f"Опубликовано: линейная скорость = {twist.linear.x}, угловая скорость = {twist.angular.z}")
            
            elif key == '\x03':  # Ctrl+C
                break

    except Exception as e:
        print(f"Ошибка: {e}")

    finally:
        twist = Twist()
        pub.publish(twist)  # Останавливаем робота перед выходом
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)  # Восстанавливаем терминал
