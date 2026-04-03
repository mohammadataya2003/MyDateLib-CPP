#define _CRT_SECURE_NO_WARNINGS
#include "MyDateLib.h"
#include <vector>
#include <ctime>

// ==========================================
// 2. User Input Functions
// ==========================================

short ReadYear() {
    short Number = 0;
    cout << "Please Enter A Year: ";
    cin >> Number;
    return Number;
}

short ReadMonth() {
    short Month = 0;
    do {
        cout << "Please Enter A Month: ";
        cin >> Month;
    } while (Month < 1 || Month > 12);
    return Month;
}

short ReadDay() {
    short Day = 0;
    do {
        cout << "Please Enter A Day: ";
        cin >> Day;
    } while (Day < 1 || Day > 31);
    return Day;
}

stDate ReadFullDate() {
    stDate Date;
    Date.Day = ReadDay();
    Date.Month = ReadMonth();
    Date.Year = ReadYear();
    cout << endl;
    return Date;
}

stPeriod ReadFullPeriod()
{
    stPeriod Period;
    cout << "Enter Start Date \n\n";
    Period.StartDate = ReadFullDate();
    cout << "Enter End Date \n\n";
    Period.EndDate = ReadFullDate();
    return Period;
}

// ==========================================
// 3. Core Date Validation & Basic Operations
// ==========================================

bool IsLeapYear(short Year) {
    return ((Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0));
}

short NumberDaysInMonth(short Month, short Year) {
    static short NumberDaysOfMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    return Month == 2 ? (IsLeapYear(Year) ? 29 : 28) : NumberDaysOfMonth[Month - 1];
}

bool IsDate1EqualDate2(stDate Date1, stDate Date2) {
    return (Date1.Year == Date2.Year) && (Date1.Month == Date2.Month) && (Date1.Day == Date2.Day);
}

bool IsDate1BeforeDate2(stDate Date1, stDate Date2) {
    return (Date1.Year < Date2.Year) ? true : (Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month) ? true : (Date1.Month == Date2.Month) ? (Date1.Day < Date2.Day) ? true : false : false : false;
}

bool IsDate1AfterDate2(stDate Date1, stDate Date2) {
    return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
}

enCompare CompareDates(stDate Date1, stDate Date2) {
    return (IsDate1EqualDate2(Date1, Date2) ? enCompare::Equal : IsDate1BeforeDate2(Date1, Date2) ? enCompare::Before : enCompare::After);
}

bool IsOverLap(stPeriod Period1, stPeriod Period2) {
    return CompareDates(Period1.EndDate, Period2.StartDate) == enCompare::After
        && CompareDates(Period1.StartDate, Period2.EndDate) == enCompare::Before;
}

bool IsLastDayInMonth(stDate Date) {
    return Date.Day == NumberDaysInMonth(Date.Month, Date.Year);
}

bool IsLastMonthInYear(stDate Date) {
    return Date.Month == 12;
}

void SwapDates(stDate& Date1, stDate& Date2) {
    stDate TempDate = Date1;
    Date1 = Date2;
    Date2 = TempDate;
}

short GetDifferenceInDays(stDate Date1, stDate Date2, bool IncludeEndDay) {
    short Days = 0;
    short SwapFlagValue = 1;

    if (!IsDate1BeforeDate2(Date1, Date2)) {
        SwapDates(Date1, Date2);
        SwapFlagValue = -1;
    }

    while (IsDate1BeforeDate2(Date1, Date2)) {
        Days++;
        Date1 = IncreaseDateByOneDay(Date1);
    }

    return IncludeEndDay ? ++Days * SwapFlagValue : Days * SwapFlagValue;
}

short CalculatePeriodLengthDays(stPeriod Period, bool IncludeEndDay) {
    return GetDifferenceInDays(Period.StartDate, Period.EndDate, IncludeEndDay);
}

bool IsDateWithinInPeriod(stPeriod Period, stDate Date) {
    return (IsDate1BeforeDate2(Date, Period.EndDate) && IsDate1AfterDate2(Date, Period.StartDate)) || IsDate1EqualDate2(Date, Period.StartDate) || IsDate1EqualDate2(Date, Period.EndDate);
}

short CountOverlapDays(stPeriod Period1, stPeriod Period2) {
    if (!IsOverLap(Period1, Period2))
        return 0;

    stDate StartOverlap;
    if (IsDate1BeforeDate2(Period1.StartDate, Period2.StartDate))
        StartOverlap = Period2.StartDate;
    else
        StartOverlap = Period1.StartDate;

    stDate EndOverlap;
    if (IsDate1BeforeDate2(Period1.EndDate, Period2.EndDate))
        EndOverlap = Period1.EndDate;
    else
        EndOverlap = Period2.EndDate;

    return GetDifferenceInDays(StartOverlap, EndOverlap);
}

