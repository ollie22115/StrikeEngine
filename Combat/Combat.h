#pragma once

#include <vector>

#include "../Core/Time.h"
#include "../Core/Input.h"

#include "Strike.h"
#include "Combatant.h"


class ActionCommand : public TimeWindow {
	//TODO!!!
public:
	inline Strike* getStrike() { return strike; }

	inline void onUpdate(const int32_t& timeStep, const KeyCode& userInput) {
		if (isFinished()) return;
		
		if (!isDirectionalKey(userInput)) return;
		else if (userInput == correctInput) successful = true;
		else { TimeWindow::onUpdate(this->elapsedTime()); }
	}

	inline Combatant& getTarget() { return *target; }
	inline bool isSuccessful() { return successful; }

private:
	KeyCode correctInput;
	Strike* strike;
	Combatant* target;
	bool successful;
};

//controls the logic of the combat
struct Combat {
	//TODO!!!
public:
	enum State {
		IDLE = 0,
		PLAYER_SELECTING_MOVES = 1,
		OPPONENT_SELECTING_MOVES = 2,
		ACTION_COMMAND = 3
	};

	Combat();

	void onUpdate(KeyCode userInput);

	~Combat();

private:
	Combatant player;
	Combatant opponent;

	std::vector<Strike> movePool;
	std::vector<Strike*> moveQueue;

	std::vector<ActionCommand> playerStrikeReel;
	std::vector<ActionCommand> opponentStrikeReel;
};