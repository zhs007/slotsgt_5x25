//
// Created by zhs007 on 2017/7/4.
//

#ifndef SLOTSGT_5X25_SLOTSLOGIC_H
#define SLOTSGT_5X25_SLOTSLOGIC_H

#include "paytable.h"
#include "symbolcount.h"

template<int WIDTH, int HEIGHT>
int countSingleLine(int symbol, SymbolCount<WIDTH, HEIGHT>& symbolcount, Paytable<WIDTH, HEIGHT>& paytable, int wild, bool isleft) {
    int hit[WIDTH];
    int payout[WIDTH];
    int whit[WIDTH];
    int wpayout[WIDTH];
    int totalpayout = 0;

    for (int x = 0; x < WIDTH; ++x) {
        int cb = 1;
        for (int bx = 0; bx <= x; ++bx) {
            cb *= symbolcount.get(bx, symbol);
        }

        int eb = 1;
        if (x < WIDTH - 1) {
            for (int ex = x + 1; ex <= WIDTH; ++ex) {
                eb *= symbolcount.get(ex, -1) - symbolcount.get(ex, symbol);
            }
        }

        hit[x] = cb * eb;
        payout[x] = paytable.get(x, symbol) * hit[x];

        totalpayout += payout[x];
    }

    if (wild >= 0) {
        for (int x = 0; x < WIDTH; ++x) {
            int cb = 1;
            for (int bx = 0; bx <= x; ++bx) {
                cb *= symbolcount.get(bx, symbol) + symbolcount.get(bx, wild);
            }

            int eb = 1;
            if (x < WIDTH - 1) {
                for (int ex = x + 1; ex <= WIDTH; ++ex) {
                    eb *= symbolcount.get(ex, -1) - symbolcount.get(ex, symbol) - symbolcount.get(ex, wild);
                }
            }

            whit[x] = cb * eb;
            wpayout[x] = paytable.get(x, symbol) * hit[x];

            totalpayout += wpayout[x];
        }
    }

    return totalpayout;
};

template<int WIDTH, int HEIGHT, int GAMESCENE_HEIGHT>
int countScatter(int symbol, SymbolCount<WIDTH, HEIGHT>& symbolcount, Paytable<WIDTH, HEIGHT>& paytable) {
    int hit[WIDTH];
    int payout[WIDTH];
    int totalpayout = 0;
    int maxval = (1 << WIDTH);

    for (int cv = 1; cv < maxval; ++cv) {
        int cb = 1;
        int eb = 1;
        int curmask[WIDTH];
        int curlen = 0;
        for (int x = 0; x < WIDTH; ++x) {
            int cm = (1 << x);
            if ((cv & cm) == cm) {
                curlen++;
                curmask[x] = 1;

                cb *= symbolcount.get(x, symbol) * GAMESCENE_HEIGHT;
            }
            else {
                curmask[x] = 0;

                eb *= symbolcount.get(x, -1) - symbolcount.get(x, symbol) * GAMESCENE_HEIGHT;
            }
        }

        hit[curlen] = cb * eb;
        payout[curlen] = paytable.get(curlen, symbol) * hit[curlen];
    }

    for (int x = 0; x < WIDTH; ++x) {
        totalpayout += payout[x];
    }

    return totalpayout;
};

#endif //SLOTSGT_5X25_SLOTSLOGIC_H
