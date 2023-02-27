#ifndef UTILS_CLASS_H
#define UTILS_CLASS_H
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <fstream>

class Utils
{


    public:

    static constexpr float EPSILON = 0.0000001f;
    static void showFloatVector(
        const std::vector<float>& v, 
        const int breakInt = 1, 
        const char* preText = ""
    ) {
        std::cout << preText << "\nFloat Vector: " << std::endl;
        for(int i = 0; i < v.size(); ++i)
        { 
            char br = (i % (breakInt) == 0) ? '\n' : '\t';
            std::cout << br << v[i]; 
        }
        std::cout << '\n';
    
    }

    static void showIntVector(const std::vector<GLuint>& v, const int breakInt = 1)
    {
        std::cout << "Int Vector: " << std::endl;
        for(int i = 0; i < v.size(); ++i)
        { 
            char br = (i % (breakInt) == 0) ? '\n' : '\t';
            std::cout << br << v[i]; 
        }
        std::cout << '\n';
    
    }

    static void showIntVector(const std::vector<int>& v, const int breakInt = 1)
    {
        std::cout << "Int Vector: " << std::endl;
        for(int i = 0; i < v.size(); ++i)
        { 
            char br = (i % (breakInt) == 0) ? '\n' : '\t';
            std::cout << br << v[i]; 
        }
        std::cout << '\n';
    
    }

    static void showGlmVec3(const glm::vec3& v)
    {
        std::cout << "GLM Vector: " << std::endl;
        std::cout << "X: " << v.x << " Y: " << v.y << " Z: " << v.z;
        std::cout << '\n';
    }

    static void showVec3Array(const std::vector<glm::vec3>& v)
    {
        std::cout << "Vector Array: " << std::endl;
        for(int i = 0; i < v.size(); ++i)
        {
            showGlmVec3(v[i]);
        }
        std::cout << '\n';
    }

    static void writeToFile(const char* path, const std::vector<glm::vec3>& v)
    {
        std::ofstream myfile;
        myfile.open (path);
        myfile << "Name: " << path << "\n\n";
        myfile << "\nVector Array: " << std::endl;
        for(int i = 0; i < v.size(); ++i)
        {
            if(i % 3 == 0)
                myfile << '\n';
           //std::cout << "\nGLM Vector: " << std::endl;
            myfile << "X: " << v[i].x << " Y: " << v[i].y << " Z: " << v[i].z;
            myfile << '\n';
        
        }
        
        myfile.close();
    }

    static void writeToFile(const char* path, const std::vector<int>& v, const int breakInt = 1)
    {
        std::ofstream myfile;
        myfile.open (path);

       myfile << "Name: " << path << "\n\n";
        myfile << "\nInt Vector: " << std::endl;
        for(int i = 0; i < v.size(); ++i)
        { 
            char br = (i % (breakInt) == 0) ? '\n' : '\t';
            myfile << br << v[i]; 
        }
        myfile << '\n';
        myfile.close();
    
    }

    static void writeToFile(const char* path, const char* s)
    {
        std::ofstream myfile;
        myfile.open (path);
        myfile << s;
        myfile.close();

    }

    static void showIntList( std::list<int>& l ) {
        std::list<int>::iterator ir = l.begin();
        std::cout << "\nItems:\n";
        for( int i = 0; i <= l.size(); ++i, ++ir ) { 
            std::cout << "\t" << *ir; 
        }
    }
  
    
    static int GetIntValueAt( std::list<int>& l, int index ) {
        std::list<int>::iterator itOut = l.begin();
        for( int i = 0; i < index; ++i, ++itOut ) {}
        return *itOut;
    }

};

#endif // !UTILS_CLASS_H