#pragma once
#include <precompiled.h>
#include <time_slot.h>

class Course
{
public:
	Course(const std::string& courseName, const std::vector<TimeSlot> preferredTimeSlots = {});

	Course() = default;
public:

	Course &operator=(const Course& other);

	Course(const Course& other);

	void displayInfo() const;

	const std::vector<TimeSlot>& GetPrefferedTimeSlots() const;

	std::string GetName() const;

private:
	void swap(Course& other);
private:
	std::string courseName_;
	std::vector<TimeSlot> preferredTimeSlots_;
};