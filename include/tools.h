#include <precompiled.h>

const std::vector<float> daily_schedule = {
	9,
	10.5,
	12,
	13.5,
	15,
    16.5
};

std::string ConvertToTimeString(double time);

float ConvertTimeStringToFloat(const std::string& time);

float MatchWithCourseEndTime(float end);

float MatchWithCourseStartTime(float start);