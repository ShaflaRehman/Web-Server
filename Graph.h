#pragma once
#include<list>
#include<string>
#include "gnode.h"
#ifndef GRAPH_H
#define GRAPH_H
class Graph
{
    list<gnode> l;
public:
    void insert_vertex(string a);
    void insert_edge(string from, string to);
    void delete_vertex(string a);
    bool isEmpty();
    void display_adjacency_list();
    bool edge_exists(string a, string b);
    void delete_edge(string a, string b);
    int vertices();
    int edges();



};
#endif

void Graph::insert_vertex(string a)
{
    gnode g;
    g.vertex = a;
    l.push_back(g);

}
void Graph::insert_edge(string from, string to) {


    if (!(edge_exists(from, to)))
    {

        auto it_from = find_if(l.begin(), l.end(), [&](const gnode& node)
            {
                return node.vertex == from;
            });

        auto it_to = find_if(l.begin(), l.end(), [&](const gnode& node) {
            return node.vertex == to;
            });


        if (it_from != l.end() && it_to != l.end()) {

            it_from->l1.push_back(to);
           // it_to->l1.push_back(from);

        }
        
    }
}
void Graph::delete_vertex(string a)
{

    auto it = find_if(l.begin(), l.end(), [&](const gnode& node) {
        return node.vertex == a;
        });

    if (it != l.end())
    {
        l.erase(it);
        for (auto& node : l) {
            node.l1.remove(a);
        }

    }
    else {
        cout << "Vertex not found in the graph." << endl;
    }
}


bool Graph::isEmpty()
{
    if (l.begin() == l.end())
    {
        return true;
    }
    return false;


}
void Graph::display_adjacency_list()
{
    cout << "   Adjacency List  : " << endl;
    cout << "Vertex :  Adjacent vertices  " << endl;
    auto it = l.begin();
    while (it != l.end())
    {
        cout << "   " << it->vertex << "     ";
        auto lt = it->l1.begin();
        while (lt != it->l1.end())
        {
            cout << *lt << "  ";
            ++lt;
        }


        cout << endl;
        ++it;
    }
}
bool Graph::edge_exists(string a, string b)
{
    auto it1 = find_if(l.begin(), l.end(), [&](const gnode& node)
        {
            return node.vertex == a;
        });

    auto lt = it1->l1.begin();
    while (lt != it1->l1.end())
    {
        if (*lt == b)
        {
            return 1;
        }
        ++lt;

    }

    return 0;

}
void Graph::delete_edge(string a, string b)
{
    auto it1 = find_if(l.begin(), l.end(), [&](const gnode& node)
        {
            return node.vertex == a;
        });
    if (it1 != l.end())
    {
        it1->l1.remove(b);

    }
}
int Graph::vertices()
{
    auto it1 = l.begin();
    int count = 0;
    while (it1 != l.end())
    {
        ++it1;
        ++count;
    }
    return count;

}
int Graph::edges()
{
    int count = 0;
    auto it = l.begin();
    while (it != l.end())
    {

        auto lt = it->l1.begin();
        while (lt != it->l1.end())
        {
            ++lt;
            ++count;
        }
        ++it;


    }
    return count / 2;
}






