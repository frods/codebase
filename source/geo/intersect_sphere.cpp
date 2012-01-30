#include "../math/vector.h"
#include "../math/math.h"

bool intersect_sphere(vector from, vector to, vector center, float radius)
{
  vector ray = to - from;
  
  vector sphere_from = center - from;
  
  vector cross_ray_sphere_from;
  cross_ray_sphere_from.cross(ray, sphere_from);
  
  // Since the length of the cross product of two vectors equals
  // the area of the parallelogram formed by the two vectors
  // Using the properties of a perallelogram the area
  // devided by one edge length gives the length of the 
  // height perpendicular to the edge and intersecting the oposite vertex.
  // Use this property to check if the ray is intersecting the sphere.
  float parallelogram_area = cross_ray_sphere_from.length();
  float ray_length = ray.length();
  float height = parallelogramarea/ray_length;
  
  if(height <= radius)
  {
    // The ray enters the sphere calculate the intersection point
    float shere_from_length = shere_from.length();
    float heightsq = height * height;
    float from_to_proj = sqrt(sphere_from_length * sphere_from_length - heightsq);
    float sphere_to_proj = sqrt(radius * radius - heightsq);
    float from_to_sphere = from_to_proj - shere_to_proj;
    float ray_fraction = from_to_sphere/ray_length;
    vector normray(ray);
    normray.normalize();
    vector intersection = from + from_to_sphere * normray;
    vector normal = intersection - center;
    normal.normalize();
    return true;
  }
  return false;
}
