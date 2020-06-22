#include "pch.h"
#include "question.h"
#include "short_answer_question.h"

ShortAnswerQuestion::ShortAnswerQuestion() {
	question_text = "";
	current_score = 0.0;
}

ShortAnswerQuestion::ShortAnswerQuestion(string set_question) {
	question_text = set_question;
	current_score = 0.0;
}

bool ShortAnswerQuestion::SubmitStudentAnswer(string answer) {
	bool answer_was_correct = false;
	for (unsigned i = 0; i < correct_answers.size(); ++i) {
		if (answer == correct_answers[i]) {
			answer_was_correct = true;
		}
	}

	if (answer_was_correct && !available_points.empty() && available_points[0] > current_score) {
		current_score = available_points[0];
	}
	if (!available_points.empty()) {
		available_points.pop_front();
	}

	student_answers.push_back(pair<string, bool>(answer, answer_was_correct));
	return answer_was_correct;
}