bool IsDateValidate(stDate Date) {
    return Date.Month <= 12 && Date.Month > 0 ? Date.Day <= NumberDaysInMonth(Date.Month, Date.Year) && Date.Day > 0 : false;
}

string ReadDateAsText() {
    cout << "Please Enter Date dd/mm/yyyy? ";
    string Date;
    getline(cin >> ws, Date);
    return Date;
}

vector<string> SplitString(string Text, string Delim) {
    string Word = "";
    vector <string> veString;
    short pos;
    while ((pos = Text.find(Delim)) != string::npos) {
        Word = Text.substr(0, pos);
        if (Word != "")
            veString.push_back(Word);

        Text = Text.erase(0, pos + Delim.length());
    }
    if (Text != "")
        veString.push_back(Text);

    return veString;
}

stDate StringToDate(string Date) {
    stDate sDate;
    vector <string> veString = SplitString(Date, "/");
    sDate.Day = stoi(veString[0]);
    sDate.Month = stoi(veString[1]);
    sDate.Year = stoi(veString[2]);
    return sDate;
}

string DateToString(stDate Date) {
    return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
}

// ==========================================
// 4. System Date & Day Of Week Calculations
// ==========================================

stDate GetDateFromSystem() {
    stDate Date;
    time_t t = time(0);
    tm* now = localtime(&t);
    Date.Year = now->tm_year + 1900;
    Date.Month = now->tm_mon + 1;
    Date.Day = now->tm_mday;
    return Date;
}

