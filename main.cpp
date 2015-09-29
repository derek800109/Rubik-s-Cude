//
//  main.cpp
//  resolveMagicCube
//
//  Created by DerekHsu on 10/28/14.
//  Copyright (c) 2014 DerekHsu. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include "MagicCubeTree.h"
#include "myQueue.h"

using std::cout;
using std::endl;

void buildMagicCubeForest(MyQueue);

int main() {
    MagicCube tree;
    
    MyQueue bucket(tree);
    buildMagicCubeForest(bucket);
    
    return EXIT_SUCCESS;
}

void buildMagicCubeForest(MyQueue bucket) {
    MagicCubeTree tree;
    
    while (!bucket.empty()) {
        tree = MagicCubeTree(bucket.front().getHistory(), bucket.front().getCompress());
        tree.setMagicCubeTree();
        if (tree.getSizeOfBranches() != 0) {
            bucket.pushs(tree);
        }
        cout << tree.getMyself().getHistory() << endl;
        cout <<"bucket "<<bucket.size() << endl;
        bucket.pop();
    }
}