#ifndef VECTOR_H
#define VECTOR_H

class vector
{
public:
  vector();
  vector(vector other);
  
  ~vector();

  float dot(vector other);
  void cross(vector first vector second);
  float m_x;
  float m_y;
  float m_z;
  
  
};

#endif
