#pragma once
#include <cstdint>

class Event {
public:
	enum EventType {
		None = 0, KeyEvent, MouseClickEvent
	};

	Event(const EventType& type) : type(type) {}

	inline EventType getType() { return type; };

private:
	EventType type;
};

class KeyEvent : public Event {
public:
	enum Action {
		None = 0, Pressed, Released
	};

	KeyEvent(const uint32_t& keyCode, const Action& action) : 
		Event(EventType::KeyEvent), keyCode(keyCode), action(action) {}

	inline uint32_t getKeyCode() const { return keyCode; }
	inline Action getAction() const { return action; }

private:
	uint32_t keyCode;
	Action action;
};

class MouseClickEvent : public Event {
public:
	enum Action {
		None = 0, Pressed, Released
	};

	MouseClickEvent(const float& xPos, const float& yPos, const Action& action) :
		Event(EventType::MouseClickEvent), action(action), xPos(xPos), yPos(yPos) {}

private:
	Action action;
	float xPos;
	float yPos;
};