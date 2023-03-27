#include "StateMachine.h"

StateMachine::StateMachine()
{
}

void StateMachine::Update()
{

	globalState->Update();

	currentState->Update();
}

void StateMachine::Add(int SizeEnum,States* listState[])
{
	if (SizeEnum+1 != sizeof(listState) / sizeof(States*))
		return;
	
	for (int i = 0; i < SizeEnum; i++)
		statesMap.insert(std::pair<int, States*>(i, listState[i]));
}

void StateMachine::ChangeState(int StateId)
{
	//std::map<int, States*>::iterator it;
	lastState = currentState;

	currentState = statesMap.find(StateId)->second;

	lastState->Exit();

	currentState->Enter();

}

StateMachine::~StateMachine()
{
}
