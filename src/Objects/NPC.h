#pragma once
#include "AI/StateMachine.h"
#include "Entity.h"
#include <iostream>

struct NPCData : public EventData
{
	float AngerCo;
	float HappyCo;
	float SadCo;
	float AnnoyedCo;
};

class NPC : public StateMachine 
{
public:
	NPC() : StateMachine(ST_MAX_STATES) {}
	
	void Walking();
	void Halt();
private:

	void ST_Idle(EventData*);
	void ST_Stop(EventData*);
	void ST_Start(NPCData*);
	void ST_Collision(NPCData*);

	// state map to define state function order
	BEGIN_STATE_MAP
		STATE_MAP_ENTRY(&NPC::ST_Idle)
		STATE_MAP_ENTRY(&NPC::ST_Stop)
		STATE_MAP_ENTRY(&NPC::ST_Start)
		STATE_MAP_ENTRY(&NPC::ST_Collision)
	END_STATE_MAP

	enum E_States {
		ST_IDLE = 0,
		ST_STOP,
		ST_START,
		ST_COLLISION,
		ST_MAX_STATES
	};
};

