#pragma once

#include <bitset>
#include <cmath>
#include <cstdint>
#include <string>

inline unsigned decodeBits(const unsigned char *& start, size_t startBit, size_t length)
{
    std::bitset<8> bin(*start);
    startBit -= 1;
    unsigned ans = 0;
    for (size_t i = 0; i < length; i++) {
        ans *= 2;
        ans += bin[startBit + i];
    }
    return ans;
}

inline bool decodeBool(const unsigned char *& start, size_t bit)
{
    return std::bitset<8>(*start)[bit - 1];
}

inline unsigned decodeUnsigned(const unsigned char *& start)
{
    unsigned ans = 0;
    for (size_t i = 0; i < 4; i++) {
        ans <<= 8;
        ans += *start++;
    }
    return ans;
}

inline double decodeChar(const unsigned char *& start)
{
    return *start++;
}

inline double decodePrice(const unsigned char *& start)
{
    return decodeUnsigned(start) / 10000.0;
}

inline std::string decodeString(const unsigned char *& start, size_t length)
{
    std::string ans;
    const unsigned char * begin = start;
    for (size_t i = 0; i < length; ++i) {
        start++;
        if (!std::isalnum(*start) || i == length - 1) {
            ans.assign(begin, start);
            start += length - i - 1;
            break;
        }
    }
    return ans;
}

inline LiquidityIndicator convertExecutedLiquidityIndicator(unsigned number)
{
    switch (number) {
    case 0:
        return LiquidityIndicator::Added;
    case 2:
        return LiquidityIndicator::Removed;
    default:
        return LiquidityIndicator::None;
    }
}

inline BreakReason convertBrokenReason(unsigned char ch)
{
    switch (ch) {
    case 'E':
        return BreakReason::Erroneous;
    case 'C':
        return BreakReason::Consent;
    case 'S':
        return BreakReason::Supervisory;
    case 'X':
        return BreakReason::External;
    default:
        return BreakReason::Unknown;
    }
}

inline LiquidityIndicator decodeLiquidityIndicator(const unsigned char *& start, size_t arg1, size_t arg2)
{
    return convertExecutedLiquidityIndicator(decodeBits(start, arg1, arg2));
}

inline BreakReason decodeBreakReason(const unsigned char *& start)
{
    return convertBrokenReason(decodeChar(start));
}

#define FIELD(name, protocol_type, return_type)                    \
    inline return_type decode_##name(const unsigned char *& start) \
    {                                                              \
        return decode##protocol_type(start);                       \
    }

#define ADD_ARITY_FIELD(name, protocol_type, return_type, arg1)    \
    inline return_type decode_##name(const unsigned char *& start) \
    {                                                              \
        return decode##protocol_type(start, arg1);                 \
    }

#define TWO_ADD_ARITY_FIELD(name, protocol_type, return_type, arg1, arg2) \
    inline return_type decode_##name(const unsigned char *& start)        \
    {                                                                     \
        return decode##protocol_type(start, arg1, arg2);                  \
    }

#define SKIP(number)

#include "decodeFields.h"

#undef FIELD
#undef ADD_ARITY_FIELD
#undef TWO_ADD_ARITY_FIELD
#undef SKIP
