#pragma once
class BaseStates
{
	protected :

	public:
		BaseStates()				{ };
		virtual void Enter()	= 0;
		virtual void Exit()		= 0;
		virtual void Update()	= 0;
		virtual ~BaseStates()		{ };
};

