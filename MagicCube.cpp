//
//  magicCube.cpp
//  resolveMagicCube
//
//  Created by DerekHsu on 10/28/14.
//  Copyright (c) 2014 DerekHsu. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "MagicCube.h"

MagicCube::MagicCube():layer(0),Rotation3D(ORIGIN),history(this->getMagicCubeID()) {
    for (int i = 0; i < COUNTOFFACE; i++) {
        CubeFace face(static_cast<NAMEOFCOLOR>(i));
        this->cubeFace[i] = face;
    }
}

MagicCube::MagicCube(const MagicCube& arg) {
    this->setMagicCube(arg);
}

MagicCube::MagicCube(std::string history, std::string compress) {
    this->setMagicCubeID(history);
    this->setMagicCubeFaces(compress);
}

void MagicCube::operator=(const MagicCube& arg) {
    this->setMagicCube(arg);
}

bool MagicCube::operator==(MagicCube& arg) {
    bool same = false;
    MagicCube cube(arg);
    
    for (int isFront = FRONT; isFront < COUNTOFFACE && !same; isFront++) {
        if (this->getCubeFace(FRONT) == cube.getCubeFace(static_cast<NAMEOFFACE>(isFront))) {
            cube.calibrateMagicCube(static_cast<NAMEOFFACE>(isFront));
            if (*this == (const MagicCube &)cube) {
                same = true;
            }
            else {
                cube = arg;
            }
        }
    }
    
    return same;
}

bool MagicCube::operator==(const MagicCube& arg) {
    return (this->getCubeFace(FRONT) == (const ::CubeFace &)arg.getCubeFace(FRONT)) &&
    (this->getCubeFace(TOP) == (const ::CubeFace &)arg.getCubeFace(TOP)) &&
    (this->getCubeFace(RIGHT) == (const ::CubeFace &)arg.getCubeFace(RIGHT));
}

std::ostream& operator<<(std::ostream& magicCubeOut, const MagicCube& arg) {
    magicCubeOut << "ID: " << arg.getMagicCubeID() << std::endl;
    magicCubeOut << "History: " << arg.getHistory() << std::endl;
    
    for (int face = 0; face < COUNTOFFACE; face++) {
        magicCubeOut << '\t' << "Face: " << SHOWFACE[face] << std::endl;
        magicCubeOut << arg.getCubeFace(static_cast<NAMEOFFACE>(face));
    }
    
    return magicCubeOut;
}

MagicCube& MagicCube::operator[](const ROTATION3D arg) {
    MagicCube *cube = new MagicCube(*this);
    
    cube->setMagicCubeID(arg);
    cube->setMagicCube(arg);
    cube->resetRotationCWs();
    
    return *cube;
}

void MagicCube::resetRotationCWs() {
    for (int face = 0; face < COUNTOFFACE; face++) {
        this->getCubeFace(static_cast<NAMEOFFACE>(face)).resetRotationCW();
    }
}

std::string MagicCube::getHistory() const {
    return this->history;
}

std::string MagicCube::getMagicCubeID() const{
    return std::to_string(this->Rotation3D) + '_' + std::to_string(this->layer);
}

std::string MagicCube::getCompression() const {
    std::string cube = "";
    
    for (int face = 0; face < COUNTOFFACE; face++) {
        for (int row = 0; row < COUNTOFCELL; row++) {
            for (int col = 0; col < COUNTOFCELL; col++) {
                cube +=  std::to_string(this->cubeFace[face].getCell(row, col));//
            }
        }
    }
    
    return cube;
}

CubeFace MagicCube::getCubeFace(NAMEOFFACE arg) const {
    return this->cubeFace[arg];
}

CubeFace& MagicCube::getCubeFace(NAMEOFFACE arg) {
    return this->cubeFace[arg];
}

void MagicCube::setMagicCube(const MagicCube &arg) {
    this->setLayer(arg.layer);
    this->setRotation3D(arg.Rotation3D);
    this->setHistory(arg.getHistory());
    for (int i = FRONT; i < COUNTOFFACE; i++) {
        this->setCubeFace(static_cast<NAMEOFFACE>(i), arg.getCubeFace(static_cast<NAMEOFFACE>(i)));
    }
}

void MagicCube::setLayer(int lastLayer) {
    this->layer = lastLayer;
}

void MagicCube::setRotation3D(ROTATION3D arg) {
    this->Rotation3D = arg;
}

void MagicCube::setHistory(std::string arg) {
    this->history = arg;
}

void MagicCube::setCubeFace(NAMEOFFACE faceIndex, const CubeFace& arg) {
    this->cubeFace[faceIndex] = arg;
}

