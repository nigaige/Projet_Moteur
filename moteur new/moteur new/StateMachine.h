#pragma once
#include "Utils.h"


class StateMachine : public Component

{

	protected :
		BaseStates* currentState_;
		BaseStates* lastState_;

		BaseStates* globalState_;

		std::map<int, BaseStates* > statesMap;



	public :
	
		StateMachine();
			
		//GETTER / SETTER
		BaseStates* currentState() { return currentState_; }
		BaseStates* lastState() { return lastState_; }
		BaseStates* globalState() { return globalState_; }


		void globalState(BaseStates* newGlobal) { globalState_ = newGlobal; }


		
		void SetStates(int SizeEnum, BaseStates* listState[]);
		void ChangeState(int StateId);


		void Update();

		



		~StateMachine();
		

};

