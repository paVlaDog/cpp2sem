#include "requests.h"

constexpr std::string_view mmt = "12-------P----\0";

namespace {
void skip(size_t number, const unsigned char *& pointer)
{
    pointer += number;
}
} // namespace

ExecutionDetails decode_executed_order(const std::vector<unsigned char> & message)
{
    ExecutionDetails exec_details;
    auto pointer = message.data();
    std::copy(mmt.begin(), mmt.end() + 1, exec_details.mmt);

#define FIELD(name, protocol_type, return_type) \
    exec_details.name = decode_##name(pointer);

#define FIELD_ARR(name, protocol_type, return_type, name_of_mas, index_in_mas) \
    exec_details.name_of_mas[index_in_mas] = decode_##name(pointer);

#define SKIP(number) \
    skip(number, pointer);

#include "executedOrderFields.h"

#undef FIELD
#undef FIELD_ARR

    return exec_details;
}

BrokenTradeDetails decode_broken_trade(const std::vector<unsigned char> & message)
{
    BrokenTradeDetails break_details;
    auto pointer = message.data();
    std::copy(mmt.begin(), mmt.end() + 1, break_details.mmt);

#define FIELD(name, protocol_type, return_type) \
    break_details.name = decode_##name(pointer);

#define FIELD_ARR(name, protocol_type, return_type, name_of_mas, index_in_mas) \
    break_details.name_of_mas[index_in_mas] = decode_##name(pointer);

#include "brokenTradeFields.h"

#undef FIELD
#undef FIELD_ARR
    return break_details;
}
