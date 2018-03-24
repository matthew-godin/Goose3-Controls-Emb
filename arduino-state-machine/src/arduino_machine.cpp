#define ASSERT_TRUE(A)
//#include <gtest/gtest.h>
#include <wlib/fsm/StateMachine.h>
#include <wlib/stl/ArrayList.h>

using namespace wlp;

class ArduinoMachine : public StateMachine
{
	public:

	ArduinoMachine() : StateMachine(States::ST_MAX_STATES, States::ST_IDLE){ }
	
	ArrayList<int> state_trace{25};

	void onSignal()
	{
		BEGIN_TRANSITION_MAP
			TRANSITION_MAP_ENTRY(ST_ACTIVE) //ST_IDLE
			TRANSITION_MAP_ENTRY(ST_ACTIVE) //ST_ACTIVE
			TRANSITION_MAP_ENTRY(EVENT_IGNORED) //ST_ERROR
			TRANSITION_MAP_ENTRY(EVENT_IGNORED) //ST_RECOVERY
		END_TRANSITION_MAP(nullptr, NoEventData)
	}

	void offSignal()
	{
		BEGIN_TRANSITION_MAP
			TRANSITION_MAP_ENTRY(ST_IDLE) //ST_IDLE
			TRANSITION_MAP_ENTRY(ST_IDLE) //ST_ACTIVE
			TRANSITION_MAP_ENTRY(EVENT_IGNORED) //ST_ERROR
			TRANSITION_MAP_ENTRY(EVENT_IGNORED) //ST_RECOVERY
		END_TRANSITION_MAP(nullptr, NoEventData)
	}

	void heartBeatNotHeard()
	{
		BEGIN_TRANSITION_MAP
			TRANSITION_MAP_ENTRY(ST_IDLE) //ST_IDLE
			TRANSITION_MAP_ENTRY(ST_ERROR) //ST_ACTIVE
			TRANSITION_MAP_ENTRY(ST_ERROR) //ST_ERROR
			TRANSITION_MAP_ENTRY(ST_ERROR) //ST_RECOVERY
		END_TRANSITION_MAP(nullptr, NoEventData)
	}

	void heartBeatHeardRecovery()
	{
		BEGIN_TRANSITION_MAP
			TRANSITION_MAP_ENTRY(EVENT_IGNORED) //ST_IDLE
			TRANSITION_MAP_ENTRY(EVENT_IGNORED) //ST_ACTIVE
			TRANSITION_MAP_ENTRY(ST_RECOVERY) //ST_ERROR
			TRANSITION_MAP_ENTRY(ST_RECOVERY) //ST_RECOVERY
		END_TRANSITION_MAP(nullptr, NoEventData)
	}

	void recoveryDoneActive()
	{
		BEGIN_TRANSITION_MAP
			TRANSITION_MAP_ENTRY(EVENT_IGNORED) //ST_IDLE
			TRANSITION_MAP_ENTRY(EVENT_IGNORED) //ST_ACTIVE
			TRANSITION_MAP_ENTRY(EVENT_IGNORED) //ST_ERROR
			TRANSITION_MAP_ENTRY(ST_ACTIVE) //ST_RECOVERY
		END_TRANSITION_MAP(nullptr, NoEventData)
	}

	enum States
	{
		ST_IDLE,
		ST_ACTIVE,
		ST_ERROR,
		ST_RECOVERY,
		ST_MAX_STATES
	};

	private:

	STATE_DECLARE(ArduinoMachine, Idle)
	STATE_DECLARE(ArduinoMachine, Active)
	STATE_DECLARE(ArduinoMachine, InError)
	STATE_DECLARE(ArduinoMachine, Recovery)

	BEGIN_STATE_MAP
		STATE_MAP_ENTRY(&Idle)
		STATE_MAP_ENTRY(&Active)
		STATE_MAP_ENTRY(&InError)
		STATE_MAP_ENTRY(&Recovery)
	END_STATE_MAP
};

STATE_DEFINE(ArduinoMachine, Idle)
{
	state_trace.push_back((int) ST_IDLE);
}

STATE_DEFINE(ArduinoMachine, Active)
{
	state_trace.push_back((int) ST_ACTIVE);
}

STATE_DEFINE(ArduinoMachine, InError)
{
	state_trace.push_back((int) ST_ERROR);
}

STATE_DEFINE(ArduinoMachine, Recovery)
{
	state_trace.push_back((int) ST_RECOVERY);
}

/*TEST(fsm_test, test_machine_transitions) {
    
}*/
