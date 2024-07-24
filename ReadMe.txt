/*
 * On Arduino, I occasionally want to test how long a section or sections  of code takes to execute.
 * I do this because I often find I want to know how long some code blocks for or how much of every
 * loop I am left with to complete a certain task. Establishing a hard limit on the length/complexity of 
 * things I might want to code.
 * In order to not fill up my program with debug global variables to store the results of my tests I 
 * thought it would be better hide all the details in a class object and store and recall these 
 * times for multiple sections of code with minimal extra text in my source code.
 * 
 * The following is my CodeTimer functions. These will let me record the runtime of sections of code and print the results
 * to serial with a meaningfull name to allow easy understanding of how long some operations take in my program.
 * I can recall the time for a given id and print the time out to the serial console to see what is going on.
 * 
 * Usage would be:
 * Create a codeTimer object and use the following static functions.
 * turnOn(); //enable timers in setup
 * startTimer("description"); // put before the code you want to time
 * stopTimer("description"); // put after the code I want to time. Must have the same name as the start time
 * printResults(); //print to Serial the times of all the sections that have been timed.
 * 
 */
