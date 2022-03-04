#pragma once
#include <iostream>
#include <string>
#include <set>
#include <time.h>

int getYear() {
	struct tm buf;
	std::time_t t = std::time(nullptr);
	localtime_s(&buf, &t);
	return 1900 + buf.tm_year;
}

class Person {
	std::string first_name;
	std::string last_name;
	std::string personal_id;
	friend ostream& operator<< (ostream& out, const Person& person);
public:
	Person() = delete;
	Person(std::string first, std::string last, std::string id) : first_name{ first }, last_name{ last }, personal_id{ id } {}
	unsigned int age() const;
	bool operator< (const Person& r) const;
};

// Output: last_name firstname, age()
void populate(std::set<Person>& group) {
	group.emplace("Bill", "Gates", "195510284424");
	group.emplace("Mark", "Zukerberg", "198405144361");
	group.emplace("George", "Soros", "193008123152");
	group.emplace("Ursula", "Von der Leyen", "195810084624");
	group.emplace("Jacob", "Wallenberg", "195601133142");
	group.emplace("Carl", "Bildt", "194907154351");
	group.emplace("Bill", "Clinton", "194608192614");
	group.emplace("Barack", "Obama", "196108045426");
	group.emplace("Larry", "Fink", "195211021313");
	group.emplace("David", "Rockefeller Jr", "194107242243");
	group.emplace("Klaus", "Schwab", "193803306654");
	group.emplace("Sven", "Svensson", "195004144253");
	group.emplace("Sven", "Svensson", "197412123214");
	group.emplace("Elsa", "Svensson", "198103044321");
	group.emplace("Frida", "Andersson", "198103041234");
}