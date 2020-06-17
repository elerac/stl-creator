# STL creator
create and edit STL files in C++ (Version of C++ is 11 or higher.)

You can see how to use STL-creator from [here](https://www.slideshare.net/secret/LV0MNJfI1xszLl).

```cpp
#include "vec3.h"
#include "triangle.h"
#include "mesh.h"

int main() {
  Vec3 p1(0, 0, 1), p2(1, 0, 1), p3(1, 1, 1), p4(0, 1, 1);
  
  Mesh mesh1, mesh2, mesh3, mesh4;
  Mesh mesh_dst;
  
  //三角形の追加
  Triangle triangle(p1, p2, p3);
  mesh1.add(triangle);
  
  //四角形の作成
  mesh2 = create_quadrilateral(p1, p2, p3, p4);
  mesh2.translate(Vec3(0, 0, -1.5));
  
  //立方体の作成
  mesh3 = create_cube();
  mesh3.scale(Vec3(1, 0.5, 2.5));
  mesh3.rotate(30, Vec3(0, 0, 1));
  
  //STLファイルの入力
  mesh4 = stl_read("sphere-ascii.stl");
  
  //メッシュの統合
  mesh_dst = mesh1 + mesh2 + mesh3 + mesh4;
  
  //STLファイルの出力
  mesh_dst.stl_write("example.stl");
}
```

## duplicate.cpp
![duplicate_result](https://github.com/elerac/stl-creator/blob/master/images/duplicate_result.jpg)

## flip.cpp
![flip_result](https://github.com/elerac/stl-creator/blob/master/images/flip_result.jpg)

## heightfield.cpp
![heightfield_result](https://github.com/elerac/stl-creator/blob/master/images/heightfield_result.jpg)

## stamp.cpp
![stamp_result](https://github.com/elerac/stl-creator/blob/master/images/stamp_result.jpg)

## function.cpp
![function_result](https://github.com/elerac/stl-creator/blob/master/images/function_result.jpg)
