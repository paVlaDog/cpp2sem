#if !defined(FIELD) || !defined(ADD_ARITY_FIELD) || !defined(TWO_ADD_ARITY_FIELD) || !defined(SKIP)
#error You need to define FIELD and ADD_ARITY_FIELD and TWO_ADD_ARITY_FIELD and SKIP macro
#else

SKIP(9)
ADD_ARITY_FIELD(cl_ord_id, String, std::string, 14)
FIELD(filled_volume, Unsigned, unsigned)
FIELD(price, Price, double)
FIELD(match_number, Unsigned, unsigned)
ADD_ARITY_FIELD(counterpart, String, std::string, 4)
FIELD(traiding_mode, Char, char)
FIELD(trasaction_category, Char, char)
FIELD(algo_indicator, Char, char)
TWO_ADD_ARITY_FIELD(liquidity_indicator, LiquidityIndicator, LiquidityIndicator, 4, 2)
ADD_ARITY_FIELD(internalized, Bool, bool, 6)
ADD_ARITY_FIELD(self_trade, Bool, bool, 8)
FIELD(reason, BreakReason, BreakReason)

#endif
