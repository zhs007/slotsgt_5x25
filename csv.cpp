//
// Created by zhs007 on 2016/12/26.
//

#include "csv.h"
#include <stdlib.h>

CSVData::CSVData()
        : m_buff(NULL)
        , m_lst(NULL)
        , m_width(0)
        , m_height(0)

{
}

CSVData::~CSVData() {
    release();
}

bool CSVData::load(const char* filename) {
    release();

    FILE* fp = fopen(filename, "r");
    if (fp != NULL) {
        fseek(fp, 0, SEEK_END);
        long fsize = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        m_buff = (char*)malloc(fsize + 1);
        fread(m_buff, fsize, 1, fp);
        m_buff[fsize] = '\0';

        fclose(fp);

        bool isok = countWH();
        if (!isok) {
            release();

            return false;
        }

        isok = onRead();
        if (!isok) {
            release();

            return false;
        }

        return true;
    }

    return false;
}

void CSVData::release() {
    if (m_buff != NULL) {
        free(m_buff);

        m_buff = NULL;
    }

    if (m_lst != NULL) {
        free(m_lst);

        m_lst = NULL;
    }

    m_width = 0;
    m_height = 0;
}

bool CSVData::countWH() {
    if (m_buff != NULL) {
        bool firstlineend = false;
        m_width = 0;
        m_height = 0;
        int i = 0;
        while(m_buff[i] != '\0') {
            bool chgline = false;

            if (m_buff[i] == '\r') {
                if (m_buff[i + 1] == '\n') {
                    chgline = true;
                    ++i;
                }
                else if (m_buff[i + 1] == '\0') {
                    chgline = true;
                }
            }
            else if (m_buff[i] == '\n') {
                chgline = true;
            }

            if (firstlineend) {
                if (chgline) {
                    ++m_height;
                }
            }
            else {
                if (chgline) {
                    ++m_height;
                    ++m_width;
                    firstlineend = true;
                }
                else if (m_buff[i] == ',') {
                    ++m_width;
                }
            }

            ++i;
        }

        --m_height;

        return true;
    }

    return false;
}

bool CSVData::onRead() {
    if (m_width > 0 && m_height > 0) {

        int h = m_height;

        m_lst = (char***)malloc(m_width * h * sizeof(char*) + h * sizeof(char**));
        char* bbuff = (char*)m_lst + h * sizeof(char**);
        for (int y = 0; y < h; ++y) {
            m_lst[y] = (char**)(bbuff + m_width * sizeof(char*) * y);
        }

        bool firstlineend = false;
        int i = 0;
        int y = 0;
        int x = 0;
        char* bstr = NULL;
        while(m_buff[i] != '\0') {
            bool chgline = false;

            if (m_buff[i] == '\r') {
                m_buff[i] = '\0';

                if (m_buff[i + 1] == '\n') {
                    m_buff[i + 1] = '\0';

                    chgline = true;
                    ++i;
                }
                else if (m_buff[i + 1] == '\0') {
                    chgline = true;
                }
            }
            else if (m_buff[i] == '\n') {
                m_buff[i] = '\0';
                chgline = true;
            }

            if (firstlineend) {
                if (chgline) {
                    m_lst[y][x] = bstr;
                    bstr = (char*)(m_buff + i + 1);

                    y++;
                    x = 0;
                }
                else if (m_buff[i] == ',') {
                    m_buff[i] = '\0';

                    m_lst[y][x] = bstr;
                    bstr = (char*)(m_buff + i + 1);

                    x++;
                }
            }
            else {
                if (chgline) {
                    firstlineend = true;

                    bstr = (char*)(m_buff + i + 1);
                }
            }

            ++i;
        }

        return true;
    }

    return false;
}