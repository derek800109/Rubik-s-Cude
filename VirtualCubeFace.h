//
//  virtualCubeFace.h
//  resolveMagicCube
//
//  Created by DerekHsu on 11/11/14.
//  Copyright (c) 2014 DerekHsu. All rights reserved.
//

#ifndef __resolveMagicCube__VirtualCubeFace__
#define __resolveMagicCube__VirtualCubeFace__

#include <stdio.h>
#include "CubeFace.h"
#include <iostream>

class VirtualCubeFace : public CubeFace {
private:
    NAMEOFCOLOR transfers[COUNTOFFACE];
public:
    VirtualCubeFace();
    VirtualCubeFace(const CubeFace &);
    VirtualCubeFace(const VirtualCubeFace &);
    bool operator==(VirtualCubeFace &);
    //operator
    NAMEOFCOLOR getVirtualTransfer(NAMEOFCOLOR index);
    void setVirtualCubeFaceColor();
    void setVirtualCubeFaceColor(NAMEOFCOLOR* transfers);
    //setter and getter
protected:
    void setVirtualCubeFace();
    void setVirtualTransfer(NAMEOFCOLOR index, NAMEOFCOLOR transfer);
    void setVirtualTransfers();
    void resetVirtualTransfers();
    //
    void showTransfer();
    //test
};

#endif /* defined(__resolveMagicCube__virtualCubeFace__) */
