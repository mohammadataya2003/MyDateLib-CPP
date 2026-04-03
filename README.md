# MyDateLib 📅

A robust, comprehensive C++ Date and Time library built entirely from scratch without relying on external date/time frameworks. 

## 🚀 Key Features
* **Date Validation:** Strict validation covering leap years, edge cases, and formatting.
* **Period Overlaps:** Mathematical $O(1)$ time complexity logic to calculate exact overlap days between multiple periods.
* **Business Logic:** Calculate business days, actual vacation lengths, and exclude weekends.
* **Serialization & Deserialization:** Seamlessly convert string formats (e.g., `dd/mm/yyyy`) to `stDate` structures and vice versa with dynamic formatting.
* **Date Math:** Increment and decrement dates by days, weeks, months, years, decades, centuries, and millenniums.

## 🛠️ Usage Example

```cpp
#include <iostream>
#include "MyDateLib.h"

int main() {
    // String to Date Conversion
    string textDate = "15/05/2026";
    stDate myDate = StringToDate(textDate);
        
    // Period Overlap Calculation
    stPeriod P1 = { StringToDate("01/01/2026"), StringToDate("10/01/2026") };
    stPeriod P2 = { StringToDate("05/01/2026"), StringToDate("15/01/2026") };
    
    cout << "Overlap Days: " << CountOverlapDays(P1, P2) << endl;

    return 0;
}
