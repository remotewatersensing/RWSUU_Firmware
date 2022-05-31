#include <storage.h>

File logfile; //The library currently has support for one file at a time. It makes sense to share the logfile and the filename
char filename[13];

/**
 * @brief Structure to save the binary data
 * The structure is as described in https://github.com/remotewatersensing/RWSUU-Diagrams/raw/main/diagrams/Datastructure.png
 */
struct data {
    uint8_t id;
    float val;
    uint8_t day;
    uint8_t month;
    uint16_t year;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
};


/**
 * @brief Initializes the SD card
 * @return if SD has been successfully initialized
 */
bool initSD()
{
  pinMode(SDCSPin, OUTPUT);
  if(SD.begin(SDCSPin)) {return true};
  else
  {
    Serial.println(F("SD: not detected"));
    errorLoop();
    return false;
  }
}


/**
 * @brief Create a new file with a new filename
 * @return if file has been created
 */
bool createFile() 
{
  char newfile[] = "RWSUU_00.DAT";
  //If the file doesn't exist yet create one, otherwise try a new number
  for (uint8_t i = 0; i < 100; i++) {
    newfile[6] = i/10 + '0';
    newfile[7] = i%10 + '0';
    if (!SD.exists(newfile)) {
      logfile = SD.open(newfile, FILE_WRITE); 
      strcpy(filename,newfile);
      break;
    }
  }
  
  //If the file could not be opened throw a fatal error
  if (!logfile) 
  {
      Serial.println(F("SD: file not initialized"));
      errorLoop();
      return false;
  }
  
  Serial.print(F("SD: Created "));
  Serial.println(filename);
  logfile.close();

  return true;
}

/**
 * @brief Log data with timestamp to opened file
 * @param id the sensor id (see defines.h)
 * @param val the sensor value
 */
void logFile(uint8_t id, float val)
{
    Serial.print(F("SD: Opening "));
    Serial.println(filename);
    logfile = SD.open(filename,FILE_WRITE);
    if(logfile)
    {
        logfile.seek(EOF);
        
        readRTC();

        //Dump the data inside the struct
        struct data myData;
        myData.id = id;
        myData.val = val;
        myData.day = getDay();
        myData.month = getMonth();
        myData.year = getYear();
        myData.hour = getHour();
        myData.minute = getMinute();
        myData.second = getSecond();

        //Write the data at the end of the file
        logfile.write((const uint8_t *)&myData, sizeof(myData));
        logfile.seek(EOF);
        logfile.flush();

        //Closes, reopens in read and closes (fixes sync?)
        logfile.close();
        logfile = SD.open(filename);
        logfile.close();
        Serial.print(F("SD: Closing "));
        Serial.println(filename);

    } else {
        Serial.println(F("SD: Failed writing"));
        errorLoop();
    }

}