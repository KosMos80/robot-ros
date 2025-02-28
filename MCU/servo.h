// lib fo servo privod


void init_pwm(void)
{
  DDRB |= (1 << PB1) | (1 << PB2);
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 1;
  // Fast PWM ? TOP = ICR1
  TCCR1A |= (1 << WGM11);

  TCCR1B |= (1 << WGM13) | (1 << WGM12);
  // OC1A  OC1B
  TCCR1A |= (1 << COM1A1) | (1 << COM1B1);
  // div 8
  TCCR1B |= (1 << CS11);
  // 40000 * (1 / 16) * 8 = 20000 us = 20 ms  == 50 Hz
  // 1 tik = 0.5 us
  // 544 us - 1088
  // 2400 us - 4800
  ICR1 = 39999;
  //OCR1A = 416;
  //OCR1B = 416;
}



// Функция для преобразования значения из одного диапазона в другой
long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Функция для установки ШИМ на пине OC1A (пин 9)
void setServoAngleA(uint8_t angle) 
{
  // Преобразуем угол (0-180) в значение ШИМ (1088-4800)
  uint16_t pwmValue = map(angle, 0, 180, 1080, 4800);
  OCR1A = pwmValue;
  print_int(pwmValue);
}

// Функция для установки ШИМ на пине OC1B (пин 10)
void setServoAngleB(uint8_t angle) 
{
  // Преобразуем угол (0-180) в значение ШИМ (1088-4800)
  uint16_t pwmValue = map(angle, 0, 180, 1080, 4800);
  OCR1B = pwmValue;
}
