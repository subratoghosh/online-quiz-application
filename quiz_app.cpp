#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <cctype> 

using namespace std;
using namespace chrono;

// --- ANSI Color Codes ---
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define MAGENTA "\033[35m"
#define WHITE   "\033[97m"

// --- Structures ---
struct Question {
    string text;
    vector<string> options;
    int correctIndex;
    int timeLimit;
    int points;
};

struct QuizResult {
    int score;
    int totalPoints;
    int correct;
    int total;
    double timeTaken;
};

// --- Question Bank ---
vector<Question> getQuestions() {
    return {
        {
            "What does OOP stand for?",
            {"Object-Oriented Programming", "Open Output Protocol",
             "Operator Overloading Process", "Object Output Parsing"},
            0, 20, 10
        },
        {
            "Which of the following is NOT a C++ data type?",
            {"int", "float", "real", "char"},
            2, 20, 10
        },
        {
            "What is the output of: cout << 10 % 3;",
            {"3", "1", "0", "2"},
            1, 15, 15
        },
        {
            "Which keyword is used to prevent a class from being inherited?",
            {"static", "sealed", "final", "const"},
            2, 25, 15
        },
        {
            "What is the time complexity of binary search?",
            {"O(n)", "O(n^2)", "O(log n)", "O(1)"},
            2, 20, 20
        },
        {
            "Which operator is used to access members of a class through a pointer?",
            {".", "->", "::", "&"},
            1, 20, 10
        },
        {
            "What does STL stand for in C++?",
            {"Standard Template Library", "Static Type Language",
             "Simple Transfer Layer", "System Template Link"},
            0, 20, 10
        },
        {
            "Which loop always executes its body at least once?",
            {"for", "while", "do-while", "foreach"},
            2, 15, 10
        },
        {
            "What is a constructor?",
            {"A function that destroys objects", "A special function called when an object is created",
             "A static method", "A virtual function"},
            1, 20, 15
        },
        {
            "Which header file is required for string operations in C++?",
            {"<stdio.h>", "<stdlib.h>", "<string>", "<text>"},
            2, 15, 10
        }
    };
}

// --- Utility Functions ---
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printBanner() {
    cout << CYAN << BOLD;
    cout << "\n";
    cout << "  +=========================================================+\n";
    cout << "  |          *  ONLINE QUIZ APPLICATION  *                  |\n";
    cout << "  |           C++ Edition - Test Your Knowledge             |\n";
    cout << "  +=========================================================+\n";
    cout << RESET << "\n";
}

void printSeparator() {
    cout << CYAN << "  -----------------------------------------------------\n" << RESET;
}

double getElapsed(steady_clock::time_point start_time) {
    return duration<double>(steady_clock::now() - start_time).count();
}

char timedInput(int timeLimit, double &timeTaken) {
    char answer = 0;
    cout << YELLOW << "  Time limit: " << timeLimit << "s  |  Enter choice (A/B/C/D): " << RESET;

    auto inputStart = steady_clock::now();
    string line;
    getline(cin, line);
    timeTaken = getElapsed(inputStart);

    if (!line.empty()) {
        answer = toupper(line[0]);
    }
    return answer;
}

void showProgressBar(int current, int total) {
    int width = 40;
    int filled = (current * width) / total;
    cout << "  [";
    for (int i = 0; i < width; ++i)
        cout << (i < filled ? "#" : "-");
    cout << "] " << current << "/" << total << "\n";
}

// --- Quiz Engine ---
QuizResult runQuiz(const vector<Question>& questions) {
    int score = 0;
    int totalPoints = 0;
    int correct = 0;
    double totalTime = 0.0;

    for (int i = 0; i < (int)questions.size(); ++i) {
        const Question& q = questions[i];
        totalPoints += q.points;

        clearScreen();
        printBanner();

        cout << BOLD << WHITE;
        cout << "  Question " << (i + 1) << " of " << questions.size() << "\n";
        showProgressBar(i, questions.size());
        printSeparator();

        cout << "\n  " << BOLD << WHITE << q.text << RESET << "\n\n";

        char labels[] = {'A', 'B', 'C', 'D'};
        for (int j = 0; j < (int)q.options.size(); ++j) {
            cout << "  " << CYAN << BOLD << labels[j] << ". " << RESET
                 << q.options[j] << "\n";
        }

        cout << "\n  " << MAGENTA << "Points: +" << q.points
             << "  |  Time Limit: " << q.timeLimit << "s\n" << RESET;
        printSeparator();

        double timeTaken = 0.0;
        char answer = timedInput(q.timeLimit, timeTaken);
        totalTime += timeTaken;

        bool overtime = timeTaken > q.timeLimit;
        bool validAnswer = (answer >= 'A' && answer <= 'D');
        int answerIndex = answer - 'A';

        cout << "\n";
        if (overtime) {
            cout << RED << "  [TIME'S UP] No points awarded.\n" << RESET;
        } else if (!validAnswer) {
            cout << RED << "  [WRONG] Invalid input. No points awarded.\n" << RESET;
        } else if (answerIndex == q.correctIndex) {
            score += q.points;
            correct++;
            cout << GREEN << BOLD << "  [CORRECT] +" << q.points << " points\n" << RESET;
        } else {
            cout << RED << "  [WRONG] Correct answer: " << BOLD
                 << labels[q.correctIndex] << ". " << q.options[q.correctIndex]
                 << RESET << "\n";
        }

        cout << "\n  " << YELLOW << "Time taken: " << fixed << setprecision(1)
             << timeTaken << "s\n" << RESET;

        this_thread::sleep_for(milliseconds(1800));
    }

    return {score, totalPoints, correct, (int)questions.size(), totalTime};
}