void MagicCube::calibrateMagicCube(NAMEOFFACE isFront) {
    this->rollingBlock(isFront);
    this->rollingFace();
}

void MagicCube::rollingBlock(NAMEOFFACE arg) {
    switch (arg) {
        case TOP:
            this->rotateMagicCubeVerticalCW();
            break;
        case RIGHT:
            this->rotateMagicCubeHorizontalCW();
            break;
        case BUTTOM:
            this->rotateMagicCubeVerticalCW();
            this->rotateMagicCubeVerticalCW();
            this->rotateMagicCubeVerticalCW();
            break;
        case LEFT:
            this->rotateMagicCubeHorizontalCW();
            this->rotateMagicCubeHorizontalCW();
            this->rotateMagicCubeHorizontalCW();
            break;
        case REAR:
            this->rotateMagicCubeHorizontalCW();
            this->rotateMagicCubeHorizontalCW();
            break;
        default:
            break;
    }
}

void MagicCube::rollingFace() {
    switch (this->getCubeFace(FRONT).getRotationCW()) {
        case QUARTER:
            this->rotateMagicCubeRollingCW();
            break;
        case HALF:
            this->rotateMagicCubeRollingCW();
            this->rotateMagicCubeRollingCW();
            break;
        case MINUSQUARTER:
            this->rotateMagicCubeRollingCW();
            this->rotateMagicCubeRollingCW();
            this->rotateMagicCubeRollingCW();
            break;
        default:
            break;
    }
}

void MagicCube::rotateMagicCubeHorizontalCW() {
    MagicCube cube(*this);
    
    this->setCubeFace(FRONT, cube.getCubeFace(RIGHT));
    this->setCubeFace(LEFT, cube.getCubeFace(FRONT));
    this->setCubeFace(REAR, cube.getCubeFace(LEFT));
    this->setCubeFace(RIGHT, cube.getCubeFace(REAR));
    this->setCubeFace(TOP, cube.getCubeFace(TOP) + QUARTER);
    this->setCubeFace(BUTTOM, cube.getCubeFace(BUTTOM) - QUARTER);
    ++this->cubeFace[FRONT];
    ++this->cubeFace[LEFT];
    ++this->cubeFace[REAR];
    ++this->cubeFace[RIGHT];
}

void MagicCube::rotateMagicCubeVerticalCW() {
    MagicCube cube(*this);
    
    this->setCubeFace(FRONT, cube.getCubeFace(TOP));
    this->setCubeFace(LEFT, cube.getCubeFace(LEFT) + QUARTER);
    this->setCubeFace(REAR, cube.getCubeFace(BUTTOM));
    this->setCubeFace(RIGHT, cube.getCubeFace(RIGHT) - QUARTER);
    this->setCubeFace(TOP, cube.getCubeFace(REAR));
    this->setCubeFace(BUTTOM, cube.getCubeFace(FRONT));
    this->cubeFace[FRONT] += HALF;
    this->cubeFace[TOP] += HALF;
}

void MagicCube::rotateMagicCubeRollingCW() {
    MagicCube cube(*this);
    
    this->setCubeFace(FRONT, cube.getCubeFace(FRONT) + QUARTER);
    this->setCubeFace(LEFT, cube.getCubeFace(BUTTOM));
    this->setCubeFace(REAR, cube.getCubeFace(REAR) - QUARTER);
    this->setCubeFace(RIGHT, cube.getCubeFace(TOP));
    this->setCubeFace(TOP, cube.getCubeFace(LEFT));
    this->setCubeFace(BUTTOM, cube.getCubeFace(RIGHT));
}

void MagicCube::setMagicCubeID(ROTATION3D arg) {
    this->layer++;
    this->Rotation3D = arg;
    this->history = this->getHistory() + '/' + this->getMagicCubeID();
}

