#pragma once
#include <Utils.h>

class MoveForward : public Component
{
public:	
	void update();
	MoveForward();	
	~MoveForward();	
	void velocity(float velocity) { velocity_ = velocity; };
	float velocity() { return velocity_; };

private: 
	float velocity_ = 0.5f;

};

