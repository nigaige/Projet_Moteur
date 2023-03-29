#pragma once



class StateMachine : public Component

{

	protected :
		BaseStates* currentState_ = nullptr;
		BaseStates* lastState_ = nullptr;
		BaseStates* globalState_= nullptr;



		std::map<int, BaseStates* > statesMap;



	public :
	
		
		StateMachine(BaseStates* current = NULL, BaseStates* last = NULL, BaseStates* global = NULL,std::map<int, BaseStates* > map=std::map<int, BaseStates* >());
			
		//GETTER / SETTER
		BaseStates* currentState() { return currentState_; }
		BaseStates* lastState() { return lastState_; }
		BaseStates* globalState() { return globalState_; }
		
		int currentStateKey();
		int lastStateKey();
		int globalStateKey();

		void globalState(BaseStates* newGlobal) { globalState_ = newGlobal; }
		void setStates(int SizeEnum, std::vector<BaseStates*> listState,int FirstState =0);
		//
		void nextState();

		void changeState(int StateId);
		void update();

		



		~StateMachine();
		

};

