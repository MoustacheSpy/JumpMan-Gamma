#pragma once
#include <JUMA_textures.h>
struct JUMA_color {
	float r;
	float g;
	float b;
	float a;
	JUMA_color() {  };
	JUMA_color(float red, float green, float blue, float alpha) {
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}
};
enum materialType { JUMA_MATTEXTURE, JUMA_MATCOLOR };