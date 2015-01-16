#pragma once
#include "Decl.h"

// Similar to player, see player for anything that overlaps
class Bullet : public Entity
{
	int m_direction;	

public:
	Bullet(GameState *a_gs, unsigned a_sprite,
		   float a_x, float a_y, int a_w, int a_h,
		   float a_speed, int direction);

	void Update(float a_dt);
	void Draw();
	void onCollide();
	bool IsActive();
};