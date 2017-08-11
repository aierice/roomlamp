#ifndef SERVO_H_
#define SERVO_H_

extern HardwareSerial  Serial1;
void torque_on();
void do_motion(int16_t *motion);

#endif
