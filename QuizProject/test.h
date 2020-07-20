#pragma once

#include <memory>
#include <queue>
#include <utility>

#include "cereal/types/tuple.hpp"

#include "numerical_question.h"
#include "short_answer_question.h"

using std::dynamic_pointer_cast;
using std::get;
using std::make_shared;
using std::shared_ptr;
using std::stoi;
using std::swap;
using std::tuple;
using std::weak_ptr;

class Test {
private:
	string                                                   name_of_test_ = "";

	// All the Questions that have been created, but which have not been removed or assigned.
	vector<shared_ptr<Question>>                             unassigned_questions_;

	//A vector containing tuples of strings, ints, and vectors of shared_ptrs to Questions that have been assigned
	//The string is just a label for the sub-vector contained within the tuple
	//If the int is negative, then all of the Questions in the corresponding sub-vector will be given in the order they were pushed
	//If the int is positive and has value n, then we will give out n random Questions from that sub-vector
	vector<tuple<string, int, vector<shared_ptr<Question>>>> assigned_questions_;

	//The current question being viewed by the test maker
	weak_ptr<Question>                                       current_question_;

	//If the current_question_ points to a Question with its shared_ptr in assigned_questions_, then we will stored the 
	//string stored in the tuple which stores the vector containing the shared pointer here.
	//If the current_question_ is null or if it points to a Question with its shared_ptr in unassigned_questions_, then
	//we will store ""
	string                                                   current_category_ = "";

	//The number of the next question.
	int                                                      next_question_number_ = 1;
public:
	//Creates a new Test object with a current_category_ of "" and a next_question_number_ of 1.
	Test(string set_name_of_test);

	//Default constructor for cereal
	Test();

	void SetNameOfTest(string set_name_of_test);

	const vector<shared_ptr<Question>> GetUnassignedQuestions() const;

	const vector<tuple<string, int, vector<shared_ptr<Question>>>>& GetAssignedQuestions() const;

	weak_ptr<Question> GetCurrentQuestion();

	string GetNameOfTest() const;

	string GetCurrentCategory() const;
	
	int GetNextQuestionNumber() const;
	
	//Creates a new ShortAnswerQuestion with question_text_ equal to set_question_text (and all other fields empty),
	//adds it to unassigned_questions_, sets it as the current_question_,
	//and sets current_category_ as ""
	//Its question_number_ will be next_question_number_, and next_question_number_ will be incremented by 1.
	void AddShortAnswerQuestion(string set_question_text);

	//Creates a new NumericalQuestion with question_text_ equal to set_question_text,
	//adds it to unassigned_questions_, sets it as the current_question_,
	//and sets current_category_ as ""
	//Its question_number_ will be next_question_number_, and next_question_number_ will be incremented by 1.
	void AddNumericalQuestion(string set_question_text);

	//Pushes a new tuple containing a string (category_name), the integer -1, and an empty vector of shared_ptrs to Questions
	//to the vector assigned_questions_. If a tuple containing category_name as its string already exists, then nothing
	//will be done.
	void CreateQuestionCategory(string category_name);

	//Takes a string representing an int
	//If the string contains any characters besides digits or is empty, then does nothing and returns.
	//Searches through first unassigned_questions_ and then assigned_questions_ for a question with the number question_number.
	//If it is found, set current_question_ to point to it. If it is in assigned_questions_, set current_category_ equal to the name of that
	//Question's category (string in tuple that stores sub-vector that contains that Question's shared_ptr). Otherwise, set current_category_ to "".
	void SelectCurrentQuestion(string question_number_string);

	//If the current_question_ is already within the tuple with a string value of category_name, then nothing will be done
	//(current_category_ == category_name)
	//If current_question_ does not refer to a Question object, then nothing will be done
	//We will iterate through assigned_questions_ to search for a category (tuple) with a string value of category_name.
	//if this is not found, then nothing will happen.
	//If the current_question_ is within unassigned_questions, then a shared_ptr referring to it will be pushed to the vector within
	//the tuple with a string value of category_name, it will be popped from unassigned_questions,
	//and current_category_ will be set to category_name
	//If the current_question_ is within the vector of one of the tuples within assigned_questions_, and category_name_ is not the string
	//stored in that tuple, then a shared_ptr referring to it will be pushed to the vector within
	//the tuple with a string value of category_name, it will be popped from its vector within assigned_questions_,
	//and current_category_ will be set to category_name
	//If the current question's max_possible_score_ does not equal the max_possible_score_ of any question within the category, nothing will be done.
	void AddCurrentQuestionToCategory(string category_name);

	//If current_category_ equals "" or if current_question_ refers to nothing then nothing happens.
	//Otherwise, we add a shared_ptr to current_question_ to unassigned_questions_, change the current_category_ to "", and
	// and pop the shared_ptr to current_question_ found there in assigned_questions_
	void RemoveCurrentQuestionFromCategory();

	//If current_question_ refers to nothing, then nothing is done.
	//If current_category_ equals "", then we pop the current question from unassigned_questions_
	//Otherwise, we iterate through assigned_questions_ until we find the tuple with the string value of current_category_, and
	//pop the current_question_ from the vector in that tuple.
	//We then set current_category_ to ""
	void DeleteCurrentQuestion();

	//If no tuple within assigned_questions_ contains the string category_name, nothing will happen.
	//Otherwise, we will push shared_ptrs of all Questions within that tuple's vector into unassigned_questions_ and then pop that tuple
	//from assigned_questions_
	//If the current_category_ equals category_name, it will be set to ""
	void DeleteQuestionCategory(string category_name);

	//If no tuple within assigned_questions_ contains the string first_category_name, nothing will happen.
	//If no tuple within assigned_questions_ contains the string second_category_name, nothing will happen
	//Otherwise, we swap the positions of the two tuples within the assigned_questions_ vector.
	//Returns if two values are the same
	void SwitchOrderOfCategories(string first_category_name, string second_category_name);

	//If there is no tuple within assigned_questions_ entitled category_name, nothing will happen.
	//If there is one entitled category_name (with category_name as its string),
	//then we will set the int in that tuple to number_of_questions (turned to int via stoi).
	//If number_of_questions is not a vald int, then nothing will be done.
	//If number_of_questions contains any characters besides digits or is empty, then does nothing and returns.
	void ChangeNumberOfQuestionsToAskFromCategory(string category_name, string number_of_questions_string);

	//Iterates through all Questions in assigned_questions_, adds up the max scores available on each, then returns that.
	//If assigned_questions_ is empty, returns 0.
	double GetMaxAvailableScore();

	template <class Archive>
	void serialize(Archive& ar) {
		ar(name_of_test_, unassigned_questions_, assigned_questions_, current_question_, current_category_, next_question_number_);
	}
};