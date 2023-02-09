# Tasks to be performed
* In this assignment we need to write a harmless polymorphic virus code and test, as
discussed in class. This requires you to generate a virus code and document the process.
Making the document clear and easy to understand is key to doing well in this work.

* a) The Virus program should have the flow as follows. It should have a function
infect()with no parameters which will copy itself into a source file (.ext of your
choice). It should call selectTarget()to identify a target. If a target exists, it should
call copyCode()with the target. If no target exists, it should occasionally call
payload(), say with a probability of 1 in 4. Add the line infect()to the bottom of your
code so the code will run automatically when loaded. Note that the codes need to be
encrypted.
* b) Write a program to detect your virus.
