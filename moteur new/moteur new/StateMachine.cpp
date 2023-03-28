#include "StateMachine.h"

StateMachine::StateMachine()
{
}

void StateMachine::Update()
{

	globalState_->Update();

	currentState_->Update();
}

void StateMachine::SetStates(int SizeEnum, BaseStates* listState[])
{
	if (SizeEnum+1 != sizeof(listState) / sizeof(States*))
		return;
	
	for (int i = 0; i < SizeEnum; i++)
		statesMap.insert(std::pair<int, BaseStates*>(i, listState[i]));
}

void StateMachine::ChangeState(int StateId)
{
	//std::map<int, States*>::iterator it;
	lastState_ = currentState_;

	currentState_ = statesMap.find(StateId)->second;

	lastState_->Exit();

	currentState_->Enter();

}

StateMachine::~StateMachine()
{
}
