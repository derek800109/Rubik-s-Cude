//
//  virtualMagicCube.h
//  resolveMagicCube
//
//  Created by DerekHsu on 11/11/14.
//  Copyright (c) 2014 DerekHsu. All rights reserved.
//

#ifndef __resolveMagicCube__VirtualMagicCube__
#define __resolveMagicCube__VirtualMagicCube__

#include <stdio.h>
#include "VirtualCubeFace.h"
#include "MagicCube.h"

class VirtualMagicCube : public MagicCube{
private:
    NAMEOFCOLOR transfers[COUNTOFFACE];
public:
    VirtualMagicCube(const MagicCube &);
    bool operator==(const VirtualMagicCube &);
    bool operator!=(const VirtualMagicCube &);
    friend std::ostream& operator<<(std::ostream& virtualMagicCubeOut, const VirtualMagicCube &);
protected:
    void resetVirtualTransfers();
    void setVirtualTransfer(NAMEOFCOLOR index, NAMEOFCOLOR color);
    bool checkVirtualTransfers(const MagicCube &);
    NAMEOFCOLOR getVirtualTransfer(NAMEOFCOLOR) const;
    NAMEOFCOLOR* getVirtualTransfers() const;
};

#endif /* defined(__resolveMagicCube__virtualMagicCube__) */
