#pragma once

struct Projectile
{
	bool alive;
	float x;
	float y;

	void update();
	void draw();
};