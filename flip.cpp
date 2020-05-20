#include "mesh.h"

int main() {
	Mesh mesh_src;
	mesh_src = stl_read("cube-ascii.stl");

	Mesh mesh_dst = mesh_src;
	mesh_dst.flip_normal();

	mesh_dst.stl_write("flip.stl");
}
