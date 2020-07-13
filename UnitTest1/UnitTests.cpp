#include "pch.h"
#include "CppUnitTest.h"

#include <string>
#include <iostream>
#include <vector>

//Must include .cpp files for some reason once added inheritance
#include "../QuizProject/numerical_question.h"
#include "../QuizProject/numerical_question.cpp"
#include "../QuizProject/question.h"
#include "../QuizProject/question.cpp"
#include "../QuizProject/short_answer_question.h"
#include "../QuizProject/short_answer_question.cpp"
#include "../QuizProject/test.h"
#include "../QuizProject/test.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;
using std::vector;
using std::cout;
using std::endl;

namespace TestCases {
	TEST_CLASS(ShortAnswerQuestionTests) {
public:
	TEST_METHOD(DefaultConstructor) {
		ShortAnswerQuestion question(3);
		string empty = "";
		Assert::AreEqual(question.GetQuestion(), empty);
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
		Assert::AreEqual(question.GetCurrentScore(), 0.0);
		Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		Assert::AreEqual(question.GetQuestionNumber(), 3);
	}

	TEST_METHOD(CustomQuestionConstructorEmptyString) {
		ShortAnswerQuestion question(1111, "");
		string empty = "";
		Assert::AreEqual(question.GetQuestion(), empty);
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
		Assert::AreEqual(question.GetCurrentScore(), 0.0);
		Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		Assert::AreEqual(question.GetQuestionNumber(), 1111);
	}

	TEST_METHOD(CustomQuestionConstructorLengthOneString) {
		ShortAnswerQuestion question(0, "a");
		string q_text = "a";
		Assert::AreEqual(question.GetQuestion(), q_text);
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
		Assert::AreEqual(question.GetCurrentScore(), 0.0);
		Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		Assert::AreEqual(question.GetQuestionNumber(), 0);
	}

	TEST_METHOD(CustomQuestionConstructor) {
		ShortAnswerQuestion question(-100, "8BADF00D");
		string q_text = "8BADF00D";
		Assert::AreEqual(question.GetQuestion(), q_text);
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
		Assert::AreEqual(question.GetCurrentScore(), 0.0);
		Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		Assert::AreEqual(question.GetQuestionNumber(), -100);
	}

	TEST_METHOD(GetSetQuestion) {
		ShortAnswerQuestion question(1);
		question.SetQuestion("Have you ever had a tangerine?");
		string q_text = "Have you ever had a tangerine?";
		Assert::AreEqual(question.GetQuestion(), q_text);
	}

	TEST_METHOD(GetSetQuestionEmpty) {
		ShortAnswerQuestion question(1);
		question.SetQuestion("");
		string empty = "";
		Assert::AreEqual(question.GetQuestion(), empty);
	}

	TEST_METHOD(GetSetQuestionLength1) {
		ShortAnswerQuestion question(328, "Should be gone");
		question.SetQuestion("5");
		string q_text = "5";
		Assert::AreEqual(question.GetQuestion(), q_text);
	}

	TEST_METHOD(AddGetRemoveAnswersSingleEmptyString) {
		ShortAnswerQuestion question(1);
		question.AddCorrectAnswer("");
		string a1 = "";
		vector<string> answers;
		answers.push_back(a1);
		Assert::AreEqual(question.GetCorrectAnswers().size(), answers.size());
		for (unsigned i = 0; i < question.GetCorrectAnswers().size(); ++i) {
			Assert::AreEqual(question.GetCorrectAnswers()[i], answers[i]);
		}
	}

	TEST_METHOD(AddGetRemoveAnswersThreeAnswers) {
		ShortAnswerQuestion question(1);
		question.AddCorrectAnswer("abcdefg");
		question.AddCorrectAnswer("");
		question.AddCorrectAnswer("H0r5eRAD1$h");
		vector<string> answers;
		answers.push_back("abcdefg");
		answers.push_back("");
		answers.push_back("H0r5eRAD1$h");
		Assert::AreEqual(question.GetCorrectAnswers().size(), answers.size());
		for (unsigned i = 0; i < question.GetCorrectAnswers().size(); ++i) {
			Assert::AreEqual(question.GetCorrectAnswers()[i], answers[i]);
		}
	}

	TEST_METHOD(AddGetRemoveAnswersAddAndRemoveAnswers) {
		ShortAnswerQuestion question(1);
		question.AddCorrectAnswer("first");
		question.AddCorrectAnswer("second");
		question.AddCorrectAnswer("removed!");
		question.RemoveCorrectAnswer("removed!");
		question.AddCorrectAnswer("Also removed!");
		question.RemoveCorrectAnswer("Also removed!");
		question.AddCorrectAnswer("done");
		vector<string> answers;
		answers.push_back("first");
		answers.push_back("second");
		answers.push_back("done");
		Assert::AreEqual(question.GetCorrectAnswers().size(), answers.size());
		for (unsigned i = 0; i < question.GetCorrectAnswers().size(); ++i) {
			Assert::AreEqual(question.GetCorrectAnswers()[i], answers[i]);
		}
	}

	TEST_METHOD(RemoveAnswerWhenNotThere) {
		ShortAnswerQuestion question(1);
		question.AddCorrectAnswer("first");
		vector<string> answers;
		answers.push_back("first");
		question.RemoveCorrectAnswer("Nothing happens");
		Assert::AreEqual(question.GetCorrectAnswers().size(), answers.size());
		for (unsigned i = 0; i < question.GetCorrectAnswers().size(); ++i) {
			Assert::AreEqual(question.GetCorrectAnswers()[i], answers[i]);
		}
	}

	TEST_METHOD(RemoveAnswerWhenNotThereTwo) {
		ShortAnswerQuestion question(1);
		question.RemoveCorrectAnswer("Nothing happens");
		Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
	}

	TEST_METHOD(ClearCorrectAnswersWhenNoneExist) {
		ShortAnswerQuestion question(1);
		question.ClearCorrectAnswers();
		Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
	}

	TEST_METHOD(ClearCorrectAnswersWhenSomeExist) {
		ShortAnswerQuestion question(1);
		question.AddCorrectAnswer("forth correct");
		question.AddCorrectAnswer("second correct");
		question.AddCorrectAnswer("third correct");
		question.AddCorrectAnswer("first correct");
		question.ClearCorrectAnswers();
		Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
	}

	TEST_METHOD(ClearCorrectAnswerAndAddNew) {
		ShortAnswerQuestion question(1);
		question.AddCorrectAnswer("forth correct");
		question.ClearCorrectAnswers();
		question.AddCorrectAnswer("new answer");
		Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)1);
		Assert::AreEqual(question.GetCorrectAnswers()[0], (string)"new answer");
	}

	TEST_METHOD(AnswerQuestionSingleCorrectAnswer) {
		ShortAnswerQuestion question(1);
		question.AddCorrectAnswer("first");
		vector<string> answers;
		answers.push_back("first");
		Assert::IsTrue(question.SubmitStudentAnswer("first"));
		Assert::AreEqual(question.GetStudentAnswers().size(), answers.size());
		for (unsigned i = 0; i < question.GetStudentAnswers().size(); ++i) {
			Assert::AreEqual(question.GetStudentAnswers()[i].first, answers[i]);
			Assert::IsTrue(question.GetStudentAnswers()[i].second);
		}
	}

	TEST_METHOD(AnswerQuestionMultipleAnswers) {
		ShortAnswerQuestion question(1);
		question.AddCorrectAnswer("forth correct");
		question.AddCorrectAnswer("second correct");
		question.AddCorrectAnswer("third correct");
		question.AddCorrectAnswer("first correct");
		pair<string, bool> a1("first correct", true);
		pair<string, bool> a2("second correct", true);
		pair<string, bool> a3("first wrong", false);
		pair<string, bool> a4("second wrong", false);
		pair<string, bool> a5("third correct", true);
		pair<string, bool> a6("", false);
		pair<string, bool> a7(" ", false);
		pair<string, bool> a8("forth correct", true);

		vector<string> answers;
		answers.push_back("first correct");
		answers.push_back("second correct");
		answers.push_back("first wrong");
		answers.push_back("second wrong");
		answers.push_back("third correct");
		answers.push_back("");
		answers.push_back(" ");
		answers.push_back("forth correct");

		Assert::IsTrue(question.SubmitStudentAnswer(answers[0]));
		Assert::IsTrue(question.SubmitStudentAnswer(answers[1]));
		Assert::IsFalse(question.SubmitStudentAnswer(answers[2]));
		Assert::IsFalse(question.SubmitStudentAnswer(answers[3]));
		Assert::IsTrue(question.SubmitStudentAnswer(answers[4]));
		Assert::IsFalse(question.SubmitStudentAnswer(answers[5]));
		Assert::IsFalse(question.SubmitStudentAnswer(answers[6]));
		Assert::IsTrue(question.SubmitStudentAnswer(answers[7]));

		Assert::AreEqual(question.GetStudentAnswers().size(), answers.size());
		for (unsigned i = 0; i < question.GetStudentAnswers().size(); ++i) {
			Assert::AreEqual(answers[i], question.GetStudentAnswers()[i].first);
			if (i == 0 || i == 1 || i == 4 || i == 7) {
				Assert::IsTrue(question.GetStudentAnswers()[i].second);
			}
			else {
				Assert::IsFalse(question.GetStudentAnswers()[i].second);
			}
		}
	}

	TEST_METHOD(ClearStudentAnswerWhenThereAreNone) {
		ShortAnswerQuestion question(1);
		question.AddCorrectAnswer("correct");
		question.ClearStudentAnswers();
		Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
	}

	TEST_METHOD(ClearStudentAnswersWhenThereAreTwo) {
		ShortAnswerQuestion question(1);
		question.AddCorrectAnswer("correct");
		question.SubmitStudentAnswer("correct");
		question.SubmitStudentAnswer("wrong");
		question.ClearStudentAnswers();
		Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
	}

	TEST_METHOD(ClearStudentAnswersAndAddNewOne) {
		ShortAnswerQuestion question(1);
		question.AddCorrectAnswer("correct");
		question.SubmitStudentAnswer("correct");
		question.SubmitStudentAnswer("wrong");
		question.ClearStudentAnswers();
		question.SubmitStudentAnswer("correct");
		Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)1);
		Assert::AreEqual(question.GetStudentAnswers()[0].first, (string)"correct");
		Assert::IsTrue(question.GetStudentAnswers()[0].second);
	}

	TEST_METHOD(FailToSetAvailablePointsEmptyString) {
		ShortAnswerQuestion question(1);
		question.SetAvailablePoints("");
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
	}

	TEST_METHOD(FailToSetAvailablePointsCommaOnly) {
		ShortAnswerQuestion question(1);
		question.SetAvailablePoints(",");
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
	}

	TEST_METHOD(FailToSetAvailablePointsDoubleComma) {
		ShortAnswerQuestion question(1);
		question.SetAvailablePoints("5,4,3,2,,1");
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
	}

	TEST_METHOD(FailToSetAvailablePointsContainsSpaces) {
		ShortAnswerQuestion question(1);
		question.SetAvailablePoints("10, 8, 6, 4, 2");
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
	}

	TEST_METHOD(FailToSetAvailablePointsTwoPeriods) {
		ShortAnswerQuestion question(1);
		question.SetAvailablePoints("10, 5.5, 6.2, 4, 2..1");
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
	}

	TEST_METHOD(FailToFailToSetAvailablePointsContainsLetter) {
		ShortAnswerQuestion question(1);
		question.SetAvailablePoints("5,3,1a");
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
	}

	TEST_METHOD(FailToSetAvailablePointsContainsSymbol) {
		ShortAnswerQuestion question(1);
		question.SetAvailablePoints("5!,3,2");
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
	}

	TEST_METHOD(FailToSetAvailablePointsScoresNotDescendingOrder) {
		ShortAnswerQuestion question(1);
		question.SetAvailablePoints("10,9,8,7,6,7,4,3,2,1");
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
	}

	TEST_METHOD(FailToSetAvailablePointsScoresAscendingOrder) {
		ShortAnswerQuestion question(1);
		question.SetAvailablePoints("0.1,0.2,0.3,0.4,0.5");
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
	}

	TEST_METHOD(SetAvailablePointsOneAttemptAllowed) {
		ShortAnswerQuestion question(1);
		question.SetAvailablePoints("5");
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)1);
		Assert::AreEqual(question.GetAvailablePoints()[0], 5.0);
		Assert::AreEqual(question.GetMaxPossibleScore(), 5.0);
	}

	TEST_METHOD(SetAvailablePointsFiveAttemptsAllowed) {
		ShortAnswerQuestion question(1);
		question.SetAvailablePoints("10,10,8,5,3");
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)5);
		Assert::AreEqual(question.GetAvailablePoints()[0], 10.0);
		Assert::AreEqual(question.GetAvailablePoints()[1], 10.0);
		Assert::AreEqual(question.GetAvailablePoints()[2], 8.0);
		Assert::AreEqual(question.GetAvailablePoints()[3], 5.0);
		Assert::AreEqual(question.GetAvailablePoints()[4], 3.0);
		Assert::AreEqual(question.GetMaxPossibleScore(), 10.0);
	}

	TEST_METHOD(SetAvailablePointsDecimalValues) {
		ShortAnswerQuestion question(1);
		question.SetAvailablePoints("1.5,0.75,0.5,0.25");
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)4);
		Assert::AreEqual(question.GetAvailablePoints()[0], 1.5);
		Assert::AreEqual(question.GetAvailablePoints()[1], 0.75);
		Assert::AreEqual(question.GetAvailablePoints()[2], 0.5);
		Assert::AreEqual(question.GetAvailablePoints()[3], 0.25);
		Assert::AreEqual(question.GetMaxPossibleScore(), 1.5);
	}

	TEST_METHOD(AnswerQuestionsPointsCorrectFirstTry) {
		ShortAnswerQuestion question(1);
		question.AddCorrectAnswer("correct");
		question.SetAvailablePoints("5");
		question.SubmitStudentAnswer("correct");
		Assert::AreEqual(question.GetCurrentScore(), 5.0);
	}

	TEST_METHOD(AnswerQuestionsPointsCorrectSecondTry) {
		ShortAnswerQuestion question(1);
		question.AddCorrectAnswer("correct");
		question.SetAvailablePoints("5,3");
		question.SubmitStudentAnswer("wrong");
		question.SubmitStudentAnswer("correct");
		Assert::AreEqual(question.GetCurrentScore(), 3.0);
	}

	TEST_METHOD(AnswerQuestionsPointsZeroPointsRanOutOfTries) {
		ShortAnswerQuestion question(1);
		question.AddCorrectAnswer("correct");
		question.SetAvailablePoints("5,3,1");
		question.SubmitStudentAnswer("wrong");
		question.SubmitStudentAnswer("incorrect");
		question.SubmitStudentAnswer("still not right");
		question.SubmitStudentAnswer("correct");
		Assert::AreEqual(question.GetCurrentScore(), 0.0);
	}

	TEST_METHOD(AnswerQuestionsPointsSubsequentCorrectAnswersDoNotReduceSCore) {
		ShortAnswerQuestion question(1);
		question.AddCorrectAnswer("correct");
		question.AddCorrectAnswer("Also correct");
		question.SetAvailablePoints("5,3,1");
		question.SubmitStudentAnswer("Also correct");
		Assert::AreEqual(question.GetCurrentScore(), 5.0);
	}

	TEST_METHOD(AnswerQuestionsPointsCorrectAndIncorrectAnswers) {
		ShortAnswerQuestion question(1);
		question.AddCorrectAnswer("correct");
		question.AddCorrectAnswer("Also correct");
		question.SetAvailablePoints("5,3,1");
		question.SubmitStudentAnswer("wrong");
		question.SubmitStudentAnswer("Also correct");
		question.SubmitStudentAnswer("correct");
		Assert::AreEqual(question.GetCurrentScore(), 3.0);
	}

	TEST_METHOD(AnswerQuestionsPointsCaseDoesNotMatter) {
		ShortAnswerQuestion question(1);
		question.AddCorrectAnswer("cOrReCt12345^&*()");
		question.SetAvailablePoints("3.5");
		question.SubmitStudentAnswer("CoRrEcT12345^&*()");
		Assert::AreEqual(question.GetCurrentScore(), 3.5);
	}

	TEST_METHOD(TwoQuestionsNotSameIfDifferentQuestionText) {
		ShortAnswerQuestion first_question(1, "apples");
		ShortAnswerQuestion second_question(1, "oranges");
		Assert::IsFalse(first_question == second_question);
	}

	TEST_METHOD(TwoQuestionsDifferentIfDifferentQuestionText) {
		ShortAnswerQuestion first_question(1, "apples");
		ShortAnswerQuestion second_question(1, "oranges");
		Assert::IsTrue(first_question != second_question);
	}

	TEST_METHOD(TwoQuestionsNotSameIfDifferentCurrentScore) {
		ShortAnswerQuestion first_question(1, "same");
		first_question.SetAvailablePoints("12,11,10,8,5,3");
		first_question.AddCorrectAnswer("abc");
		first_question.SubmitStudentAnswer("xyz");
		first_question.SubmitStudentAnswer("abc");
		ShortAnswerQuestion second_question(1, "same");
		second_question.SetAvailablePoints("12,10.5,10,8,5,3");
		second_question.AddCorrectAnswer("abc");
		second_question.SubmitStudentAnswer("xyz");
		second_question.SubmitStudentAnswer("abc");
		Assert::IsFalse(first_question == second_question);
	}

	TEST_METHOD(TwoQuestionsDifferentIfDifferentCurrentScore) {
		ShortAnswerQuestion first_question(1, "same");
		first_question.SetAvailablePoints("12,11,10,8,5,3");
		first_question.AddCorrectAnswer("abc");
		first_question.SubmitStudentAnswer("xyz");
		first_question.SubmitStudentAnswer("abc");
		ShortAnswerQuestion second_question(1, "same");
		second_question.SetAvailablePoints("12,10.5,10,8,5,3");
		second_question.AddCorrectAnswer("abc");
		second_question.SubmitStudentAnswer("xyz");
		second_question.SubmitStudentAnswer("abc");
		Assert::IsTrue(first_question != second_question);
	}

	TEST_METHOD(TwoQuestionsNotSameIfDifferentMaxPossibleScore) {
		ShortAnswerQuestion first_question(1, "same");
		first_question.SetAvailablePoints("12,11,10,8,5,3");
		first_question.AddCorrectAnswer("abc");
		first_question.SubmitStudentAnswer("xyz");
		ShortAnswerQuestion second_question(1, "same");
		second_question.SetAvailablePoints("13,11,10,8,5,3");
		second_question.AddCorrectAnswer("abc");
		second_question.SubmitStudentAnswer("xyz");
		Assert::IsFalse(first_question == second_question);
	}

	TEST_METHOD(TwoQuestionsDifferentIfDifferentMaxPossibleScore) {
		ShortAnswerQuestion first_question(1, "same");
		first_question.SetAvailablePoints("12,11,10,8,5,3");
		first_question.AddCorrectAnswer("abc");
		first_question.SubmitStudentAnswer("xyz");
		ShortAnswerQuestion second_question(1, "same");
		second_question.SetAvailablePoints("13,11,10,8,5,3");
		second_question.AddCorrectAnswer("abc");
		second_question.SubmitStudentAnswer("xyz");
		Assert::IsTrue(first_question != second_question);
	}

	TEST_METHOD(TwoQuestionsNotSameIfDifferentQuestionNumber) {
		ShortAnswerQuestion first_question(1, "same");
		ShortAnswerQuestion second_question(2, "same");
		Assert::IsFalse(first_question == second_question);
	}

	TEST_METHOD(TwoQuestionsDifferentIfDifferentQuestionNumber) {
		ShortAnswerQuestion first_question(1, "same");
		ShortAnswerQuestion second_question(2, "same");
		Assert::IsTrue(first_question != second_question);
	}

	TEST_METHOD(TwoQuestionsNotSameIfDifferentLengthAvailablePointsDeque) {
		ShortAnswerQuestion first_question(1, "same");
		first_question.SetAvailablePoints("5,4,3,2,1");
		ShortAnswerQuestion second_question(1, "same");
		second_question.SetAvailablePoints("5,4,3,2");
		Assert::IsFalse(first_question == second_question);
	}

	TEST_METHOD(TwoQuestionsDifferentIfDifferentLengthAvailablePointsDeque) {
		ShortAnswerQuestion first_question(1, "same");
		first_question.SetAvailablePoints("5,4,3,2,1");
		ShortAnswerQuestion second_question(1, "same");
		second_question.SetAvailablePoints("5,4,3,2");
		Assert::IsTrue(first_question != second_question);
	}

	TEST_METHOD(TwoQuestionsNotSameIfDifferentAvailablePointsDeque) {
		ShortAnswerQuestion first_question(1, "same");
		first_question.SetAvailablePoints("5,3,1");
		ShortAnswerQuestion second_question(1, "same");
		second_question.SetAvailablePoints("5,3,0.95");
		Assert::IsFalse(first_question == second_question);
	}

	TEST_METHOD(TwoQuestionsDifferentIfDifferentAvailablePointsDeque) {
		ShortAnswerQuestion first_question(1, "same");
		first_question.SetAvailablePoints("5,3,1");
		ShortAnswerQuestion second_question(1, "same");
		second_question.SetAvailablePoints("5,3,0.95");
		Assert::IsTrue(first_question != second_question);
	}

	TEST_METHOD(TwoQuestionsNotSameIfDifferentLengthCorrectAnswersVector) {
		ShortAnswerQuestion first_question(1, "same");
		first_question.AddCorrectAnswer("a");
		first_question.AddCorrectAnswer("a");
		first_question.AddCorrectAnswer("a");
		ShortAnswerQuestion second_question(1, "same");
		second_question.AddCorrectAnswer("a");
		second_question.AddCorrectAnswer("a");
		Assert::IsFalse(first_question == second_question);
	}

	TEST_METHOD(TwoQuestionsDifferentIfDifferentLengthCorrectAnswersVector) {
		ShortAnswerQuestion first_question(1, "same");
		first_question.AddCorrectAnswer("a");
		first_question.AddCorrectAnswer("a");
		first_question.AddCorrectAnswer("a");
		ShortAnswerQuestion second_question(1, "same");
		second_question.AddCorrectAnswer("a");
		second_question.AddCorrectAnswer("a");
		Assert::IsTrue(first_question != second_question);
	}

	TEST_METHOD(TwoQuestionsNotSameIfDifferentCorrectAnswersVector) {
		ShortAnswerQuestion first_question(1, "same");
		first_question.AddCorrectAnswer("a");
		first_question.AddCorrectAnswer("b");
		first_question.AddCorrectAnswer("c");
		ShortAnswerQuestion second_question(1, "same");
		second_question.AddCorrectAnswer("aa");
		second_question.AddCorrectAnswer("b");
		second_question.AddCorrectAnswer("c");
		Assert::IsFalse(first_question == second_question);
	}

	TEST_METHOD(TwoQuestionsDifferentIfDifferentCorrectAnswersVector) {
		ShortAnswerQuestion first_question(1, "same");
		first_question.AddCorrectAnswer("a");
		first_question.AddCorrectAnswer("b");
		first_question.AddCorrectAnswer("c");
		ShortAnswerQuestion second_question(1, "same");
		second_question.AddCorrectAnswer("aa");
		second_question.AddCorrectAnswer("b");
		second_question.AddCorrectAnswer("c");
		Assert::IsTrue(first_question != second_question);
	}

	TEST_METHOD(TwoQuestionsNotSameIfDifferentLengthStudentAnswersVector) {
		ShortAnswerQuestion first_question(1, "same");
		first_question.AddCorrectAnswer("a");
		first_question.SubmitStudentAnswer("a");
		ShortAnswerQuestion second_question(1, "same");
		second_question.AddCorrectAnswer("a");
		Assert::IsFalse(first_question == second_question);
	}

	TEST_METHOD(TwoQuestionsDifferentIfDifferentLengthStudentAnswersVector) {
		ShortAnswerQuestion first_question(1, "same");
		first_question.AddCorrectAnswer("a");
		first_question.SubmitStudentAnswer("a");
		ShortAnswerQuestion second_question(1, "same");
		second_question.AddCorrectAnswer("a");
		Assert::IsTrue(first_question != second_question);
	}

	TEST_METHOD(TwoQuestionsNotSameIfDifferentStudentAnswersVector) {
		ShortAnswerQuestion first_question(1, "same");
		first_question.AddCorrectAnswer("a");
		first_question.SubmitStudentAnswer("b");
		first_question.SubmitStudentAnswer("a");
		ShortAnswerQuestion second_question(1, "same");
		second_question.AddCorrectAnswer("a");
		second_question.SubmitStudentAnswer("c");
		second_question.SubmitStudentAnswer("a");
		Assert::IsFalse(first_question == second_question);
	}

	TEST_METHOD(TwoQuestionsDifferentIfDifferentStudentAnswersVector) {
		ShortAnswerQuestion first_question(1, "same");
		first_question.AddCorrectAnswer("a");
		first_question.SubmitStudentAnswer("b");
		first_question.SubmitStudentAnswer("a");
		ShortAnswerQuestion second_question(1, "same");
		second_question.AddCorrectAnswer("a");
		second_question.SubmitStudentAnswer("c");
		second_question.SubmitStudentAnswer("a");
		Assert::IsTrue(first_question != second_question);
	}

	TEST_METHOD(QuestionSameAsItself) {
		ShortAnswerQuestion question(1, "text");
		question.SetAvailablePoints("1.5,0.75,0.5,0.25");
		question.AddCorrectAnswer("foo");
		question.AddCorrectAnswer("bar");
		question.AddCorrectAnswer("foobar");
		question.SubmitStudentAnswer("wrong");
		question.SubmitStudentAnswer("foobar");
		Assert::IsTrue(question == question);
	}

	TEST_METHOD(QuestionNotDifferentFromItself) {
		ShortAnswerQuestion question(1, "text");
		question.SetAvailablePoints("1.5,0.75,0.5,0.25");
		question.AddCorrectAnswer("foo");
		question.AddCorrectAnswer("bar");
		question.AddCorrectAnswer("foobar");
		question.SubmitStudentAnswer("wrong");
		question.SubmitStudentAnswer("foobar");
		Assert::IsFalse(question != question);
	}

	TEST_METHOD(QuestionSameAsIdenticalQuestion) {
		ShortAnswerQuestion first_question(1, "text");
		first_question.SetAvailablePoints("1.5,0.75,0.5,0.25");
		first_question.AddCorrectAnswer("a");
		first_question.AddCorrectAnswer("b");
		first_question.AddCorrectAnswer("c");
		first_question.SubmitStudentAnswer("d");
		first_question.SubmitStudentAnswer("a");

		ShortAnswerQuestion second_question(1, "text");
		second_question.SetAvailablePoints("1.5,0.75,0.5,0.25");
		second_question.AddCorrectAnswer("a");
		second_question.AddCorrectAnswer("b");
		second_question.AddCorrectAnswer("c");
		second_question.SubmitStudentAnswer("d");
		second_question.SubmitStudentAnswer("a");
		Assert::IsTrue(first_question == second_question);
	}

	TEST_METHOD(QuestionNotDifferentFromIdenticalQuestion) {
		ShortAnswerQuestion first_question(1, "text");
		first_question.SetAvailablePoints("1.5,0.75,0.5,0.25");
		first_question.AddCorrectAnswer("a");
		first_question.AddCorrectAnswer("b");
		first_question.AddCorrectAnswer("c");
		first_question.SubmitStudentAnswer("d");
		first_question.SubmitStudentAnswer("a");

		ShortAnswerQuestion second_question(1, "text");
		second_question.SetAvailablePoints("1.5,0.75,0.5,0.25");
		second_question.AddCorrectAnswer("a");
		second_question.AddCorrectAnswer("b");
		second_question.AddCorrectAnswer("c");
		second_question.SubmitStudentAnswer("d");
		second_question.SubmitStudentAnswer("a");
		Assert::IsFalse(first_question != second_question);
	}
	};

	TEST_CLASS(NumericalQuestionTests) {
public:
	TEST_METHOD(DefaultConstructor) {
		NumericalQuestion question(4346);
		string empty = "";
		Assert::AreEqual(question.GetQuestion(), empty);
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
		Assert::AreEqual(question.GetCurrentScore(), 0.0);
		Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
		Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
		Assert::AreEqual(question.GetQuestionNumber(), 4346);
	}

	TEST_METHOD(CustomQuestionConstructorEmptyString) {
		NumericalQuestion question(7, "");
		string empty = "";
		Assert::AreEqual(question.GetQuestion(), empty);
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
		Assert::AreEqual(question.GetCurrentScore(), 0.0);
		Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
		Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
		Assert::AreEqual(question.GetQuestionNumber(), 7);
	}

	TEST_METHOD(CustomQuestionConstructorLengthOneString) {
		NumericalQuestion question(16, "a");
		string q_text = "a";
		Assert::AreEqual(question.GetQuestion(), q_text);
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
		Assert::AreEqual(question.GetCurrentScore(), 0.0);
		Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
		Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
		Assert::AreEqual(question.GetQuestionNumber(), 16);
	}

	TEST_METHOD(CustomQuestionConstructor) {
		NumericalQuestion question(2, "8BADF00D");
		string q_text = "8BADF00D";
		Assert::AreEqual(question.GetQuestion(), q_text);
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
		Assert::AreEqual(question.GetCurrentScore(), 0.0);
		Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
		Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
		Assert::AreEqual(question.GetQuestionNumber(), 2);
	}

	TEST_METHOD(GetSetPermittedAbsoluteError) {
		NumericalQuestion question(1);
		question.SetPermittedAbsoluteError(5.1);
		Assert::AreEqual(question.GetPermittedAbsoluteError(), 5.1);
		Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
	}

	TEST_METHOD(GetSetPermittedRelativeError) {
		NumericalQuestion question(1);
		question.SetPermittedRelativeError(0.078);
		Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
		Assert::AreEqual(question.GetPermittedRelativeError(), 0.078);
	}

	TEST_METHOD(GetSetQuestion) {
		NumericalQuestion question(1);
		question.SetQuestion("What is 5 + 5?");
		string q_text = "What is 5 + 5?";
		Assert::AreEqual(question.GetQuestion(), q_text);
	}

	TEST_METHOD(GetSetQuestionEmpty) {
		NumericalQuestion question(1);
		question.SetQuestion("");
		string empty = "";
		Assert::AreEqual(question.GetQuestion(), empty);
	}

	TEST_METHOD(GetSetQuestionLength1) {
		NumericalQuestion question(5, "Should be gone");
		question.SetQuestion("5");
		string q_text = "5";
		Assert::AreEqual(question.GetQuestion(), q_text);
	}

	TEST_METHOD(FailToAddEmptyStringAsCorrectAnswer) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("");
		Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
	}

	TEST_METHOD(FailToAddSpaceAsCorrectAnswer) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer(" ");
		Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
	}

	TEST_METHOD(FailToAddWordAsCorrectAnswer) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("aeftrser");
		Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
	}

	TEST_METHOD(FailToAddNumberWithLetterAsCorrectAnswer) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("5a");
		Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
	}

	TEST_METHOD(FailToAddNumberWithSymbolAsCorrectAnswer) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("2.1!");
		Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
	}

	TEST_METHOD(FailToAddMixOfCharactersAsCorrectAnswer) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("UIH8efhfrui9#*9e");
		Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
	}

	TEST_METHOD(FailToAddNumberWithTwoPeriodsAsCorrectAnswer) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("5.3.1");
		Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
	}

	TEST_METHOD(AddIntegerAsCorrectAnswer) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("8");
		vector<string> answers;
		answers.push_back("8");
		Assert::AreEqual(question.GetCorrectAnswers().size(), answers.size());
		for (unsigned i = 0; i < answers.size(); ++i) {
			Assert::AreEqual(question.GetCorrectAnswers()[i], answers[i]);
		}
	}

	TEST_METHOD(AddDoubleAsCorrectAnswer) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("3.1415");
		vector<string> answers;
		answers.push_back("3.1415");
		Assert::AreEqual(question.GetCorrectAnswers().size(), answers.size());
		for (unsigned i = 0; i < answers.size(); ++i) {
			Assert::AreEqual(question.GetCorrectAnswers()[i], answers[i]);
		}
	}

	TEST_METHOD(AddMultipleCorrectAnswers) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("8");
		question.AddCorrectAnswer("3.1415");
		question.AddCorrectAnswer("1.1");
		question.AddCorrectAnswer("1.1");
		vector<string> answers;
		answers.push_back("8");
		answers.push_back("3.1415");
		answers.push_back("1.1");
		answers.push_back("1.1");
		Assert::AreEqual(question.GetCorrectAnswers().size(), answers.size());
		for (unsigned i = 0; i < answers.size(); ++i) {
			Assert::AreEqual(question.GetCorrectAnswers()[i], answers[i]);
		}
	}

	TEST_METHOD(AddNegativeCorrectAnswer) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("-3.89");
		vector<string> answers;
		answers.push_back("-3.89");
		Assert::AreEqual(question.GetCorrectAnswers().size(), answers.size());
		for (unsigned i = 0; i < answers.size(); ++i) {
			Assert::AreEqual(question.GetCorrectAnswers()[i], answers[i]);
		}
	}

	TEST_METHOD(FailToAddCorrectAnswersWithMultipleNegativeSignsOrNegativeSignsInWrongPlaces) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("--3.89");
		question.AddCorrectAnswer("5-2");
		Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
	}

	TEST_METHOD(FailToAddCorrectAnswerThatIsJustNegativeSign) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("-");
		Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
	}

	TEST_METHOD(AddMultipleCorrectAnswersAndFailToAddSome) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("banana");
		question.AddCorrectAnswer("8");
		question.AddCorrectAnswer("");
		question.AddCorrectAnswer(" ");
		question.AddCorrectAnswer("3.1415");
		question.AddCorrectAnswer("!@#$%^&*()");
		question.AddCorrectAnswer("1.1");
		question.AddCorrectAnswer("3..4");
		question.AddCorrectAnswer("1.1");
		question.AddCorrectAnswer("dfhzzudo8s5hys78ghu78ghEF7");
		vector<string> answers;
		answers.push_back("8");
		answers.push_back("3.1415");
		answers.push_back("1.1");
		answers.push_back("1.1");
		Assert::AreEqual(question.GetCorrectAnswers().size(), answers.size());
		for (unsigned i = 0; i < answers.size(); ++i) {
			Assert::AreEqual(question.GetCorrectAnswers()[i], answers[i]);
		}
	}

	TEST_METHOD(RemoveAnswersSingleAnswer) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("5");
		question.RemoveCorrectAnswer("5");
		Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
	}

	TEST_METHOD(AddGetRemoveAnswersThreeAnswers) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("3.14");
		question.AddCorrectAnswer("2.57");
		question.AddCorrectAnswer("10");
		question.RemoveCorrectAnswer("2.57");
		vector<string> answers;
		answers.push_back("3.14");
		answers.push_back("10");
		Assert::AreEqual(question.GetCorrectAnswers().size(), answers.size());
		for (unsigned i = 0; i < question.GetCorrectAnswers().size(); ++i) {
			Assert::AreEqual(question.GetCorrectAnswers()[i], answers[i]);
		}
	}

	TEST_METHOD(AddGetRemoveAnswersAddAndRemoveAnswers) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("1");
		question.AddCorrectAnswer("2");
		question.AddCorrectAnswer("3");
		question.RemoveCorrectAnswer("3");
		question.AddCorrectAnswer("4");
		question.RemoveCorrectAnswer("4");
		question.AddCorrectAnswer("5");
		vector<string> answers;
		answers.push_back("1");
		answers.push_back("2");
		answers.push_back("5");
		Assert::AreEqual(question.GetCorrectAnswers().size(), answers.size());
		for (unsigned i = 0; i < question.GetCorrectAnswers().size(); ++i) {
			Assert::AreEqual(question.GetCorrectAnswers()[i], answers[i]);
		}
	}

	TEST_METHOD(RemoveAnswerWhenNotThere) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("5");
		vector<string> answers;
		answers.push_back("5");
		question.RemoveCorrectAnswer("2");
		Assert::AreEqual(question.GetCorrectAnswers().size(), answers.size());
		for (unsigned i = 0; i < question.GetCorrectAnswers().size(); ++i) {
			Assert::AreEqual(question.GetCorrectAnswers()[i], answers[i]);
		}
	}

	TEST_METHOD(RemoveAnswerWhenNotThereTwo) {
		NumericalQuestion question(1);
		question.RemoveCorrectAnswer("5");
		Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
	}

	TEST_METHOD(ClearCorrectAnswersWhenNoneExist) {
		NumericalQuestion question(1);
		question.ClearCorrectAnswers();
		Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
	}

	TEST_METHOD(ClearCorrectAnswersWhenSomeExist) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("5.5");
		question.AddCorrectAnswer("1.23");
		question.AddCorrectAnswer("-5");
		question.AddCorrectAnswer("0");
		question.ClearCorrectAnswers();
		Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
	}

	TEST_METHOD(ClearCorrectAnswerAndAddNew) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("5");
		question.ClearCorrectAnswers();
		question.AddCorrectAnswer("3");
		Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)1);
		Assert::AreEqual(question.GetCorrectAnswers()[0], (string)"3");
	}

	TEST_METHOD(SubmitSingleAnswerExactlyCorrect) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("5.1689");
		question.SetAvailablePoints("5,3,1");

		vector<pair<string, bool>> expected_student_answers;
		expected_student_answers.push_back(pair<string, bool>("5.1689", true));

		Assert::IsTrue(question.SubmitStudentAnswer("5.1689"));
		Assert::AreEqual(question.GetStudentAnswers().size(), expected_student_answers.size());
		for (unsigned i = 0; i < expected_student_answers.size(); ++i) {
			Assert::AreEqual(question.GetStudentAnswers()[i].first, expected_student_answers[i].first);
			Assert::AreEqual(question.GetStudentAnswers()[i].second, expected_student_answers[i].second);
		}
		Assert::AreEqual(question.GetCurrentScore(), 5.0);
	}

	TEST_METHOD(SubmitSingleAnswerWithinAbsoluteAndRelativeErrorLimits) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("5.1689");
		question.SetAvailablePoints("5,3,1");
		question.SetPermittedAbsoluteError(0.01);
		question.SetPermittedRelativeError(0.002);

		vector<pair<string, bool>> expected_student_answers;
		expected_student_answers.push_back(pair<string, bool>("5.16", true));

		Assert::IsTrue(question.SubmitStudentAnswer("5.16"));
		Assert::AreEqual(question.GetStudentAnswers().size(), expected_student_answers.size());
		for (unsigned i = 0; i < expected_student_answers.size(); ++i) {
			Assert::AreEqual(question.GetStudentAnswers()[i].first, expected_student_answers[i].first);
			Assert::AreEqual(question.GetStudentAnswers()[i].second, expected_student_answers[i].second);
		}
		Assert::AreEqual(question.GetCurrentScore(), 5.0);
	}

	TEST_METHOD(SubmitSingleAnswerWithinAbsoluteErrorLimitsNotCareAboutRelative) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("1000.0");
		question.SetAvailablePoints("5,3,1");
		question.SetPermittedAbsoluteError(10.0);
		question.SetPermittedRelativeError(-1);

		vector<pair<string, bool>> expected_student_answers;
		expected_student_answers.push_back(pair<string, bool>("1009.999", true));

		Assert::IsTrue(question.SubmitStudentAnswer("1009.999"));
		Assert::AreEqual(question.GetStudentAnswers().size(), expected_student_answers.size());
		for (unsigned i = 0; i < expected_student_answers.size(); ++i) {
			Assert::AreEqual(question.GetStudentAnswers()[i].first, expected_student_answers[i].first);
			Assert::AreEqual(question.GetStudentAnswers()[i].second, expected_student_answers[i].second);
		}
		Assert::AreEqual(question.GetCurrentScore(), 5.0);
	}

	TEST_METHOD(SubmitSingleAnswerWithinRelativeErrorLimitsNotCareAboutAbsolute) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("-21489.349");
		question.SetAvailablePoints("5,3,1");
		question.SetPermittedAbsoluteError(-439889.489389);
		question.SetPermittedRelativeError(0.001);

		vector<pair<string, bool>> expected_student_answers;
		expected_student_answers.push_back(pair<string, bool>("-21469.8505", true));

		Assert::IsTrue(question.SubmitStudentAnswer("-21469.8505"));
		Assert::AreEqual(question.GetStudentAnswers().size(), expected_student_answers.size());
		for (unsigned i = 0; i < expected_student_answers.size(); ++i) {
			Assert::AreEqual(question.GetStudentAnswers()[i].first, expected_student_answers[i].first);
			Assert::AreEqual(question.GetStudentAnswers()[i].second, expected_student_answers[i].second);
		}
		Assert::AreEqual(question.GetCurrentScore(), 5.0);
	}

	//Any answer will be right in this case
	TEST_METHOD(SubmitSingleAnswerNotCareAboutRelativeOrAbsoluteError) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("432690930");
		question.SetAvailablePoints("5,3,1");
		question.SetPermittedAbsoluteError(-0.37);
		question.SetPermittedRelativeError(-2);

		vector<pair<string, bool>> expected_student_answers;
		expected_student_answers.push_back(pair<string, bool>("-0.328957", true));

		Assert::IsTrue(question.SubmitStudentAnswer("-0.328957"));
		Assert::AreEqual(question.GetStudentAnswers().size(), expected_student_answers.size());
		for (unsigned i = 0; i < expected_student_answers.size(); ++i) {
			Assert::AreEqual(question.GetStudentAnswers()[i].first, expected_student_answers[i].first);
			Assert::AreEqual(question.GetStudentAnswers()[i].second, expected_student_answers[i].second);
		}
		Assert::AreEqual(question.GetCurrentScore(), 5.0);
	}

	TEST_METHOD(SubmitSingleAnswerCareAboutBothAbsoluteAndRelativeErrorAndHaveTooMuchAbsoluteError) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("-21489.349");
		question.SetAvailablePoints("5,3,1");
		question.SetPermittedAbsoluteError(19.49);
		question.SetPermittedRelativeError(0.001);

		vector<pair<string, bool>> expected_student_answers;
		expected_student_answers.push_back(pair<string, bool>("-21469.8505", false));

		Assert::IsFalse(question.SubmitStudentAnswer("-21469.8505"));
		Assert::AreEqual(question.GetStudentAnswers().size(), expected_student_answers.size());
		for (unsigned i = 0; i < expected_student_answers.size(); ++i) {
			Assert::AreEqual(question.GetStudentAnswers()[i].first, expected_student_answers[i].first);
			Assert::AreEqual(question.GetStudentAnswers()[i].second, expected_student_answers[i].second);
		}
		Assert::AreEqual(question.GetCurrentScore(), 0.0);
	}

	TEST_METHOD(SubmitSingleAnswerCareAboutBothAbsoluteAndRelativeErrorAndHaveTooMuchRelativeError) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("1000.0");
		question.SetAvailablePoints("5,3,1");
		question.SetPermittedAbsoluteError(10.0);
		question.SetPermittedRelativeError(0.0099);

		vector<pair<string, bool>> expected_student_answers;
		expected_student_answers.push_back(pair<string, bool>("1009.999", false));

		Assert::IsFalse(question.SubmitStudentAnswer("1009.999"));
		Assert::AreEqual(question.GetStudentAnswers().size(), expected_student_answers.size());
		for (unsigned i = 0; i < expected_student_answers.size(); ++i) {
			Assert::AreEqual(question.GetStudentAnswers()[i].first, expected_student_answers[i].first);
			Assert::AreEqual(question.GetStudentAnswers()[i].second, expected_student_answers[i].second);
		}
		Assert::AreEqual(question.GetCurrentScore(), 0.0);
	}

	TEST_METHOD(SubmitSingleAnswerCareAboutBothAbsoluteAndRelativeErrorAndHaveTooMuchOfBoth) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("-0.000218");
		question.SetAvailablePoints("5,3,1");
		question.SetPermittedAbsoluteError(0.000001);
		question.SetPermittedRelativeError(0.00499);

		vector<pair<string, bool>> expected_student_answers;
		expected_student_answers.push_back(pair<string, bool>("-0.00021691", false));

		Assert::IsFalse(question.SubmitStudentAnswer("-0.00021691"));
		Assert::AreEqual(question.GetStudentAnswers().size(), expected_student_answers.size());
		for (unsigned i = 0; i < expected_student_answers.size(); ++i) {
			Assert::AreEqual(question.GetStudentAnswers()[i].first, expected_student_answers[i].first);
			Assert::AreEqual(question.GetStudentAnswers()[i].second, expected_student_answers[i].second);
		}
		Assert::AreEqual(question.GetCurrentScore(), 0.0);
	}

	TEST_METHOD(SubmitSingleAnswerCareAboutAbsoluteErrorOnlyAndHaveTooMuch) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("0.000000001");
		question.SetAvailablePoints("5,3,1");
		question.SetPermittedAbsoluteError(0.0000000005);
		question.SetPermittedRelativeError(-293573948);

		vector<pair<string, bool>> expected_student_answers;
		expected_student_answers.push_back(pair<string, bool>("0.0000000016", false));

		Assert::IsFalse(question.SubmitStudentAnswer("0.0000000016"));
		Assert::AreEqual(question.GetStudentAnswers().size(), expected_student_answers.size());
		for (unsigned i = 0; i < expected_student_answers.size(); ++i) {
			Assert::AreEqual(question.GetStudentAnswers()[i].first, expected_student_answers[i].first);
			Assert::AreEqual(question.GetStudentAnswers()[i].second, expected_student_answers[i].second);
		}
		Assert::AreEqual(question.GetCurrentScore(), 0.0);
	}

	TEST_METHOD(SubmitSingleAnswerCareAboutRelativeErrorOnlyAndHaveTooMuch) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("8934956759948.5");
		question.SetAvailablePoints("5,3,1");
		question.SetPermittedAbsoluteError(-1);
		question.SetPermittedRelativeError(0.05);

		vector<pair<string, bool>> expected_student_answers;
		expected_student_answers.push_back(pair<string, bool>("9381704597946", false));

		Assert::IsFalse(question.SubmitStudentAnswer("9381704597946"));
		Assert::AreEqual(question.GetStudentAnswers().size(), expected_student_answers.size());
		for (unsigned i = 0; i < expected_student_answers.size(); ++i) {
			Assert::AreEqual(question.GetStudentAnswers()[i].first, expected_student_answers[i].first);
			Assert::AreEqual(question.GetStudentAnswers()[i].second, expected_student_answers[i].second);
		}
		Assert::AreEqual(question.GetCurrentScore(), 0.0);
	}

	TEST_METHOD(SubmitMultipleAnswers) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("100.0");
		question.SetAvailablePoints("5,4,3,2,1");
		question.SetPermittedAbsoluteError(5.0);
		question.SetPermittedRelativeError(0.05);

		vector<pair<string, bool>> expected_student_answers;
		expected_student_answers.push_back(pair<string, bool>("9381704597946", false));
		expected_student_answers.push_back(pair<string, bool>("101.54893489", true));
		expected_student_answers.push_back(pair<string, bool>("95", true));
		expected_student_answers.push_back(pair<string, bool>("105.0", true));
		expected_student_answers.push_back(pair<string, bool>("94.999", false));


		Assert::IsFalse(question.SubmitStudentAnswer("9381704597946"));
		Assert::IsTrue(question.SubmitStudentAnswer("101.54893489"));
		Assert::IsTrue(question.SubmitStudentAnswer("95"));
		Assert::IsTrue(question.SubmitStudentAnswer("105.0"));
		Assert::IsFalse(question.SubmitStudentAnswer("94.999"));

		Assert::AreEqual(question.GetStudentAnswers().size(), expected_student_answers.size());
		for (unsigned i = 0; i < expected_student_answers.size(); ++i) {
			Assert::AreEqual(question.GetStudentAnswers()[i].first, expected_student_answers[i].first);
			Assert::AreEqual(question.GetStudentAnswers()[i].second, expected_student_answers[i].second);
		}
		Assert::AreEqual(question.GetCurrentScore(), 4.0);
	}

	TEST_METHOD(SubmitMultipleAnswersRanOutOfAttempts) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("100.0");
		question.SetAvailablePoints("5,3");
		question.SetPermittedAbsoluteError(5.0);
		question.SetPermittedRelativeError(0.05);

		vector<pair<string, bool>> expected_student_answers;
		expected_student_answers.push_back(pair<string, bool>("9381704597946", false));
		expected_student_answers.push_back(pair<string, bool>("94.999", false));
		expected_student_answers.push_back(pair<string, bool>("101.54893489", true));
		expected_student_answers.push_back(pair<string, bool>("95", true));
		expected_student_answers.push_back(pair<string, bool>("105.0", true));


		Assert::IsFalse(question.SubmitStudentAnswer("9381704597946"));
		Assert::IsFalse(question.SubmitStudentAnswer("94.999"));
		Assert::IsTrue(question.SubmitStudentAnswer("101.54893489"));
		Assert::IsTrue(question.SubmitStudentAnswer("95"));
		Assert::IsTrue(question.SubmitStudentAnswer("105.0"));

		Assert::AreEqual(question.GetStudentAnswers().size(), expected_student_answers.size());
		for (unsigned i = 0; i < expected_student_answers.size(); ++i) {
			Assert::AreEqual(question.GetStudentAnswers()[i].first, expected_student_answers[i].first);
			Assert::AreEqual(question.GetStudentAnswers()[i].second, expected_student_answers[i].second);
		}
		Assert::AreEqual(question.GetCurrentScore(), 0.0);
	}

	TEST_METHOD(ClearStudentAnswerWhenThereAreNone) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("5");
		question.ClearStudentAnswers();
		Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
	}

	TEST_METHOD(ClearStudentAnswersWhenThereAreTwo) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("5");
		question.SubmitStudentAnswer("6");
		question.SubmitStudentAnswer("5");
		question.ClearStudentAnswers();
		Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
	}

	TEST_METHOD(ClearStudentAnswersAndAddNewOne) {
		NumericalQuestion question(1);
		question.AddCorrectAnswer("2.0");
		question.SubmitStudentAnswer("2.0");
		question.SubmitStudentAnswer("3.0");
		question.ClearStudentAnswers();
		question.SubmitStudentAnswer("2.0");
		Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)1);
		Assert::AreEqual(question.GetStudentAnswers()[0].first, (string)"2.0");
		Assert::IsTrue(question.GetStudentAnswers()[0].second);
	}

	TEST_METHOD(FailToSetAvailablePointsEmptyString) {
		NumericalQuestion question(1);
		question.SetAvailablePoints("");
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
	}

	TEST_METHOD(FailToSetAvailablePointsCommaOnly) {
		NumericalQuestion question(1);
		question.SetAvailablePoints(",");
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
	}

	TEST_METHOD(FailToSetAvailablePointsDoubleComma) {
		NumericalQuestion question(1);
		question.SetAvailablePoints("5,4,3,2,,1");
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
	}

	TEST_METHOD(FailToSetAvailablePointsContainsSpaces) {
		NumericalQuestion question(1);
		question.SetAvailablePoints("10, 8, 6, 4, 2");
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
	}

	TEST_METHOD(FailToSetAvailablePointsTwoPeriods) {
		NumericalQuestion question(1);
		question.SetAvailablePoints("10, 5.5, 6.2, 4, 2..1");
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
	}

	TEST_METHOD(FailToFailToSetAvailablePointsContainsLetter) {
		NumericalQuestion question(1);
		question.SetAvailablePoints("5,3,1a");
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
	}

	TEST_METHOD(FailToSetAvailablePointsContainsSymbol) {
		NumericalQuestion question(1);
		question.SetAvailablePoints("5!,3,2");
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
	}

	TEST_METHOD(FailToSetAvailablePointsScoresNotDescendingOrder) {
		NumericalQuestion question(1);
		question.SetAvailablePoints("10,9,8,7,6,7,4,3,2,1");
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
	}

	TEST_METHOD(FailToSetAvailablePointsScoresAscendingOrder) {
		NumericalQuestion question(1);
		question.SetAvailablePoints("0.1,0.2,0.3,0.4,0.5");
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
		Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
	}

	TEST_METHOD(SetAvailablePointsOneAttemptAllowed) {
		NumericalQuestion question(1);
		question.SetAvailablePoints("5");
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)1);
		Assert::AreEqual(question.GetAvailablePoints()[0], 5.0);
		Assert::AreEqual(question.GetMaxPossibleScore(), 5.0);
	}

	TEST_METHOD(SetAvailablePointsFiveAttemptsAllowed) {
		NumericalQuestion question(1);
		question.SetAvailablePoints("10,10,8,5,3");
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)5);
		Assert::AreEqual(question.GetAvailablePoints()[0], 10.0);
		Assert::AreEqual(question.GetAvailablePoints()[1], 10.0);
		Assert::AreEqual(question.GetAvailablePoints()[2], 8.0);
		Assert::AreEqual(question.GetAvailablePoints()[3], 5.0);
		Assert::AreEqual(question.GetAvailablePoints()[4], 3.0);
		Assert::AreEqual(question.GetMaxPossibleScore(), 10.0);
	}

	TEST_METHOD(SetAvailablePointsDecimalValues) {
		NumericalQuestion question(1);
		question.SetAvailablePoints("1.5,0.75,0.5,0.25");
		Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)4);
		Assert::AreEqual(question.GetAvailablePoints()[0], 1.5);
		Assert::AreEqual(question.GetAvailablePoints()[1], 0.75);
		Assert::AreEqual(question.GetAvailablePoints()[2], 0.5);
		Assert::AreEqual(question.GetAvailablePoints()[3], 0.25);
		Assert::AreEqual(question.GetMaxPossibleScore(), 1.5);
	}

	TEST_METHOD(TwoQuestionsNotSameIfDifferentQuestionText) {
		NumericalQuestion first_question(1, "apples");
		NumericalQuestion second_question(1, "oranges");
		Assert::IsFalse(first_question == second_question);
	}

	TEST_METHOD(TwoQuestionsDifferentIfDifferentQuestionText) {
		NumericalQuestion first_question(1, "apples");
		NumericalQuestion second_question(1, "oranges");
		Assert::IsTrue(first_question != second_question);
	}

	TEST_METHOD(TwoQuestionsNotSameIfDifferentCurrentScore) {
		NumericalQuestion first_question(1, "same");
		first_question.SetAvailablePoints("12,11,10,8,5,3");
		first_question.AddCorrectAnswer("5.0");
		first_question.SubmitStudentAnswer("100.0");
		first_question.SubmitStudentAnswer("5.0");
		NumericalQuestion second_question(1, "same");
		second_question.SetAvailablePoints("12,10.5,10,8,5,3");
		second_question.AddCorrectAnswer("5.0");
		second_question.SubmitStudentAnswer("100.0");
		second_question.SubmitStudentAnswer("5.0");
		Assert::IsFalse(first_question == second_question);
	}

	TEST_METHOD(TwoQuestionsDifferentIfDifferentCurrentScore) {
		NumericalQuestion first_question(1, "same");
		first_question.SetAvailablePoints("12,11,10,8,5,3");
		first_question.AddCorrectAnswer("5.0");
		first_question.SubmitStudentAnswer("100.0");
		first_question.SubmitStudentAnswer("5.0");
		NumericalQuestion second_question(1, "same");
		second_question.SetAvailablePoints("12,10.5,10,8,5,3");
		second_question.AddCorrectAnswer("5.0");
		second_question.SubmitStudentAnswer("100.0");
		second_question.SubmitStudentAnswer("5.0");
		Assert::IsTrue(first_question != second_question);
	}

	TEST_METHOD(TwoQuestionsNotSameIfDifferentMaxPossibleScore) {
		NumericalQuestion first_question(1, "same");
		first_question.SetAvailablePoints("12,11,10,8,5,3");
		first_question.AddCorrectAnswer("5.0");
		first_question.SubmitStudentAnswer("100.0");
		NumericalQuestion second_question(1, "same");
		second_question.SetAvailablePoints("13,10.5,10,8,5,3");
		second_question.AddCorrectAnswer("5.0");
		second_question.SubmitStudentAnswer("100.0");
		Assert::IsFalse(first_question == second_question);
	}

	TEST_METHOD(TwoQuestionsDifferentIfDifferentMaxPossibleScore) {
		NumericalQuestion first_question(1, "same");
		first_question.SetAvailablePoints("12,11,10,8,5,3");
		first_question.AddCorrectAnswer("5.0");
		first_question.SubmitStudentAnswer("100.0");
		NumericalQuestion second_question(1, "same");
		second_question.SetAvailablePoints("13,10.5,10,8,5,3");
		second_question.AddCorrectAnswer("5.0");
		second_question.SubmitStudentAnswer("100.0");
		Assert::IsTrue(first_question != second_question);
	}

	TEST_METHOD(TwoQuestionsNotSameIfDifferentQuestionNumber) {
		NumericalQuestion first_question(1, "same");
		NumericalQuestion second_question(2, "same");
		Assert::IsFalse(first_question == second_question);
	}

	TEST_METHOD(TwoQuestionsDifferentIfDifferentQuestionNumber) {
		NumericalQuestion first_question(1, "same");
		NumericalQuestion second_question(2, "same");
		Assert::IsTrue(first_question != second_question);
	}

	TEST_METHOD(TwoQuestionsNotSameIfDifferentMaxPermittedAbsoluteError) {
		NumericalQuestion first_question(1, "same");
		first_question.SetPermittedAbsoluteError(0.01);
		NumericalQuestion second_question(1, "same");
		second_question.SetPermittedAbsoluteError(0.011);
		Assert::IsFalse(first_question == second_question);
	}

	TEST_METHOD(TwoQuestionsDifferentIfDifferentMaxPermittedAbsoluteError) {
		NumericalQuestion first_question(1, "same");
		first_question.SetPermittedAbsoluteError(0.01);
		NumericalQuestion second_question(1, "same");
		second_question.SetPermittedAbsoluteError(0.011);
		Assert::IsTrue(first_question != second_question);
	}

	TEST_METHOD(TwoQuestionsNotSameIfDifferentMaxPermittedRelativeError) {
		NumericalQuestion first_question(1, "same");
		first_question.SetPermittedRelativeError(0.00001);
		NumericalQuestion second_question(1, "same");
		second_question.SetPermittedRelativeError(0.00000999999999);
		Assert::IsFalse(first_question == second_question);
	}

	TEST_METHOD(TwoQuestionsDifferentIfDifferentMaxPermittedRelativeError) {
		NumericalQuestion first_question(1, "same");
		first_question.SetPermittedRelativeError(0.00001);
		NumericalQuestion second_question(1, "same");
		second_question.SetPermittedRelativeError(0.00000999999999);
		Assert::IsTrue(first_question != second_question);
	}

	TEST_METHOD(TwoQuestionsNotSameIfDifferentLengthAvailablePointsDeque) {
		NumericalQuestion first_question(1, "same");
		first_question.SetAvailablePoints("5,4,3,2,1");
		NumericalQuestion second_question(1, "same");
		second_question.SetAvailablePoints("5,4,3,2");
		Assert::IsFalse(first_question == second_question);
	}

	TEST_METHOD(TwoQuestionsDifferentIfDifferentLengthAvailablePointsDeque) {
		NumericalQuestion first_question(1, "same");
		first_question.SetAvailablePoints("5,4,3,2,1");
		NumericalQuestion second_question(1, "same");
		second_question.SetAvailablePoints("5,4,3,2");
		Assert::IsTrue(first_question != second_question);
	}

	TEST_METHOD(TwoQuestionsNotSameIfDifferentAvailablePointsDeque) {
		NumericalQuestion first_question(1, "same");
		first_question.SetAvailablePoints("5,3,1");
		NumericalQuestion second_question(1, "same");
		second_question.SetAvailablePoints("5,3,0.95");
		Assert::IsFalse(first_question == second_question);
	}

	TEST_METHOD(TwoQuestionsDifferentIfDifferentAvailablePointsDeque) {
		NumericalQuestion first_question(1, "same");
		first_question.SetAvailablePoints("5,3,1");
		NumericalQuestion second_question(1, "same");
		second_question.SetAvailablePoints("5,3,0.95");
		Assert::IsTrue(first_question != second_question);
	}

	TEST_METHOD(TwoQuestionsNotSameIfDifferentLengthCorrectAnswersVector) {
		NumericalQuestion first_question(1, "same");
		first_question.AddCorrectAnswer("3");
		first_question.AddCorrectAnswer("3");
		first_question.AddCorrectAnswer("3");
		NumericalQuestion second_question(1, "same");
		second_question.AddCorrectAnswer("3");
		second_question.AddCorrectAnswer("3");
		Assert::IsFalse(first_question == second_question);
	}

	TEST_METHOD(TwoQuestionsDifferentIfDifferentLengthCorrectAnswersVector) {
		NumericalQuestion first_question(1, "same");
		first_question.AddCorrectAnswer("3");
		first_question.AddCorrectAnswer("3");
		first_question.AddCorrectAnswer("3");
		NumericalQuestion second_question(1, "same");
		second_question.AddCorrectAnswer("3");
		second_question.AddCorrectAnswer("3");
		Assert::IsTrue(first_question != second_question);
	}

	TEST_METHOD(TwoQuestionsNotSameIfDifferentCorrectAnswersVector) {
		NumericalQuestion first_question(1, "same");
		first_question.AddCorrectAnswer("1");
		first_question.AddCorrectAnswer("2");
		first_question.AddCorrectAnswer("3");
		NumericalQuestion second_question(1, "same");
		second_question.AddCorrectAnswer("1.5");
		second_question.AddCorrectAnswer("2");
		second_question.AddCorrectAnswer("3");
		Assert::IsFalse(first_question == second_question);
	}

	TEST_METHOD(TwoQuestionsDifferentIfDifferentCorrectAnswersVector) {
		NumericalQuestion first_question(1, "same");
		first_question.AddCorrectAnswer("1");
		first_question.AddCorrectAnswer("2");
		first_question.AddCorrectAnswer("3");
		NumericalQuestion second_question(1, "same");
		second_question.AddCorrectAnswer("1.5");
		second_question.AddCorrectAnswer("2");
		second_question.AddCorrectAnswer("3");
		Assert::IsTrue(first_question != second_question);
	}

	TEST_METHOD(TwoQuestionsNotSameIfDifferentLengthStudentAnswersVector) {
		NumericalQuestion first_question(1, "same");
		first_question.AddCorrectAnswer("3");
		first_question.SubmitStudentAnswer("3");
		NumericalQuestion second_question(1, "same");
		second_question.AddCorrectAnswer("3");
		Assert::IsFalse(first_question == second_question);
	}

	TEST_METHOD(TwoQuestionsDifferentIfDifferentLengthStudentAnswersVector) {
		NumericalQuestion first_question(1, "same");
		first_question.AddCorrectAnswer("3");
		first_question.SubmitStudentAnswer("3");
		NumericalQuestion second_question(1, "same");
		second_question.AddCorrectAnswer("3");
		Assert::IsTrue(first_question != second_question);
	}

	TEST_METHOD(TwoQuestionsNotSameIfDifferentStudentAnswersVector) {
		NumericalQuestion first_question(1, "same");
		first_question.AddCorrectAnswer("3");
		first_question.SubmitStudentAnswer("4");
		first_question.SubmitStudentAnswer("3");
		NumericalQuestion second_question(1, "same");
		second_question.AddCorrectAnswer("3");
		second_question.SubmitStudentAnswer("3.9");
		second_question.SubmitStudentAnswer("3");
		Assert::IsFalse(first_question == second_question);
	}

	TEST_METHOD(TwoQuestionsDifferentIfDifferentStudentAnswersVector) {
		NumericalQuestion first_question(1, "same");
		first_question.AddCorrectAnswer("3");
		first_question.SubmitStudentAnswer("4");
		first_question.SubmitStudentAnswer("3");
		NumericalQuestion second_question(1, "same");
		second_question.AddCorrectAnswer("3");
		second_question.SubmitStudentAnswer("3.9");
		second_question.SubmitStudentAnswer("3");
		Assert::IsTrue(first_question != second_question);
	}

	TEST_METHOD(QuestionSameAsItself) {
		NumericalQuestion question(1, "text");
		question.SetAvailablePoints("1.5,0.75,0.5,0.25");
		question.AddCorrectAnswer("5");
		question.AddCorrectAnswer("6");
		question.AddCorrectAnswer("7");
		question.SetPermittedAbsoluteError(0.1);
		question.SetPermittedRelativeError(0.02);
		question.SubmitStudentAnswer("10");
		question.SubmitStudentAnswer("5");
		Assert::IsTrue(question == question);
	}

	TEST_METHOD(QuestionNotDifferentFromItself) {
		NumericalQuestion question(1, "text");
		question.SetAvailablePoints("1.5,0.75,0.5,0.25");
		question.AddCorrectAnswer("5");
		question.AddCorrectAnswer("6");
		question.AddCorrectAnswer("7");
		question.SetPermittedAbsoluteError(0.1);
		question.SetPermittedRelativeError(0.02);
		question.SubmitStudentAnswer("10");
		question.SubmitStudentAnswer("5");
		Assert::IsFalse(question != question);
	}

	TEST_METHOD(QuestionSameAsIdenticalQuestion) {
		NumericalQuestion first_question(1, "text");
		first_question.SetAvailablePoints("1.5,0.75,0.5,0.25");
		first_question.AddCorrectAnswer("5");
		first_question.AddCorrectAnswer("6");
		first_question.AddCorrectAnswer("7");
		first_question.SetPermittedAbsoluteError(0.1);
		first_question.SetPermittedRelativeError(0.02);
		first_question.SubmitStudentAnswer("10");
		first_question.SubmitStudentAnswer("5");

		NumericalQuestion second_question(1, "text");
		second_question.SetAvailablePoints("1.5,0.75,0.5,0.25");
		second_question.AddCorrectAnswer("5");
		second_question.AddCorrectAnswer("6");
		second_question.AddCorrectAnswer("7");
		second_question.SetPermittedAbsoluteError(0.1);
		second_question.SetPermittedRelativeError(0.02);
		second_question.SubmitStudentAnswer("10");
		second_question.SubmitStudentAnswer("5");
		Assert::IsTrue(first_question == second_question);
	}

	TEST_METHOD(QuestionNotDifferentFromIdenticalQuestion) {
		NumericalQuestion first_question(1, "text");
		first_question.SetAvailablePoints("1.5,0.75,0.5,0.25");
		first_question.AddCorrectAnswer("5");
		first_question.AddCorrectAnswer("6");
		first_question.AddCorrectAnswer("7");
		first_question.SetPermittedAbsoluteError(0.1);
		first_question.SetPermittedRelativeError(0.02);
		first_question.SubmitStudentAnswer("10");
		first_question.SubmitStudentAnswer("5");

		NumericalQuestion second_question(1, "text");
		second_question.SetAvailablePoints("1.5,0.75,0.5,0.25");
		second_question.AddCorrectAnswer("5");
		second_question.AddCorrectAnswer("6");
		second_question.AddCorrectAnswer("7");
		second_question.SetPermittedAbsoluteError(0.1);
		second_question.SetPermittedRelativeError(0.02);
		second_question.SubmitStudentAnswer("10");
		second_question.SubmitStudentAnswer("5");
		Assert::IsFalse(first_question != second_question);
	}
	};

	//TEST_CLASS(QuestionKeyTests) {
	//public:
	//	TEST_METHOD(TwoQuestionKeysEqualIfSameQuestionIndex) {
	//		QuestionKey key_one(3, "apples");
	//		QuestionKey key_two(3, "oranges");
	//		Assert::IsTrue(key_one == key_two);
	//	}

	//	TEST_METHOD(TwoQuestionKeysNotDifferentIfSameQuestionIndex) {
	//		QuestionKey key_one(3, "apples");
	//		QuestionKey key_two(3, "oranges");
	//		Assert::IsFalse(key_one != key_two);
	//	}

	//	TEST_METHOD(TwoQuestionKeysEqualIfSameQuestionLabel) {
	//		QuestionKey key_one(347867845, "UY5848&878efy&4t");
	//		QuestionKey key_two(-17, "UY5848&878efy&4t");
	//		Assert::IsTrue(key_one == key_two);
	//	}

	//	TEST_METHOD(TwoQuestionKeysNotDifferentIfSameQuestionLabel) {
	//		QuestionKey key_one(347867845, "UY5848&878efy&4t");
	//		QuestionKey key_two(-17, "UY5848&878efy&4t");
	//		Assert::IsFalse(key_one != key_two);
	//	}

	//	TEST_METHOD(TwoQuestionKeysEqualIfSameQuestionIndexAndQuestionLabel) {
	//		QuestionKey key_one(57, "word");
	//		QuestionKey key_two(57, "word");
	//		Assert::IsTrue(key_one == key_two);
	//	}

	//	TEST_METHOD(TwoQuestionKeysNotDifferentIfSameSameQuestionIndexAndQuestionLabel) {
	//		QuestionKey key_one(57, "word");
	//		QuestionKey key_two(57, "word");
	//		Assert::IsFalse(key_one != key_two);
	//	}

	//	TEST_METHOD(TwoQuestionKeysNotEqualIfDifferentQuestionIndexAndQuestionLabel) {
	//		QuestionKey key_one(1, "banana");
	//		QuestionKey key_two(0, "bananna");
	//		Assert::IsFalse(key_one == key_two);
	//	}

	//	TEST_METHOD(TwoQuestionKeysDifferentIfIfDifferentQuestionIndexAndQuestionLabel) {
	//		QuestionKey key_one(1, "banana");
	//		QuestionKey key_two(0, "bananna");
	//		Assert::IsTrue(key_one != key_two);
	//	}
	//};

	TEST_CLASS(TestClassTests) {
public:
	TEST_METHOD(ConstructorEmptyStringName) {
		Test test("");
		Assert::AreEqual(test.GetNameOfTest(), (string)"");
		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
		Assert::AreEqual((int)test.GetAssignedQuestions().size(), 0);
		Assert::IsTrue(test.GetCurrentQuestion().expired());
		Assert::AreEqual(test.GetCurrentCategory(), (string)"");
		Assert::AreEqual(test.GetNextQuestionNumber(), 1);
	}

	TEST_METHOD(ConstructorOneCharacterStringName) {
		Test test("5");
		Assert::AreEqual(test.GetNameOfTest(), (string)"5");
		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
		Assert::AreEqual((int)test.GetAssignedQuestions().size(), 0);
		Assert::IsTrue(test.GetCurrentQuestion().expired());
		Assert::AreEqual(test.GetCurrentCategory(), (string)"");
		Assert::AreEqual(test.GetNextQuestionNumber(), 1);
	}

	TEST_METHOD(Constructor) {
		Test test("Ag2*UGHr78ys589shru7y*(th7a8grui");
		Assert::AreEqual(test.GetNameOfTest(), (string)"Ag2*UGHr78ys589shru7y*(th7a8grui");
		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
		Assert::AreEqual((int)test.GetAssignedQuestions().size(), 0);
		Assert::IsTrue(test.GetCurrentQuestion().expired());
		Assert::AreEqual(test.GetCurrentCategory(), (string)"");
		Assert::AreEqual(test.GetNextQuestionNumber(), 1);
	}

	TEST_METHOD(AddShortAnswerAndNumericalQuestions) {
		Test test("test");
		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		NumericalQuestion question_one(1, "What is 5 + 3?");
		ShortAnswerQuestion question_two(2, "What is George Washington's name?");
		NumericalQuestion question_three(3, "What is 3 times 7?");

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)3);

		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[0]) == question_one);
		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetUnassignedQuestions()[1]) == question_two);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[2]) == question_three);
	}

	TEST_METHOD(CreateQuestionCategories) {
		Test test("test");

		test.CreateQuestionCategory("History");
		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("Bananas");

		Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)3);
		Assert::IsTrue(test.GetAssignedQuestions()[0] == tuple<string, int, vector<shared_ptr<Question>>>("History", -1, vector<shared_ptr<Question>>()));
		Assert::IsTrue(test.GetAssignedQuestions()[1] == tuple<string, int, vector<shared_ptr<Question>>>("Math", -1, vector<shared_ptr<Question>>()));
		Assert::IsTrue(test.GetAssignedQuestions()[2] == tuple<string, int, vector<shared_ptr<Question>>>("Bananas", -1, vector<shared_ptr<Question>>()));
	}

	TEST_METHOD(CreateQuestionCategoriesAndCannotHaveTwoCategoriesWithSameName) {
		Test test("test");

		test.CreateQuestionCategory("History");
		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("Bananas");
		test.CreateQuestionCategory("Math");

		Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)3);
		Assert::IsTrue(test.GetAssignedQuestions()[0] == tuple<string, int, vector<shared_ptr<Question>>>("History", -1, vector<shared_ptr<Question>>()));
		Assert::IsTrue(test.GetAssignedQuestions()[1] == tuple<string, int, vector<shared_ptr<Question>>>("Math", -1, vector<shared_ptr<Question>>()));
		Assert::IsTrue(test.GetAssignedQuestions()[2] == tuple<string, int, vector<shared_ptr<Question>>>("Bananas", -1, vector<shared_ptr<Question>>()));
	}

	TEST_METHOD(SelectQuestionInUnassignedQuestions) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		NumericalQuestion question(3, "What is 3 times 7?");

		test.SelectCurrentQuestion("3");
		shared_ptr<NumericalQuestion> current_question = dynamic_pointer_cast<NumericalQuestion>(test.GetCurrentQuestion().lock());
		Assert::IsTrue(*current_question == question);
		Assert::AreEqual(test.GetCurrentCategory(), (string)"");
	}

	TEST_METHOD(FailToSelectQuestionThatDoesNotExist) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.SelectCurrentQuestion("0");
		NumericalQuestion question(3, "What is 3 times 7?");

		shared_ptr<NumericalQuestion> current_question = dynamic_pointer_cast<NumericalQuestion>(test.GetCurrentQuestion().lock());
		Assert::IsTrue(*current_question == question);
		Assert::AreEqual(test.GetCurrentCategory(), (string)"");
	}

	TEST_METHOD(FailToSelectOtherQuestionThatDoesNotExist) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.SelectCurrentQuestion("2");
		ShortAnswerQuestion question(2, "What is George Washington's name?");
		test.SelectCurrentQuestion("24");

		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetCurrentQuestion().lock()) == question);
		Assert::AreEqual(test.GetCurrentCategory(), (string)"");
	}

	TEST_METHOD(FailToSelectQuestionBecauseStringIsNotNumerical) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.SelectCurrentQuestion("2");
		ShortAnswerQuestion question(2, "What is George Washington's name?");
		test.SelectCurrentQuestion("abc");

		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetCurrentQuestion().lock()) == question);
		Assert::AreEqual(test.GetCurrentCategory(), (string)"");
	}

	TEST_METHOD(FailToSelectQuestionBecauseStringContainsSymbol) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.SelectCurrentQuestion("2");
		ShortAnswerQuestion question(2, "What is George Washington's name?");
		test.SelectCurrentQuestion("1!");

		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetCurrentQuestion().lock()) == question);
		Assert::AreEqual(test.GetCurrentCategory(), (string)"");
	}

	TEST_METHOD(FailToSelectQuestionBecauseStringIsDecimal) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.SelectCurrentQuestion("2");
		ShortAnswerQuestion question(2, "What is George Washington's name?");
		test.SelectCurrentQuestion("1.5");

		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetCurrentQuestion().lock()) == question);
		Assert::AreEqual(test.GetCurrentCategory(), (string)"");
	}

	TEST_METHOD(FailToSelectQuestionBecauseStringIsEmpty) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.SelectCurrentQuestion("2");
		ShortAnswerQuestion question(2, "What is George Washington's name?");
		test.SelectCurrentQuestion("");

		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetCurrentQuestion().lock()) == question);
		Assert::AreEqual(test.GetCurrentCategory(), (string)"");
	}

	TEST_METHOD(FailToSelectQuestionBecauseStringIsSpace) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.SelectCurrentQuestion("2");
		ShortAnswerQuestion question(2, "What is George Washington's name?");
		test.SelectCurrentQuestion(" ");

		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetCurrentQuestion().lock()) == question);
		Assert::AreEqual(test.GetCurrentCategory(), (string)"");
	}

	TEST_METHOD(FailToSelectQuestionBecauseStringContainsSpace) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.SelectCurrentQuestion("2");
		ShortAnswerQuestion question(2, "What is George Washington's name?");
		test.SelectCurrentQuestion(" 3");

		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetCurrentQuestion().lock()) == question);
		Assert::AreEqual(test.GetCurrentCategory(), (string)"");
	}

	TEST_METHOD(FailToSelectQuestionBecauseStringContainsPeriod) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.SelectCurrentQuestion("2");
		ShortAnswerQuestion question(2, "What is George Washington's name?");
		test.SelectCurrentQuestion("1.");

		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetCurrentQuestion().lock()) == question);
		Assert::AreEqual(test.GetCurrentCategory(), (string)"");
	}

	TEST_METHOD(AddQuestionsToCategoriesFromUnassigned) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("History");

		test.SelectCurrentQuestion("1");
		test.AddCurrentQuestionToCategory("Math");
		Assert::AreEqual(test.GetCurrentCategory(), (string)"Math");

		test.SelectCurrentQuestion("2");
		test.AddCurrentQuestionToCategory("History");
		Assert::AreEqual(test.GetCurrentCategory(), (string)"History");

		test.SelectCurrentQuestion("3");
		test.AddCurrentQuestionToCategory("Math");
		Assert::AreEqual(test.GetCurrentCategory(), (string)"Math");

		NumericalQuestion question_one(1, "What is 5 + 3?");
		ShortAnswerQuestion question_two(2, "What is George Washington's name?");
		NumericalQuestion question_three(3, "What is 3 times 7?");

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
		Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)2);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[1]) == question_three);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);
	}

	TEST_METHOD(FailToAddQuestionToCategoryBecauseItWasDeleted) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("History");

		test.SelectCurrentQuestion("2");
		test.DeleteCurrentQuestion();
		test.AddCurrentQuestionToCategory("History");

		NumericalQuestion question_one(1, "What is 5 + 3?");
		NumericalQuestion question_three(3, "What is 3 times 7?");

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)2);
		Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);
		Assert::AreEqual(test.GetCurrentCategory(), (string)"");
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[0]) == question_one);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[1]) == question_three);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)0);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)0);
	}

	TEST_METHOD(SelectAssignedQuestion) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("History");

		test.SelectCurrentQuestion("1");
		test.AddCurrentQuestionToCategory("Math");
		test.SelectCurrentQuestion("2");
		test.AddCurrentQuestionToCategory("History");
		test.SelectCurrentQuestion("3");
		test.AddCurrentQuestionToCategory("Math");

		ShortAnswerQuestion question_two(2, "What is George Washington's name?");

		test.SelectCurrentQuestion("2");
		Assert::AreEqual(test.GetCurrentCategory(), (string)"History");
		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetCurrentQuestion().lock()) == question_two);
	}

	TEST_METHOD(MoveQuestionFromOneCategoryToAnother) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("History");

		test.SelectCurrentQuestion("1");
		test.AddCurrentQuestionToCategory("Math");
		test.SelectCurrentQuestion("2");
		test.AddCurrentQuestionToCategory("History");
		test.SelectCurrentQuestion("3");
		test.AddCurrentQuestionToCategory("Math");

		test.SelectCurrentQuestion("2");
		test.AddCurrentQuestionToCategory("Math");

		ShortAnswerQuestion question_two(2, "What is George Washington's name?");

		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)0);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)3);
		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[0])[2]) == question_two);
		Assert::AreEqual(test.GetCurrentCategory(), (string)"Math");
	}

	TEST_METHOD(MovingQuestionThatIsAlreadyInCategoryDoesNothing) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("History");

		test.SelectCurrentQuestion("1");
		test.AddCurrentQuestionToCategory("Math");

		test.SelectCurrentQuestion("2");
		test.AddCurrentQuestionToCategory("History");

		test.SelectCurrentQuestion("3");
		test.AddCurrentQuestionToCategory("Math");

		test.SelectCurrentQuestion("3");
		test.AddCurrentQuestionToCategory("Math");

		NumericalQuestion question_one(1, "What is 5 + 3?");
		ShortAnswerQuestion question_two(2, "What is George Washington's name?");
		NumericalQuestion question_three(3, "What is 3 times 7?");

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
		Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);
		Assert::AreEqual(test.GetCurrentCategory(), (string)"Math");

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)2);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[1]) == question_three);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
	}

	TEST_METHOD(CannotAddQuestionToCategoryIfNoCurrentQuestion) {
		Test test("test");

		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("History");

		test.SelectCurrentQuestion("1");
		test.AddCurrentQuestionToCategory("Math");

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)0);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)0);
	}

	TEST_METHOD(CannotAddQuestionToNonexistantCategory) {
		Test test("test");
		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.CreateQuestionCategory("Category");
		test.SelectCurrentQuestion("1");
		test.AddCurrentQuestionToCategory("Does not exist");

		NumericalQuestion question_one(1, "What is 5 + 3?");
		ShortAnswerQuestion question_two(2, "What is George Washington's name?");
		NumericalQuestion question_three(3, "What is 3 times 7?");

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)3);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[0]) == question_one);
		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetUnassignedQuestions()[1]) == question_two);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[2]) == question_three);

		Assert::AreEqual(test.GetCurrentCategory(), (string)"");
		Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)1);
		Assert::IsTrue(test.GetAssignedQuestions()[0] == tuple<string, int, vector<shared_ptr<Question>>>("Category", -1, vector<shared_ptr<Question>>()));
	}

	TEST_METHOD(CannotRemoveQuestionFromCategoryIfNoCurrentQuestion) {
		Test test("test");

		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("History");

		test.SelectCurrentQuestion("1");
		test.RemoveCurrentQuestionFromCategory();

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
		Assert::AreEqual(test.GetCurrentCategory(), (string)"");
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)0);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)0);
	}

	TEST_METHOD(CannotRemoveQuestionFromCategoryIfNotInCategory) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("History");

		test.SelectCurrentQuestion("2");
		test.RemoveCurrentQuestionFromCategory();

		NumericalQuestion question_one(1, "What is 5 + 3?");
		ShortAnswerQuestion question_two(2, "What is George Washington's name?");
		NumericalQuestion question_three(3, "What is 3 times 7?");

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)3);
		Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)0);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)0);

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)3);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[0]) == question_one);
		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetUnassignedQuestions()[1]) == question_two);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[2]) == question_three);
	}

	TEST_METHOD(CannotRemoveQuestionFromCategoryIfQuestionWasDeleted) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("History");

		test.SelectCurrentQuestion("1");
		test.AddCurrentQuestionToCategory("Math");

		test.SelectCurrentQuestion("2");
		test.AddCurrentQuestionToCategory("History");

		test.SelectCurrentQuestion("3");
		test.AddCurrentQuestionToCategory("Math");

		test.SelectCurrentQuestion("1");
		test.DeleteCurrentQuestion();
		test.RemoveCurrentQuestionFromCategory();

		ShortAnswerQuestion question_two(2, "What is George Washington's name?");
		NumericalQuestion question_three(3, "What is 3 times 7?");

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
		Assert::AreEqual(test.GetCurrentCategory(), (string)"");

		Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)1);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_three);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);
	}

	TEST_METHOD(RemoveQuestionFromCategory) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("History");

		test.SelectCurrentQuestion("1");
		test.AddCurrentQuestionToCategory("Math");

		test.SelectCurrentQuestion("2");
		test.AddCurrentQuestionToCategory("History");

		test.SelectCurrentQuestion("3");
		test.AddCurrentQuestionToCategory("Math");
		test.RemoveCurrentQuestionFromCategory();

		NumericalQuestion question_one(1, "What is 5 + 3?");
		ShortAnswerQuestion question_two(2, "What is George Washington's name?");
		NumericalQuestion question_three(3, "What is 3 times 7?");

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)1);
		Assert::AreEqual(test.GetCurrentCategory(), (string)"");
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[0]) == question_three);

		Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)1);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);
	}

	TEST_METHOD(RemoveQuestionsFromCategories) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("History");

		test.SelectCurrentQuestion("1");
		test.AddCurrentQuestionToCategory("Math");

		test.SelectCurrentQuestion("2");
		test.AddCurrentQuestionToCategory("History");

		test.SelectCurrentQuestion("3");
		test.AddCurrentQuestionToCategory("Math");
		test.RemoveCurrentQuestionFromCategory();

		test.SelectCurrentQuestion("1");
		test.RemoveCurrentQuestionFromCategory();

		test.SelectCurrentQuestion("2");
		test.RemoveCurrentQuestionFromCategory();

		NumericalQuestion question_one(1, "What is 5 + 3?");
		ShortAnswerQuestion question_two(2, "What is George Washington's name?");
		NumericalQuestion question_three(3, "What is 3 times 7?");

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)3);
		Assert::AreEqual(test.GetCurrentCategory(), (string)"");
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[0]) == question_three);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[1]) == question_one);
		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetUnassignedQuestions()[2]) == question_two);

		Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)0);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)0);
	}

	TEST_METHOD(CannotDeleteQuestionIfNoCurrentQuestion) {
		Test test("test");

		test.DeleteCurrentQuestion();

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
		Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)0);
		Assert::AreEqual(test.GetCurrentCategory(), (string)"");
	}

	TEST_METHOD(DeleteUnassignedQuestion) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.SelectCurrentQuestion("1");
		test.DeleteCurrentQuestion();

		ShortAnswerQuestion question_two(2, "What is George Washington's name?");
		NumericalQuestion question_three(3, "What is 3 times 7?");

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)2);
		Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)0);

		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetUnassignedQuestions()[0]) == question_two);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[1]) == question_three);

		Assert::AreEqual(test.GetCurrentCategory(), (string)"");
	}

	TEST_METHOD(DeleteQuestionInAssignedQuestions) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("History");

		test.SelectCurrentQuestion("1");
		test.AddCurrentQuestionToCategory("Math");
		Assert::AreEqual(test.GetCurrentCategory(), (string)"Math");

		test.SelectCurrentQuestion("2");
		test.AddCurrentQuestionToCategory("History");
		Assert::AreEqual(test.GetCurrentCategory(), (string)"History");

		test.SelectCurrentQuestion("3");
		test.AddCurrentQuestionToCategory("Math");
		Assert::AreEqual(test.GetCurrentCategory(), (string)"Math");

		NumericalQuestion question_one(1, "What is 5 + 3?");
		ShortAnswerQuestion question_two(2, "What is George Washington's name?");

		test.DeleteCurrentQuestion();

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
		Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)1);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);

		Assert::AreEqual(test.GetCurrentCategory(), (string)"");
	}

	TEST_METHOD(DeleteNonexistentCategory) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("History");

		test.SelectCurrentQuestion("1");
		test.AddCurrentQuestionToCategory("Math");

		test.SelectCurrentQuestion("2");
		test.AddCurrentQuestionToCategory("History");

		test.SelectCurrentQuestion("3");
		test.AddCurrentQuestionToCategory("Math");

		test.DeleteQuestionCategory("Does not exist");

		NumericalQuestion question_one(1, "What is 5 + 3?");
		ShortAnswerQuestion question_two(2, "What is George Washington's name?");
		NumericalQuestion question_three(3, "What is 3 times 7?");

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
		Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)2);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[1]) == question_three);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);

		Assert::AreEqual(test.GetCurrentCategory(), (string)"Math");
	}

	TEST_METHOD(DeleteCategoryContainingNoQuestions) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("History");
		test.CreateQuestionCategory("Empty");

		test.SelectCurrentQuestion("1");
		test.AddCurrentQuestionToCategory("Math");

		test.SelectCurrentQuestion("2");
		test.AddCurrentQuestionToCategory("History");

		test.SelectCurrentQuestion("3");
		test.AddCurrentQuestionToCategory("Math");

		test.DeleteQuestionCategory("Empty");

		NumericalQuestion question_one(1, "What is 5 + 3?");
		ShortAnswerQuestion question_two(2, "What is George Washington's name?");
		NumericalQuestion question_three(3, "What is 3 times 7?");

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
		Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)2);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[1]) == question_three);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);

		Assert::AreEqual(test.GetCurrentCategory(), (string)"Math");
	}

	TEST_METHOD(DeleteCategoryContainingQuestions) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("History");

		test.SelectCurrentQuestion("1");
		test.AddCurrentQuestionToCategory("Math");

		test.SelectCurrentQuestion("2");
		test.AddCurrentQuestionToCategory("History");

		test.SelectCurrentQuestion("3");
		test.AddCurrentQuestionToCategory("Math");

		test.DeleteQuestionCategory("History");

		NumericalQuestion question_one(1, "What is 5 + 3?");
		ShortAnswerQuestion question_two(2, "What is George Washington's name?");
		NumericalQuestion question_three(3, "What is 3 times 7?");

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)1);
		Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)1);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)2);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[1]) == question_three);

		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(test.GetUnassignedQuestions()[0]) == question_two);

		Assert::AreEqual(test.GetCurrentCategory(), (string)"Math");
	}

	TEST_METHOD(DeleteCategoryContainingCurrentQuestion) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("History");

		test.SelectCurrentQuestion("1");
		test.AddCurrentQuestionToCategory("Math");

		test.SelectCurrentQuestion("2");
		test.AddCurrentQuestionToCategory("History");

		test.SelectCurrentQuestion("3");
		test.AddCurrentQuestionToCategory("Math");

		test.DeleteQuestionCategory("Math");

		NumericalQuestion question_one(1, "What is 5 + 3?");
		ShortAnswerQuestion question_two(2, "What is George Washington's name?");
		NumericalQuestion question_three(3, "What is 3 times 7?");

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)2);
		Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)1);

		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[0]) == question_one);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(test.GetUnassignedQuestions()[1]) == question_three);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"History");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)1);
		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_two);

		Assert::AreEqual(test.GetCurrentCategory(), (string)"");
	}

	TEST_METHOD(CannotSwitchOrderOfCategoriesBecauseFirstCategoryDoesNotExist) {
		Test test("test");

		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("History");
		test.CreateQuestionCategory("Biology");

		test.SwitchOrderOfCategories("Chemistry", "History");

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
		Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)3);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)0);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)0);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[2]), (string)"Biology");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[2]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[2]).size(), (size_t)0);

		Assert::AreEqual(test.GetCurrentCategory(), (string)"");
	}

	TEST_METHOD(CannotSwitchOrderOfCategoriesBecauseSecondCategoryDoesNotExist) {
		Test test("test");

		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("History");
		test.CreateQuestionCategory("Biology");

		test.SwitchOrderOfCategories("History", "Chemistry");

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
		Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)3);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)0);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)0);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[2]), (string)"Biology");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[2]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[2]).size(), (size_t)0);

		Assert::AreEqual(test.GetCurrentCategory(), (string)"");
	}

	TEST_METHOD(CannotSwitchOrderOfCategoriesBecauseNeitherExists) {
		Test test("test");

		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("History");
		test.CreateQuestionCategory("Biology");

		test.SwitchOrderOfCategories("Literature", "Physics");

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
		Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)3);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)0);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)0);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[2]), (string)"Biology");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[2]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[2]).size(), (size_t)0);

		Assert::AreEqual(test.GetCurrentCategory(), (string)"");
	}

	TEST_METHOD(SwitchOrderOfTwoCategories) {
		Test test("test");

		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("History");
		test.CreateQuestionCategory("Biology");

		test.SwitchOrderOfCategories("Math", "Biology");

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
		Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)3);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Biology");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)0);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)0);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[2]), (string)"Math");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[2]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[2]).size(), (size_t)0);

		Assert::AreEqual(test.GetCurrentCategory(), (string)"");
	}

	TEST_METHOD(SwitchOrderOfTwoCategoriesContainingQuestions) {
		Test test("test");

		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("History");
		test.CreateQuestionCategory("Biology");

		test.AddNumericalQuestion("What is 5!?");
		test.AddCurrentQuestionToCategory("Math");
		test.AddShortAnswerQuestion("Who came first, Ivan the Great or Ivan the Terrible?");
		test.AddCurrentQuestionToCategory("History");
		test.AddShortAnswerQuestion("Which is thicker, a microtubule or a microfilament?");
		test.AddCurrentQuestionToCategory("Biology");

		NumericalQuestion question_one(1, "What is 5!?");
		ShortAnswerQuestion question_two(2, "Who came first, Ivan the Great or Ivan the Terrible?");
		ShortAnswerQuestion question_three(3, "Which is thicker, a microtubule or a microfilament?");

		test.SwitchOrderOfCategories("Math", "Biology");

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
		Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)3);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Biology");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)1);
		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_three);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[2]), (string)"Math");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[2]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[2]).size(), (size_t)1);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[2])[0]) == question_one);

		Assert::AreEqual(test.GetCurrentCategory(), (string)"Biology");
	}

	TEST_METHOD(FailToChangeNumberOfQuestionsToAskFromCategoryBecauseCategoryDoesNotExist) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("History");

		test.SelectCurrentQuestion("1");
		test.AddCurrentQuestionToCategory("Math");

		test.SelectCurrentQuestion("2");
		test.AddCurrentQuestionToCategory("History");

		test.SelectCurrentQuestion("3");
		test.AddCurrentQuestionToCategory("Math");

		test.ChangeNumberOfQuestionsToAskFromCategory("Literature", "3");

		NumericalQuestion question_one(1, "What is 5 + 3?");
		ShortAnswerQuestion question_two(2, "What is George Washington's name?");
		NumericalQuestion question_three(3, "What is 3 times 7?");

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
		Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)2);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[1]) == question_three);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);
	}

	TEST_METHOD(FailToChangeNumberOfQuestionsToAskFromCategoryBecauseNumberOfQuestionsStringEmpty) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("History");

		test.SelectCurrentQuestion("1");
		test.AddCurrentQuestionToCategory("Math");

		test.SelectCurrentQuestion("2");
		test.AddCurrentQuestionToCategory("History");

		test.SelectCurrentQuestion("3");
		test.AddCurrentQuestionToCategory("Math");

		test.ChangeNumberOfQuestionsToAskFromCategory("Math", "");

		NumericalQuestion question_one(1, "What is 5 + 3?");
		ShortAnswerQuestion question_two(2, "What is George Washington's name?");
		NumericalQuestion question_three(3, "What is 3 times 7?");

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
		Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)2);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[1]) == question_three);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);
	}

	TEST_METHOD(FailToChangeNumberOfQuestionsToAskFromCategoryBecauseNumberOfQuestionsStringIsSpace) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("History");

		test.SelectCurrentQuestion("1");
		test.AddCurrentQuestionToCategory("Math");

		test.SelectCurrentQuestion("2");
		test.AddCurrentQuestionToCategory("History");

		test.SelectCurrentQuestion("3");
		test.AddCurrentQuestionToCategory("Math");

		test.ChangeNumberOfQuestionsToAskFromCategory("Math", " ");

		NumericalQuestion question_one(1, "What is 5 + 3?");
		ShortAnswerQuestion question_two(2, "What is George Washington's name?");
		NumericalQuestion question_three(3, "What is 3 times 7?");

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
		Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)2);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[1]) == question_three);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);
	}

	TEST_METHOD(FailToChangeNumberOfQuestionsToAskFromCategoryBecauseNumberOfQuestionsStringNotANumber) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("History");

		test.SelectCurrentQuestion("1");
		test.AddCurrentQuestionToCategory("Math");

		test.SelectCurrentQuestion("2");
		test.AddCurrentQuestionToCategory("History");

		test.SelectCurrentQuestion("3");
		test.AddCurrentQuestionToCategory("Math");

		test.ChangeNumberOfQuestionsToAskFromCategory("Math", "UJHbueih7YT47yg#*(");

		NumericalQuestion question_one(1, "What is 5 + 3?");
		ShortAnswerQuestion question_two(2, "What is George Washington's name?");
		NumericalQuestion question_three(3, "What is 3 times 7?");

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
		Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)2);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[1]) == question_three);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);
	}

	TEST_METHOD(FailToChangeNumberOfQuestionsToAskFromCategoryBecauseNumberOfQuestionsStringIsDecimal) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("History");

		test.SelectCurrentQuestion("1");
		test.AddCurrentQuestionToCategory("Math");

		test.SelectCurrentQuestion("2");
		test.AddCurrentQuestionToCategory("History");

		test.SelectCurrentQuestion("3");
		test.AddCurrentQuestionToCategory("Math");

		test.ChangeNumberOfQuestionsToAskFromCategory("Math", "2.3");

		NumericalQuestion question_one(1, "What is 5 + 3?");
		ShortAnswerQuestion question_two(2, "What is George Washington's name?");
		NumericalQuestion question_three(3, "What is 3 times 7?");

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
		Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)2);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[1]) == question_three);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);
	}

	TEST_METHOD(FailToChangeNumberOfQuestionsToAskFromCategoryBecauseNumberOfQuestionsStringContainsLetter) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("History");

		test.SelectCurrentQuestion("1");
		test.AddCurrentQuestionToCategory("Math");

		test.SelectCurrentQuestion("2");
		test.AddCurrentQuestionToCategory("History");

		test.SelectCurrentQuestion("3");
		test.AddCurrentQuestionToCategory("Math");

		test.ChangeNumberOfQuestionsToAskFromCategory("Math", "812a");

		NumericalQuestion question_one(1, "What is 5 + 3?");
		ShortAnswerQuestion question_two(2, "What is George Washington's name?");
		NumericalQuestion question_three(3, "What is 3 times 7?");

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
		Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)2);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[1]) == question_three);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);
	}

	TEST_METHOD(ChangeNumberOfQuestionsToAskFromCategoryOnce) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("History");

		test.SelectCurrentQuestion("1");
		test.AddCurrentQuestionToCategory("Math");

		test.SelectCurrentQuestion("2");
		test.AddCurrentQuestionToCategory("History");

		test.SelectCurrentQuestion("3");
		test.AddCurrentQuestionToCategory("Math");

		test.ChangeNumberOfQuestionsToAskFromCategory("Math", "1");

		NumericalQuestion question_one(1, "What is 5 + 3?");
		ShortAnswerQuestion question_two(2, "What is George Washington's name?");
		NumericalQuestion question_three(3, "What is 3 times 7?");

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
		Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), 1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)2);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[1]) == question_three);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);
	}

	TEST_METHOD(ChangeNumberOfQuestionsToAskFromCategoryRepeatedly) {
		Test test("test");

		test.AddNumericalQuestion("What is 5 + 3?");
		test.AddShortAnswerQuestion("What is George Washington's name?");
		test.AddNumericalQuestion("What is 3 times 7?");

		test.CreateQuestionCategory("Math");
		test.CreateQuestionCategory("History");

		test.SelectCurrentQuestion("1");
		test.AddCurrentQuestionToCategory("Math");

		test.SelectCurrentQuestion("2");
		test.AddCurrentQuestionToCategory("History");

		test.SelectCurrentQuestion("3");
		test.AddCurrentQuestionToCategory("Math");

		test.ChangeNumberOfQuestionsToAskFromCategory("Math", "1");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), 1);

		test.ChangeNumberOfQuestionsToAskFromCategory("Math", "-97218");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -97218);

		test.ChangeNumberOfQuestionsToAskFromCategory("Math", "2");

		NumericalQuestion question_one(1, "What is 5 + 3?");
		ShortAnswerQuestion question_two(2, "What is George Washington's name?");
		NumericalQuestion question_three(3, "What is 3 times 7?");

		Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
		Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), 2);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)2);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);
		Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[1]) == question_three);

		Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
		Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
		Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
		Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);
	}
	};
}

