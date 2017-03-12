//
//  debug.cpp
//
//  Created by Matt on 12/03/2017.
//  Copyright © 2017 Matt. All rights reserved.
//

#include "debug.hpp"

///<summary>
/// Needs at least 3 columns with no box, and 5 columns with box and title.
/// You can choose not to draw box or title anyways, on by default.
///</summary>
NC_DBG::NC_DBG(int rows, int cols, int pos_y, int pos_x, bool drawBox, bool drawTitle)
{
    dbg_win = newwin(rows, cols, pos_y, pos_x);
    
    if (rows < 3 || cols < 3)
        throw "Cannot initialize debug viewport with less than 3 columns or rows";
    
    if (drawBox)
    {
        // from now on firstCol tells us if we've drawn a box,
        // meaning if we have a margin to print line indicators
        if (cols < 5 || rows < 5)
        {
            firstCol = 0;
            firstRow = 0;
        }
        else
        {
            firstCol = 1;
            firstRow = 1;
            box(dbg_win, 0, 0);
        }
    }
    else
    {
        firstCol = 0;
    }
    
    if (drawTitle)
    {
        if (cols < 5)
            firstRow = 0;
        else
        {
            mvwprintw(dbg_win, 0, 0, "Dbg:");
        }
    }
    else
        firstRow = 0;
    
    dbg_line = 0;
    width = cols - firstCol*2;
    height = rows - firstRow*2;
    emptyLine = *new string(width, ' ');
    wrefresh(dbg_win);
}

void NC_DBG::addLineInd(const char c, const char* s)
{
    if (firstCol)
    {
        char* tmp = (char*)malloc(sizeof(char) * width);
        tmp[0] = c;
        strcat(tmp, s);
        disp_buffer.push_back(tmp);
    }
    else
    {
        disp_buffer.push_back(s);
    }
}

void NC_DBG::lineWrapHandler(const char* s)
{
    size_t length = strlen(s);
    unsigned long nbLines;
    int remChars = length % width;
    // first calculate over how many lines we will wrap
    if (length > width)
        nbLines = (remChars) ? (length / width) + 1 : length / width;
    else
        nbLines = 1;
    std::string sAsStdStr = s;
    int i;
    for (i = 0; i < nbLines; i++)
    {
        scrollBuffer();
        // if last linewrap, need to check last line length so substr()
        // call does not cause segmentation fault
        int subStringLgth = (i == nbLines - 1 && remChars) ? remChars : width;
        if (!i)
            addLineInd(line_ind, &sAsStdStr.substr(i * width, subStringLgth)[0]);
        else
            addLineInd(wrap_ind, &sAsStdStr.substr(i * width, subStringLgth)[0]);
        render();
    }
}

void NC_DBG::scrollBuffer()
{
    if (dbg_line == height)
    {
        disp_buffer.pop_front();
    }
    else
    {
        dbg_line++;
    }
}

void NC_DBG::render()
{
    for (int i = 0; i < dbg_line; i++)
    {
        mvwprintw(dbg_win, i+1, 1, &emptyLine[0]);
        mvwprintw(dbg_win, i+1, 0, &disp_buffer[i][0]);
    }
    wrefresh(dbg_win);
}

void NC_DBG::trace(int variable)
{
    char* s = &std::to_string(variable)[0];
    lineWrapHandler(s);
}

///<summary>
/// NOTE: choice is made to print decimal value of the char binary value.
/// To print a char normally, make a char* and pass it to trace(char* x)
///</summary>
void NC_DBG::trace(unsigned char variable)
{
    char* s = &std::to_string(variable)[0];
    lineWrapHandler(s);
}

void NC_DBG::trace(std::string x)
{
    char* s = &x[0];
    lineWrapHandler(s);
}

void NC_DBG::trace(char *x)
{
    lineWrapHandler(x);
}
