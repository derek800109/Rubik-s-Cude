//
//  cubeFace.cpp
//  resolveMagicCube
//
//  Created by DerekHsu on 10/28/14.
//  Copyright (c) 2014 DerekHsu. All rights reserved.
//

#include <iostream>
#include "CubeFace.h"

CubeFace::CubeFace() {
    this->resetRotationCW();
    this->setCells(TRANSPARENT);
}

CubeFace::CubeFace(const CubeFace& arg) {
    this->setCubeFace(arg);
}

CubeFace::CubeFace(const NAMEOFCOLOR& arg) {
    this->resetRotationCW();
    this->setCells(arg);
}

void CubeFace::setCubeFace(const CubeFace& arg) {
    this->RotationCW = arg.RotationCW;
    this->setCells(arg.getCells());
}

void CubeFace::operator=(const CubeFace& arg) {
    this->setCubeFace(arg);
}

bool CubeFace::operator==(CubeFace& arg) {
    bool same = false;
    CubeFace face(arg);
    
    do {
        if ((same = (*this == (const CubeFace &)face))) {
            arg.setRotation(face.getRotationCW());
        } else {
            ++face;
        }
    }while (face.getRotationCW() != NONE && !same);
    
    return same;
}


bool CubeFace::operator==(const CubeFace& arg) {
    return this->isSameCells(arg);
}

void CubeFace::setRotation(int arg) {
    switch (arg) {
        case NONE:
            this->RotationCW = NONE;
            break;
        case QUARTER:
            this->RotationCW = QUARTER;
            break;
        case HALF:
            this->RotationCW = HALF;
            break;
        case MINUSQUARTER:
            this->RotationCW = MINUSQUARTER;
            break;
        default:
            break;
    }
}

void CubeFace::updateRotation(int arg) {
    this->setRotation((this->getRotationCW() + arg) % COUNTOFSIDE);
}

bool CubeFace::isSameCells(const CubeFace& arg) {
    bool same = true;
    
    for (int i = 0; i < COUNTOFCELL; i++) {
        for (int j = 0; j < COUNTOFCELL; j++) {
            if (this->getCell(i, j) != arg.getCell(i, j)) {
                same = false;
            }
        }
    }
    
    return same;
}

void CubeFace::operator++() {
    this->updateRotation(QUARTER);
    this->rotate90CW();
}

void CubeFace::operator--() {
    this->updateRotation(MINUSQUARTER);
    for (int rotation = 0; rotation < COUNTOFSIDE - 1; rotation++) {
        this->rotate90CW();
    }
}

CubeFace& CubeFace::operator-(ROTATION arg) const{
    CubeFace *face = new CubeFace(*this);
    int rLimit = (COUNTOFSIDE - arg) % COUNTOFSIDE;
    
    face->updateRotation(rLimit);
    for (int rotation = 0; rotation < rLimit; rotation++) {
        face->rotate90CW();
    }
    
    return *face;
}

CubeFace& CubeFace::operator+(ROTATION arg) const{
    CubeFace *face = new CubeFace(*this);
    
    face->updateRotation(arg);
    for (int rotation = 0; rotation < arg; rotation++) {
        face->rotate90CW();
    }
    
    return *face;
}

void CubeFace::operator+=(ROTATION arg) {
    this->updateRotation(arg);
    for (int i = 0; i < arg; i++) {
        this->rotate90CW();
    }
}

std::ostream& operator<<(std::ostream& cubeFaceOut, const CubeFace& arg) {
    for (int i = 0; i < COUNTOFCELL; i++) {
        for (int j = 0; j < COUNTOFCELL; j++) {
            cubeFaceOut << '\t' <<  SHOWCOLOR[arg.getCell(i, j)] << ' ';
        }
        cubeFaceOut << std::endl;
    }
    
    return cubeFaceOut;
}

NAMEOFCOLOR** CubeFace::getCells() const{
    NAMEOFCOLOR** color= new NAMEOFCOLOR*[COUNTOFCELL];
    for (int i = 0; i < COUNTOFCELL; i++) {
        color[i] = new NAMEOFCOLOR[COUNTOFCELL];
    }
    
    for (int i = 0; i < COUNTOFCELL; i++) {
        for (int j = 0; j < COUNTOFCELL; j++) {
            color[i][j] = this->getCell(i, j);
        }
    }
    
    return color;
}

NAMEOFCOLOR CubeFace::getColorByFace(NAMEOFFACE arg) {
    NAMEOFCOLOR color = TRANSPARENT;
    
    switch (arg) {
        case RED:
            color = RED;
            break;
        case YELLOW:
            color = YELLOW;
            break;
        case GREEN:
            color = GREEN;
            break;
        case WHITE:
            color = WHITE;
            break;
        case BLUE:
            color = BLUE;
            break;
        case ORANGE:
            color = ORANGE;
            break;
        default:
            break;
    }
    
    return color;
}