//TEST_METHOD(DeleteNonexistentCategory) {
//	Test test("test");
//
//	test.AddNumericalQuestion("What is 5 + 3?");
//	test.AddShortAnswerQuestion("What is George Washington's name?");
//	test.AddNumericalQuestion("What is 3 times 7?");
//
//	test.CreateQuestionCategory("Math");
//	test.CreateQuestionCategory("History");
//
//	test.SelectCurrentQuestion(1);
//	test.AddCurrentQuestionToCategory("Math");
//
//	test.SelectCurrentQuestion(2);
//	test.AddCurrentQuestionToCategory("History");
//
//	test.SelectCurrentQuestion(3);
//	test.AddCurrentQuestionToCategory("Math");
//
//	NumericalQuestion question_one(1, "What is 5 + 3?");
//	ShortAnswerQuestion question_two(2, "What is George Washington's name?");
//	NumericalQuestion question_three(3, "What is 3 times 7?");
//
//	Assert::AreEqual(test.GetUnassignedQuestions().size(), (size_t)0);
//	Assert::AreEqual(test.GetAssignedQuestions().size(), (size_t)2);
//
//	Assert::AreEqual(get<0>(test.GetAssignedQuestions()[0]), (string)"Math");
//	Assert::AreEqual(get<1>(test.GetAssignedQuestions()[0]), -1);
//	Assert::AreEqual(get<2>(test.GetAssignedQuestions()[0]).size(), (size_t)2);
//	Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[0]) == question_one);
//	Assert::IsTrue(*dynamic_pointer_cast<NumericalQuestion>(get<2>(test.GetAssignedQuestions()[0])[1]) == question_three);
//
//	Assert::AreEqual(get<0>(test.GetAssignedQuestions()[1]), (string)"History");
//	Assert::AreEqual(get<1>(test.GetAssignedQuestions()[1]), -1);
//	Assert::AreEqual(get<2>(test.GetAssignedQuestions()[1]).size(), (size_t)1);
//	Assert::IsTrue(*dynamic_pointer_cast<ShortAnswerQuestion>(get<2>(test.GetAssignedQuestions()[1])[0]) == question_two);
//}