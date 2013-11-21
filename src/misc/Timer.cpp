#pragma once

#include "Timer.h"

/*
 * constructor creates the timer. default verbose mode is off
*/
Timer::Timer(void) 
        : verbose(false)
{
        
}

/*
 * the destructor does nothing so far
*/
Timer::~Timer(void)
{

}

/*
 * starts the timer. so it starts logging the time.
*/
void Timer::start(void)
{
        startMillis = std::clock();
        if(verbose)
        {
                std::cout << "Timer started " << startMillis << "ms" << std::endl;
        }
}

/*
 * stops the timer. the elapsed time is currently only temporarily stored.
*/
void Timer::stop(void)
{
        elapsedMillis = clock() - startMillis;
}

/* 
 * stores the temporarily saved elapsed time.
*/
void Timer::store(void)
{
        savedTimes.push_back(elapsedMillis);
        if(verbose)
        {
                std::cout << "Timer stopped " << elapsedMillis << "ms" << std::endl;
        }
}

/* 
 * toggles the command line output on/off
*/
void Timer::setVerbose(bool verb)
{
        verbose = verb;
}

/*
 * returns a pointer to a vector of all stored elapsed times
*/
std::vector<long>* Timer::getSavedTimes(void)
{
        return &savedTimes;
}

/*
 * returns and calculates the average time from the stored elapsed times
*/
double Timer::getAverageTime(void)
{
        double returnValue = 0.0;
        long sum = 0;

        for(auto it = getSavedTimes()->begin(); it != getSavedTimes()->end(); ++it)
        {
                sum += *it;
        }

        returnValue = sum / static_cast<double>(getSavedTimes()->size());
        return returnValue;
}

/*
 * clears the vector containing all stored values
*/
void Timer::clear(void)
{
        getSavedTimes()->clear();
}

/*
 * returns the latest recording of the timer.
*/
long Timer::getLatest(void)
{
        return elapsedMillis;
}

std::string Timer::getAverageTimeStdString( void )
{
	std::stringstream strs;
	strs << std::fixed << std::setprecision( 15 ) << getAverageTime();
	std::string str = strs.str();
	return str;
}

std::string Timer::getLatestStdString( void )
{
	std::stringstream strs;
	strs << std::fixed << std::setprecision( 15 ) << getLatest();
	std::string str = strs.str();
	return str;
}
