//
//  virtualMagicCube.cpp
//  resolveMagicCube
//
//  Created by DerekHsu on 11/11/14.
//  Copyright (c) 2014 DerekHsu. All rights reserved.
//

#include "VirtualMagicCube.h"

VirtualMagicCube::VirtualMagicCube(const MagicCube& arg) : MagicCube(arg) {
    this->resetVirtualTransfers();
}

bool VirtualMagicCube::operator==(const VirtualMagicCube& arg) {
    bool same = false;
    MagicCube cube(arg);
    
    for (int isFront = FRONT; isFront < COUNTOFFACE && !same; isFront++) {
        if ((VirtualCubeFace)this->getCubeFace(FRONT) ==
            reinterpret_cast<VirtualCubeFace &>(cube.getCubeFace(static_cast<NAMEOFFACE>(isFront)))) {//need rotate all
            cube.calibrateMagicCube(static_cast<NAMEOFFACE>(isFront));
            same = VirtualMagicCube(cube).checkVirtualTransfers(*this);
        }
    }
    
    return same;
}

bool VirtualMagicCube::operator!=(const VirtualMagicCube& arg) {
    return !(*this == arg);
}

std::ostream& operator<<(std::ostream& VirtualMagicCubeOut, const VirtualMagicCube& arg) {
    std::cout << (const MagicCube &)arg;
    std::cout << "Transfers: ";
    for (int i = 0; i < COUNTOFFACE; i++) {
        VirtualMagicCubeOut << arg.getVirtualTransfer(static_cast<NAMEOFCOLOR>(i)) << ' ';
    }
    std::cout << std::endl;
    
    return VirtualMagicCubeOut;
}
/*
void VirtualMagicCube::setVirtualTransfers(NAMEOFCOLOR frontColor,
                                           NAMEOFCOLOR topColor,
                                           NAMEOFCOLOR rightColor) {
    CubeFace* method = new CubeFace;
    
    this->setVirtualTransfer(frontColor, method->getColorByFace(FRONT));
    this->setVirtualTransfer(topColor, method->getColorByFace(TOP));
    this->setVirtualTransfer(rightColor, method->getColorByFace(RIGHT));
    this->setVirtualTransfer(method->getOppositeColor(topColor), method->getColorByFace(BUTTOM));
    this->setVirtualTransfer(method->getOppositeColor(rightColor), method->getColorByFace(LEFT));
    this->setVirtualTransfer(method->getOppositeColor(frontColor), method->getColorByFace(REAR));
    
    delete method;
}
*/
bool VirtualMagicCube::checkVirtualTransfers(const MagicCube& arg) {//this is the cube will be change
    NAMEOFCOLOR sorColor = TRANSPARENT, tarColor = TRANSPARENT;
    bool repeat = false;
    
    for (int face = 0; face < COUNTOFFACE/2 && !repeat; face++) {
        for (int row = 0; row < COUNTOFCELL && !repeat; row++) {
            for (int col = 0; col < COUNTOFCELL && !repeat; col++) {
                sorColor = this->getCubeFace(static_cast<NAMEOFFACE>(face)).getCell(row, col);
                tarColor = arg.getCubeFace(static_cast<NAMEOFFACE>(face)).getCell(row, col);
                if (this->getVirtualTransfer(sorColor) == TRANSPARENT) {
                    this->setVirtualTransfer(sorColor, tarColor);
                } else {
                    if (this->getVirtualTransfer(sorColor) != tarColor) {
                        this->resetVirtualTransfers();
                        repeat = true;
                    }
                }
            }
        }
    }
    
    return !repeat;
}

void VirtualMagicCube::setVirtualTransfer(NAMEOFCOLOR index, NAMEOFCOLOR color) {
    if (color != TRANSPARENT) {
        this->transfers[index] = color;
    }
}

void VirtualMagicCube::resetVirtualTransfers() {
    this->transfers[RED] = TRANSPARENT;
    this->transfers[YELLOW] = TRANSPARENT;
    this->transfers[GREEN] = TRANSPARENT;
    this->transfers[WHITE] = TRANSPARENT;
    this->transfers[BLUE] = TRANSPARENT;
    this->transfers[ORANGE] = TRANSPARENT;
}

NAMEOFCOLOR VirtualMagicCube::getVirtualTransfer(NAMEOFCOLOR arg) const{
    return this->transfers[arg];
}

NAMEOFCOLOR* VirtualMagicCube::getVirtualTransfers() const{
    NAMEOFCOLOR* pTransfers = new NAMEOFCOLOR[COUNTOFFACE];
    
    for (int i = 0; i < COUNTOFFACE; i++) {
        pTransfers[i] = this->getVirtualTransfer(static_cast<NAMEOFCOLOR>(i));
    }
    
    return pTransfers;
}