short OrderDayInWeek(stDate Date) {
    short a = (14 - Date.Month) / 12;
    short y = Date.Year - a;
    short m = Date.Month + (12 * a) - 2;
    return (Date.Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
}

string NameDays(short Day) {
    string Days[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
    return Days[Day];
}

bool IsEndOfWeek(stDate Date) {
    return OrderDayInWeek(Date) == 6;
}

bool IsWeekEnd(stDate Date) {
    short IndexDay = OrderDayInWeek(Date);
    return IndexDay == 5 || IndexDay == 6;
}

bool IsBusinessDay(stDate Date) {
    return !IsWeekEnd(Date);
}

short DaysUntilTheEndOfWeek(stDate Date) {
    return 6 - OrderDayInWeek(Date);
}

short DaysUntilTheEndOfMonth(stDate Date) {
    return NumberDaysInMonth(Date.Month, Date.Year) - Date.Day;
}

short NumberDayInYear(stDate Date) {
    short Days = Date.Day;
    while (Date.Month > 1) {
        Date.Month--;
        Days += NumberDaysInMonth(Date.Month, Date.Year);
    }
    return Days;
}

short DaysUntilTheEndOfYear(stDate Date) {
    return IsLeapYear(Date.Year) ? 366 - NumberDayInYear(Date) : 365 - NumberDayInYear(Date);
}

// ==========================================
// 5. Date Addition (Incrementing)
// ==========================================

stDate IncreaseDateByOneDay(stDate Date) {
    if (IsLastDayInMonth(Date)) {
        Date.Day = 1;
        if (IsLastMonthInYear(Date)) { Date.Month = 1; Date.Year++; }
        else Date.Month++;
    }
    else Date.Day++;
    return Date;
}

stDate IncreaseDateByXDays(stDate Date, short Days) {
    for (int i = 0; i < Days; i++) Date = IncreaseDateByOneDay(Date);
    return Date;
}

stDate IncreaseDateByOneWeek(stDate Date) { return IncreaseDateByXDays(Date, 7); }
stDate IncreaseDateByXWeek(stDate Date, short Weeks) {
    for (int i = 0; i < Weeks; i++) Date = IncreaseDateByOneWeek(Date);
    return Date;
}

stDate IncreaseDateByOneMonth(stDate Date) {
    if (IsLastMonthInYear(Date)) { Date.Month = 1; Date.Year++; }
    else Date.Month++;
    short MaxDays = NumberDaysInMonth(Date.Month, Date.Year);
    if (Date.Day > MaxDays) Date.Day = MaxDays;
    return Date;
}

stDate IncreaseDateByXMonth(stDate Date, short Months) {
    for (int i = 0; i < Months; i++) Date = IncreaseDateByOneMonth(Date);
    return Date;
}

stDate IncreasDateByOneYear(stDate Date) {
    Date.Year++;
    short MaxDays = NumberDaysInMonth(Date.Month, Date.Year);
    if (Date.Day > MaxDays) Date.Day = MaxDays;
    return Date;
}

stDate IncreseDateByXYears(stDate Date, short Years) {
    for (int i = 0; i < Years; i++) Date = IncreasDateByOneYear(Date);
    return Date;
}

stDate IncreseDateByXYearsFaster(stDate Date, short Years) {
    Date.Year += Years;
    short MaxDays = NumberDaysInMonth(Date.Month, Date.Year);
    if (Date.Day > MaxDays) Date.Day = MaxDays;
    return Date;
}

stDate IncreaseDateByOneDecade(stDate Date) { return IncreseDateByXYearsFaster(Date, 10); }
stDate IncreaseDateByXDecades(stDate Date, short Decades) { return IncreseDateByXYearsFaster(Date, Decades * 10); }
stDate IncreaseDateByXDecadesFaster(stDate Date, short Decades) { return IncreseDateByXYearsFaster(Date, Decades * 10); }
stDate IncreaseDateByOneCentury(stDate Date) { return IncreseDateByXYearsFaster(Date, 100); }
stDate IncreaseDateByOneMillenium(stDate Date) { return IncreseDateByXYearsFaster(Date, 1000); }

// ==========================================
// 6. Date Subtraction (Decrementing)
// ==========================================

stDate DecreaseDateByOneDay(stDate Date) {
    if (Date.Day == 1) {
        if (Date.Month == 1) { Date.Month = 12; Date.Day = 31; Date.Year--; }
        else { Date.Month--; Date.Day = NumberDaysInMonth(Date.Month, Date.Year); }
    }
    else Date.Day--;
    return Date;
}

stDate DecreaseDateByXDays(stDate Date, short Days) {
    for (int i = 0; i < Days; i++) Date = DecreaseDateByOneDay(Date);
    return Date;
}

stDate DecreaseDateByOneWeek(stDate Date) { return DecreaseDateByXDays(Date, 7); }
stDate DecreaseDateByXWeeks(stDate Date, short Weeks) {
    for (int i = 0; i < Weeks; i++) Date = DecreaseDateByOneWeek(Date);
    return Date;
}

stDate DecreaseDateByOneMonth(stDate Date) {
    if (Date.Month == 1) { Date.Month = 12; Date.Year--; }
    else Date.Month--;
    short MaxDays = NumberDaysInMonth(Date.Month, Date.Year);
    if (Date.Day > MaxDays) Date.Day = MaxDays;
    return Date;
}

stDate DecreaseDateByXMonths(stDate Date, short Months) {
    for (int i = 0; i < Months; i++) Date = DecreaseDateByOneMonth(Date);
    return Date;
}

stDate DecreaseDateByOneYear(stDate Date) {
    Date.Year--;
    short MaxDays = NumberDaysInMonth(Date.Month, Date.Year);
    if (Date.Day > MaxDays) Date.Day = MaxDays;
    return Date;
}

stDate DecreaseDateByXYears(stDate Date, short Years) {
    for (int i = 0; i < Years; i++) Date = DecreaseDateByOneYear(Date);
    return Date;
}

stDate DecreaseDateByXYearsFaster(stDate Date, short Years) {
    Date.Year -= Years;
    short MaxDays = NumberDaysInMonth(Date.Month, Date.Year);
    if (Date.Day > MaxDays) Date.Day = MaxDays;
    return Date;
}

stDate DecreaseDateByOneDecade(stDate Date) { return DecreaseDateByXYearsFaster(Date, 10); }
stDate DecreaseDateByXDecades(stDate Date, short Decades) { return DecreaseDateByXYearsFaster(Date, Decades * 10); }
stDate DecreaseDateByXDecadesFaster(stDate Date, short Decades) { return DecreaseDateByXYearsFaster(Date, Decades * 10); }
stDate DecreaseDateByOneCentury(stDate Date) { return DecreaseDateByXYearsFaster(Date, 100); }
stDate DecreaseDateByOneMillenium(stDate Date) { return DecreaseDateByXYearsFaster(Date, 1000); }

// ==========================================
// 7. Business Logic (Vacations & Workdays)
// ==========================================

short ActualVacationDays(stDate VacationStart, stDate VacationEnd) {
    short CounterVacation = 0;
    while (IsDate1BeforeDate2(VacationStart, VacationEnd)) {
        if (IsBusinessDay(VacationStart)) {
            CounterVacation++;
        }
        VacationStart = IncreaseDateByOneDay(VacationStart);
    }
    return CounterVacation;
}

stDate CalculateTheVacationReturnDate(stDate StartVacation, short Days) {
    short VacationDays = 0;
    while (VacationDays < Days) {
        if (IsBusinessDay(StartVacation))
            VacationDays++;
        StartVacation = IncreaseDateByOneDay(StartVacation);
    }
    while (IsWeekEnd(StartVacation)) {
        StartVacation = IncreaseDateByOneDay(StartVacation);
    }
    return StartVacation;
}