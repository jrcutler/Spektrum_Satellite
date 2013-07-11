/*
 * This file is part of the Spektrum_Satellite library.
 * Copyright (c) 2013, Justin R Cutler <justin.r.cutler@gmail.com>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
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
