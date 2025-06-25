#include <iostream>

enum TDays
{
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

enum TMonths
{
    January = 1,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December
};

void myFunction(TDays &day)
{
    switch (day)
    {
        case Sunday:
            std::cout << "It's a relaxing day!" << std::endl;
            break;
        case Monday:
            std::cout << "Back to work!" << std::endl;
            break;
        case Tuesday:
            std::cout << "Keep going!" << std::endl;
            break;
        case Wednesday:
            std::cout << "Halfway through the week!" << std::endl;
            break;
        case Thursday:
            std::cout << "Almost there!" << std::endl;
            break;
        case Friday:
            std::cout << "Weekend is near!" << std::endl;
            break;
        case Saturday:
            std::cout << "Enjoy your weekend!" << std::endl;
            break;
	}

	//day = Monday; // Changing the day to Monday after processing
}

int main()
{
    TDays day;
	TMonths month;

    day = Sunday;
    month = TMonths(1);

	myFunction(day);
	std::cout << "Current day is now: " << day << std::endl;
    
}

