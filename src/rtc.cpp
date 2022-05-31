#include <rtc.h>
#include <led.h>

tmElements_t tm;

/** @brief days of the month */
const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

/** @brief Get the Day object @return uint8_t calendar day*/
uint8_t getDay() {return tm.Day;}
/** @brief Get the Month object @return uint8_t calendar month*/
uint8_t getMonth() {return tm.Month;}
/** @brief Get the Year object @return uint8_t calendar year*/
uint16_t getYear() {return tmYearToCalendar(tm.Year);}
/** @brief Get the Hour object @return uint8_t hour*/
uint8_t getHour() {return tm.Hour;}
/** @brief Get the Minute object @return uint8_t minute*/
uint8_t getMinute() {return tm.Minute;}
/** @brief Get the Second object @return uint8_t second*/
uint8_t getSecond() {return tm.Second;}


/** @brief Notifies what is wrong with the RTC and get into the fatal error loop */
void errorRTC(void)
{
    if (RTC.chipPresent()) 
    {
      Serial.println(F("DS1307: not running"));
    } else 
    {
      Serial.println(F("DS1307: not detected"));
    }
    errorLoop();
}

/** @brief Writes the time object to the RTC 
 *  @return if no errors
*/
bool writeRTC(void) 
{
  if (RTC.write(tm)) {return true;}
  else 
  {
    errorRTC();
    return false;
  }
}

/**
 * @brief Reads from the RTC and puts it in the tm
 * @return if no errors
 */
bool readRTC(void) 
{
  if (RTC.read(tm)) {return true;}
  else 
  {
    errorRTC();
    return false;
  }
}


/**
 * @brief Set the tm from a time string
 * @param str time string
 * @return if parsed correctly
 */
bool setTime(const char *str)
{
  int Hour;int Min;int Sec;

  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) {return false;}
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}


/**
 * @brief Set the tm from a date string
 * @param str date string
 * @return if parsed correctly
 */
bool setDate(const char *str)
{
  char Month[12];
  int Day;int Year;
  uint8_t monthIndex;

  if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3) {return false;}
  for (monthIndex = 0; monthIndex < 12; monthIndex++) {
    if (strcmp(Month, monthName[monthIndex]) == 0) break;
  }
  if (monthIndex >= 12) {return false;}
  tm.Day = Day;
  tm.Month = monthIndex + 1;
  tm.Year = CalendarYrToTm(Year);
  return true;
}

//Writes the compile time to RTC if available
/**
 * @brief Initializes the RTC
 * Extract the date and time from the compiler and write it to the RTC if available.
 * @return if RTC was able to extract a new date and time from the compiler
 */
bool initRTC() 
{
  bool dateSet = setDate(__DATE__);
  bool timeSet = setTime(__TIME__);
  bool rtcWritten = false;
  if(dateSet&&timeSet) {rtcWritten = writeRTC();}
  return (rtcWritten);
}
