#include "Utils.h"


StateMachine::StateMachine(BaseStates* current, BaseStates* last, BaseStates* global, std::map<int, BaseStates*> map)
{
	currentState_	= current;
	lastState_		= last;
	globalState_	= global;
	statesMap		= map;
}

int StateMachine::currentStateKey()
{
	return Utils::GetKeyViaValue(statesMap, currentState_);
}
int StateMachine::lastStateKey() 
{ 
	return Utils::GetKeyViaValue(statesMap, lastState_); 
}
int StateMachine::globalStateKey()
{
	return Utils::GetKeyViaValue(statesMap, globalState_);
} 

void StateMachine::setStates(int SizeEnum, std::vector<BaseStates*> listState,int FirstState)
{
	if (SizeEnum+1 != listState.size())
		return;
	
	for (int i = 0; i <= SizeEnum; i++)
		statesMap.insert(std::pair<int, BaseStates*>(i, listState[i]));
	currentState_ = listState[FirstState];
}

void StateMachine::nextState()
{
	if (currentState_ != nullptr)
	{
		lastState_ = currentState_;
		auto Key = Utils::GetKeyViaValue(statesMap, lastState_);
		currentState_ = statesMap.find(Key + 1)->second;
	}
	else
		Utils::DebugLogMessage("CurrentState NULL");
		return;
}

void StateMachine::changeState(int StateId)
{
	if (currentState_ != nullptr)
	{
		lastState_ = currentState_;
		if (StateId != Utils::GetKeyViaValue(statesMap, currentState_))
			currentState_ = statesMap.find(StateId)->second;
		lastState_->Exit();
		currentState_->Enter();
	}
	else
		Utils::DebugLogMessage("CurrentState NULL");
		return;
}


void StateMachine::update()
{
	if (globalState_ != nullptr) 
		globalState_->Update();
	
	if (currentState_ != nullptr) 
		currentState_->Update();
	
}

StateMachine::~StateMachine()
{
}
