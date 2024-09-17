#pragma once
#ifndef GNODE_H
#endif GNODE_H
#include<iostream>
using namespace std;
#include<string>;
#include<list>
class gnode
{
public:
    string vertex;
    list<string> l1;
    bool visited;
    gnode();


};
gnode::gnode()
{
    vertex = "";
    visited = 0;
}