#include "vec3.h"
#include "mesh.h"

#define HEIGHT 101
#define WIDTH 101
#define PITCH 0.3
#define THICKNESS 3
#define AMP 1.0 //ランダムな凹凸の最大高さ

int main() {
	int x, y;
	double heightmap[HEIGHT][WIDTH];

	//ランダムな高さマップを生成する
	for(y = 0; y < HEIGHT; y++) {
		for(x = 0; x < WIDTH; x++) {
			heightmap[y][x] = ((double)rand() / RAND_MAX) * AMP;

			//周囲を高さ0にする（穴あきを防ぐ）
			if ( (x==0) or (x==WIDTH-1) or (y==0) or (y==HEIGHT-1) ) {
				heightmap[y][x] = 0;
			}
		}
	}


	Mesh mesh_heightfield, mesh_base, mesh_dst;

	//高さマップの作成
	for(y = 0; y < HEIGHT-1; y++) {
		for(x = 0; x < WIDTH-1; x++) {
			mesh_heightfield += create_quadrilateral(
					Vec3((x+0) * PITCH, (y+0) * PITCH, heightmap[(y+0)][(x+0)]),
					Vec3((x+0) * PITCH, (y+1) * PITCH, heightmap[(y+1)][(x+0)]),
					Vec3((x+1) * PITCH, (y+1) * PITCH, heightmap[(y+1)][(x+1)]),
					Vec3((x+1) * PITCH, (y+0) * PITCH, heightmap[(y+0)][(x+1)]));
		}
	}
	mesh_heightfield.flip_normal();

	//土台の作成
	mesh_base = create_cube();
	mesh_base.scale(Vec3((WIDTH-1)*PITCH, (HEIGHT-1)*PITCH, THICKNESS));
	mesh_base.translate(Vec3(0.5*(WIDTH-1)*PITCH, 0.5*(HEIGHT-1)*PITCH, -0.5*THICKNESS));

	//高さマップと土台の統合
	mesh_dst = mesh_heightfield + mesh_base;
	mesh_dst.stl_write("heightfield.stl");
}
