#include "vec3.h"
#include "mesh.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

#define THICKNESS 100 //持ち手部分の長さ
#define AMP 6 //スタンプの凹凸の長さ

int main() {
	unsigned char *image;
	int width, height;
	int n;
	image = stbi_load("images/maeda_stamp.png", &width, &height, &n, 1);

	Mesh mesh_cube, mesh_cube_mv;
	Mesh mesh_base, mesh_stamp;

	//スタンプの凹凸を作成
	mesh_cube = create_cube();
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			if(image[y * width + x] > 128) continue;

			mesh_cube_mv = mesh_cube;
			mesh_cube_mv.translate(Vec3(x, y, 0.5));
			mesh_cube_mv.scale(Vec3(1, 1, AMP));
			mesh_stamp += mesh_cube_mv;
		}
	}
	mesh_stamp.translate(Vec3(-0.5*(width-1), -0.5*(height-1), 0));

	//スタンプの土台（持ち手部分）を作成
	mesh_base = mesh_cube;
	mesh_base.translate(Vec3(0, 0, -0.5));
	mesh_base.scale(Vec3(width, height, THICKNESS));
	
	//スタンプと土台を統合
	mesh_stamp += mesh_base;

	mesh_stamp.stl_write("stamp.stl");
}
