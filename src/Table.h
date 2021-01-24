//
// Created by otto001 on 9/8/20.
//

#ifndef CFAN_TABLE_H
#define CFAN_TABLE_H
#include <string>
#include <vector>

class Control;

class Table {
public:
    enum class Alignment {
        LEFT, RIGHT
    };

protected:
    Control* control;

    void printHorizontalDivider();
    void nextRow();

    void printCell(const std::string& val, Alignment align = Alignment::LEFT);

    template<typename T>
    std::string formatCell(const char* format, T value);

    std::vector<int> widths;

    int rowCount = 0;
    int field = 0;

    int y = 0;
    int x = 0;

public:
    explicit Table(Control* control);
    void refreshTable();
    void resetRows();

    inline size_t getColCount() {
        return widths.size() + 1;
    }
};


#endif //CFAN_TABLE_H
