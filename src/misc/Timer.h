#pragma once

#include < vector >
#include < ctime >
#include < iostream >
#include < string >
#include < iostream >
#include < iomanip >
#include < sstream >

class Timer
{
public:
	Timer(void);
	~Timer(void);

	void start(void); // starts the timer
	void stop(void); // stops the timer
	void store(void); // adds the currently determined time to the stored values
	long getLatest(void); // returns the latest recording of the timer.
	std::vector<long>* getSavedTimes(void); // returns a pointer to a vector of all stored elapsed times
	double getAverageTime(void); // returns and calculates the average time from the stored elapsed times
	void setVerbose(bool verbose); // toggles the terminal logging on/off
	void clear(void);// clears the stored times

	std::string getAverageTimeStdString( void );
	std::string getLatestStdString( void );

private:
	bool verbose; // terminal logging on/off
	clock_t startMillis, elapsedMillis; // temporarily holding elapsed time in millis
	std::vector<long> savedTimes; // this is where all stored elapsed times are saved to
};