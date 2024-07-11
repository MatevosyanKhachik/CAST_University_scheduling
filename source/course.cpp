#include <course.h>

Course::Course(const std::string& courseName, const std::vector<TimeSlot> preferredTimeSlots)
    : courseName_(courseName)
    , preferredTimeSlots_(preferredTimeSlots)
{}

Course& Course::operator=(const Course & other)
{
	Course cs(other);
	swap(cs);
	return *this;
}

Course::Course(const Course & other)
{
	courseName_ = other.courseName_;
	preferredTimeSlots_ = other.preferredTimeSlots_;
}

void Course::displayInfo() const
{
    /*std::cout << "Course name: " << courseName_ << std::endl;
    std::cout << "\nPreferred time slots: " << std::endl;*/
	
	std::cout << " \"" << courseName_ << "\" ";

    /*for (const auto& timeSlot : preferredTimeSlots_)
    {
        timeSlot.displayInfo();
        std::cout << std::endl;
    }*/
}

const std::vector<TimeSlot>& Course::GetPrefferedTimeSlots() const
{
    return preferredTimeSlots_;
}

std::string Course::GetName() const
{
    return courseName_;
}

void Course::swap(Course & other)
{
	std::swap(courseName_, other.courseName_); 
	std::swap(preferredTimeSlots_, other.preferredTimeSlots_);
}