void MagicCube::setMagicCube(ROTATION3D arg) {
    CubeFace bar;
    
    switch (arg) {
        case TOPCW:
            ++this->cubeFace[TOP];
            bar = this->getCubeFace(REAR);
            this->cubeFace[REAR].setBar(BUTTOMSIDE, this->getCubeFace(LEFT).getBar(LEFTSIDE));
            this->cubeFace[LEFT].setBar(LEFTSIDE, this->getCubeFace(FRONT).getReverseBar(TOPSIDE));//Reverse
            this->cubeFace[FRONT].setBar(TOPSIDE, this->getCubeFace(RIGHT).getBar(RIGHTSIDE));
            this->cubeFace[RIGHT].setBar(RIGHTSIDE, bar.getReverseBar(BUTTOMSIDE));//Reverse
            break;
        case TOPCCW:
            --this->cubeFace[TOP];
            bar = this->getCubeFace(REAR);
            this->cubeFace[REAR].setBar(BUTTOMSIDE, this->getCubeFace(RIGHT).getReverseBar(RIGHTSIDE));//Reverse
            this->cubeFace[RIGHT].setBar(RIGHTSIDE, this->getCubeFace(FRONT).getBar(TOPSIDE));
            this->cubeFace[FRONT].setBar(TOPSIDE, this->getCubeFace(LEFT).getReverseBar(LEFTSIDE));//Reverse
            this->cubeFace[LEFT].setBar(LEFTSIDE, bar.getBar(BUTTOMSIDE));
            break;
        case BUTTOMCW:
            ++this->cubeFace[BUTTOM];
            bar = this->cubeFace[REAR];
            this->cubeFace[REAR].setBar(TOPSIDE, this->getCubeFace(RIGHT).getReverseBar(LEFTSIDE));//Reverse
            this->cubeFace[RIGHT].setBar(LEFTSIDE, this->getCubeFace(FRONT).getBar(BUTTOMSIDE));
            this->cubeFace[FRONT].setBar(BUTTOMSIDE, this->getCubeFace(LEFT).getReverseBar(RIGHTSIDE));//Reverse
            this->cubeFace[LEFT].setBar(RIGHTSIDE, bar.getBar(TOPSIDE));
            break;
        case BUTTOMCCW:
            --this->cubeFace[BUTTOM];
            bar = this->getCubeFace(REAR);
            this->cubeFace[REAR].setBar(TOPSIDE, this->getCubeFace(LEFT).getBar(RIGHTSIDE));
            this->cubeFace[LEFT].setBar(RIGHTSIDE, this->getCubeFace(FRONT).getReverseBar(BUTTOMSIDE));//Reverse
            this->cubeFace[FRONT].setBar(BUTTOMSIDE, this->getCubeFace(RIGHT).getBar(LEFTSIDE));
            this->cubeFace[RIGHT].setBar(LEFTSIDE, bar.getReverseBar(TOPSIDE));//Reverse
            break;
        case LEFTCW:
            ++this->cubeFace[LEFT];
            bar = this->getCubeFace(TOP);
            this->cubeFace[TOP].setBar(RIGHTSIDE, this->getCubeFace(REAR).getReverseBar(LEFTSIDE));//Reverse
            this->cubeFace[REAR].setBar(LEFTSIDE, this->getCubeFace(BUTTOM).getBar(LEFTSIDE));
            this->cubeFace[BUTTOM].setBar(LEFTSIDE, this->getCubeFace(FRONT).getBar(LEFTSIDE));
            this->cubeFace[FRONT].setBar(LEFTSIDE, bar.getReverseBar(RIGHTSIDE));//Reverse
            break;
        case LEFTCCW:
            --this->cubeFace[LEFT];
            bar = this->getCubeFace(TOP);
            this->cubeFace[TOP].setBar(RIGHTSIDE, this->getCubeFace(FRONT).getReverseBar(LEFTSIDE));//Reverse
            this->cubeFace[FRONT].setBar(LEFTSIDE, this->getCubeFace(BUTTOM).getBar(LEFTSIDE));
            this->cubeFace[BUTTOM].setBar(LEFTSIDE, this->getCubeFace(REAR).getBar(LEFTSIDE));
            this->cubeFace[REAR].setBar(LEFTSIDE, bar.getReverseBar(RIGHTSIDE));//Reverse
            break;
        case RIGHTCW:
            ++this->cubeFace[RIGHT];
            bar = this->getCubeFace(TOP);
            this->cubeFace[TOP].setBar(LEFTSIDE, this->getCubeFace(FRONT).getReverseBar(RIGHTSIDE));//Reverse
            this->cubeFace[FRONT].setBar(RIGHTSIDE, this->getCubeFace(BUTTOM).getBar(RIGHTSIDE));
            this->cubeFace[BUTTOM].setBar(RIGHTSIDE, this->getCubeFace(REAR).getBar(RIGHTSIDE));
            this->cubeFace[REAR].setBar(RIGHTSIDE, bar.getReverseBar(LEFTSIDE));//Reverse
            break;
        case RIGHTCCW:
            --this->cubeFace[RIGHT];
            bar = this->getCubeFace(TOP);
            this->cubeFace[TOP].setBar(LEFTSIDE, this->getCubeFace(REAR).getReverseBar(RIGHTSIDE));//Reverse
            this->cubeFace[REAR].setBar(RIGHTSIDE, this->getCubeFace(BUTTOM).getBar(RIGHTSIDE));
            this->cubeFace[BUTTOM].setBar(RIGHTSIDE, this->getCubeFace(FRONT).getBar(RIGHTSIDE));
            this->cubeFace[FRONT].setBar(RIGHTSIDE, bar.getReverseBar(LEFTSIDE));//Reverse
            break;
        case FRONTCW:
            ++this->cubeFace[FRONT];
            bar = this->getCubeFace(TOP);
            this->cubeFace[TOP].setBar(TOPSIDE, this->getCubeFace(LEFT).getBar(TOPSIDE));
            this->cubeFace[LEFT].setBar(TOPSIDE, this->getCubeFace(BUTTOM).getBar(TOPSIDE));
            this->cubeFace[BUTTOM].setBar(TOPSIDE, this->getCubeFace(RIGHT).getBar(TOPSIDE));
            this->cubeFace[RIGHT].setBar(TOPSIDE, bar.getBar(TOPSIDE));
            break;
        case FRONTCCW:
            --this->cubeFace[FRONT];
            bar = this->getCubeFace(TOP);
            this->cubeFace[TOP].setBar(TOPSIDE, this->getCubeFace(RIGHT).getBar(TOPSIDE));
            this->cubeFace[RIGHT].setBar(TOPSIDE, this->getCubeFace(BUTTOM).getBar(TOPSIDE));
            this->cubeFace[BUTTOM].setBar(TOPSIDE, this->getCubeFace(LEFT).getBar(TOPSIDE));
            this->cubeFace[LEFT].setBar(TOPSIDE, bar.getBar(TOPSIDE));
            break;
        case REARCW:
            ++this->cubeFace[REAR];
            bar = this->getCubeFace(TOP);
            this->cubeFace[TOP].setBar(BUTTOMSIDE, this->getCubeFace(RIGHT).getBar(BUTTOMSIDE));
            this->cubeFace[RIGHT].setBar(BUTTOMSIDE, this->getCubeFace(BUTTOM).getBar(BUTTOMSIDE));
            this->cubeFace[BUTTOM].setBar(BUTTOMSIDE, this->getCubeFace(LEFT).getBar(BUTTOMSIDE));
            this->cubeFace[LEFT].setBar(BUTTOMSIDE, bar.getBar(BUTTOMSIDE));
            break;
        case REARCCW:
            --this->cubeFace[REAR];
            bar = this->getCubeFace(TOP);
            this->cubeFace[TOP].setBar(BUTTOMSIDE, this->getCubeFace(LEFT).getBar(BUTTOMSIDE));
            this->cubeFace[LEFT].setBar(BUTTOMSIDE, this->getCubeFace(BUTTOM).getBar(BUTTOMSIDE));
            this->cubeFace[BUTTOM].setBar(BUTTOMSIDE, this->getCubeFace(RIGHT).getBar(BUTTOMSIDE));
            this->cubeFace[RIGHT].setBar(BUTTOMSIDE, bar.getBar(BUTTOMSIDE));
            break;
        default:
            break;
    }
}

