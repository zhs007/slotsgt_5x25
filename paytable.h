//
// Created by zhs007 on 2017/7/4.
//

#ifndef SLOTSGT_5X25_PAYTABLE_H
#define SLOTSGT_5X25_PAYTABLE_H

#include "csv.h"
#include <vector>
#include <string.h>
#include <cstdlib>

template <int WIDTH, int HEIGHT>
class Paytable {
public:
    Paytable() {}
    ~Paytable() {}
public:
    bool load(const char* filename) {
        CSVData csv;
        csv.load(filename);

        if (csv.m_height != HEIGHT) {
            return false;
        }

        for (int y = 0; y < csv.m_height; ++y) {
            int s = atoi(csv.m_lst[y][0]);

            if (s != y) {
                return false;
            }

            int p1 = atoi(csv.m_lst[y][2]);
            int p2 = atoi(csv.m_lst[y][3]);
            int p3 = atoi(csv.m_lst[y][4]);
            int p4 = atoi(csv.m_lst[y][5]);
            int p5 = atoi(csv.m_lst[y][6]);

            m_lst[s][0] = p1;
            m_lst[s][1] = p2;
            m_lst[s][2] = p3;
            m_lst[s][3] = p4;
            m_lst[s][4] = p5;
        }
    }

    int get(int x, int y) {
        if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
            return -1;
        }

        return m_lst[y][x];
    }
public:
    void output(const char* str) {
        printf("paytable %s\n", str);
        for (int ii = 0; ii < HEIGHT; ++ii) {
            printf("%d", ii);

            for (int jj = 0; jj < WIDTH; ++jj) {
                printf(",%d", m_lst[ii][jj]);
            }

            printf("\n");
        }
    }
protected:
    int m_lst[HEIGHT][WIDTH];
};

#endif //SLOTSGT_5X25_PAYTABLE_H
