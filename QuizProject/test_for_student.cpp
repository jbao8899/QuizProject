#include "test_for_student.h"

TestForStudent::TestForStudent() {

}

TestForStudent::TestForStudent(const TestForInstructor& test_for_instructor) {
	max_possible_score_ = 0.0;
	name_of_test_ = test_for_instructor.GetNameOfTest();
	//https://www.techiedelight.com/shuffle-vector-cpp/
	unsigned seed = system_clock::now().time_since_epoch().count();

	for (unsigned i = 0; i < test_for_instructor.GetAssignedQuestions().size(); ++i) {
		if (get<1>(test_for_instructor.GetAssignedQuestions()[i]) < 0) {
			for (unsigned j = 0; j < get<2>(test_for_instructor.GetAssignedQuestions()[i]).size(); ++j) {
				if (dynamic_pointer_cast<NumericalQuestion>(get<2>(test_for_instructor.GetAssignedQuestions()[i])[j]) != nullptr) {
					questions_.push_back(make_shared<NumericalQuestion>(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test_for_instructor.GetAssignedQuestions()[i])[j])));
				}
				else {
					questions_.push_back(make_shared<ShortAnswerQuestion>(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test_for_instructor.GetAssignedQuestions()[i])[j])));
				}
				max_possible_score_ += get<2>(test_for_instructor.GetAssignedQuestions()[i])[j]->GetMaxPossibleScore();
			}
		}
		else {
			vector<shared_ptr<Question>> shuffled_question_category = get<2>(test_for_instructor.GetAssignedQuestions()[i]);
			shuffle(shuffled_question_category.begin(), shuffled_question_category.end(), default_random_engine(seed));

			for (unsigned j = 0; j < min((unsigned)get<1>(test_for_instructor.GetAssignedQuestions()[i]), (unsigned)shuffled_question_category.size()); ++j) {
				if (dynamic_pointer_cast<NumericalQuestion>(shuffled_question_category[j]) != nullptr) {
					questions_.push_back(make_shared<NumericalQuestion>(*dynamic_pointer_cast<NumericalQuestion>(shuffled_question_category[j])));
				}
				else {
					questions_.push_back(make_shared<ShortAnswerQuestion>(*dynamic_pointer_cast<ShortAnswerQuestion>(shuffled_question_category[j])));
				}
				max_possible_score_ += shuffled_question_category[j]->GetMaxPossibleScore();
			}
		}
	}
}

string TestForStudent::GetNameOfTest() {
	return name_of_test_;
}

weak_ptr<Question> TestForStudent::GetPreviousQuestion() {
	if (index_of_current_question_ <= 0) {
		return weak_ptr<Question>();
	}
	else {
		--index_of_current_question_;
		return weak_ptr<Question>(questions_[index_of_current_question_]);
	}
}

weak_ptr<Question> TestForStudent::GetNextQuestion() {
	if (index_of_current_question_ >= questions_.size() - 1) {
		return weak_ptr<Question>();
	}
	else if (order_of_questions_fixed_ == true && questions_[index_of_current_question_]->IsQuestionCompleted() == false) {
		return weak_ptr<Question>();
	}
	else {
		++index_of_current_question_;
		return weak_ptr<Question>(questions_[index_of_current_question_]);
	}
}

double TestForStudent::GetMaxPossibleScore() {
	return max_possible_score_;
}

double TestForStudent::GetCurrentScore() {
	double current_score = 0.0;
	for (unsigned i = 0; i < questions_.size(); ++i) {
		current_score += questions_[i]->GetCurrentScore();
	}
	return current_score;
}

unsigned TestForStudent::GetIndexOfCurrentQuestion() {
	return index_of_current_question_;
}


void TestForStudent::GoToQuestionNumber(string set_index_of_current_question) {
	if (order_of_questions_fixed_ == true || set_index_of_current_question.size() == 0) {
		return;
	}

	for (unsigned i = 0; i < set_index_of_current_question.length(); ++i) {
		if (!isdigit(set_index_of_current_question[i])) {
			return;
		}
	}

	int question_number = stoi(set_index_of_current_question);

	if (question_number < 1 || question_number > (int)(questions_.size())) {
		return;
	}

	index_of_current_question_ = question_number - 1;
}

vector<shared_ptr<Question>>& TestForStudent::GetQuestions() {
	return questions_;
}

bool TestForStudent::IsOrderOfQuestionsFixed() {
	return order_of_questions_fixed_;
}

void TestForStudent::ChangeIfOrderOfQuestionsIsFixed() {
	order_of_questions_fixed_ = !order_of_questions_fixed_;
}