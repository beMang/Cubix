#include "mesh.hpp"
#include <cstdio>
#include <cstring>
#include <cstdlib>

//TODO : rewrite using C++ file handling

namespace objects
{
    Mesh::Mesh(string filename, Vector position, Vector rotation, double scale) : Object(position, rotation), scale(scale)
    {
        this->vertices = vector<Vector>();
        this->faces = vector<Face>();

        loadVerticesAndFaces(filename, this->vertices, this->faces);
        for (vector<Face>::iterator it = this->faces.begin(); it < this->faces.end(); it++)
        {
            it->computeNormal(this->vertices);
        }
    }

    Mesh::Mesh(Vector position, Vector rotation) : Object(position, rotation)
    {
    }

    Mesh::~Mesh()
    {
    }

    void Mesh::print()
    {
        printf("Mesh\n");
        printf("Position : ");
        this->position.print();
        printf("Rotation : ");
        this->rotation.print();
        printf("Vertices : \n");
        for (vector<Vector>::iterator it = this->vertices.begin(); it < this->vertices.end(); it++)
        {
            it->print();
        }
        printf("Faces : \n");
        for (vector<Face>::iterator it = this->faces.begin(); it < this->faces.end(); it++)
        {
            it->print();
        }
    }

    vector<Vector> Mesh::getGlobalVertices()
    {
        maths::Matrix rotationX = maths::Matrix::rotationX_matrix(this->rotation(0));
        maths::Matrix rotationY = maths::Matrix::rotationY_matrix(this->rotation(1));
        maths::Matrix rotationZ = maths::Matrix::rotationZ_matrix(this->rotation(2));

        vector<Vector> global_vertices = vector<Vector>();
        for (vector<Vector>::iterator it = this->vertices.begin(); it < this->vertices.end(); it++)
        {
            Vector global_vertex = rotationX*rotationY*rotationZ*(*it)*scale + this->position;
            global_vertices.push_back(global_vertex);
        }
        return global_vertices;
    }

    void Mesh::countVerticesAndFaces(string filename, int &n_vertices, int &n_faces)
    {
        const int MAX = 100;
        char buf[MAX];
        FILE* input = fopen(filename.c_str(), "r");

        fgets(buf, MAX, input);
        n_vertices = 0;
        n_faces = 0;

        while (buf!=NULL)
        {
            char* occurence = strtok(buf, " ");
            if (*occurence==*"v") n_vertices++;
            if (*occurence==*"f") {
                n_faces++;
            }
            if (fgets(buf, MAX, input)==NULL) break;
        }
        fclose(input);
    }

    void Mesh::loadVerticesAndFaces(string filename, vector<Vector> &vertices, vector<Face> &faces)
    {
        int n_vertices, n_faces;
        countVerticesAndFaces(filename, n_vertices, n_faces);

        printf("Number of faces : %d\n", n_faces);
        printf("Number of vertices : %d\n", n_vertices);

        const int MAX = 100;
        char buf[MAX];
        FILE* input = fopen(filename.c_str(), "r");

        fgets(buf, MAX, input);

        int current_vertice = 0;
        int current_face = 0;

        while (buf!=NULL)
        {
            char* occurence = strtok(buf, " ");
            if (*occurence==*"v") {
                vertices.push_back(Vector(0,0,0));
                for (int i = 0; i < 3; i++)
                {
                    occurence = strtok(NULL, " ");
                    vertices[current_vertice](i) = strtod(occurence, NULL);
                }
                current_vertice++;
            } else if (*occurence==*"f") {
                vector<int> vertices_number = vector<int>();
                for (int i = 0; i < 6; i++) //5 is the maximum number of vertices per face
                {
                    occurence = strtok(NULL, " ");
                    if(occurence==NULL) break;
                    vertices_number.push_back(atoi(occurence)-1);
                }
                faces.push_back(Face(vertices_number));
                current_face++;
            }
            if (fgets(buf, MAX, input)==NULL) break;
        }
        fclose(input);
    }
} // namespace objects
