/***************************************************************************
                          mesh.hpp  -  description
                             -------------------
    copyright            : (C) 2012 by Biri
    email                : biri@univ-mlv.fr
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef _STP3D_INDEXED_MESH_HPP_
#define _STP3D_INDEXED_MESH_HPP_


#include <iostream>
#include <vector>
#include "globals.hpp"
#include "mesh.h"


namespace STP3D {

    /**
      * \class IndexedMesh allows to store generic informations about an indexed mesh.
      * IndexedMesh class allows to store several float buffer to use with a GL shaders in
      * an indexed way. Such buffers are not interleaved and each has a semantic on his own.
      * Note that an indexed mesh MUST have at least one buffer of coordinates.
      * This class allows also the creation of the corresponding VBO.
      * This class may or may not store the data.
      */
    class IndexedMesh {
    public:
        /// Standard construtor. Creates an empty mesh withouh any information.
        IndexedMesh(uint n_prim = 0,uint elts = 0,uint new_gl_type = GL_TRIANGLES) : id_vao(0) {
            buffers.clear();
            size_one_elt.clear();
            attr_id.clear();
            attr_semantic.clear();
            vbo_id.clear();
            memory_buffers_owner.clear();
            gl_type_mesh = new_gl_type;
            nb_primitive = n_prim;
            index_buffer = NULL;
            nb_idx_per_primitive = getNbIdxPerPrimitive();
            if (nb_primitive>0) {
                index_buffer = new uint[nb_primitive*nb_idx_per_primitive];
            }
            nb_elts = elts;
            id_index = 0;
            memory_index_owner = false;
        }

        //! Decorator for Mesh
        IndexedMesh(Mesh const & mesh) {
            if ( mesh.get_model() == 1 )
                gl_type_mesh = GL_POINTS;
            else if ( mesh.get_model() == 2 )
                gl_type_mesh = GL_LINES;
            else if ( mesh.get_model() == 3 )
                gl_type_mesh = GL_TRIANGLES;
            else
                gl_type_mesh = GL_TRIANGLE_FAN;
            buffers.clear();
            size_one_elt.clear();
            attr_id.clear();
            attr_semantic.clear();
            vbo_id.clear();
            memory_buffers_owner.clear();
            nb_idx_per_primitive = getNbIdxPerPrimitive();
            memory_index_owner = false;
            nb_elts = mesh.vertex_count();
            nb_primitive = mesh.face_count();
            addIndexBuffer( const_cast < uint * > ( &mesh.faces[0] ),false);
            addOneBuffer(0, 3, const_cast < float * > ( &mesh.vertices[0] ), std::string("position"),false);
        }

        ~IndexedMesh();

        //  User defined members
        /// The index buffer
        uint* index_buffer;
        /// The index buffer
        uint nb_primitive;
        /// The id of index buffer
        uint id_index;
        /// All the data in CPU buffers
        std::vector<float*> buffers;
        /// Number of elements in each buffer : must be common !!
        uint nb_elts;
        /// Size of one element in each buffer
        std::vector<uint> size_one_elt;
        /// Attribute id corresponding to each buffer
        std::vector<uint> attr_id;
        /// Attribute semantic corresponding to each buffer
        std::vector<std::string> attr_semantic;
        /// Attribute semantic corresponding to each buffer
        uint gl_type_mesh;

        //  GL defined members
        /// Id of all VBO. Created by the GL API
        std::vector<uint> vbo_id;
        /// Id of the corresponding VAO
        uint id_vao;

        /// Set the number of elements in each buffers
        void setNbElt(uint elts) {nb_elts = elts;}
        void setNbIndex(uint idx) {nb_primitive = idx;if (index_buffer) delete[](index_buffer);}
        void addIndexBuffer(uint* data,bool copy = false);
        void addOneBuffer(uint id_attribute,uint one_elt_size,
                          float* data,std::string semantic="",bool copy=false);
        void releaseCPUMemory();
        /*****************************************************************
         *                      GL RELATED FUNCTIONS
         *****************************************************************/
        void changeType(uint new_gl_type) {
            gl_type_mesh = new_gl_type;
            nb_idx_per_primitive = getNbIdxPerPrimitive();
        }
        bool createVAO();
        void draw();

    private:
        uint nb_idx_per_primitive;
        uint getNbIdxPerPrimitive();
        bool memory_index_owner;
        std::vector < bool > memory_buffers_owner;

    };

    inline IndexedMesh::~IndexedMesh() {
        if (buffers.size()>0) {
            for(std::vector<int>::size_type i = 0; i < buffers.size(); ++i) {
                if ( memory_buffers_owner[i] == true )
                    if (buffers[i]) delete[](buffers[i]);
            }
        }
        if (index_buffer && memory_index_owner == true) delete[](index_buffer);
    }

    inline uint IndexedMesh::getNbIdxPerPrimitive() {
        if(gl_type_mesh == GL_POINTS) return 1;
        if(gl_type_mesh == GL_LINES) return 2;
        if(gl_type_mesh == GL_TRIANGLES) return 3;
        if(gl_type_mesh == GL_TRIANGLE_FAN) return 4;
        STP3D::setError("Wrong type of type in getNbIdxPerPrimitive");
        return 0;
    }


    inline bool IndexedMesh::createVAO() {
        // Create and use the VAO
        glGenVertexArrays(1,&id_vao);
        if (id_vao == 0) {
            STP3D::setError("Unable to find a value for a VAO");
            return false;
        }
        glBindVertexArray(id_vao);

        // Check if mesh is defined
        if (buffers.size()==0) {
            STP3D::setError("Impossible to create VBO from empty buffers. This mesh has not been initialized");
        }

        // Create all VBO (and check)
        vbo_id.resize(buffers.size());
        uint* new_id = new uint[buffers.size()];
        glGenBuffers(buffers.size(),new_id);
        for(uint i=0;i<buffers.size();++i) {
            if (new_id[i]==0) {STP3D::setError("Unable to find an empty VBO");return false;}
            vbo_id[i]=new_id[i];
        }
        delete[](new_id);

        // Create the index VBO (and check)
        glGenBuffers(1,&id_index);
        if (id_index==0) {STP3D::setError("Unable to find an empty VBO for index buffer");return false;}


        // Transfer all data for all VBO from CPU to GPU
        for(std::vector<int>::size_type i = 0; i < buffers.size(); ++i) {
            glEnableVertexAttribArray(attr_id[i]);

            glBindBuffer(GL_ARRAY_BUFFER,vbo_id[i]);

            glBufferData(GL_ARRAY_BUFFER,nb_elts*size_one_elt[i]*sizeof(GLfloat),buffers[i],GL_STATIC_DRAW);

            glVertexAttribPointer(attr_id[i], size_one_elt[i], GL_FLOAT, GL_FALSE, 0, 0);

            glBindBuffer(GL_ARRAY_BUFFER,0);
        }
        // Transfer index data VBO from CPU to GPU
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id_index);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,nb_idx_per_primitive*nb_primitive*sizeof(uint),index_buffer,GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

        glBindVertexArray(0);
        return true;
    }

    inline void IndexedMesh::addIndexBuffer(uint* data,bool copy) {
        if (copy) {
            memcpy(index_buffer,data,nb_idx_per_primitive*nb_primitive*sizeof(uint));
            memory_index_owner = true;
        }
        else {
            if (index_buffer) delete[](index_buffer);
            index_buffer = data;
            memory_index_owner = false;
        }
    }

    inline void IndexedMesh::addOneBuffer(uint id_attribute,uint one_elt_size,
                                           float* data,std::string semantic,bool copy) {
        if (copy) {
            float* tab = new float[one_elt_size*nb_elts];
            memcpy(tab,data,one_elt_size*nb_elts*sizeof(float));
            buffers.push_back(tab);
            memory_buffers_owner.push_back(true);

        }
        else
        {
            buffers.push_back(data);
            memory_buffers_owner.push_back(false);
        }
        attr_id.push_back(id_attribute);
        size_one_elt.push_back(one_elt_size);
        attr_semantic.push_back(semantic);
    }

    inline void IndexedMesh::draw() {
        glBindVertexArray(id_vao);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id_index);
        glDrawElements(gl_type_mesh,nb_primitive*nb_idx_per_primitive,GL_UNSIGNED_INT,0);

        glBindVertexArray(0);
    }


    inline void IndexedMesh::releaseCPUMemory() {
        for(std::vector<int>::size_type i = 0; i < buffers.size(); ++i) {
            if (buffers[i]) delete[](buffers[i]);
            buffers[i] = NULL;
        }
        if (index_buffer) {
            delete[](index_buffer);
            index_buffer = NULL;
        }
    }
}

#endif


