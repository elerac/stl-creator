#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vec3.h"

inline Vec3 get_normal(const Point3 &v1, const Point3 &v2, const Point3 &v3) {
	return unit_vector(cross(v2-v1, v3-v2));
}

class Triangle {
	public:
		Point3 v1;
		Point3 v2;
		Point3 v3;
		Vec3 n;
	
		Triangle(const Point3& vertex1,
				 const Point3& vertex2,
				 const Point3& vertex3)
			: v1(vertex1), v2(vertex2), v3(vertex3) 
		{
			n = get_normal(v1, v2, v3);
		}
		
		Triangle(const Point3& vertex1, const Point3& vertex2, const Point3& vertex3, const Vec3& normal)
			: v1(vertex1), v2(vertex2), v3(vertex3), n(normal) {}

		void flip_normal() {
			std::swap(v2, v3);
			n = get_normal(v1, v2, v3);
		}

		Point3 vertex1() const { return v1; }
		Point3 vertex2() const { return v2; }
		Point3 vertex3() const { return v3; }
		Point3 normal()  const { return n; }
};

#endif 
