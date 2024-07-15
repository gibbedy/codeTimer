/*
 * I occasionally want to test how long a section or sections  of code takes to execute.
 * I do this because I often find I want to know how long some code blocks for or how much of every
 * loop I am left with to complete a certain task. Establishing a hard limit on the lenght/complexity of 
 * things I might want to code.
 * In order to not fill up my program with debug global variables to store the results of my tests I 
 * thought it would be better hide all the details in an object (later changed to some variables/functions in a namespace) 
 * where I can time, store, and recall these times for multiple sections of code with minimal extra text in my source code.
 * 
 * The following is my CodeTimer functions. These will let me record the runtime of sections of code and print the results
 * to serial with a meaningfull name to allow easy understanding of how long some operations take in my program.
 * I can recall the time for a given id and print the time out to the serial console to see what is going on.
 * 
 * I put them in their own namespace so i can call these functions through that name and not have to worry about naming conflicts.
 * 
 * If I don't have DEBUG defined all these functions will be empty and do nothing, so I can easily enable and disable this with one define without
 * having to put an #ifdef aroun every location where I use these functions. 
 * I assume the empty functions are filtered out at compilation so I end up with the same result as if there was no function
 * calls at all?
 * 
 * Usage would be:
 * CodeTimer::startTimer("description"); // put before the code you want to time
 * CodeTimer::stopTimer("description"); // put after the code I want to time. Must have the same name as the start time
 * CodeTimer::printResults(); //print to Serial the times of all the sections that have been timed.
 * 
 */
