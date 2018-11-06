#ifndef _STATE_MACHINE_H
#define _STATE_MACHINE_H
#include <stdio.h>
#include "Objects/Entity.h"

class EventData
{
public:
	virtual ~EventData() {};
};

struct StateStruct;

/**
 * Base class for state machines.
 * @author Mathew Causby
 * @version 0.1
 */
class StateMachine : public Objects::Entity
{
public:
	StateMachine(unsigned char maxStates);
	virtual ~StateMachine() {}
protected:
	enum { EVENT_IGNORED = 0xFE, CANNOT_HAPPEN };
	unsigned char currentState;

	/**
	 * Generates an external event.
	 * @param[in] newState The new state to transition to.
	 * @param[out] pData Pointer to external event data.
	 */
	void ExternalEvent(unsigned char, EventData* = NULL);

	/**
	 * Generates an internal event.
	 * @param[in] newState The new state to transition to.
	 * @param[out] pData Pointer to internal event data.
	 */
	void InternalEvent(unsigned char, EventData* = NULL);
	virtual const StateStruct* GetStateMap() = 0;
private:
	const unsigned char _maxStates;
	bool _eventGenerated;
	EventData* _pEventData;

	/**
	 * The state engine executes the states within the state machine.
	 */
	void StateEngine(void);
};

typedef void (StateMachine::*StateFunc)(EventData *);
struct StateStruct
{
	StateFunc pStateFunc;
};

#define BEGIN_STATE_MAP \
public:\
const StateStruct* GetStateMap() {\
    static const StateStruct StateMap[] = { 

#define STATE_MAP_ENTRY(stateFunc)\
    { reinterpret_cast<StateFunc>(stateFunc) },

#define END_STATE_MAP \
    }; \
    return &StateMap[0]; }

#define BEGIN_TRANSITION_MAP \
    static const unsigned char TRANSITIONS[] = {\

#define TRANSITION_MAP_ENTRY(entry)\
    entry,

#define END_TRANSITION_MAP(data) \
    0 };\
    ExternalEvent(TRANSITIONS[currentState], data);

#endif //STATE_MACHINE_H