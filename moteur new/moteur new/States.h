#pragma once
class States
{
	protected :

	public:
		States()				{ };
		virtual void Enter()	= 0;
		virtual void Exit()		= 0;
		virtual void Update()	= 0;
		virtual ~States()		{ };
};

