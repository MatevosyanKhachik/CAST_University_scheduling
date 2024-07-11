#include <precompiled.h>
#include <university.h>


int main()
{	
	//std::vector<TimeSlot> courseTS1 = {TimeSlot("June 24", "14:00", "16:00"),
	//TimeSlot("June 26", "14:00", "16:00"), TimeSlot("June 28", "14:00", "16:00") };

	//std::vector<TimeSlot> courseTS2 = { TimeSlot("June 25", "10:00", "12:00"),
	//TimeSlot("June 27", "10:00", "12:00"), TimeSlot("June 29", "12:00", "14:00") };

	//std::vector<TimeSlot> courseTS3 = { TimeSlot("June 26", "19:00", "22:00"),//24-8
	//TimeSlot("June 30", "12:00", "16:00") };

	//std::vector<TimeSlot> courseTS4 = { TimeSlot("June 25", "19:00", "22:00"),//24-8
	//TimeSlot("June 29", "12:00", "16:00"), TimeSlot("July 2", "19:00", "22:00"),
	//TimeSlot("July 6", "12:00", "16:00") };

	//std::vector<TimeSlot> courseTS5 = { TimeSlot("June 24", "13:00", "15:00"),//24-8
	//TimeSlot("June 27", "13:00", "15:00"), TimeSlot("June 30", "15:00", "18:00"),
	//TimeSlot("July 3", "13:00", "15:00") };
	//
	//std::vector<TimeSlot> courseTS6 = { TimeSlot("June 25", "11:00", "13:00"),//24-8
	//TimeSlot("June 27", "11:00", "13:00"), TimeSlot("July 1", "15:00", "17:00"),
	//TimeSlot("July 3", "15:00", "17:00"), TimeSlot("July 5", "15:00", "17:00") };
	//
	//std::vector<TimeSlot> courseTS7 = { TimeSlot("June 24", "16:00", "18:00"),//24-8
	//TimeSlot("June 26", "16:00", "18:00"), TimeSlot("July 28", "16:00", "18:00"),
	//TimeSlot("July 2", "17:00", "19:00"), TimeSlot("July 4", "17:00", "19:00"),
	//TimeSlot("July 6", "17:00", "19:00") };



	//Course course1("Algebra", courseTS1);
	//Course course2("Physics", courseTS2);
	//Course course3("Statistics", courseTS3);
	//Course course4 ("Banking", courseTS4);
	//Course course5 ("Data Structures And Algorithms", courseTS5);
	//Course course6 ("Math Analysis", courseTS6);
	//Course course7 ("Programming with C++", courseTS6);

	//std::vector<Course> courseSet1 = { course1, course3, course7 };
	//std::vector<Course> courseSet2 = { course4, course5, course7 };
	//std::vector<Course> courseSet3 = { course2, course3, course6 };

	//std::vector<TimeSlot> instrTS1 = { TimeSlot("June 25", "10:00", "12:00"),
	//TimeSlot("June 27", "10:00", "12:00"), TimeSlot("June 29", "12:00", "14:00") };

	//std::vector<TimeSlot> instrTS2 = { TimeSlot("June 25", "11:00", "13:00"),//24-8
	//TimeSlot("June 27", "11:00", "13:00"), TimeSlot("July 1", "15:00", "17:00"),
	//TimeSlot("July 3", "15:00", "17:00"), TimeSlot("July 5", "15:00", "17:00") };

	//std::vector<TimeSlot> instrTS3 = { TimeSlot("June 25", "19:00", "22:00"),//24-8
	//TimeSlot("June 29", "12:00", "16:00"), TimeSlot("July 2", "19:00", "22:00"),
	//TimeSlot("July 6", "12:00", "16:00") };

	//Instructor instr1("Gagoy",instrTS1, courseSet1);
	//Instructor instr2("Vahe Ghazaryan", instrTS2, courseSet2);
	//Instructor instr3("Thach Mard", instrTS3, courseSet3);

	University unik;
	//unik.AddCourse(course1);
	//unik.AddCourse(course2);
	//unik.AddCourse(course3);
	//unik.AddCourse(course4);
	//unik.AddCourse(course5);
	//unik.AddCourse(course6);
	//unik.AddCourse(course7);

	//unik.AddInstructor(instr1);
	//unik.AddInstructor(instr2);
	//unik.AddInstructor(instr3);

	//unik.AddTimeSlot (TimeSlot("June 27", "11:00", "13:00"));
	//unik.AddTimeSlot(TimeSlot("July 2", "19:00", "22:00"));
	//unik.AddTimeSlot(TimeSlot("July 6", "12:00", "16:00"));
	//unik.AddTimeSlot(TimeSlot("June 24", "16:00", "18:00"));
	//unik.AddTimeSlot(TimeSlot("June 29", "12:00", "14:00"));

	unik.LoadState("D:\\Documents\\Cast_assignment\\a.txt");
	//unik.SaveState("D:\\Documents\\Cast_assignment\\b.txt");

	unik.build_graph();


	//unik.print();

}

