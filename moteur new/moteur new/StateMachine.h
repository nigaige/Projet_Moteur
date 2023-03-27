#pragma once
#include "Utils.h"


class StateMachine : public Component

{

	protected :
		States* currentState_;
		States* lastState_;

		States* globalState_;

		std::map<int, States* > statesMap;



	public :
	
		StateMachine();
			
		//GETTER / SETTER
		States* currentState() { return currentState_; }
		States* lastState() { return lastState_; }
		States* globalState() { return globalState_; }


		void globalState(States* newGlobal) { globalState_ = newGlobal; }


		
		void SetStates(int SizeEnum, States* listState[]);
		void ChangeState(int StateId);


		void Update();

		



		~StateMachine();
		

};

