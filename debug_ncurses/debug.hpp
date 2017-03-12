//
//  debug.hpp
//
//  Created by Matt on 12/03/2017.
//  Copyright © 2017 Matt. All rights reserved.
//

#ifndef debug_hpp
#define debug_hpp

#include <stdio.h>
#include <iostream>
#include <ncurses.h>
#include <string>
#include <deque>
using namespace std;
//#include "mattutils.hpp"

class NC_DBG {
    
public:
    // init
    NC_DBG(int rows, int cols, int pos_y, int pos_x, bool drawBox = true, bool drawTitle = true);
    
    // display variables
    char line_ind = '>';
    char wrap_ind = ' ';
    
    // trace polymorphisms
    void trace(int x);
    void trace(unsigned char x);
    void trace(std::string x);
    void trace(char* x);
    
private:
    int dbg_line;
    deque<string> disp_buffer;
    string emptyLine;
    WINDOW* dbg_win;
    
    int firstCol;
    int firstRow;
    int height;
    int width;
    
    // internal graphics functions
    void addLineInd(const char c, const char* s);
    void lineWrapHandler(const char* s);
    void scrollBuffer();
    void render();
};


#endif /* debug_hpp */
