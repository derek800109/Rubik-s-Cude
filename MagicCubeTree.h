//
//  magicCubeTree.h
//  resolveMagicCube
//
//  Created by DerekHsu on 10/28/14.
//  Copyright (c) 2014 DerekHsu. All rights reserved.
//

#ifndef __resolveMagicCube__MagicCubeTree__
#define __resolveMagicCube__MagicCubeTree__

#include <stdio.h>
#include <vector>
#include "MagicCube.h"

class MagicCubeTree {//need queue
private:
    MagicCube myself;
    MagicCube branches[COUNTOFROTATION];
    int sizeOfBranches;
public:
    MagicCubeTree();
    MagicCubeTree(MagicCube &);
    MagicCubeTree(std::string history, std::string compress);
    
    void setMagicCubeTree();
    MagicCube getBranch(ROTATION3D) const;
    MagicCube getMyself() const;
    int getSizeOfBranches() const;
    int size(int);
    void outFile();
    std::string getCompress(std::string);
protected:
    bool isHistory(std::string);
    bool findMagicCube(const MagicCubeTree &);
    bool findMagicCube();
};

#endif /* defined(__resolveMagicCube__magicCubeTree__) */
