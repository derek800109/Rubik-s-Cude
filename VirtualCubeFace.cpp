//
//  virtualCubeFace.cpp
//  resolveMagicCube
//
//  Created by DerekHsu on 11/11/14.
//  Copyright (c) 2014 DerekHsu. All rights reserved.
//

#include "VirtualCubeFace.h"

VirtualCubeFace::VirtualCubeFace() {
    this->resetVirtualTransfers();
}

VirtualCubeFace::VirtualCubeFace(const CubeFace& arg) : CubeFace(arg) {
    this->setVirtualCubeFace();
}

VirtualCubeFace::VirtualCubeFace(const VirtualCubeFace& arg) : CubeFace(arg) {
    this->setVirtualCubeFace();
}

bool VirtualCubeFace::operator==(VirtualCubeFace& arg) {
    bool same = false;
    VirtualCubeFace treatment(arg);
    
    do {
        if (!(same = ((CubeFace &)*this == (const CubeFace &)treatment))) {
            ++treatment;
            treatment.setVirtualCubeFace();
        }
        else {
            arg.setRotation(treatment.getRotationCW());
        }
    } while (treatment.getRotationCW() != NONE && !same);
    
    return same;
}

void VirtualCubeFace::setVirtualCubeFace() {
    this->resetVirtualTransfers();
    this->setVirtualTransfers();
    this->setVirtualCubeFaceColor();
}

void VirtualCubeFace::setVirtualTransfers() {
    NAMEOFCOLOR index = TRANSPARENT;
    int colorCount = 0;
    
    for (int i = 0; i < COUNTOFCELL; i++) {
        for (int j = 0; j < COUNTOFCELL; j++) {
            if (this->getVirtualTransfer(index = this->getCell(i, j)) == TRANSPARENT) {
                this->setVirtualTransfer(index, static_cast<NAMEOFCOLOR>(colorCount++));
            }
        }
    }
}

void VirtualCubeFace::showTransfer() {
    for (int i = 0; i < COUNTOFFACE; i++) {
        std::cout << this->getVirtualTransfer(static_cast<NAMEOFCOLOR>(i)) << ' ';
    }
    std::cout << std::endl;
}

void VirtualCubeFace::setVirtualCubeFaceColor() {
    NAMEOFCOLOR color = TRANSPARENT;

    for (int i = 0; i < COUNTOFCELL; i++) {
        for (int j = 0; j < COUNTOFCELL; j++) {
            if ((color = this->getVirtualTransfer(this->getCell(i, j))) != TRANSPARENT) {
                this->setCell(i, j, color);
            }
        }
    }
}

void VirtualCubeFace::setVirtualCubeFaceColor(NAMEOFCOLOR *transfers) {
    NAMEOFCOLOR color = TRANSPARENT;
    
    for (int i = 0; i < COUNTOFCELL; i++) {
        for (int j = 0; j < COUNTOFCELL; j++) {
            if ((color = transfers[this->getCell(i, j)]) != TRANSPARENT) {
                this->setCell(i, j, color);
            }
        }
    }
    
    delete[] transfers;
}

void VirtualCubeFace::resetVirtualTransfers() {
    for (int i = 0; i < COUNTOFFACE; i++) {
        this->setVirtualTransfer(static_cast<NAMEOFCOLOR>(i), TRANSPARENT);
    }
}

void VirtualCubeFace::setVirtualTransfer(NAMEOFCOLOR index, NAMEOFCOLOR transfer) {
    this->transfers[index] = transfer;
}

NAMEOFCOLOR VirtualCubeFace::getVirtualTransfer(NAMEOFCOLOR arg) {
    return this->transfers[arg];
}