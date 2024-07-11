#include <tools.h>


std::string ConvertToTimeString(double time)
{

    int hours = static_cast<int>(time);
    int minutes = static_cast<int>((time - hours) * 60);

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours << ":"
        << std::setw(2) << std::setfill('0') << minutes;

    return oss.str();
}

float ConvertTimeStringToFloat(const std::string& time)
{
    std::stringstream ss(time);
    std::string hours;
    std::string minutes; //half an hour

    std::getline(ss, hours, ':');
    std::getline(ss, minutes);

    float time_f = std::stoi(hours);//9:30
    if(minutes == "30")
    {
        time_f += 0.5;
    }
    
    return time_f;
}

float MatchWithCourseEndTime(float end)
{
    if(daily_schedule[daily_schedule.size() - 1] <= end)
    {
        end = daily_schedule[daily_schedule.size() - 1];
        return end;
    }
    else
    {
        for(int i = 0;i < daily_schedule.size(); ++i)
        {
            if(daily_schedule[i] > end)
            {
                end = daily_schedule[i - 1];//skizby u verjy berel daseri jamerin hamapatasxan
                return end;
            }
            if(daily_schedule[i] > end)
            {
                end = daily_schedule[i];
                return end;
            }
        }
    }
}

float MatchWithCourseStartTime(float start)
{
    for(const auto& time: daily_schedule)
    {
        if(time >= start)
        {
            start = time;
            return time;
        }
    }
}