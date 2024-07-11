#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\json_parser.hpp>
#include <university.h>

const int INF = std::numeric_limits<int>::max();


void University::AddCourse(const Course& course)
{
    courses.push_back(course);
}

void University::AddInstructor(Instructor instructor)
{
    instructors.push_back(instructor);
}

void University::AddTimeSlot(const TimeSlot& timeSlot)
{
    timeSlots.push_back(timeSlot);
    NormalizeTimeSlots();
} 

void University::SaveState(const std::string& filename) const
{
    boost::property_tree::ptree pt;

    boost::property_tree::ptree coursesTree;

    boost::property_tree::ptree instructorsTree;

    boost::property_tree::ptree timeSlotsTree;
    
    for (const auto& course : courses)
    {
        boost::property_tree::ptree tmpCourse;

        for (const auto& timeSlot : course.GetPrefferedTimeSlots())
        {
            std::string s1 = timeSlot.GetStartTime();
            s1.append(" - ");
            std::string s2 = timeSlot.GetEndTime(); //"Day : 12:00 - 14:00"
            tmpCourse.put(timeSlot.GetDay(), s1 + s2);
        }

        boost::property_tree::ptree CourseEntry;
        CourseEntry.add_child(course.GetName(), tmpCourse);
        coursesTree.push_back(std::make_pair("", CourseEntry));
    }

    for (const auto& instructor : instructors)
    {
        boost::property_tree::ptree tmpInstructor;

        boost::property_tree::ptree tmpInstructorCourses;

        for (const auto& InstrCourse : instructor.GetPreferredCourses())
        {
            boost::property_tree::ptree InstrNode;
            InstrNode.put("", InstrCourse.GetName());
            tmpInstructorCourses.push_back(std::make_pair("", InstrNode));
        }

        boost::property_tree::ptree tmpInstructorTimeSlot;

        for (const auto& instrTS : instructor.GetAvailability())
        {
            std::string s1 = instrTS.GetStartTime();
            s1.append(" - ");
            std::string s2 = instrTS.GetEndTime();
            tmpInstructorTimeSlot.put(instrTS.GetDay(), s1 + s2);
        }

        boost::property_tree::ptree tmpInstructorEntry;
        tmpInstructorEntry.add_child("Time Slots", tmpInstructorTimeSlot);
        tmpInstructorEntry.add_child("Preferred Courses", tmpInstructorCourses);
        tmpInstructor.push_back(std::make_pair("", tmpInstructorEntry));

        boost::property_tree::ptree InstrEntry;
        InstrEntry.add_child(instructor.GetName(), tmpInstructor); 
        instructorsTree.push_back(std::make_pair("", InstrEntry));
    }

    for (const auto& timeSlot : timeSlots)
    {
        std::string s1 = timeSlot.GetStartTime();
        s1.append(" - ");
        std::string s2 = timeSlot.GetEndTime();
        timeSlotsTree.put(timeSlot.GetDay(), s1 + s2);
    }

    pt.add_child("Courses", coursesTree);
    pt.add_child("Instructors", instructorsTree);
    pt.add_child("Time slots", timeSlotsTree);

    std::ofstream file(filename);

    if (file.is_open())
    {
        boost::property_tree::write_json(file, pt);
        file.close();
        std::cout << "JSON data has been written to " << filename << std::endl;
    }
    else
    {
        std::cerr << "Unable to open file for writing" << std::endl;
    }
}

void University::LoadState(const std::string& filename)
{
    courses.clear();
    instructors.clear(); // Reset the current state before loading
    timeSlots.clear();

    boost::property_tree::ptree pt;
    std::ifstream file(filename);

    if (file.is_open())
    {
        boost::property_tree::read_json(file, pt);
        file.close();	
        
        for (const auto& courseArrItem : pt.get_child("Courses"))
        {
            std::vector<TimeSlot> ReadtimeSlots;
            for (const auto& course : courseArrItem.second)
            {
                for (const auto& courseTS : course.second)
                {
                    ReadtimeSlots.push_back(ParseTimeSlot(courseTS.first, courseTS.second.data()));
                }
                courses.push_back(Course(course.first, ReadtimeSlots));
            }
        }

        for (const auto& instructorArrItem : pt.get_child("Instructors"))
        {
            std::vector<TimeSlot> ReadtimeSlots;
            std::vector<Course> ReadCourses;
            for (const auto& instructor : instructorArrItem.second)
            {
                for (const auto& instrArrItem : instructor.second)
                {
                    for (const auto& instDataArr : instrArrItem.second)
                    {
                        if (instDataArr.first == "Time Slots")
                        {
                            for (const auto& instrTS : instDataArr.second)
                            {
                                ReadtimeSlots.push_back(ParseTimeSlot(instrTS.first, instrTS.second.data()));
                            }
                        }
                        else
                        {
                            for (const auto& instrCourse : instDataArr.second)
                            {
                                ReadCourses.push_back(Course(instrCourse.second.data()));
                            }
                        }
                    }
                }
				Instructor tmpInstr(instructor.first, ReadtimeSlots, ReadCourses);
                instructors.push_back(tmpInstr);
            }
        }

        for (const auto& TS : pt.get_child("Time slots"))
        {
            timeSlots.push_back(ParseTimeSlot(TS.first, TS.second.data()));
        }

		NormalizeTimeSlots();

        std::cout << "JSON data has been loaded from input.json\n" << std::endl;

    }
    else
    {
        std::cerr << "Unable to open file for reading" << std::endl;
    }
}

