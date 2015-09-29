//
//  magicCube.h
//  resolveMagicCube
//
//  Created by DerekHsu on 10/28/14.
//  Copyright (c) 2014 DerekHsu. All rights reserved.
//

#ifndef __resolveMagicCube__MagicCube__
#define __resolveMagicCube__MagicCube__

#include <stdio.h>
#include <string>
#include "CubeFace.h"

static const int COUNTOFROTATION = 12;
static const std::string fileName = "resolveMagicCube.txt";

enum ROTATION3D {
    TOPCW = 0, TOPCCW = 1,
    BUTTOMCW = 2, BUTTOMCCW = 3,
    LEFTCW = 4, LEFTCCW = 5,
    RIGHTCW = 6, RIGHTCCW = 7,
    FRONTCW = 8, FRONTCCW = 9,
    REARCW = 10, REARCCW = 11,
    ORIGIN = 12
};

static const std::string SHOWROTATION3D[] = {
    "TOPCW", "TOPCCW" ,
    "BUTTOMCW", "BUTTOMCCW" ,
    "LEFTCW" , "LEFTCCW" ,
    "RIGHTCW" , "RIGHTCCW" ,
    "FRONTCW" , "FRONTCCW" ,
    "REARCW" , "REARCCW" ,
    "ORIGIN"
};

class MagicCube {
private:
    ROTATION3D Rotation3D;
    int layer;//uni ID by layer and NameOfRotation
    std::string history;
    CubeFace cubeFace[COUNTOFFACE];
public:
    MagicCube();
    MagicCube(const MagicCube &);
    MagicCube(std::string hisory, std::string compress);
    //constructure
    std::string getHistory() const;
    std::string getMagicCubeID() const;
    std::string getCompression() const;
    CubeFace getCubeFace(NAMEOFFACE) const;
    CubeFace& getCubeFace(NAMEOFFACE);
    //setter & getter
    void operator=(const MagicCube &);
    bool operator==(MagicCube &);// will calibrate te arg cube
    bool operator==(const MagicCube &);
    friend std::ostream& operator<<(std::ostream& magicCubeOut, const MagicCube &);
    MagicCube& operator[](ROTATION3D);
    //operator
    void setCubeFace(NAMEOFFACE,const CubeFace &);
    void setCubeFaces(NAMEOFCOLOR* transfers);
    void calibrateMagicCube(NAMEOFFACE isFront);
    void outFile() const;
protected:
    void rotateMagicCubeVerticalCW();
    void rotateMagicCubeHorizontalCW();
    void rotateMagicCubeRollingCW();
    void setLayer(int lastLayer);
    void setRotation3D(ROTATION3D);
    void setHistory(std::string);
    void setMagicCube(const MagicCube &);
    void setMagicCube(ROTATION3D);//new rotation magic cube
    void setMagicCubeID(ROTATION3D);
    void setMagicCubeID(std::string);
    void setMagicCubeFaces(std::string);
    void resetRotationCWs();
    
    void rollingBlock(NAMEOFFACE isFront);
    void rollingFace();
};

#endif /* defined(__resolveMagicCube__magicCube__) */
