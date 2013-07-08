// Arduino Leonardo/Micro Spektrum Satellite servo demo
#include <Spektrum_Satellite.h>
#include <Servo.h>

Spektrum_Satellite rx;

// 8 servos (from pin 12 down to pin 5)
Servo servo[8];

void setup()
{
  // setup serial ports
  Serial.begin(115200);
  Serial1.begin(115200);
  // setup servos
  for (uint8_t index = 0; index < 8; ++index)
  {
    servo[index].attach(12 - index);
  }
}

void updateServos()
{
  for (uint8_t index = 0; index < 8; ++index)
  {
    servo[index].write(map(rx.getChannel(index), 0, 2047, 0, 179));
  }
}

void loop()
{
  if (Serial1.available())
  {
    uint8_t c = Serial1.read();
    if (rx.update(c))
    {
      // frame received
      updateServos();
    }
  }
}
