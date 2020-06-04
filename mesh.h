#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <sstream>
#include <vector>

#include <fstream>
#include <string>

#include "vec3.h"
#include "triangle.h"

class Mesh {
	public:
		Mesh() {}
		
		//三角形の追加
		void add(Triangle t) { Triangles.push_back(t); }
		
		//頂点による，三角形の追加
		void add(const Point3& vertex1, 
				 const Point3& vertex2,
				 const Point3& vertex3)
		{
			Triangle t(vertex1, vertex2, vertex3);
			Triangles.push_back(t);
		}

		//全て消去
		void clear() { Triangles.clear(); }

		//三角形の数を返す
		int size() { return Triangles.size(); }

		//拡大・縮小
		Mesh& scale(const Vec3& s)
		{
			//スケール値が0なら1にする
			double x, y, z;
			x = ((s.x()!=0) ? s.x() : 1);
			y = ((s.y()!=0) ? s.y() : 1);
			z = ((s.z()!=0) ? s.z() : 1);
			Vec3 _s(x, y, z);

			Vec3 v1, v2, v3;
			for (auto& t : Triangles) {
				v1 = t.v1 * _s;
				v2 = t.v2 * _s;
				v3 = t.v3 * _s;
				t = {v1, v2, v3};
			}
			return *this;
		}

		//移動
		Mesh& translate(const Vec3& trans)
		{
			Vec3 v1, v2, v3;
			for (auto& t : Triangles) {
				v1 = t.v1 + trans;
				v2 = t.v2 + trans;
				v3 = t.v3 + trans;
				t = {v1, v2, v3};
			}
			return *this;
		}

		//回転
		Mesh& rotate(double deg, const Vec3& n)
		{
			Vec3 v1, v2, v3;
			for (auto& t : Triangles) {
				v1 = rodrigues_rotate(t.v1, deg, n);
				v2 = rodrigues_rotate(t.v2, deg, n);
				v3 = rodrigues_rotate(t.v3, deg, n);
				t = {v1, v2, v3};
			}
			return *this;
		}

		//法線の反転
		Mesh& flip_normal()
		{
			for( auto& t : Triangles) {
				t.flip_normal();
			}
			return *this;
		}

		//STLファイルの書き出し
		void stl_write(const std::string& filename, const std::string& name="") const {
			std::ofstream file(filename);

			file << "solid" << " " << name << std::endl;
			for (const auto& t : Triangles) {
				file << "\t" << "facet normal" << " " << t.normal() << std::endl;
				file << "\t\t" << "outer loop" << std::endl;
				file << "\t\t\t" << " " << "vertex" << " " << t.vertex1() << std::endl;
				file << "\t\t\t" << " " << "vertex" << " " << t.vertex2() << std::endl;
				file << "\t\t\t" << " " << "vertex" << " " << t.vertex3() << std::endl;
				file << "\t\t" << "endloop" << std::endl;
				file << "\t" << "endfacet" << std::endl;
			}
			file << "endsolid" << " " << name << std::endl;

			file.close();
		}


		Mesh& operator+=(const Mesh &m) {
			Triangles.insert(Triangles.end(), (m.Triangles).begin(), (m.Triangles).end());
			return *this;
		}

	public:
		std::vector<Triangle> Triangles;

};

//2つのメッシュを統合する
inline Mesh operator+(const Mesh &m1, const Mesh &m2) {
	Mesh m;
	(m.Triangles).insert((m.Triangles).end(), (m1.Triangles).begin(), (m1.Triangles).end());
	(m.Triangles).insert((m.Triangles).end(), (m2.Triangles).begin(), (m2.Triangles).end());
	return m;
}

//四角形を，対角線で2つの三角形に分割して作る
inline Mesh create_quadrilateral (const Point3& p1,
					const Point3& p2,
			   		const Point3& p3,
			   		const Point3& p4)
{
	Mesh m;
	m.add(p1, p2, p4);
	m.add(p4, p2, p3);
	return m;
};

//立方体の生成
inline Mesh create_cube ()
{
	Mesh m;
	Point3 vertex1, vertex2, vertex3;

	vertex1 = {0, 0, 1};
	vertex2 = {1, 0, 1};
	vertex3 = {0, 1, 1};
	m.add(vertex1, vertex2, vertex3);

	vertex1 = {1, 1, 1};
	vertex2 = {0, 1, 1};
	vertex3 = {1, 0, 1};
	m.add(vertex1, vertex2, vertex3);

	vertex1 = {1, 0, 1};
	vertex2 = {1, 0, 0};
	vertex3 = {1, 1, 1};
	m.add(vertex1, vertex2, vertex3);

	vertex1 = {1, 1, 0};
	vertex2 = {1, 1, 1};
	vertex3 = {1, 0, 0};
	m.add(vertex1, vertex2, vertex3);

	vertex1 = {1, 0, 0};
	vertex2 = {0, 0, 0};
	vertex3 = {1, 1, 0};
	m.add(vertex1, vertex2, vertex3);
	
	vertex1 = {0, 1, 0};
	vertex2 = {1, 1, 0};
	vertex3 = {0, 0, 0};
	m.add(vertex1, vertex2, vertex3);
	
	vertex1 = {0, 0, 0};
	vertex2 = {0, 0, 1};
	vertex3 = {0, 1, 0};
	m.add(vertex1, vertex2, vertex3);
	
	vertex1 = {0, 1, 1};
	vertex2 = {0, 1, 0};
	vertex3 = {0, 0, 1};
	m.add(vertex1, vertex2, vertex3);
	
	vertex1 = {0, 1, 1};
	vertex2 = {1, 1, 1};
	vertex3 = {0, 1, 0};
	m.add(vertex1, vertex2, vertex3);
	
	vertex1 = {1, 1, 0};
	vertex2 = {0, 1, 0};
	vertex3 = {1, 1, 1};
	m.add(vertex1, vertex2, vertex3);
	
	vertex1 = {1, 0, 1};
	vertex2 = {0, 0, 1};
	vertex3 = {1, 0, 0};
	m.add(vertex1, vertex2, vertex3);
	
	vertex1 = {0, 0, 0};
	vertex2 = {1, 0, 0};
	vertex3 = {0, 0, 1};
	m.add(vertex1, vertex2, vertex3);

	m.translate(Vec3(-0.5, -0.5, -0.5));
	return m;
}

//STLファイルの読み込み
//(読み込みの成功判定は，ファイル読み込みができたかでしか判定していない．中身は関係ない．)
inline Mesh stl_read(const std::string& filename) {
	Mesh m;

	std::ifstream file(filename);
	if ( file.fail() ) {
		std::cerr << "Failed to open " << filename << "." << std::endl;
		return m;
	}

	std::string line, buf;
	double px, py, pz;
	Vec3 v[3];
	int i=0;
	while ( getline(file, line) ) {
		if( line.find("vertex") != std::string::npos ) {
			std::istringstream s(line);
			s >> buf >> px >> py >> pz;
			v[i] = {px, py, pz};
			if(++i>=3) {
				i=0;
				Triangle t(v[0], v[1], v[2]);
				m.add(t);
			}
			continue;
		}
	}
	return m;
}

#endif
