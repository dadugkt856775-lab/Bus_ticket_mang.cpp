
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Question {
public:
    string questionText;
    string options[4];
    char correctAnswer;

    Question(string text, string a, string b,
             string c, string d, char answer) {
        questionText = text;
        options[0] = a;
        options[1] = b;
        options[2] = c;
        options[3] = d;
        correctAnswer = answer;
    }

    void displayQuestion(int number) const {
        cout << "\nQuestion " << number << ": "
             << questionText << endl;

        cout << "A. " << options[0] << endl;
        cout << "B. " << options[1] << endl;
        cout << "C. " << options[2] << endl;
        cout << "D. " << options[3] << endl;
    }
};

class ExamSystem {
private:
    vector<Question> questions;
    vector<char> studentAnswers;
    string studentName;
    int score;

    void loadQuestions() {
        questions.emplace_back(
            "Which language is used in this program?",
            "HTML", "CSS", "C++", "SQL", 'C');

        questions.emplace_back(
            "Which symbol ends most C++ statements?",
            ".", ";", ":", ",", 'B');

        questions.emplace_back(
            "Which keyword creates a class?",
            "object", "define", "class", "structs", 'C');

        questions.emplace_back(
            "Which loop checks its condition before each iteration?",
            "while", "do-while only", "switch", "None", 'A');

        questions.emplace_back(
            "Which container stores a sequence of elements dynamically?",
            "vector", "int", "char", "bool", 'A');

        questions.emplace_back(
            "Which function is the usual entry point of a C++ program?",
            "start()", "main()", "run()", "begin()", 'B');

        questions.emplace_back(
            "Which operator checks equality?",
            "=", "==", "!=", "<=", 'B');

        questions.emplace_back(
            "Which header provides cout and cin?",
            "<string>", "<vector>", "<iostream>", "<iomanip>", 'C');

        questions.emplace_back(
            "Which access specifier allows access from anywhere "
            "through a public interface?",
            "private", "protected", "public", "hidden", 'C');

        questions.emplace_back(
            "Which data type stores true or false?",
            "int", "bool", "double", "string", 'B');
    }

    char readAnswer() {
        char answer;

        while (true) {
            cout << "Your answer (A/B/C/D): ";
            cin >> answer;

            if (answer >= 'a' && answer <= 'z')
                answer = answer - 'a' + 'A';

            if (answer >= 'A' && answer <= 'D')
                return answer;

            cout << "Invalid choice. Enter A, B, C, or D.\n";
        }
    }

    string calculateGrade(double percentage) const {
        if (percentage >= 90) return "A+";
        if (percentage >= 80) return "A";
        if (percentage >= 70) return "B";
        if (percentage >= 60) return "C";
        if (percentage >= 50) return "D";
        return "Needs Improvement";
    }

public:
    ExamSystem() {
        score = 0;
        loadQuestions();
    }

    void startExam() {
        cout << "Enter student name: ";
        getline(cin >> ws, studentName);

        studentAnswers.clear();
        score = 0;

        cout << "\nWelcome, " << studentName << "!\n";
        cout << "Total Questions: " << questions.size() << endl;
        cout << "Each correct answer carries 1 mark.\n";
        cout << "There is no negative marking.\n";

        for (int i = 0; i < (int)questions.size(); i++) {
            questions[i].displayQuestion(i + 1);

            char answer = readAnswer();
            studentAnswers.push_back(answer);

            if (answer == questions[i].correctAnswer)
                score++;
        }

        cout << "\nExam submitted successfully!\n";
        displayResult();
    }

    void displayResult() const {
        if (studentAnswers.empty()) {
            cout << "No exam result available. Take the exam first.\n";
            return;
        }

        double percentage =
            (score * 100.0) / questions.size();

        cout << "\n========== EXAM RESULT ==========\n";
        cout << "Student Name : " << studentName << endl;
        cout << "Total Marks  : " << questions.size() << endl;
        cout << "Marks Scored : " << score << endl;
        cout << fixed << setprecision(2);
        cout << "Percentage   : " << percentage << "%\n";
        cout << "Grade        : "
             << calculateGrade(percentage) << endl;

        if (percentage >= 40)
            cout << "Status       : PASS\n";
        else
            cout << "Status       : FAIL\n";

        cout << "=================================\n";
    }

    void reviewAnswers() const {
        if (studentAnswers.empty()) {
            cout << "Please take the exam before reviewing answers.\n";
            return;
        }

        cout << "\n========== ANSWER REVIEW ==========\n";

        for (int i = 0; i < (int)questions.size(); i++) {
            cout << "\nQuestion " << i + 1 << ": "
                 << questions[i].questionText << endl;

            cout << "Your answer   : "
                 << studentAnswers[i] << endl;

            cout << "Correct answer: "
                 << questions[i].correctAnswer << endl;

            if (studentAnswers[i] ==
                questions[i].correctAnswer) {
                cout << "Result        : Correct\n";
            } else {
                cout << "Result        : Incorrect\n";
            }
        }
    }

    void run() {
        int choice;

        do {
            cout << "\n===== ONLINE EXAMINATION SYSTEM =====\n";
            cout << "1. Start Examination\n";
            cout << "2. View Latest Result\n";
            cout << "3. Review Answers\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";

            if (!(cin >> choice)) {
                cout << "Invalid input!\n";
                break;
            }

            switch (choice) {
                case 1:
                    startExam();
                    break;
                case 2:
                    displayResult();
                    break;
                case 3:
                    reviewAnswers();
                    break;
                case 0:
                    cout << "Thank you for using the Exam System!\n";
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
            }

        } while (choice != 0);
    }
};

int main() {
    ExamSystem exam;
    exam.run();
    return 0;
}
