#include <glm/glm.hpp>
#include "Vector.h"

class Matrix4{
public:
    inline Matrix4(const glm::mat4& matrix) : matrix(matrix){}

    //TODO!!! change glm::vec4 for Vector4 when possible for below [] operator overloads
    inline glm::vec4& operator[](size_t i){
        return matrix[i];
    }
    inline const glm::vec4& operator[](size_t i) const{
        return matrix[i];
    }

    inline Matrix4& operator=(const Matrix4& other){
        matrix = (const glm::mat4&)other;
        return *this;
    }

    inline Matrix4 operator+(const Matrix4& other){
        return Matrix4(matrix + (const glm::mat4&)other);
    }

    inline Matrix4 operator-(const Matrix4& other){
        return Matrix4(matrix - (const glm::mat4&)other);
    }

    inline Matrix4 operator*(const Matrix4& other){
        return Matrix4(matrix * (const glm::mat4&) other);
    }

    inline operator glm::mat4&() { return matrix; }
    inline operator glm::mat4() const { return matrix; }
    inline operator const glm::mat4&() const { return matrix; }

private:
    glm::mat4 matrix;
};