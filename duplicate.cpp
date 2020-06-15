#include "vec3.h"
#include "mesh.h"

#define HEIGHT 5   // x方向の複製数
#define WIDTH 5    // y方向の複製数
#define THICKNESS 5 // z方向の複製数
#define PITCH 2     // 複製ピッチ
#define RAND_RATE 3 // ランダムに出現させる確率の逆数（1で100%）
#define RAND_SEL 2  // ランダムに出現させるときの剰余 0 <= RAND_SEL < RAND_RATE

int main() {
	Mesh mesh_src;
	mesh_src = stl_read("cube-ascii.stl");
	
	Mesh mesh_dst;

	//ランダムに複製させる
	for(int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {
			for(int z = 0; z < THICKNESS; z++) {

				if(rand() % RAND_RATE != RAND_SEL) continue;

				Mesh mesh_dup = mesh_src;
				mesh_dup.translate(Vec3(x*PITCH, y*PITCH, z*PITCH));
				mesh_dst += mesh_dup;
			}
		}
	}

	mesh_dst.stl_write("duplicate.stl");
}
