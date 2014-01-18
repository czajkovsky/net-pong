#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>

const unsigned char BEGIN_MESSAGE = 0xAB;
const unsigned char REQUEST_END = 0x11;
const unsigned char UPDATE_STATE = 0x12;
const unsigned char END_ACK = 0x13;

#endif // PROTOCOL_H
