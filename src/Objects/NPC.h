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

	/**
	 * An automated NPC.
	 * @author Mason Tolman
	 * @version 0.1
	 */
class NPC : public StateMachine 
{
public:
	NPC() : StateMachine(ST_MAX_STATES) {}
	
		/**
		 * Tells the NPC to move.
		 */
	void Walking();
		/**
		 * Tells the NPC to stop.
		 */
	void Halt();
private:

		/**
		 * Creates an event that indicates the NPC is idle.
		 * @param[out] pData Pointer to the event data.
		 */
	void ST_Idle(EventData*);
		/**
		 * Creates an event that indicates the NPC has stopped acting.
		 * @param[out] pData Pointer to the event data.
		 */
	void ST_Stop(EventData*);
		/**
		 * Creates an event that indicates the NPC has started acting.
		 * @param[out] pData Pointer to the NPC data.
		 */
	void ST_Start(NPCData*);
		/**
		 * Creates an event that indicates the NPC has collided with something.
		 * @param[out] pData Pointer to the NPC data.
		 */
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

