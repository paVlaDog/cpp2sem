#if !defined(FIELD) || !defined(FIELD_ARR) || !defined(SKIP)
#error You need to define FIELD and FIELD_ARR and SKIP macro
#else

SKIP(9)
FIELD(cl_ord_id, String, std::string)
FIELD(filled_volume, Unsigned, unsigned)
FIELD(price, Price, double)
SKIP(1)
FIELD(match_number, Unsigned, unsigned)
FIELD(counterpart, String, std::string)
FIELD_ARR(traiding_mode, Char, char, mmt, 1)
FIELD_ARR(trasaction_category, Char, char, mmt, 2)
FIELD_ARR(algo_indicator, Char, char, mmt, 10)
FIELD(liquidity_indicator, LiquidityIndicator, LiquidityIndicator)
FIELD(internalized, Bool, bool)
FIELD(self_trade, Bool, bool)

#endif
