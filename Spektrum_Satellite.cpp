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
