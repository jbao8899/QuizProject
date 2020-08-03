#pragma once

#include <chrono>
#include <random>

#include "test_for_instructor.h"

using std::chrono::system_clock;
using std::default_random_engine;
using std::min;
using std::shared_ptr;
using std::shuffle;
using std::weak_ptr;

class TestForStudent {
private:
	string                       name_of_test_ = "";
	vector<shared_ptr<Question>> questions_;
	double                       max_possible_score_ = 0.0;
	unsigned                     index_of_current_question_ = 0;

	//If true, the student must complete each question before moving to the next one. If false, they can move between them at will.
	bool                         order_of_questions_fixed_ = true;
public:
	//Default constructor setting no values, for cereal.
	TestForStudent();

	//Constructs a TestForStudent with the Questions in TestForInstructor (with same name_of_test_ as the TestForInstructor)
	//Goes through assigned_questions_ in test_for_instructor.
	//If the int in a tuple (category of questions) is negative, then all of the Questions in the corresponding sub-vector
	//will be given in the order they were pushed
	//If the int is positive and has value n, then we will give out n random Questions from that sub-vector
	//Also sums the maximum available score of all the questions and stores it as max_possible_score_.
	TestForStudent(const TestForInstructor& test_for_instructor);

	string                        GetNameOfTest();

	//Returns a weak_ptr to the previous question in the vector (if index_of_current_question_ <= 0, then returns a weak_ptr to nothing.
	//Also decrements index_of_current_question_ (if there is a previous question)
	weak_ptr<Question>            GetPreviousQuestion();

	//Returns a weak_ptr to the next question in the vector (if index_of_current_question_ >= questions_.size() - 1, then returns a weak_ptr to nothing.
	//Also increments index_of_current_question_ (if there is a next question)
	//If order_of_questions_fixed_ == true, then does nothing unless questions_[index_of_current_question_]->IsQuestionCompleted() == true
	weak_ptr<Question>            GetNextQuestion();
	
	//Returns the max_possible_score_.
	double                        GetMaxPossibleScore();

	//Iterates through all the questions and sums the values you get from doing GetCurrentScore() on all of them.
	double						  GetCurrentScore();

	//Returns the index of the current question.
	unsigned                      GetIndexOfCurrentQuestion();

	//Sets index_of_current_question_ to set_index_of_current_question - 1. If set_index_of_current_question cannot be converted to an int, then does nothing.
	//Sets index_of_current_question_ to set_index_of_current_question - 1 because questions are numbered starting from 1 for test taker.
	//If it is less than 1 or greater than questions_.size(), then nothing will be done
	//Not allowed (will do nothing) if order_of_questions_fixed_ == true
	void                          GoToQuestionNumber(string set_index_of_current_question);

	//Returns a reference to the vector of questions.
	vector<shared_ptr<Question>>& GetQuestions();

	bool                          IsOrderOfQuestionsFixed();

	//If order_of_questions_fixed_ == true, then turns it to false. If order_of_questions_fixed_ == false, then turns it to true.
	void                          ChangeIfOrderOfQuestionsIsFixed();

	template <class Archive>
	void serialize(Archive& ar) {
		ar(name_of_test_, questions_, max_possible_score_, index_of_current_question_, order_of_questions_fixed_);
	}
};