#include <instructor.h>
#include <precompiled.h>

Instructor::Instructor(const std::string& name, std::vector<TimeSlot> availability, std::vector<Course> preferredCourses)
    : name_(name)
    , availability_(availability)
    , preferredCourses_(preferredCourses)
{
	NormalizeTimeSlots();
}

Instructor::Instructor(const Instructor & other)
{
	name_ = other.name_;
	availability_ = other.availability_;
	NormalizedAvailability_ = other.NormalizedAvailability_;
	preferredCourses_ = other.preferredCourses_;
}

void Instructor::displayInfo() const
{
    /*std::cout << "Instructor name: " << name_ << std::endl;
    std::cout << "\nAvailability: " << std::endl;
    
    for (const auto& timeSlot : availability_)
    {
        timeSlot.displayInfo();
        std::cout << std::endl;
    }

    std::cout << "\nPreferred courses: " << std::endl;

    for (const auto& course : preferredCourses_)
    {
        std::cout << course.GetName() << std::endl;
    }*/
	std::cout << " \"" << name_ << "\"";
}

const std::vector<Course>& Instructor::GetPreferredCourses() const
{
    return preferredCourses_;
}

const std::vector<TimeSlot>& Instructor::GetAvailability() const
{
    return availability_;
}

const std::vector<TimeSlot>& Instructor::GetNormalizedAvailability() const
{
    return NormalizedAvailability_;
}

void Instructor::NormalizeTimeSlots()
{
    for(const auto& timeslot: availability_)
    {
        float start = ConvertTimeStringToFloat(timeslot.GetStartTime());//12:30 -> 12.5

        float end = ConvertTimeStringToFloat(timeslot.GetEndTime());

        start = MatchWithCourseStartTime(start);//12.5 -> 12 matching

        end = MatchWithCourseEndTime(end);

        int count = (end - start) / 1.5;        

        for(int i = 0;i < count; ++i)
        {
            NormalizedAvailability_.push_back(TimeSlot(timeslot.GetDay(), ConvertToTimeString(start + i * 1.5),ConvertToTimeString(start + ((1 + i) * 1.5))));
        }
    }
}

std::string Instructor::GetName() const
{
    return name_;
}