#ifndef VECTOR_H
#define VECTOR_H

class vector
{
public:
  vector();
  vector(const vector &other);
  
  ~vector();

  float length();
  float dot(const vector &other);
  void cross(const vector &first, const vector &second);
  vector operator-(const vector &other);
  vector operator+(const vector &other);
  void normalize();
  vector scalar_multiply(float val);
  float m_x;
  float m_y;
  float m_z;
};

#endif