// --- Result Screen ---
void showResults(const QuizResult& r, const string& name) {
    clearScreen();
    printBanner();

    double percentage = (r.totalPoints > 0)
        ? (100.0 * r.score / r.totalPoints) : 0;

    string grade;
    string gradeColor;
    if      (percentage >= 90) { grade = "A+  Excellent!";   gradeColor = GREEN; }
    else if (percentage >= 75) { grade = "B   Good Job!";    gradeColor = CYAN; }
    else if (percentage >= 50) { grade = "C   Keep Trying";  gradeColor = YELLOW; }
    else                       { grade = "F   Need Practice"; gradeColor = RED; }

    cout << BOLD << WHITE << "\n  ========== QUIZ RESULTS ==========\n\n" << RESET;
    cout << "  Player      : " << CYAN << BOLD << name << RESET << "\n";
    cout << "  Score       : " << GREEN << BOLD << r.score << " / " << r.totalPoints << RESET << "\n";
    cout << "  Percentage  : " << YELLOW << BOLD << fixed << setprecision(1) << percentage << "%" << RESET << "\n";
    cout << "  Correct     : " << r.correct << " / " << r.total << " questions\n";
    cout << "  Total Time  : " << fixed << setprecision(1) << r.timeTaken << " seconds\n";
    cout << "  Grade       : " << gradeColor << BOLD << grade << RESET << "\n\n";
    printSeparator();

    cout << "\n  Score Progress:\n  ";
    int barWidth = 40;
    int filled = (int)(percentage / 100.0 * barWidth);
    cout << "[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < filled) cout << GREEN << "#" << RESET;
        else            cout << "-";
    }
    cout << "] " << fixed << setprecision(1) << percentage << "%\n\n";
}

// --- Main Menu ---
void showMenu() {
    cout << CYAN << BOLD;
    cout << "\n  +=========================+\n";
    cout << "  |       MAIN MENU         |\n";
    cout << "  +=========================+\n";
    cout << "  |  1. Start Quiz          |\n";
    cout << "  |  2. View Instructions   |\n";
    cout << "  |  3. Exit                |\n";
    cout << "  +=========================+\n" << RESET;
    cout << "\n  Choice: ";
}

void showInstructions() {
    clearScreen();
    printBanner();
    cout << WHITE << BOLD << "  HOW TO PLAY\n" << RESET;
    printSeparator();
    cout << "\n"
         << "  1. Each question has a time limit - answer before it expires.\n"
         << "  2. Enter A, B, C, or D and press Enter.\n"
         << "  3. Points vary per question based on difficulty.\n"
         << "  4. Late answers (past the time limit) receive 0 points.\n"
         << "  5. Your final grade is based on total points earned.\n\n"
         << GREEN << "  Grading:\n" << RESET
         << "    A+  90-100%  Excellent!\n"
         << "    B   75-89%   Good Job!\n"
         << "    C   50-74%   Keep Trying\n"
         << "    F   0-49%    Need Practice\n\n";
    printSeparator();
    cout << "\n  Press Enter to return...";
    cin.get();
}

// --- Entry Point ---
int main() {
    clearScreen();
    printBanner();

    cout << "\n  " << BOLD << WHITE << "Enter your name: " << RESET;
    string playerName;
    getline(cin, playerName);
    if (playerName.empty()) playerName = "Player";

    bool running = true;
    while (running) {
        clearScreen();
        printBanner();
        cout << "\n  " << CYAN << "Welcome, " << BOLD << playerName << RESET << "!\n";
        showMenu();

        string choice;
        getline(cin, choice);

        if (choice == "1") {
            auto questions = getQuestions();
            QuizResult result = runQuiz(questions);
            showResults(result, playerName);
            cout << "  Press Enter to return to menu...";
            cin.get();
        } else if (choice == "2") {
            showInstructions();
        } else if (choice == "3") {
            clearScreen();
            cout << GREEN << BOLD << "\n  Thanks for playing! Goodbye, "
                 << playerName << "!\n\n" << RESET;
            running = false;
        } else {
            cout << RED << "\n  Invalid choice. Try again.\n" << RESET;
            this_thread::sleep_for(milliseconds(900));
        }
    }

    return 0;
}