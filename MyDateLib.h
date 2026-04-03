#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ==========================================
// 1. Structures & Enums
// ==========================================
struct stDate {
    short Year;
    short Month;
    short Day;
};

enum enCompare { Equal = 0, Before = -1, After = 1 };

struct stPeriod {
    stDate StartDate;
    stDate EndDate;
};

// ==========================================
// 2. User Input Functions
// ==========================================
short ReadYear();
short ReadMonth();
short ReadDay();
stDate ReadFullDate();
stPeriod ReadFullPeriod();

// ==========================================
// 3. Core Date Validation & Basic Operations
// ==========================================
bool IsLeapYear(short Year);
short NumberDaysInMonth(short Month, short Year);
bool IsDate1EqualDate2(stDate Date1, stDate Date2);
bool IsDate1BeforeDate2(stDate Date1, stDate Date2);
bool IsDate1AfterDate2(stDate Date1, stDate Date2);
enCompare CompareDates(stDate Date1, stDate Date2);
bool IsOverLap(stPeriod Period1, stPeriod Period2);
bool IsLastDayInMonth(stDate Date);
bool IsLastMonthInYear(stDate Date);
void SwapDates(stDate& Date1, stDate& Date2);
short GetDifferenceInDays(stDate Date1, stDate Date2, bool IncludeEndDay = false);
short CalculatePeriodLengthDays(stPeriod Period, bool IncludeEndDay = false);
bool IsDateWithinInPeriod(stPeriod Period, stDate Date);
short CountOverlapDays(stPeriod Period1, stPeriod Period2);
bool IsDateValidate(stDate Date);
string ReadDateAsText();
vector<string> SplitString(string Text, string Delim);
stDate StringToDate(string Date);
string DateToString(stDate Date);

// ==========================================
// 4. System Date & Day Of Week Calculations
// ==========================================
stDate GetDateFromSystem();
short OrderDayInWeek(stDate Date);
string NameDays(short Day);
bool IsEndOfWeek(stDate Date);
bool IsWeekEnd(stDate Date);
bool IsBusinessDay(stDate Date);
short DaysUntilTheEndOfWeek(stDate Date);
short DaysUntilTheEndOfMonth(stDate Date);
short NumberDayInYear(stDate Date);
short DaysUntilTheEndOfYear(stDate Date);

// ==========================================
// 5. Date Addition (Incrementing)
// ==========================================
stDate IncreaseDateByOneDay(stDate Date);
stDate IncreaseDateByXDays(stDate Date, short Days);
stDate IncreaseDateByOneWeek(stDate Date);
stDate IncreaseDateByXWeek(stDate Date, short Weeks);
stDate IncreaseDateByOneMonth(stDate Date);
stDate IncreaseDateByXMonth(stDate Date, short Months);
stDate IncreasDateByOneYear(stDate Date);
stDate IncreseDateByXYears(stDate Date, short Years);
stDate IncreseDateByXYearsFaster(stDate Date, short Years);
stDate IncreaseDateByOneDecade(stDate Date);
stDate IncreaseDateByXDecades(stDate Date, short Decades);
stDate IncreaseDateByXDecadesFaster(stDate Date, short Decades);
stDate IncreaseDateByOneCentury(stDate Date);
stDate IncreaseDateByOneMillenium(stDate Date);

// ==========================================
// 6. Date Subtraction (Decrementing)
// ==========================================
stDate DecreaseDateByOneDay(stDate Date);
stDate DecreaseDateByXDays(stDate Date, short Days);
stDate DecreaseDateByOneWeek(stDate Date);
stDate DecreaseDateByXWeeks(stDate Date, short Weeks);
stDate DecreaseDateByOneMonth(stDate Date);
stDate DecreaseDateByXMonths(stDate Date, short Months);
stDate DecreaseDateByOneYear(stDate Date);
stDate DecreaseDateByXYears(stDate Date, short Years);
stDate DecreaseDateByXYearsFaster(stDate Date, short Years);
stDate DecreaseDateByOneDecade(stDate Date);
stDate DecreaseDateByXDecades(stDate Date, short Decades);
stDate DecreaseDateByXDecadesFaster(stDate Date, short Decades);
stDate DecreaseDateByOneCentury(stDate Date);
stDate DecreaseDateByOneMillenium(stDate Date);

// ==========================================
// 7. Business Logic (Vacations & Workdays)
// ==========================================
short ActualVacationDays(stDate VacationStart, stDate VacationEnd);
stDate CalculateTheVacationReturnDate(stDate StartVacation, short Days);