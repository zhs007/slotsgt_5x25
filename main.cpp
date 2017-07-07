#include <iostream>
#include "paytable.h"
#include "symbolcount.h"
#include "slotslogic.h"

const int MAX_SYMBOL_NUMS   = 11;
const int REELS_NUMS        = 5;
const int GAMESCENE_HEIGHT  = 3;

typedef Paytable<REELS_NUMS, MAX_SYMBOL_NUMS>               PaytableEx;
typedef SymbolCount_Maybe<REELS_NUMS, MAX_SYMBOL_NUMS>      SymbolCount_MaybeEx;
typedef SymbolCount<REELS_NUMS, MAX_SYMBOL_NUMS>            SymbolCountEx;

int main() {
    PaytableEx paytable;
    SymbolCount_MaybeEx symbolcount_maybe;

    paytable.load("/Users/zhs007/work/github/slotsgt_5x25/game122_paytables.csv");
    paytable.output("");

    symbolcount_maybe.load("/Users/zhs007/work/github/slotsgt_5x25/game122_symbolcount.csv");
    symbolcount_maybe.output("");

    return 0;
}