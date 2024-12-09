#pragma once

#include "../Observer/Subject.h"
#include <vector>
#include <memory>

class EventManager : public ISubject
{
private:
	std::vector<std::shared_ptr<IObserver>> observers;
	EventManager() {}

public:
	static EventManager& getInstance();
	EventManager(const EventManager& other) = delete;
	EventManager& operator=(const EventManager& other) = delete;
	void addObserver(std::shared_ptr<IObserver> ob) override;

	void removeObserver(std::shared_ptr<IObserver> ob) override;

	void notify(std::shared_ptr<Event> event) override;

	void pop_back();
};