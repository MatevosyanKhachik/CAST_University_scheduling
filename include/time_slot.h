#pragma once
#include <precompiled.h>

class TimeSlot
{
public:
	TimeSlot(const std::string& day, const std::string& startTime, const std::string& endTime);

	TimeSlot(const TimeSlot& other);

	TimeSlot() = default;

public:

	bool operator==(const TimeSlot& other) const;

	void displayInfo() const;
	
	std::string GetDay() const;

	std::string GetStartTime() const;

	std::string GetEndTime() const;

private:
	std::string day_;
	std::string startTime_;
	std::string endTime_;
};