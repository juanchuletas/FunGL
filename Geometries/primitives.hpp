#if !defined(_GEOMETRIES_H_)
#define _GEOMETRIES_H_
#include <vector>
#include "../Vertex/fungtVertex.hpp"
class Primitive{

private:
    std::vector<Vertex> vertex; 
    std::vector<GLuint> index; 


    public: 
        Primitive();
        virtual ~Primitive();


        void set(const Vertex *vertices, const unsigned numOfvert, const GLuint *indices, const unsigned numOfindices);
        Vertex *getVertices();
        GLuint* getIndices();
        unsigned getNumOfVertices();
        unsigned getNumOfIndices();
        long unsigned sizeOfVertices();
        long unsigned sizeOfIndices();


}; 



#endif // _GEOMETRIES_H_

