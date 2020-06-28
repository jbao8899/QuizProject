#include "stdafx.h"
#include "CppUnitTest.h"

#include <string>
#include <iostream>
#include <vector>

//Must include .cpp files for some reason once added inheritance
#include "../QuizProject/numerical_question.h"
#include "../QuizProject/numerical_question.cpp"
#include "../QuizProject/question.h"
#include "../QuizProject/question.cpp"
#include "../QuizProject/question_key.h"
#include "../QuizProject/question_key.cpp"
#include "../QuizProject/short_answer_question.h"
#include "../QuizProject/short_answer_question.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;
using std::vector;

namespace TestCases {		
	TEST_CLASS(ShortAnswerQuestionTests) {
	public:
		TEST_METHOD(DefaultConstructor) {
			ShortAnswerQuestion question;
			string empty = "";
			Assert::AreEqual(question.GetQuestion(), empty);
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetCurrentScore(), 0.0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(CustomQuestionConstructorEmptyString) {
			ShortAnswerQuestion question("");
			string empty = "";
			Assert::AreEqual(question.GetQuestion(), empty);
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetCurrentScore(), 0.0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(CustomQuestionConstructorLengthOneString) {
			ShortAnswerQuestion question("a");
			string q_text = "a";
			Assert::AreEqual(question.GetQuestion(), q_text);
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetCurrentScore(), 0.0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(CustomQuestionConstructor) {
			ShortAnswerQuestion question("8BADF00D");
			string q_text = "8BADF00D";
			Assert::AreEqual(question.GetQuestion(), q_text);
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetCurrentScore(), 0.0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(GetSetQuestion) {
			ShortAnswerQuestion question;
			question.SetQuestion("Have you ever had a tangerine?");
			string q_text = "Have you ever had a tangerine?";
			Assert::AreEqual(question.GetQuestion(), q_text);
		}

		TEST_METHOD(GetSetQuestionEmpty) {
			ShortAnswerQuestion question;
			question.SetQuestion("");
			string empty = "";
			Assert::AreEqual(question.GetQuestion(), empty);
		}

		TEST_METHOD(GetSetQuestionLength1) {
			ShortAnswerQuestion question("Should be gone");
			question.SetQuestion("5");
			string q_text = "5";
			Assert::AreEqual(question.GetQuestion(), q_text);
		}

		TEST_METHOD(AddGetRemoveAnswersSingleEmptyString) {
			ShortAnswerQuestion question;
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
			ShortAnswerQuestion question;
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
			ShortAnswerQuestion question;
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
			ShortAnswerQuestion question;
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
			ShortAnswerQuestion question;
			question.RemoveCorrectAnswer("Nothing happens");
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(ClearCorrectAnswersWhenNoneExist) {
			ShortAnswerQuestion question;
			question.ClearCorrectAnswers();
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(ClearCorrectAnswersWhenSomeExist) {
			ShortAnswerQuestion question;
			question.AddCorrectAnswer("forth correct");
			question.AddCorrectAnswer("second correct");
			question.AddCorrectAnswer("third correct");
			question.AddCorrectAnswer("first correct");
			question.ClearCorrectAnswers();
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(ClearCorrectAnswerAndAddNew) {
			ShortAnswerQuestion question;
			question.AddCorrectAnswer("forth correct");
			question.ClearCorrectAnswers();
			question.AddCorrectAnswer("new answer");
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)1);
			Assert::AreEqual(question.GetCorrectAnswers()[0], (string)"new answer");
		}

		TEST_METHOD(AnswerQuestionSingleCorrectAnswer) {
			ShortAnswerQuestion question;
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
			ShortAnswerQuestion question;
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
			ShortAnswerQuestion question;
			question.AddCorrectAnswer("correct");
			question.ClearStudentAnswers();
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
		}

		TEST_METHOD(ClearStudentAnswersWhenThereAreTwo) {
			ShortAnswerQuestion question;
			question.AddCorrectAnswer("correct");
			question.SubmitStudentAnswer("correct");
			question.SubmitStudentAnswer("wrong");
			question.ClearStudentAnswers();
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
		}

		TEST_METHOD(ClearStudentAnswersAndAddNewOne) {
			ShortAnswerQuestion question;
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
			ShortAnswerQuestion question;
			question.SetAvailablePoints("");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToSetAvailablePointsCommaOnly) {
			ShortAnswerQuestion question;
			question.SetAvailablePoints(",");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToSetAvailablePointsDoubleComma) {
			ShortAnswerQuestion question;
			question.SetAvailablePoints("5,4,3,2,,1");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToSetAvailablePointsContainsSpaces) {
			ShortAnswerQuestion question;
			question.SetAvailablePoints("10, 8, 6, 4, 2");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToSetAvailablePointsTwoPeriods) {
			ShortAnswerQuestion question;
			question.SetAvailablePoints("10, 5.5, 6.2, 4, 2..1");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToFailToSetAvailablePointsContainsLetter) {
			ShortAnswerQuestion question;
			question.SetAvailablePoints("5,3,1a");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToSetAvailablePointsContainsSymbol) {
			ShortAnswerQuestion question;
			question.SetAvailablePoints("5!,3,2");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToSetAvailablePointsScoresNotDescendingOrder) {
			ShortAnswerQuestion question;
			question.SetAvailablePoints("10,9,8,7,6,7,4,3,2,1");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToSetAvailablePointsScoresAscendingOrder) {
			ShortAnswerQuestion question;
			question.SetAvailablePoints("0.1,0.2,0.3,0.4,0.5");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(SetAvailablePointsOneAttemptAllowed) {
			ShortAnswerQuestion question;
			question.SetAvailablePoints("5");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)1);
			Assert::AreEqual(question.GetAvailablePoints()[0], 5.0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 5.0);
		}

		TEST_METHOD(SetAvailablePointsFiveAttemptsAllowed) {
			ShortAnswerQuestion question;
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
			ShortAnswerQuestion question;
			question.SetAvailablePoints("1.5,0.75,0.5,0.25");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)4);
			Assert::AreEqual(question.GetAvailablePoints()[0], 1.5);
			Assert::AreEqual(question.GetAvailablePoints()[1], 0.75);
			Assert::AreEqual(question.GetAvailablePoints()[2], 0.5);
			Assert::AreEqual(question.GetAvailablePoints()[3], 0.25);
			Assert::AreEqual(question.GetMaxPossibleScore(), 1.5);
		}

		TEST_METHOD(AnswerQuestionsPointsCorrectFirstTry) {
			ShortAnswerQuestion question;
			question.AddCorrectAnswer("correct");
			question.SetAvailablePoints("5");
			question.SubmitStudentAnswer("correct");
			Assert::AreEqual(question.GetCurrentScore(), 5.0);
		}

		TEST_METHOD(AnswerQuestionsPointsCorrectSecondTry) {
			ShortAnswerQuestion question;
			question.AddCorrectAnswer("correct");
			question.SetAvailablePoints("5,3");
			question.SubmitStudentAnswer("wrong");
			question.SubmitStudentAnswer("correct");
			Assert::AreEqual(question.GetCurrentScore(), 3.0);
		}

		TEST_METHOD(AnswerQuestionsPointsZeroPointsRanOutOfTries) {
			ShortAnswerQuestion question;
			question.AddCorrectAnswer("correct");
			question.SetAvailablePoints("5,3,1");
			question.SubmitStudentAnswer("wrong");
			question.SubmitStudentAnswer("incorrect");
			question.SubmitStudentAnswer("still not right");
			question.SubmitStudentAnswer("correct");
			Assert::AreEqual(question.GetCurrentScore(), 0.0);
		}

		TEST_METHOD(AnswerQuestionsPointsSubsequentCorrectAnswersDoNotReduceSCore) {
			ShortAnswerQuestion question;
			question.AddCorrectAnswer("correct");
			question.AddCorrectAnswer("Also correct");
			question.SetAvailablePoints("5,3,1");
			question.SubmitStudentAnswer("Also correct");
			Assert::AreEqual(question.GetCurrentScore(), 5.0);
		}

		TEST_METHOD(AnswerQuestionsPointsCorrectAndIncorrectAnswers) {
			ShortAnswerQuestion question;
			question.AddCorrectAnswer("correct");
			question.AddCorrectAnswer("Also correct");
			question.SetAvailablePoints("5,3,1");
			question.SubmitStudentAnswer("wrong");
			question.SubmitStudentAnswer("Also correct");
			question.SubmitStudentAnswer("correct");
			Assert::AreEqual(question.GetCurrentScore(), 3.0);
		}

		TEST_METHOD(AnswerQuestionsPointsCaseDoesNotMatter) {
			ShortAnswerQuestion question;
			question.AddCorrectAnswer("cOrReCt12345^&*()");
			question.SetAvailablePoints("3.5");
			question.SubmitStudentAnswer("CoRrEcT12345^&*()");
			Assert::AreEqual(question.GetCurrentScore(), 3.5);
		}
	};

	TEST_CLASS(NumericalQuestionTests) {
	public:
		TEST_METHOD(DefaultConstructor) {
			NumericalQuestion question;
			string empty = "";
			Assert::AreEqual(question.GetQuestion(), empty);
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetCurrentScore(), 0.0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
			Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
			Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
		}

		TEST_METHOD(CustomQuestionConstructorEmptyString) {
			NumericalQuestion question("");
			string empty = "";
			Assert::AreEqual(question.GetQuestion(), empty);
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetCurrentScore(), 0.0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
			Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
			Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
		}

		TEST_METHOD(CustomQuestionConstructorLengthOneString) {
			NumericalQuestion question("a");
			string q_text = "a";
			Assert::AreEqual(question.GetQuestion(), q_text);
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetCurrentScore(), 0.0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
			Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
			Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);

		}

		TEST_METHOD(CustomQuestionConstructor) {
			NumericalQuestion question("8BADF00D");
			string q_text = "8BADF00D";
			Assert::AreEqual(question.GetQuestion(), q_text);
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
			Assert::AreEqual(question.GetCurrentScore(), 0.0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
			Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
			Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
		}

		TEST_METHOD(GetSetPermittedAbsoluteError) {
			NumericalQuestion question;
			question.SetPermittedAbsoluteError(5.1);
			Assert::AreEqual(question.GetPermittedAbsoluteError(), 5.1);
			Assert::AreEqual(question.GetPermittedRelativeError(), 0.0);
		}

		TEST_METHOD(GetSetPermittedRelativeError) {
			NumericalQuestion question;
			question.SetPermittedRelativeError(0.078);
			Assert::AreEqual(question.GetPermittedAbsoluteError(), 0.0);
			Assert::AreEqual(question.GetPermittedRelativeError(), 0.078);
		}

		TEST_METHOD(GetSetQuestion) {
			NumericalQuestion question;
			question.SetQuestion("What is 5 + 5?");
			string q_text = "What is 5 + 5?";
			Assert::AreEqual(question.GetQuestion(), q_text);
		}

		TEST_METHOD(GetSetQuestionEmpty) {
			NumericalQuestion question;
			question.SetQuestion("");
			string empty = "";
			Assert::AreEqual(question.GetQuestion(), empty);
		}

		TEST_METHOD(GetSetQuestionLength1) {
			NumericalQuestion question("Should be gone");
			question.SetQuestion("5");
			string q_text = "5";
			Assert::AreEqual(question.GetQuestion(), q_text);
		}

		TEST_METHOD(FailToAddEmptyStringAsCorrectAnswer) {
			NumericalQuestion question;
			question.AddCorrectAnswer("");
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(FailToAddSpaceAsCorrectAnswer) {
			NumericalQuestion question;
			question.AddCorrectAnswer(" ");
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(FailToAddWordAsCorrectAnswer) {
			NumericalQuestion question;
			question.AddCorrectAnswer("aeftrser");
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(FailToAddNumberWithLetterAsCorrectAnswer) {
			NumericalQuestion question;
			question.AddCorrectAnswer("5a");
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(FailToAddNumberWithSymbolAsCorrectAnswer) {
			NumericalQuestion question;
			question.AddCorrectAnswer("2.1!");
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(FailToAddMixOfCharactersAsCorrectAnswer) {
			NumericalQuestion question;
			question.AddCorrectAnswer("UIH8efhfrui9#*9e");
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(FailToAddNumberWithTwoPeriodsAsCorrectAnswer) {
			NumericalQuestion question;
			question.AddCorrectAnswer("5.3.1");
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(AddIntegerAsCorrectAnswer) {
			NumericalQuestion question;
			question.AddCorrectAnswer("8");
			vector<string> answers;
			answers.push_back("8");
			Assert::AreEqual(question.GetCorrectAnswers().size(), answers.size());
			for (unsigned i = 0; i < answers.size(); ++i) {
				Assert::AreEqual(question.GetCorrectAnswers()[i], answers[i]);
			}
		}

		TEST_METHOD(AddDoubleAsCorrectAnswer) {
			NumericalQuestion question;
			question.AddCorrectAnswer("3.1415");
			vector<string> answers;
			answers.push_back("3.1415");
			Assert::AreEqual(question.GetCorrectAnswers().size(), answers.size());
			for (unsigned i = 0; i < answers.size(); ++i) {
				Assert::AreEqual(question.GetCorrectAnswers()[i], answers[i]);
			}
		}

		TEST_METHOD(AddMultipleCorrectAnswers) {
			NumericalQuestion question;
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
			NumericalQuestion question;
			question.AddCorrectAnswer("-3.89");
			vector<string> answers;
			answers.push_back("-3.89");
			Assert::AreEqual(question.GetCorrectAnswers().size(), answers.size());
			for (unsigned i = 0; i < answers.size(); ++i) {
				Assert::AreEqual(question.GetCorrectAnswers()[i], answers[i]);
			}
		}

		TEST_METHOD(FailToAddCorrectAnswersWithMultipleNegativeSignsOrNegativeSignsInWrongPlaces) {
			NumericalQuestion question;
			question.AddCorrectAnswer("--3.89");
			question.AddCorrectAnswer("5-2");
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(FailToAddCorrectAnswerThatIsJustNegativeSign) {
			NumericalQuestion question;
			question.AddCorrectAnswer("-");
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(AddMultipleCorrectAnswersAndFailToAddSome) {
			NumericalQuestion question;
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
			NumericalQuestion question;
			question.AddCorrectAnswer("5");
			question.RemoveCorrectAnswer("5");
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(AddGetRemoveAnswersThreeAnswers) {
			NumericalQuestion question;
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
			NumericalQuestion question;
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
			NumericalQuestion question;
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
			NumericalQuestion question;
			question.RemoveCorrectAnswer("5");
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(ClearCorrectAnswersWhenNoneExist) {
			NumericalQuestion question;
			question.ClearCorrectAnswers();
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(ClearCorrectAnswersWhenSomeExist) {
			NumericalQuestion question;
			question.AddCorrectAnswer("5.5");
			question.AddCorrectAnswer("1.23");
			question.AddCorrectAnswer("-5");
			question.AddCorrectAnswer("0");
			question.ClearCorrectAnswers();
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)0);
		}

		TEST_METHOD(ClearCorrectAnswerAndAddNew) {
			NumericalQuestion question;
			question.AddCorrectAnswer("5");
			question.ClearCorrectAnswers();
			question.AddCorrectAnswer("3");
			Assert::AreEqual(question.GetCorrectAnswers().size(), (size_t)1);
			Assert::AreEqual(question.GetCorrectAnswers()[0], (string)"3");
		}

		TEST_METHOD(SubmitSingleAnswerExactlyCorrect) {
			NumericalQuestion question;
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
			NumericalQuestion question;
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
			NumericalQuestion question;
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
			NumericalQuestion question;
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
			NumericalQuestion question;
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
			NumericalQuestion question;
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
			NumericalQuestion question;
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
			NumericalQuestion question;
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
			NumericalQuestion question;
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
			NumericalQuestion question;
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
			NumericalQuestion question;
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
			NumericalQuestion question;
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
			NumericalQuestion question;
			question.AddCorrectAnswer("5");
			question.ClearStudentAnswers();
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
		}

		TEST_METHOD(ClearStudentAnswersWhenThereAreTwo) {
			NumericalQuestion question;
			question.AddCorrectAnswer("5");
			question.SubmitStudentAnswer("6");
			question.SubmitStudentAnswer("5");
			question.ClearStudentAnswers();
			Assert::AreEqual(question.GetStudentAnswers().size(), (size_t)0);
		}

		TEST_METHOD(ClearStudentAnswersAndAddNewOne) {
			NumericalQuestion question;
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
			NumericalQuestion question;
			question.SetAvailablePoints("");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToSetAvailablePointsCommaOnly) {
			NumericalQuestion question;
			question.SetAvailablePoints(",");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToSetAvailablePointsDoubleComma) {
			NumericalQuestion question;
			question.SetAvailablePoints("5,4,3,2,,1");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToSetAvailablePointsContainsSpaces) {
			NumericalQuestion question;
			question.SetAvailablePoints("10, 8, 6, 4, 2");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToSetAvailablePointsTwoPeriods) {
			NumericalQuestion question;
			question.SetAvailablePoints("10, 5.5, 6.2, 4, 2..1");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToFailToSetAvailablePointsContainsLetter) {
			NumericalQuestion question;
			question.SetAvailablePoints("5,3,1a");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToSetAvailablePointsContainsSymbol) {
			NumericalQuestion question;
			question.SetAvailablePoints("5!,3,2");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToSetAvailablePointsScoresNotDescendingOrder) {
			NumericalQuestion question;
			question.SetAvailablePoints("10,9,8,7,6,7,4,3,2,1");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(FailToSetAvailablePointsScoresAscendingOrder) {
			NumericalQuestion question;
			question.SetAvailablePoints("0.1,0.2,0.3,0.4,0.5");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 0.0);
		}

		TEST_METHOD(SetAvailablePointsOneAttemptAllowed) {
			NumericalQuestion question;
			question.SetAvailablePoints("5");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)1);
			Assert::AreEqual(question.GetAvailablePoints()[0], 5.0);
			Assert::AreEqual(question.GetMaxPossibleScore(), 5.0);
		}

		TEST_METHOD(SetAvailablePointsFiveAttemptsAllowed) {
			NumericalQuestion question;
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
			NumericalQuestion question;
			question.SetAvailablePoints("1.5,0.75,0.5,0.25");
			Assert::AreEqual(question.GetAvailablePoints().size(), (size_t)4);
			Assert::AreEqual(question.GetAvailablePoints()[0], 1.5);
			Assert::AreEqual(question.GetAvailablePoints()[1], 0.75);
			Assert::AreEqual(question.GetAvailablePoints()[2], 0.5);
			Assert::AreEqual(question.GetAvailablePoints()[3], 0.25);
			Assert::AreEqual(question.GetMaxPossibleScore(), 1.5);
		}	};

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
}