void University::NormalizeTimeSlots()
{
    for(const auto& timeslot: timeSlots)
    {
        float start = ConvertTimeStringToFloat(timeslot.GetStartTime());

        float end = ConvertTimeStringToFloat(timeslot.GetEndTime());

        start = MatchWithCourseStartTime(start);

        end = MatchWithCourseEndTime(end);

        int count = (end - start) / 1.5;        

        for(int i = 0;i < count; ++i)
        {
            NormalizedTimeSlots.push_back(TimeSlot(timeslot.GetDay(), ConvertToTimeString(start + i * 1.5),ConvertToTimeString(start + ((1 + i) * 1.5))));
        }
    }
}

void University::build_graph()
{
   std::unordered_map<int, std::pair<TimeSlot, Course>> coursesMap;

   for(int i = 0;i < courses.size(); ++i)
   {
	   for (const auto& csTimeSlot : courses[i].GetPrefferedTimeSlots())
	   {
			coursesMap[leftInd] = std::make_pair(csTimeSlot, courses[i]);
			graph.insert({ leftInd, {} });
			leftInd++;
	   }
   }

   rightInd = coursesMap.size();
   int firstRightInd = rightInd;

   std::unordered_map<int, std::pair<TimeSlot, Instructor>> instrTimeSlots;

   for(const auto& instructor: instructors)
   {
        for(const auto& timeslot: instructor.GetNormalizedAvailability())
        {
            instrTimeSlots[rightInd] = std::make_pair(timeslot, instructor);
			graph.insert({ rightInd, {} });
            ++rightInd;
        }
   }

   for(const auto& [csIndex, TSCourse]: coursesMap)
   {
       for(const auto& [pairIndex, instrTSPair]: instrTimeSlots)
       {
           if(FindCourseInInstrCourses(instrTSPair.second, TSCourse.second))
           {
               for(const auto& timeslot: TSCourse.second.GetPrefferedTimeSlots())
               {
                   if(CanTeach(timeslot, instrTSPair.first))
                   {
                       graph[csIndex].push_back(pairIndex);
                   }
               }
           }
       }
   }
   dist.resize(rightInd);
   match.resize(rightInd);

   using myTuple = std::tuple<TimeSlot, Course, Instructor>;

   std::vector<int> result = maxMatching();
   for (int i = 0; i <= leftInd; ++i)
   {
	   if (result[i] != 0) 
	   {
		   myTuple tmpRes;

		   std::get<0>(tmpRes) = instrTimeSlots[result[i]].first;
		   std::get<1>(tmpRes) = coursesMap[i].second;
		   std::get<2>(tmpRes) = instrTimeSlots[result[i]].second;

		   schedule.push_back(tmpRes);
	   }
   }
   

   std::sort(schedule.begin(), schedule.end(), 
	   [](const myTuple& left, const myTuple& right) {

			std::string leftDay = std::get<0>(left).GetDay();
			std::string tmp1 = leftDay.substr(leftDay.size() - 2);
			std::string rightDay = std::get<0>(right).GetDay();
			std::string tmp2 = rightDay.substr(rightDay.size() - 2);

			return tmp1 < tmp2;
		});

   for (const myTuple& elem: schedule)
   {
	   std::get<0>(elem).displayInfo();
	   std::get<1>(elem).displayInfo();
	   std::get<2>(elem).displayInfo();
	   std::cout << "\n\n";
   }

}

void University::print() const
{
    for(const auto& [key, value]: graph)
    {
        std::cout << key << " -> ";
        for(const auto& item: value)
        {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
}

bool University::CanTeach(const TimeSlot& ts, const TimeSlot& timeSlot)
{
    return ts == timeSlot;
}


bool University::bfs()
{
	std::queue<int> q;
	for (int u = 1; u <= leftInd; ++u) {
		if (match[u] == 0) {
			dist[u] = 0;
			q.push(u);
		}
		else {
			dist[u] = INF;
		}
	}
	dist[0] = INF;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		if (dist[u] < dist[0]) {
			for (int v : graph[u]) {
				if (dist[match[v]] == INF) {
					dist[match[v]] = dist[u] + 1;
					q.push(match[v]);
				}
			}
		}
	}
	return dist[0] != INF;
}

 bool University::dfs(int u)
{
	 if (u != 0) 
	 {
		 for (int v : graph[u])
		 {
			 if (dist[match[v]] == dist[u] + 1 && dfs(match[v])) {
				 match[v] = u;
				 match[u] = v;
				 return true;
			 }
		 }
		 dist[u] = INF;
		 return false;
	 }
	 return true;
}

 std::vector<int> University::maxMatching()
 {
	 int matching = 0;
	 while (bfs()) {
		 for (int u = 1; u <= leftInd; ++u) {
			 if (match[u] == 0 && dfs(u)) {
				 ++matching;
			 }
		 }
	 }
	return match;
}

bool University::FindCourseInInstrCourses(const Instructor& instr, const Course course) const
{
    for(const auto& InstrCourse: instr.GetPreferredCourses())
    {
        if(InstrCourse.GetName() == course.GetName())
            return true;
    }
    return false;
}

TimeSlot University::ParseTimeSlot(const std::string& day, const std::string& timeRange)
{
    std::string startTime;
    std::string endTime;

    std::stringstream ss(timeRange);
    std::getline(ss, startTime, '-');
    std::getline(ss, endTime);

    startTime.erase(startTime.begin() + startTime.size() - 1);
    endTime.erase(endTime.begin());

    TimeSlot ts(day, startTime, endTime);

    return ts;
}