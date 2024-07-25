#ifndef CODETIMER_H 				//Include guards
#define CODETIMER_H
#include <Arduino.h>

class CodeTimer
{
	private:
    static const int MAX_TEST_NAME = 15;  // Maximum length of testname that is used to identify the section of code that is being timed
    static const int MAX_TESTS = 20; // Maximum number of unique tests that can be performed. 
    static const int MAX_RECORDS = 100; // Maximum number of records for each test. When printing these will be averaged.   
    bool enableTests;
	int numberOfTests;
	
    	
	/*
	* Holds the all results of a timing test 
	*/
	struct testResult
      {
        char testId[MAX_TEST_NAME];  // The name of the section of code under test
        unsigned long runTime[MAX_RECORDS];  // The runtime, in microseconds, of the section of code is put in here
        int recordNumber = 0; // Number of records currently stored for this testId.  Used so I know when the runtime array is full.
        unsigned long startTime; // Store the start time of the test currently being performed
        bool recordsFull = false; // If i fill the runTime array i set this flag. 
                                  // This was added  because when averaging I stop at recordNumber (an array that is not full)
                                  // but if recordsFull is set I know the array is full (times are recorded over and over in array)
                                  // represents an array of runTimes thatso when averging I know to ignore recordNumber and average the whole Array
      };
	  
	  testResult tests[MAX_TESTS]; // holds all the timimg tests
      
	public:
	/*
	* Constructor
	*/
	CodeTimer(); 
	
	/*
	* Enable or disable the timeing function callse without needing to remove calls to the codtimer class 
	* functions wherever they may be used. 
	* The idea is i don't need to put defines around every location where i start and stop a timer
	*/
	void turnOn();
	void turnOff();

	void startTimer(const char recName[]);
	void stopTimer(const char recName[]);
	void printResults();
	
	private:
	int getMaxIndex(int testIndex);	
	unsigned long getAverage(int testsIndex); // get the average of all the runtimes for a given test by array index. Used by printTests function.
	unsigned long getMinTime(int testIndex);
	int checkRecordsForTest(const char recName[]);  // Check if a record name is already in the tests array and return the index of it or -1 if not
};
#endif
