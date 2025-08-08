#pragma once
#include <glm/glm.hpp>

class Vector2{
public:
    Vector2(float v0, float v1) : vector(glm::vec2(v0, v1)) {};
    Vector2(const glm::vec2& vector) : vector(vector) {};

    inline float& operator[](size_t i){ return vector[i]; }
    inline float operator[](size_t i) const {return vector[i]; }

    inline Vector2& operator=(const Vector2& other){
        vector = (glm::vec2)other;
        return *this;
    }

    inline Vector2 operator*(const float& scalar){
        return Vector2(vector * scalar); 
    }

    inline Vector2 operator/(const float& scalar){
        return Vector2(vector / scalar);
    }

    inline Vector2 operator+(const Vector2& other){
        return Vector2(vector + (const glm::vec2&)other);
    }

    inline Vector2 operator-(const Vector2& other){
        return Vector2(vector - (const glm::vec2&)other);
    }

    inline void operator*=(const float& scalar){
        vector *= scalar;
    }

    inline void operator/=(const float& scalar){
        vector /= scalar;
    }

    inline void operator+=(const Vector2& other){
        vector += (glm::vec2)other;
    }
    inline void operator-=(const Vector2& other){
        vector -= (glm::vec2)other;
    }

    inline operator glm::vec2&() {return vector;}
    inline operator glm::vec2() const {return vector;}
    inline operator const glm::vec2&() const {return vector;}

private:
    glm::vec2 vector;
};

class Vector3{
public:
    Vector3(float v0, float v1, float v2) : vector(glm::vec3(v0, v1, v2)) {};
    Vector3(const glm::vec3& vector) : vector(vector) {};

    inline float& operator[](size_t i){ return vector[i]; }
    inline float operator[](size_t i) const {return vector[i]; }

    inline Vector3 operator*(const float& scalar){
        return Vector3(vector * scalar); 
    }

    inline Vector3 operator/(const float& scalar){
        return Vector3(vector / scalar);
    }

    inline Vector3 operator+(const Vector3& other){
        return Vector3(vector + (const glm::vec3&)other);
    }

    inline Vector3 operator-(const Vector3& other){
        return Vector3(vector - (const glm::vec3&)other);
    }

    inline void operator*=(const float& scalar){
        vector *= scalar;
    }

    inline void operator/=(const float& scalar){
        vector /= scalar;
    }

    inline void operator+=(const Vector3& other){
        vector += (const glm::vec3&)other;
    }
    inline void operator-=(const Vector3& other){
        vector -= (const glm::vec3&)other;
    }

    inline operator glm::vec3&() {return vector;}
    inline operator glm::vec3() const {return vector;}
    inline operator const glm::vec3&() const {return vector;}

private:
    glm::vec3 vector;
};

class Vector4{
    public:
    Vector4(float v0, float v1, float v2, float v3) : vector(glm::vec4(v0, v1, v2, v3)) {};
    Vector4(const glm::vec4& vector) : vector(vector) {};

    inline float& operator[](size_t i){ return vector[i]; }
    inline float operator[](size_t i) const {return vector[i]; }

    inline Vector4 operator*(const float& scalar){
        return Vector4(vector * scalar); 
    }

    inline Vector4 operator/(const float& scalar){
        return Vector4(vector / scalar);
    }

    inline Vector4 operator+(const Vector4& other){
        return Vector4(vector + (const glm::vec4&)other);
    }

    inline Vector4 operator-(const Vector4& other){
        return Vector4(vector - (const glm::vec4&)other);
    }

    inline void operator*=(const float& scalar){
        vector *= scalar;
    }

    inline void operator/=(const float& scalar){
        vector /= scalar;
    }

    inline void operator+=(const Vector4& other){
        vector += (const glm::vec4&)other;
    }
    inline void operator-=(const Vector4& other){
        vector -= (const glm::vec4&)other;
    }

    inline operator glm::vec4&() {return vector;}
    inline operator glm::vec4() const {return vector;}
    inline operator const glm::vec4&() const {return vector;}

private:
    glm::vec4 vector;
};