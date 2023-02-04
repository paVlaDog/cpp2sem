#if !defined(FIELD) || !defined(FIELD_ARR)
#error You need to define FIELD and FIELD_ARR macro
#else

SKIP(9)
FIELD(cl_ord_id, String, std::string)
FIELD(match_number, Unsigned, unsigned)
FIELD(reason, BreakReason, BreakReason)
FIELD_ARR(traiding_mode, Char, char, mmt, 1)
FIELD_ARR(trasaction_category, Char, char, mmt, 2)
FIELD_ARR(algo_indicator, Char, char, mmt, 10)

#endif
