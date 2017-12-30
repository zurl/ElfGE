//
// Created by sky on 2017/12/8.
//

#ifndef ELFGE_WATERTILE_H_H
#define ELFGE_WATERTILE_H_H
class WaterTile {

	float height;
	float x,z;
public:
	const float TILE_SIZE = 60;


	WaterTile(float centerX, float centerZ, float height){
		x = centerX;
		z = centerZ;
		height = height;
	}

	float getHeight() {
		return height;
	}

	float getX() {
		return x;
	}

	float getZ() {
		return z;
	}

};
#endif
