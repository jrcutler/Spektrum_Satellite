// Arduino Leonardo/Micro Spektrum Satellite demo
#include <Spektrum_Satellite.h>

Spektrum_Satellite rx;

void setup()
{
  // wait for serial monitor
  while (!Serial);
  // setup serial ports
  Serial.begin(115200);
  Serial1.begin(115200);
}

void dumpChannels()
{
  for (uint8_t ch = 0; ch < rx.channels; ++ch)
  {
    Serial.print(rx.getChannel(ch));
    Serial.write(ch == rx.channels - 1 ? '\n' : ',');
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
      dumpChannels();
    }
  }
}
