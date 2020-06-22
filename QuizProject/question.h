#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <deque>

using std::string;
using std::vector;
using std::pair;
using std::find;
using std::deque;

class Question {
protected:
	string                     question_text;
	deque<double>			   available_points;
	vector<string>             correct_answers;
	vector<pair<string, bool>> student_answers; //string is what the student inputted, bool is if they got it correct
	double                     current_score;
public:
	//Changes the question_text to set_question
	virtual void                              SetQuestion(string set_question);

	//Returns the current question_text
	virtual string                            GetQuestion() const;

	//Adds to_add to the vector containing correct answers
	virtual void                              AddCorrectAnswer(string to_add);

	//Removes to_remove from the vector containing the correct answers. If it is not in that vector, nothing will be done
	virtual void                              RemoveCorrectAnswer(string to_remove);

	//Clears the vector containing correct answers
	virtual void                              ClearCorrectAnswers();

	//Returns a constant reference to the vector of correct answers
	virtual const vector<string>&             GetCorrectAnswers() const;

	//Used when the student submits an answer. Looks through the vector of correct answers, and if their answer is right,
	//true is returned, and if it is wrong, false is returned. In either case, we save their answer, along with whether it
	//was right or not
	virtual bool                              SubmitStudentAnswer(string answer);

	//Returns a constant reference to the vector containing all student answers,
	//as well as bools indicating if they were right or not
	virtual const vector<pair<string, bool>>& GetStudentAnswers();

	//Clears the vector containing all student answers and bools indicating if they were right or not.
	virtual void                              ClearStudentAnswers();

	//Takes a string of numbers separated by commas, with the first number being the score the student
	//can receive by getting the question right on their first try, the second being the score they can get 
	//for getting it right on the second try, and so forth, and savees these availalble points in a vector.
	//Clears previous available points vector, if not empty.
	//If there are 2 or more commas in a row,  if the string is just a single comma, or if 
	//the string contains any characters besides digits and commas, then clear the vector and return.
	virtual void                              SetAvailablePoints(string available_points_string);

	//Returns a constant reference to the vector of available points
	virtual const deque<double>&              GetAvailablePoints();

	//Returns the current score
	virtual double                            GetCurrentScore();
};