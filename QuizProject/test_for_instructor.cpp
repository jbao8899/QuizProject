#include "test_for_instructor.h"

TestForInstructor::TestForInstructor(string set_name_of_test) {
	name_of_test_ = set_name_of_test;
	current_category_ = "";
	next_question_number_ = 1;
}

TestForInstructor::TestForInstructor() {

}

void TestForInstructor::SetNameOfTest(string set_name_of_test) {
	name_of_test_ = set_name_of_test;
}

string TestForInstructor::GetNameOfTest() const {
	return name_of_test_;
}

const vector<shared_ptr<Question>> TestForInstructor::GetUnassignedQuestions() const {
	return unassigned_questions_;
}

const vector<tuple<string, int, vector<shared_ptr<Question>>>>& TestForInstructor::GetAssignedQuestions() const {
	return assigned_questions_;
}

weak_ptr<Question> TestForInstructor::GetCurrentQuestion() {
	return current_question_;
}

string TestForInstructor::GetCurrentCategory() const {
	return current_category_;
}

int TestForInstructor::GetNextQuestionNumber() const {
	return next_question_number_;
}

void TestForInstructor::AddShortAnswerQuestion(string set_question_text) {
	unassigned_questions_.push_back(make_shared<ShortAnswerQuestion>(next_question_number_, set_question_text));
	current_question_ = unassigned_questions_[unassigned_questions_.size() - 1];
	current_category_ = "";
	next_question_number_++;
}

void TestForInstructor::AddNumericalQuestion(string set_question_text) {
	unassigned_questions_.push_back(make_shared<NumericalQuestion>(next_question_number_, set_question_text));
	current_question_ = unassigned_questions_[unassigned_questions_.size() - 1];
	current_category_ = "";
	next_question_number_++;
}

void TestForInstructor::CreateQuestionCategory(string category_name) {
	for (unsigned i = 0; i < assigned_questions_.size(); ++i) {
		if (get<0>(assigned_questions_[i]) == category_name) {
			return;
		}
	}

	assigned_questions_.push_back(tuple<string, int, vector<shared_ptr<Question>>>(category_name, -1, vector <shared_ptr<Question>>()));
}

void TestForInstructor::SelectCurrentQuestion(string question_number_string) {
	if (question_number_string.size() == 0) {
		return;
	}

	for (unsigned i = 0; i < question_number_string.length(); ++i) {
		if (!isdigit(question_number_string[i])) {
			return;
		}
	}

	int question_number = stoi(question_number_string);

	for (unsigned i = 0; i < unassigned_questions_.size(); ++i) {
		if (unassigned_questions_[i]->GetQuestionNumber() == question_number) {
			current_question_ = unassigned_questions_[i];
			current_category_ = "";
			return;
		}
	}

	for (unsigned i = 0; i < assigned_questions_.size(); ++i) {
		for (unsigned j = 0; j < get<2>(assigned_questions_[i]).size(); ++j) {
			if (get<2>(assigned_questions_[i])[j]->GetQuestionNumber() == question_number) {
				current_question_ = get<2>(assigned_questions_[i])[j];
				current_category_ = get<0>(assigned_questions_[i]);
				return;
			}
		}
	}
}

void TestForInstructor::AddCurrentQuestionToCategory(string category_name) {
	if (current_category_ == category_name) {
		return;
	}

	if (current_question_.expired() == true) {
		return;
	}

	bool desired_category_exists = false;
	int index_of_desired_category = -1;
	for (unsigned i = 0; i < assigned_questions_.size(); ++i) {
		if (get<0>(assigned_questions_[i]) == category_name) {
			desired_category_exists = true;
			index_of_desired_category = i;
			break;
		}
	}
	if (desired_category_exists == false) {
		return;
	}

	for (unsigned i = 0; i < get<2>(assigned_questions_[index_of_desired_category]).size(); ++i) {
		if (get<2>(assigned_questions_[index_of_desired_category])[i]->GetMaxPossibleScore() != current_question_.lock()->GetMaxPossibleScore()) {
			return;
		}
	}

	if (current_category_ == "") {
		get<2>(assigned_questions_[index_of_desired_category]).push_back(current_question_.lock());
		current_category_ = category_name;

		for (auto itr = unassigned_questions_.begin(); itr != unassigned_questions_.end(); ++itr) {
			if (*itr == current_question_.lock()) {
				unassigned_questions_.erase(itr);
				return;
			}
		}
	}
	else {
		get<2>(assigned_questions_[index_of_desired_category]).push_back(current_question_.lock());

		for (unsigned i = 0; i < assigned_questions_.size(); ++i) {
			if (get<0>(assigned_questions_[i]) == current_category_) {
				for (auto itr = get<2>(assigned_questions_[i]).begin(); itr != get<2>(assigned_questions_[i]).end(); ++itr) {
					if (*itr == current_question_.lock()) {
						get<2>(assigned_questions_[i]).erase(itr);
						break;
					}
				}
			}
		}
		current_category_ = category_name;
	}
}

