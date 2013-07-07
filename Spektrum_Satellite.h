#ifndef SPEKTRUM_SATELLITE_H
#define SPEKTRUM_SATELLITE_H

#ifndef ARDUINO
# include <stdint.h>
#else
# if (ARDUINO >= 100)
#  include <Arduino.h>
# else
#  include <WProgram.h>
# endif
#endif

class Spektrum_Satellite
{
public:
  Spektrum_Satellite();

  void reset();
  boolean update(uint8_t b);

  uint16_t getHeader() const;
  uint16_t getChannel(uint8_t ch) const;

  const uint8_t channels;

protected:

  void parseFrame(void);
  uint16_t header;
  int16_t channelData[8];

private:
  unsigned long last_update;
  uint8_t frame_index;
  uint8_t frame_seen;
  uint8_t frame[16];
};

#endif