void MagicCube::setCubeFaces(NAMEOFCOLOR* transfers) {
    this->cubeFace[FRONT].setCells(transfers);
    this->cubeFace[TOP].setCells(transfers);
    this->cubeFace[RIGHT].setCells(transfers);
    this->cubeFace[BUTTOM].setCells(transfers);
    this->cubeFace[LEFT].setCells(transfers);
    this->cubeFace[REAR].setCells(transfers);
    
    delete[] transfers;
}

void MagicCube::setMagicCubeID(std::string arg) {
    std::string temp = "";
    int position = 0;
    
    this->history = arg;
    for (position = (int)arg.length() - 1; arg.at(position) != '_'; position--) {
        temp += arg.at(position);
    }
    this->layer = atoi((char*)temp.c_str());
    
    temp = "";
    for (position--; position >= 0 && arg.at(position) != '/'; position--) {
        temp = arg.at(position) + temp;
    }
    this->Rotation3D = static_cast<ROTATION3D>(atoi((char*)temp.c_str()));
}

void MagicCube::setMagicCubeFaces(std::string arg) {
    int cellOfFace = COUNTOFCELL * COUNTOFCELL;
    int cell = 0, color;
    
    for (int i = 0; i < arg.length(); i++) {
        cell = i % cellOfFace;
        color = arg.at(i) - '0';
        this->cubeFace[i/cellOfFace].setCell(cell / COUNTOFCELL, cell % COUNTOFCELL, static_cast<NAMEOFCOLOR>(color));
    }
}

void MagicCube::outFile() const{
    std::ofstream outFile;
    
    outFile.open(fileName, std::ios::in| std::ios::app);
    if (outFile.is_open()) {
        outFile << this->getHistory() << std::endl;
        outFile << this->getCompression() << std::endl;
        //outFile << this->front().getMyself()<<std::endl;
        outFile.close();
    }
    else {
        std::cout<<"The file is not exist"<< std::endl;
    }
}