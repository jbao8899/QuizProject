Test Creator
======
This is a console application which allows users to create and take tests. As it does not currently have a
gui, all input and output is in the form of text. Users are able to save the tests that they create and that
they are in the process of taking via the cereal library.

Note: This project was created on Windows 10 using Visual Studio 2019, and only tested in this environment, so it
may not work elsewhere.

## Dependencies

This project uses the cereal library for save files, but that is header only and does not require installation.
Additionally, this code uses features from C++17.

## How to run:
1. Clone this repository.
2. Go into the Debug folder.
3. Select QuizProject.exe.

## How to use:
Instructions are provided within the program. In general, you usually select which action to perform by
inputting a number, then enter additional information as prompted. You can create a test, add questions
to it, organize them into categories, change the order in which they are asked, add answers to the questions,
set how many points are available, save a test you are working on creating (into the folder QuizProject/TestsForInstructors),
create versions of the test to take (in the folder QuizProject/TestsForStudents), take tests that you have created,
and save tests that you are taking.