NAMEOFCOLOR CubeFace::getOppositeColor(NAMEOFCOLOR arg) {
    NAMEOFCOLOR color = TRANSPARENT;
    
    switch (arg) {
        case RED:
        case ORANGE:
            color = (arg == RED) ? ORANGE : RED;
            break;
        case YELLOW:
        case WHITE:
            color = (arg == YELLOW) ? WHITE : YELLOW;
            break;
        case GREEN:
        case BLUE:
            color = (arg == GREEN) ? BLUE : GREEN;
            break;
        default:
            break;
    }
    
    return color;
}

int CubeFace::getRotationCW(ROTATION arg) const{
    return (this->getRotationCW() + arg) % COUNTOFSIDE;
}

int CubeFace::getRotationCCW(ROTATION arg) const{
    return (COUNTOFSIDE - arg + this->getRotationCW()) % COUNTOFSIDE;
}

void CubeFace::rotate90CW() {
    CubeFace Face(*this);
    for (int row = 0; row < COUNTOFCELL; row++) {
        for (int col = 0; col < COUNTOFCELL; col++) {
            this->setCell(col, COUNTOFCELL - row - 1, Face.getCell(row, col));
        }
    }
}

void CubeFace::resetRotationCW() {
    this->RotationCW = NONE;
}

void CubeFace::setCells(NAMEOFCOLOR **arg) {
    for (int i = 0; i < COUNTOFCELL; i++) {
        for (int j = 0; j < COUNTOFCELL; j++) {
            if (arg[i][j] != TRANSPARENT) {
                this->setCell(i, j, arg[i][j]);
            }
        }
    }
    
    for(int i = 0 ; i < COUNTOFCELL; ++i) {
        delete[] arg[i];
    }
    delete[] arg;
}

void CubeFace::setCells(NAMEOFCOLOR* transfers) {
    for (int i = 0; i < COUNTOFCELL; i++) {
        for (int j = 0; j < COUNTOFCELL; j++) {
            if (transfers[this->getCell(i, j)] != TRANSPARENT) {
                this->setCell(i, j, transfers[this->getCell(i, j)]);
            }
        }
    }
    
    delete[] transfers;
}

void CubeFace::setCell(int row, int col, NAMEOFCOLOR arg) {
    this->cells[row][col] = arg;
}

void CubeFace::setCells(NAMEOFCOLOR arg) {
    for (int i = 0; i < COUNTOFCELL; i++) {
        for (int j = 0; j < COUNTOFCELL; j++) {
            this->setCell(i, j, arg);
        }
    }
}

NAMEOFCOLOR CubeFace::getCell(int row, int col) const {
    return this->cells[row][col];
}

ROTATION CubeFace::getRotationCW() const{
    return this->RotationCW;
}

void CubeFace::setBar(DIRECTION targetDir ,NAMEOFCOLOR* arg) {
    switch (targetDir) {
        case TOPSIDE:
            for (int i = 0; i < COUNTOFCELL; i++) {
                this->setCell(0, i, arg[i]);
            }
            break;
        case BUTTOMSIDE:
            for (int i = 0; i < COUNTOFCELL; i++) {
                this->setCell(COUNTOFCELL-1, i, arg[i]);
            }
            break;
        case LEFTSIDE:
            for (int i = 0; i < COUNTOFCELL; i++) {
                this->setCell(i, 0, arg[i]);
            }
            break;
        case RIGHTSIDE:
            for (int i = 0; i < COUNTOFCELL; i++) {
                this->setCell(i, COUNTOFCELL - 1, arg[i]);
            }
            break;
        default:
            break;
    }
    
    delete[] arg;
}

NAMEOFCOLOR *CubeFace::getBar(DIRECTION arg) const{
    NAMEOFCOLOR *bar = new NAMEOFCOLOR[COUNTOFCELL];
    
    switch (arg) {
        case TOPSIDE:
            for (int i = 0; i < COUNTOFCELL; i++) {
                bar[i] = this->getCell(0, i);
            }
            break;
        case BUTTOMSIDE:
            for (int i = 0; i < COUNTOFCELL; i++) {
                bar[i] = this->getCell(COUNTOFCELL-1, i);
            }
            break;
        case LEFTSIDE:
            for (int i = 0; i < COUNTOFCELL; i++) {
                bar[i] = this->getCell(i, 0);
            }
            break;
        case RIGHTSIDE:
            for (int i = 0; i < COUNTOFCELL; i++) {
                bar[i] = this->getCell(i, COUNTOFCELL-1);
            }
            break;
        default:
            break;
    }
    
    return bar;
}

NAMEOFCOLOR* CubeFace::getReverseBar(DIRECTION arg) const{
    CubeFace face(*this);
    int direction = (arg + HALF) % COUNTOFSIDE;
    
    face += HALF;
    
    return face.getBar(static_cast<DIRECTION>(direction));
}