#include "CodeTimer.h"
CodeTimer::CodeTimer()
{
	bool enableTests = false;  // Enable tests allows leaving timer starts and stops in your main code and disabling them with one change here
	int numberOfTests = 0; // how many tests are currently in the tests array.
	testResult tests[MAX_TESTS]; //tests for up to MAX_TESTS  are stored here
}

void CodeTimer::turnOn()
      {
        enableTests = true;
      }
void CodeTimer::turnOff()
      {
        enableTests = false;
      }
      // Each test stores its results in this structure:
      

      
int CodeTimer::checkRecordsForTest(const char recName[])
{
  if(enableTests)
	{		
	  int recordIndex = 0;
	  for (; recordIndex < numberOfTests; recordIndex++)  // For each section of code that is being tested
	  {
		if (strcmp(tests[recordIndex].testId, recName) == 0) return recordIndex;  //break out of loop if recName is found in the records
	  }
	  
	  return -1; // If we got this far the loop was searched and no recName was found so return -1
				// I can imagine more complex functions having common code that you would want to run regardless
				// of whether a previous function return was made or not, and writing the function in a way so you
				// have only one return function. By having one return function I would be helping avoid a situation
				// where this common code was missed. Doing things that way would add a little overhead in this, and
				// I think it is correct to say all cases. in this case It would add no benifit and an extra
				// if check.  It was drummed into me from java days. Why was that particularly important in java?   
	}     
}

/* return the number of records in a given test. This will nearly always be MAX_RECORDS however in case it isn't I need to check
* so average/min/max calculations are correct
*/
int CodeTimer::getMaxIndex(int testIndex)
{
	int maxIndex = tests[testIndex].recordNumber;
	if (tests[testIndex].recordsFull) // The test located at 'testsIndex' is full (not on the first pass of filling the array)
	{
		maxIndex = MAX_RECORDS;  // So override maxIndex to be the index of a full records array
	}
	return maxIndex;
}

unsigned long CodeTimer::getAverage(int testsIndex)
{ 
	if(enableTests)
	{
	  unsigned long sum = 0;
	  int maxIndex = getMaxIndex(testsIndex);
	  for (int i = 0; i < maxIndex; i++)
	  {
		sum += tests[testsIndex].runTime[i];
	  }       
	  return sum / maxIndex;
	}
}

unsigned long CodeTimer::getMinTime(int testIndex)
{

	int maxIndex = getMaxIndex(testIndex);
	int minTime = tests[maxIndex].runTime;
	for (int i = 0; i < maxIndex; i++)
	{
	  int time = tests[testIndex].runTime[i];
	  if (time < minTime)
	  {
		minTime = time;
	  }
	}
	return minTime;
}

// Record the start time of the test and give the record a name
void CodeTimer::startTimer(const char recName[])
{
	if(enableTests)
	{
	  int startTime = micros();  
	  int recordIndex = checkRecordsForTest(recName); //if the testname is already in the testResults then it returns the position of that test in the testResults array otherwise it returns -1

	  if(recordIndex >= 0) //record exists
	  {
		tests[recordIndex].startTime = startTime; //Store the start time in the appropriate test record 
	  }
	  else //record doesn't exist so create one
	  {
		if (numberOfTests <  MAX_TESTS)  //check we havne't maxed out our number of sections of code to test
		{
		  strncpy(tests[numberOfTests].testId,recName,MAX_TEST_NAME - 1); // set name for test by copying char string
		  tests[numberOfTests].testId[MAX_TEST_NAME - 1] = '\0'; //null terminate it. Only needed if I accidentally made the name longer than allowed by MAX_TESTNAME
		  tests[numberOfTests].startTime = startTime;  //set the startTime we recorded at the start of this function.
		  numberOfTests++;               
		}
		else
		{
		  Serial.println("too many tests");
		  Serial.println("Increase MAX_TESTS");
		}       
	  }
	}       
}

// Stop the timer and specifiy an id to be used to store the result
void CodeTimer::stopTimer(const char recName[])
{
	if(enableTests)
	{
		unsigned long runTime = micros(); // for now just put current time in there until i find the start time.
		int recordIndex = checkRecordsForTest(recName); //if the testname is already in the testResults then it returns the position of that test in the testResults array 
		if(recordIndex >= 0) //record exists
		{ 
		  tests[recordIndex].runTime[tests[recordIndex].recordNumber] = runTime - tests[recordIndex].startTime; //Store the start time in the appropriate test record 
		  tests[recordIndex].recordNumber++;

		  if (tests[recordIndex].recordNumber >= MAX_RECORDS)
		  {
			tests[recordIndex].recordNumber = 0;
			tests[recordIndex].recordsFull = true;
		  }
		}
		else //record doesn't exist so we have called a stop on a start that doesn't exist
		{      
		  Serial.print("Called a stop with an Id: ");
		  Serial.print(recName);
		  Serial.println (" that doesn't exist!");
		}
	 }
}

void CodeTimer::printResults()
{
	if(enableTests)
	{
	  Serial.print("CodeTimer results for ");
	  Serial.print(numberOfTests);
	  Serial.println(" tests");
	  for (int i = 0; i < numberOfTests; i++)
	  {
		Serial.print(tests[i].testId);
		Serial.print(" took on average ");
		unsigned long average = getAverage(i);
		Serial.print(average);
		Serial.println(" uS");          
	  }
	  Serial.println();
	}
}