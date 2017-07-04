//
// Created by zhs007 on 2016/12/26.
//

#ifndef EXSLOTS_CSV_H
#define EXSLOTS_CSV_H

#include <string>
#include <stdio.h>

// CSV文件读取类，第一行为文件头
class CSVData{
public:
    CSVData();
    ~CSVData();
public:
    bool load(const char* filename);

    void release();
protected:
    bool countWH();

    bool onRead();
public:
    char*   m_buff;
    int     m_width;
    int     m_height;

    char*** m_lst;
};

#endif //EXSLOTS_CSV_H
