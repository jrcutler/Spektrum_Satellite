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
#include "Spektrum_Satellite.h"


Spektrum_Satellite::Spektrum_Satellite():
    channels(sizeof(channelData)/sizeof(channelData[0]))
{
    reset();
}


void Spektrum_Satellite::reset()
{
    for (uint8_t i = 0; i < channels; ++i)
    {
        channelData[i] = 0;
    }
    frame_index = 0;
    frame_seen = 0;
    last_update = millis();
}


boolean Spektrum_Satellite::update(uint8_t b)
{
    unsigned long current = millis();
    // detect inter-frame delay
    if (current - last_update > 6)
    {
        // start of frame
        frame_index = 0;
    }
    // add to frame
    frame[frame_index++] = b;
    if (frame_index == sizeof(frame))
    {
        // end of frame
        parseFrame();
        frame_index = 0;
    }
    last_update = current;
    return !frame_index && frame_seen == 3;
}


uint16_t Spektrum_Satellite::getHeader() const
{
    return header;
}


uint16_t Spektrum_Satellite::getChannel(uint8_t ch) const
{
    return ch < channels ? channelData[ch] : 0;
}


void Spektrum_Satellite::parseFrame(void)
{
    header = frame[0] << 8 | frame[1];

    if (!(frame[2] >> 7))
    {
        frame_seen = 1;
    }
    else
    {
        frame_seen |= 2;
    }

    for (uint8_t i = 2; i < sizeof(frame); i += 2)
    {
        uint8_t hi = frame[i];
        uint8_t lo = frame[i+1];
        // extract channel
        uint8_t ch = (hi >> 3) & 0xf;
        // if channel is valid, extract value
        if (ch < channels)
        {
            channelData[ch] = (hi & 0x7) << 8 | lo;
        }
    }
}
