//
//  CubeFace.h
//  resolveMagicCube
//
//  Created by DerekHsu on 10/28/14.
//  Copyright (c) 2014 DerekHsu. All rights reserved.
//

#ifndef __resolveMagicCube__CubeFace__
#define __resolveMagicCube__CubeFace__

#include <stdio.h>
#include <ostream>

static const int COUNTOFCELL = 3;
static const int COUNTOFSIDE = 4;
static const int COUNTOFFACE = 6;

    enum NAMEOFFACE {FRONT = 0, TOP = 1, RIGHT = 2, BUTTOM = 3, LEFT = 4, REAR = 5};
    enum NAMEOFCOLOR {RED = 0, YELLOW = 1, GREEN = 2, WHITE = 3, BLUE = 4, ORANGE = 5, TRANSPARENT = 6};
    enum ROTATION {NONE = 0, QUARTER = 1, HALF = 2, MINUSQUARTER = 3};
    enum DIRECTION {TOPSIDE = 0, RIGHTSIDE = 1, BUTTOMSIDE = 2, LEFTSIDE = 3, SELF = 4};
    static const std::string SHOWFACE[] =  {"FRONT", "TOP", "RIGHT", "BUTTOM", "LEFT", "REAR"};
    static const char SHOWCOLOR[] = {'R','Y','G','W','B','O','T'};

class CubeFace {
private:
    ROTATION RotationCW;// set by program
    NAMEOFCOLOR cells[COUNTOFCELL][COUNTOFCELL];//set by user
public:
    CubeFace();
    CubeFace(const CubeFace &);
    CubeFace(const NAMEOFCOLOR &);//id of face
    //contruster
    
    bool operator==(CubeFace &);//face is same, maybe rotation
    bool operator==(const CubeFace &);//face is same; can not be rotation
    void operator=(const CubeFace &);
    CubeFace& operator-(ROTATION) const;//rotation CCW
    CubeFace& operator+(ROTATION) const;//rotation CW
    void operator+=(ROTATION);
    void operator++();
    void operator--();
    friend std::ostream& operator<<(std::ostream& cubeFaceOut, const CubeFace &);
    //opertor
    
    void setCells(NAMEOFCOLOR **);
    void setCells(NAMEOFCOLOR);
    void setCells(NAMEOFCOLOR* transfers);
    void setCell(int row, int col, NAMEOFCOLOR);
    NAMEOFCOLOR getCell(int row, int col) const;//col: x, row y
    NAMEOFCOLOR** getCells() const;
    void resetRotationCW();
    void setRotation(int);
    void updateRotation(int);
    
    ROTATION getRotationCW() const;
    int getRotationCW(ROTATION) const;
    int getRotationCCW(ROTATION) const;
    void setBar(DIRECTION tar,NAMEOFCOLOR *);
    NAMEOFCOLOR *getBar(DIRECTION) const;
    NAMEOFCOLOR *getReverseBar(DIRECTION) const;
    NAMEOFCOLOR getColorByFace(NAMEOFFACE);
    NAMEOFCOLOR getOppositeColor(NAMEOFCOLOR);
    //other
protected:
    bool isSameCells(const CubeFace &);
    void setCubeFace(const CubeFace &);
    void rotate90CW();
};

/*
 
             U
         L      R
             D
            
             D
         R       L
             U
 
    L        U        R        D
 D      U L      R U      D R      L
    R        D        L        U
 
             U
         L       R
             D
 */

#endif /* defined(__resolveMagicCube__cubeFace__) */
