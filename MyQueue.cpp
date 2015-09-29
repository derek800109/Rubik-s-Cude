//
//  myQueue.cpp
//  resolveMagicCube
//
//  Created by DerekHsu on 12/10/14.
//  Copyright (c) 2014 DerekHsu. All rights reserved.
//

#include <vector>
#include <iostream>
#include <fstream>
#include "MyQueue.h"

Node::Node() : history(""), compress("") {}

Node::Node(std::string history, std::string line) : history(history), compress(line) {}

std::string Node::getHistory() {
    return this->history;
}

std::string Node::getCompress() {
    return  this->compress;
}

void Node::setCompress(std::string arg) {
    this->compress = arg;
}

void Node::setHistory(std::string arg) {
    this->history = arg;
}

MyQueue::MyQueue(const MagicCube& arg) {
    this->push(arg);
}

void MyQueue::push(const MagicCube& arg) {
    this->push(arg.getHistory(), arg.getCompression());
    arg.outFile();
}

void MyQueue::push(std::string history, std::string compress) {
    std::ofstream outFile;
    
    outFile.open(queueFile, std::ios::app);
    outFile << history << std::endl;
    outFile << compress << std::endl;
    
    outFile.close();
}

void MyQueue::pushs(const MagicCubeTree& arg){
    for (int i = 0; i < arg.getSizeOfBranches(); i++) {
        this->push(arg.getBranch(static_cast<ROTATION3D>(i)));
    }
}

void MyQueue::pop() {
    this->exporting(2);
    this->retrieve();
}

void MyQueue::exporting(int skip) {
    std::string temp;
    std::ofstream outFileTemp;
    std::ifstream inFileCube;
    
    outFileTemp.open(tempFile, std::ios::trunc);
    inFileCube.open(queueFile);
    if (!outFileTemp.is_open() || !inFileCube.is_open()) {
        std::cout << "[exporting] file not open" << std::endl;
        getchar();
    } else {
        for (int i = 0; i < skip; i++, getline(inFileCube, temp));
        for (getline(inFileCube, temp); temp != ""; getline(inFileCube, temp)) {
            outFileTemp << temp << std::endl;
        }
    
        inFileCube.close();
        outFileTemp.close();
    }
}

void MyQueue::retrieve() {
    std::string temp;
    std::ifstream inFileTemp;
    std::ofstream outFileCube;
    
    inFileTemp.open(tempFile);
    outFileCube.open(queueFile, std::ios::trunc);
    if (!inFileTemp.is_open() || !outFileCube.is_open()) {
        std::cout << "[retrieve] file not open" << std::endl;
        getchar();
    } else {
        for (getline(inFileTemp, temp); temp != ""; getline(inFileTemp, temp)) {
            outFileCube << temp << std::endl;
        }
    }
}

bool MyQueue::empty() {
    std::ifstream inFile;
    std::string temp;
    
    inFile.open(queueFile);
    getline(inFile, temp);
    inFile.close();
    
    return temp == "";
}

int MyQueue::size() {
    int count = 0;
    std::string temp;
    std::ifstream inFile;
    inFile.open(queueFile);
    
    do {
        count++;
        getline(inFile, temp);
    } while (temp != "");
    inFile.close();
    
    return count / 2;
}

Node MyQueue::front() {
    Node node;
    std::string temp;
    std::ifstream inFile;
    
    inFile.open(queueFile);
    
    getline(inFile, temp);
    node.setHistory(temp);
    getline(inFile, temp);
    node.setCompress(temp);
    inFile.close();
    
    return node;
}