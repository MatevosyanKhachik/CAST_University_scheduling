#include <time_slot.h>

TimeSlot::TimeSlot(const std::string& day, const std::string& startTime, const std::string& endTime)
    : day_(day) 
    , startTime_(startTime)
    , endTime_(endTime)
{}

TimeSlot::TimeSlot(const TimeSlot & other)
{
	day_ = other.day_;
	startTime_ = other.startTime_;
	endTime_ = other.endTime_;
}

bool TimeSlot::operator==(const TimeSlot & other) const
{
	if (day_ == other.day_ && startTime_ == other.startTime_ && endTime_ == other.endTime_)
		return true;
	return false;
}

void TimeSlot::displayInfo() const
{
    std::cout << "\"" << day_ << ":"; 
    std::cout << startTime_ << " - ";
    std::cout <<  endTime_ << "\" ";
}

std::string TimeSlot::GetDay() const
{
    return day_;
}

std::string TimeSlot::GetStartTime() const
{
    return startTime_;
}

std::string TimeSlot::GetEndTime() const
{
    return endTime_;
}