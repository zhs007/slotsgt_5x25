//
// Created by zhs007 on 2017/7/4.
//

#ifndef SLOTSGT_5X25_SYMBOLCOUNT_H
#define SLOTSGT_5X25_SYMBOLCOUNT_H

#include "csv.h"
#include <vector>
#include <string.h>
#include <cstdlib>

template <int WIDTH, int HEIGHT>
class SymbolCount {
public:
    SymbolCount() {}
    ~SymbolCount() {}
public:
    int get(int x, int y) const {
        if (y == -1) {
            if (x < 0 || x >= WIDTH) {
                return -1;
            }

            return m_total[x];
        }

        if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
            return -1;
        }

        return m_lst[y][x];
    }

    void set(int x, int y, int val) const {
        if (y == -1) {
            if (x < 0 || x >= WIDTH) {
                return ;
            }

            m_total[x] = val;
        }

        if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
            return ;
        }

        m_lst[y][x] = val;
    }

public:
    void output(const char* str) {
        printf("symbolcount %s\n", str);
        for (int ii = 0; ii < HEIGHT; ++ii) {
            printf("%d", ii);

            for (int jj = 0; jj < WIDTH; ++jj) {
                printf(",%d", m_lst[ii][jj]);
            }

            printf("\n");
        }

        printf("total");

        for (int jj = 0; jj < WIDTH; ++jj) {
            printf(",%d", m_total[jj]);
        }

        printf("\n");
    }
protected:
    int m_lst[HEIGHT][WIDTH];
    int m_total[WIDTH];
};

template <int WIDTH, int HEIGHT>
class SymbolCount_Maybe {
public:
    struct _Node {
        int minnums;
        int maxnums;
    };
public:
    SymbolCount_Maybe() {}
    ~SymbolCount_Maybe() {}
public:
    bool load(const char* filename) {
        CSVData csv;
        csv.load(filename);

        if (csv.m_height != HEIGHT + 1) {
            return false;
        }

        for (int y = 0; y < csv.m_height; ++y) {
            int s = atoi(csv.m_lst[y][0]);

            if (s == -1) {
                int p1i = atoi(csv.m_lst[y][2]);
                int p1a = atoi(csv.m_lst[y][3]);
                int p2i = atoi(csv.m_lst[y][4]);
                int p2a = atoi(csv.m_lst[y][5]);
                int p3i = atoi(csv.m_lst[y][6]);
                int p3a = atoi(csv.m_lst[y][7]);
                int p4i = atoi(csv.m_lst[y][8]);
                int p4a = atoi(csv.m_lst[y][9]);
                int p5i = atoi(csv.m_lst[y][10]);
                int p5a = atoi(csv.m_lst[y][11]);

                m_total[0].minnums = p1i;
                m_total[0].maxnums = p1a;
                m_total[1].minnums = p2i;
                m_total[1].maxnums = p2a;
                m_total[2].minnums = p3i;
                m_total[2].maxnums = p3a;
                m_total[3].minnums = p4i;
                m_total[3].maxnums = p4a;
                m_total[4].minnums = p5i;
                m_total[4].maxnums = p5a;

                break;
            }

            if (s != y) {
                return false;
            }

            int p1i = atoi(csv.m_lst[y][2]);
            int p1a = atoi(csv.m_lst[y][3]);
            int p2i = atoi(csv.m_lst[y][4]);
            int p2a = atoi(csv.m_lst[y][5]);
            int p3i = atoi(csv.m_lst[y][6]);
            int p3a = atoi(csv.m_lst[y][7]);
            int p4i = atoi(csv.m_lst[y][8]);
            int p4a = atoi(csv.m_lst[y][9]);
            int p5i = atoi(csv.m_lst[y][10]);
            int p5a = atoi(csv.m_lst[y][11]);

            m_lst[s][0].minnums = p1i;
            m_lst[s][0].maxnums = p1a;
            m_lst[s][1].minnums = p2i;
            m_lst[s][1].maxnums = p2a;
            m_lst[s][2].minnums = p3i;
            m_lst[s][2].maxnums = p3a;
            m_lst[s][3].minnums = p4i;
            m_lst[s][3].maxnums = p4a;
            m_lst[s][4].minnums = p5i;
            m_lst[s][4].maxnums = p5a;
        }

        return true;
    }

    int getMin(int x, int y) const {
        if (y == -1) {
            if (x < 0 || x >= WIDTH) {
                return -1;
            }

            return m_total[x].minnums;
        }

        if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
            return -1;
        }

        return m_lst[y][x].minnums;
    }

    int getMax(int x, int y) const {
        if (y == -1) {
            if (x < 0 || x >= WIDTH) {
                return -1;
            }

            return m_total[x].maxnums;
        }

        if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
            return -1;
        }

        return m_lst[y][x].maxnums;
    }
public:
    void output(const char* str) {
        printf("symbolcount_maybe %s\n", str);
        for (int ii = 0; ii < HEIGHT; ++ii) {
            printf("%d", ii);

            for (int jj = 0; jj < WIDTH; ++jj) {
                printf(",[%d, %d]", m_lst[ii][jj].minnums, m_lst[ii][jj].maxnums);
            }

            printf("\n");
        }

        printf("total");

        for (int jj = 0; jj < WIDTH; ++jj) {
            printf(",[%d, %d]", m_total[jj].minnums, m_total[jj].maxnums);
        }

        printf("\n");
    }
protected:
    _Node m_lst[HEIGHT][WIDTH];
    _Node m_total[WIDTH];
};

#endif //SLOTSGT_5X25_SYMBOLCOUNT_H
