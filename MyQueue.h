//
//  myQueue.h
//  resolveMagicCube
//
//  Created by DerekHsu on 12/10/14.
//  Copyright (c) 2014 DerekHsu. All rights reserved.
//

#ifndef __resolveMagicCube__MyQueue__
#define __resolveMagicCube__MyQueue__

#include <stdio.h>
#include "MagicCubeTree.h"

static const std::string queueFile = "myQueue.txt";
static const std::string tempFile = "temp.txt";

class Node {
private:
    std::string history;
    std::string compress;
public:
    Node();
    Node(std::string history, std::string compress);
    std::string getHistory();
    std::string getCompress();
    void setHistory(std::string);
    void setCompress(std::string);
};

class MyQueue {
public:
    MyQueue(const MagicCube& arg);
    void push(const MagicCube &);
    void push(std::string history,std::string compress);
    void pushs(const MagicCubeTree &);
    bool empty();
    int size();
    void pop();
    Node front();
protected:
    void exporting(int skip);
    void retrieve();
};

#endif /* defined(__resolveMagicCube__myQueue__) */