void TestForInstructor::RemoveCurrentQuestionFromCategory() {
	if (current_question_.expired() || current_category_ == "") {
		return;
	}
	else {
		unassigned_questions_.push_back(current_question_.lock());
		
		for (unsigned i = 0; i < assigned_questions_.size(); ++i) {
			if (get<0>(assigned_questions_[i]) == current_category_) {
				for (auto itr = get<2>(assigned_questions_[i]).begin(); itr != get<2>(assigned_questions_[i]).end(); ++itr) {
					if (*itr == current_question_.lock()) {
						get<2>(assigned_questions_[i]).erase(itr);
						break;
					}
				}
			}
		}

		current_category_ = "";
	}
}

void TestForInstructor::DeleteCurrentQuestion() {
	if (current_question_.expired() == true) {
		return;
	}
	else if (current_category_ == "") {
		for (auto itr = unassigned_questions_.begin(); itr != unassigned_questions_.end(); ++itr) {
			if (*itr == current_question_.lock()) {
				unassigned_questions_.erase(itr);
				return;
			}
		}
		current_category_ = ""; 
	}
	else {
		for (unsigned i = 0; i < assigned_questions_.size(); ++i) {
			if (get<0>(assigned_questions_[i]) == current_category_) {
				for (auto itr = get<2>(assigned_questions_[i]).begin(); itr != get<2>(assigned_questions_[i]).end(); ++itr) {
					if (*itr == current_question_.lock()) {
						get<2>(assigned_questions_[i]).erase(itr);
						break;
					}
				}
			}
		}
		current_category_ = "";
	}
}

void TestForInstructor::DeleteQuestionCategory(string category_name) {
	if (current_category_ == category_name) {
		current_category_ = "";
	}
	for (auto itr = assigned_questions_.begin(); itr != assigned_questions_.end(); itr++) {
		if (get<0>(*itr) == category_name) {
			for (unsigned j = 0; j < get<2>(*itr).size(); j++) {
				unassigned_questions_.push_back(get<2>(*itr)[j]);
			}
			assigned_questions_.erase(itr);
			return;
		}
	}
}

void TestForInstructor::SwitchOrderOfCategories(string first_category_name, string second_category_name) {
	if (first_category_name == second_category_name) {
		return;
	}

	unsigned index_first_category = -1;
	unsigned index_second_category = -1;

	for (unsigned i = 0; i < assigned_questions_.size(); i++) {
		if (get<0>(assigned_questions_[i]) == first_category_name) {
			index_first_category = i;
		}
		else if (get<0>(assigned_questions_[i]) == second_category_name) {
			index_second_category = i;
		}

		if (index_first_category != -1 && index_second_category != -1) {
			break;
		}
	}
	
	if (index_first_category == -1 || index_second_category == -1) {
		return;
	}
	else {
		swap(assigned_questions_[index_first_category], assigned_questions_[index_second_category]);
	}
}

void TestForInstructor::ChangeNumberOfQuestionsToAskFromCategory(string category_name, string number_of_questions_string) {
	if (number_of_questions_string.length() == 0) {
		return;
	}

	for (unsigned i = 0; i < number_of_questions_string.length(); ++i) {
		if (!isdigit(number_of_questions_string[i]) && number_of_questions_string[i] != '-') {
			return;
		}
	}

	int number_of_questions = stoi(number_of_questions_string);

	for (unsigned i = 0; i < assigned_questions_.size(); ++i) {
		if (get<0>(assigned_questions_[i]) == category_name) {
			get<1>(assigned_questions_[i]) = number_of_questions;
			return;
		}
	}
}

double TestForInstructor::GetMaxAvailableScore() {
	double max_available_score = 0;
	for (unsigned i = 0; i < assigned_questions_.size(); ++i) {
		for (unsigned j = 0; j < get<2>(assigned_questions_[i]).size(); ++j) {
			max_available_score += get<2>(assigned_questions_[i])[j]->GetMaxPossibleScore();
		}
	}
	return max_available_score;
}