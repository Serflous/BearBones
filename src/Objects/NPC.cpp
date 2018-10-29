#include "NPC.h"

void NPC::Walking()
{
}

void NPC::Halt()
{
}

void NPC::ST_Idle(EventData* pData)
{
	std::cout << "Motor::ST_Idle" << std::endl;
}

// stop the motor 
void NPC::ST_Stop(EventData* pData)
{
	std::cout << "Motor::ST_Stop" << std::endl;
	

	// perform the stop processing here
	InternalEvent(ST_IDLE);
}

// start the motor going
void NPC::ST_Start(NPCData* pData)
{
	std::cout << "Motor::ST_Start" << std::endl;
	// set initial motor speed processing here
}
