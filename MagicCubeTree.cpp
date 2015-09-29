//
//  magicCubeTree.cpp
//  resolveMagicCube
//
//  Created by DerekHsu on 10/28/14.
//  Copyright (c) 2014 DerekHsu. All rights reserved.
//

#include <fstream>
#include "MagicCubeTree.h"
#include "VirtualMagicCube.h"

MagicCubeTree::MagicCubeTree() : sizeOfBranches(0) {}

MagicCubeTree::MagicCubeTree(MagicCube& arg) : myself(arg), sizeOfBranches(0) {}

MagicCubeTree::MagicCubeTree(std::string history, std::string compress) : myself(history,compress), sizeOfBranches(0) {
}

void MagicCubeTree::setMagicCubeTree() {
    for (int rotate = 0; rotate < COUNTOFROTATION; rotate++) {
        MagicCubeTree cubeTree(this->myself[static_cast<ROTATION3D>(rotate)]);
        if (!this->findMagicCube(cubeTree) && !cubeTree.findMagicCube()) {
            this->branches[this->sizeOfBranches++] = cubeTree.getMyself();
        }
    }
}

bool MagicCubeTree::findMagicCube(){
    std::ifstream inFile;
    std::string history = "", compress = "";
    MagicCube cube;
    bool found = false;
    
    inFile.open(fileName);
    if (inFile.is_open()) {
        getline(inFile, history);
        while (!found && history != "") {
            getline(inFile, compress);
            cube = MagicCube(history, compress);
            if ((VirtualMagicCube &)cube == (VirtualMagicCube &)this->myself) {
                found = true;
            }
            getline(inFile, history);
        }
        inFile.close();
    } else {
        std::cout << "[findMagicCube()]The file is not open!" << std::endl;
        getchar();
    }
    
    return  found;
}

bool MagicCubeTree::findMagicCube(const MagicCubeTree& arg){
    bool found = false;
    
    for (int i = 0; i < this->sizeOfBranches && !found; i++) {
        if ((VirtualMagicCube &)this->branches[i] == (VirtualMagicCube &)arg.myself) {
            found = true;
        }
    }
    
    return  found;
}

MagicCube MagicCubeTree::getMyself() const{
    return this->myself;
}

int MagicCubeTree::getSizeOfBranches() const{
    return this->sizeOfBranches;
}

MagicCube MagicCubeTree::getBranch(ROTATION3D arg) const{
    return this->branches[arg];
}

void MagicCubeTree::outFile() {
    std::ofstream outFile;
    
    outFile.open(fileName, std::ios::in| std::ios::app);
    if (outFile.is_open()) {
        outFile << this->getMyself().getHistory() << std::endl;
        outFile << this->getMyself().getCompression() << std::endl;
        //outFile << this->front().getMyself()<<std::endl;
        outFile.close();
    }
    else {
        std::cout<<"The file is not exist"<< std::endl;
    }
}

std::string MagicCubeTree::getCompress(std::string arg) {
    std::ifstream inFile;
    std::string compress = "";
    
    inFile.open(fileName);
    if (inFile.is_open()) {
        while (compress != arg) {
            getline(inFile, compress);
        }
        getline(inFile, compress);
    } else {
        std::cout << "The File is not exit" << std::endl;
    }
    
    return compress;
}

bool MagicCubeTree::isHistory(std::string arg) {
    return arg.empty() ? false : arg.at(2) == '_';
}