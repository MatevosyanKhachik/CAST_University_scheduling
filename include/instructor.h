#pragma once
#include <precompiled.h>
#include <tools.h>
#include <course.h>

class Instructor
{
public:
	Instructor(const std::string& name, std::vector<TimeSlot> availability, std::vector<Course> preferredCourses);

	Instructor(const Instructor& other);

	Instructor() = default;

public:
	void displayInfo() const;

	const std::vector<Course>& GetPreferredCourses() const;

	const std::vector<TimeSlot>& GetAvailability() const;

	const std::vector<TimeSlot>& GetNormalizedAvailability() const;

	std::string GetName() const;

private:
	void NormalizeTimeSlots();

private:
	std::string name_;
	std::vector<TimeSlot> availability_;
	std::vector<TimeSlot> NormalizedAvailability_;
	std::vector<Course> preferredCourses_;
};