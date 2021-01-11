//
// Created by otto001 on 9/8/20.
//

#include "Table.h"
#include "Control.h"
#include <type_traits>
#include <ncurses.h>

Table::Table(Control *control) : control(control){
    widths = {20, 6, 8, 7, 7};
    initscr();
}

void Table::refreshTable() {
    resetRows();

    printCell("name");
    printCell("score", Table::Alignment::RIGHT);
    printCell("build up", Table::Alignment::RIGHT);
    printCell("started", Table::Alignment::RIGHT);
    printCell("speed", Table::Alignment::RIGHT);
    printHorizontalDivider();


    rowCount = 0;
    for (auto device : control->getCoolingDevices()) {
        printCell(device->getName());
        printCell(formatCell("%.2f", device->getCurrentHighScore()), Table::Alignment::RIGHT);
        printCell(formatCell("%.1f", device->getBuildUp()), Table::Alignment::RIGHT);
        printCell(device->getIsStarted() ? "t" : "f", Table::Alignment::RIGHT);
        printCell(formatCell("%.2f", device->getCurrentSetSpeed()), Table::Alignment::RIGHT);


    }
    refresh();
}

void Table::printHorizontalDivider() {
    std::string result;
    bool first = true;
    for (int width : widths) {

        if (first) {
            first = false;
        } else {
            result += '+';
        }

        if (width > 0) {
            auto bars = std::string(width, '-');
            result += bars;
        }
    }
    //tableString += result;
    printw(result.c_str());
    nextRow();
}



void Table::nextRow() {
    y++;
    rowCount++;
    x = 0;
    field = 0;
    move(y, x);
}


void Table::printCell(const std::string&  val, Alignment align) {
    //static_assert(std::is_same<decltype(val), const char*>::value || std::is_same<decltype(val), double>::value, "T must be const char* or double");

    int width = widths[field];
    int xStart = x;

    if (field > 0) {
        move(y, x);
        printw("|");
        x++;
        xStart++;
    }

    int textWidth = int(val.size());

    switch (align) {
        case Table::Alignment::RIGHT:
            move(y, xStart);
            printw(std::string(width-textWidth, ' ').c_str());
            x += width - textWidth;
            break;
        case Table::Alignment::LEFT:
            move(y, xStart+textWidth);
            printw(std::string(width-textWidth, ' ').c_str());
            break;
    }

    move(y, x);

    printw(val.c_str());


    field ++;
    x = xStart + width;
    if (field >= getColCount() - 1) {
        nextRow();
    }
}

template<typename T>
std::string Table::formatCell(const char *format, T value) {
    char buf[127];
    snprintf(buf, sizeof(buf), format, value);
    return buf;
}


void Table::resetRows() {
    rowCount = 0;
    x = 0;
    y = 0;
    field = 0;
    move(y, x);
}



