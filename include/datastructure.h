#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include <vector>

class Vertex
{
public:
   double x;
   double y;
   double z;
   Vertex()
   {
       x = y = z = 0.;
   }
};

class Edge
{
private:
    unsigned int m_begin;
    unsigned int m_end;
public:
    Edge ( unsigned int begin, unsigned int end ) { m_begin = begin; m_end = end; }
    unsigned int begin() const { return m_begin; }
    unsigned int end() const { return m_end; }
};


class Face
{
private:
    std::vector < int > vertices;
public:
    Face(){}
    bool add_vertex ( unsigned int index );
    //! read access to indexes of vertices
    int operator[] ( unsigned int index ) const;
    int size() const { return vertices.size(); }
};


#endif // DATA_STRUCTURE_H
