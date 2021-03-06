#import "vector.h"
#import "../math/math.h"

vector::vector()
{
  m_x = 0.0f;
  m_y = 0.0f;
  m_z = 0.0f;
}

vector::vector(const vector & other)
{
  m_x = other.m_x;
  m_y = other.m_y;
  m_z = other.m_z;
}

float vector::length()
{
  // Return the length of this vector
  return sqrt(dot(*this));
}

vector vector::operator-(const vector &other)
{
  vector result;
  result.m_x = m_x - other.m_x;
  result.m_y = m_y - other.m_y;
  result.m_z = m_z - other.m_z;
  return result;
}

vector vector::operator+(const vector &other)
{
  vector result;
  result.m_x = m_x + other.m_x;
  result.m_y = m_y + other.m_y;
  result.m_z = m_z + other.m_z;
  return result;
}

void vector::normalize()
{
  // Normalize the vector in place
  float len = length();
  m_x = m_x / len;
  m_y = m_y / len;
  m_z = m_z / len;
}

vector vector::scalar_multiply(float val)
{
  vector result;
  result.m_x = m_x * val;
  result.m_y = m_y * val;
  result.m_z = m_z * val;
  return result;
}


float vector::dot(const vector &other)
{
  // Calculate the dot product of this vector and other.
  // Geometrically the dot product = length(this)*length(other)*cos(theta)
  // where theta is the angle between this and other at the origin
  // A value of 0.0 indicates that the vectors are parallel
  // a value of 1.0 indicates taht the vectors are perpendicular
  return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z;
}

void vector::cross(const vector &first, const vector &second)
{
  // Set this vector to the value of the cross product of 
  // first and second.
  // The cross product is the projection of first onto second.
  // 
  m_x = first.m_y * second.m_z - first.m_z * second.m_y;
  m_y = first.m_x * second.m_z - first.m_z * second.m_x;
  m_z = first.m_x * second.m_y - first.m_x * second.m_y;
}
