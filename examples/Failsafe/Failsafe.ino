// Arduino Leonardo/Micro Spektrum Satellite failsafe demo (turn on LED on fail)
#include <Spektrum_Satellite.h>
#include "Watchdog.h"

Spektrum_Satellite rx;

const uint8_t LED = 13;
volatile boolean rx_failure = false;

void setup()
{
  // setup LED
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  // wait for serial monitor
  while (!Serial);
  // setup serial ports
  Serial.begin(115200);
  Serial1.begin(115200);
  // trigger watchdog IRQ after 500ms without a frame
  wdt_enable_irq(WDTO_500MS);
}

ISR(WDT_vect)
{
  // communications failure: set failure flag & turn on LED
  rx_failure = true;
  digitalWrite(LED, HIGH);
  // reset watchdog to prevent IRQ loop
  wdt_reset();
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
      // frame received: clear failure flag, turn off LED & reset watchdog
      rx_failure = false;
      digitalWrite(LED, LOW);
      wdt_reset();
      dumpChannels();
    }
  }
}
