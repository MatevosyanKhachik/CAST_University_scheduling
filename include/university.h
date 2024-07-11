#pragma once
#include <precompiled.h>
#include <instructor.h>


class University
{
public:
	void AddCourse(const Course& course);
	
	void AddInstructor(Instructor instructor);

	void AddTimeSlot(const TimeSlot& timeSlot);

	void SaveState(const std::string& filename) const;

	void LoadState(const std::string& filename);

	void print() const;

	void build_graph();
private:
	void NormalizeTimeSlots();


	bool FindCourseInInstrCourses(const Instructor& instr, const Course course) const;

	TimeSlot ParseTimeSlot(const std::string& day, const std::string& timeRange);

	bool CanTeach(const TimeSlot& ts, const TimeSlot& timeSlot);

	bool bfs();	

	bool dfs(int u);

	std::vector<int> maxMatching();

private:
	int leftInd = 0;
	int rightInd;
	std::vector<Course> courses;
	std::vector<Instructor> instructors;
	std::vector<TimeSlot> timeSlots;
	std::vector<TimeSlot> NormalizedTimeSlots;
	std::vector<int> dist;
    std::vector<int> match;
	std::unordered_map<int, std::vector<int>> graph;
	std::vector<std::tuple<TimeSlot, Course, Instructor>> schedule;
};