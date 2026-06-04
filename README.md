# 🧠 Online Quiz Application

> A C++ terminal quiz app with a matching web-based frontend — test your programming knowledge with timed questions, scoring, and instant feedback.

---

## 📌 Repository Info

| Field | Details |
|---|---|
| **Repo Name** | `online-quiz-application` |
| **Description** | A C++ and web-based quiz app with timed questions, scoring, grading, and a sleek dark-themed UI. |
| **Topics / Tags** | `cpp` `quiz` `html` `css` `javascript` `timed-quiz` `educational` `programming-quiz` |

---

## 🗂️ Project Structure

```
online-quiz-application/
├── quiz_app.cpp        # C++ terminal quiz application
├── index.html          # Web app — markup & structure
├── style.css           # Web app — dark-themed stylesheet
├── quiz.js             # Web app — quiz logic & timer
└── README.md
```

---

## ✨ Features

- **10 C++ / Programming Questions** — covering OOP, data types, STL, algorithms, and more
- **Per-question Time Limits** — 15–25 seconds depending on difficulty
- **Dynamic Scoring** — 10–20 points per question based on difficulty
- **Live Timer Ring** — animated countdown with color-coded urgency
- **Instant Feedback** — correct/wrong highlighting after each answer
- **Grade System** — A+ / B / C / F based on percentage scored
- **Progress Bar** — visual question progress across the quiz
- **Responsive Web UI** — works on desktop and mobile
- **Terminal Version (C++)** — full ANSI color, ASCII art, and progress bars

---

## 🚀 Getting Started

### Web Version

Just open `index.html` in any modern browser — no build tools or dependencies needed.

```bash
# Clone the repo
git clone https://github.com/YOUR_USERNAME/online-quiz-application.git
cd online-quiz-application

# Open in browser
open index.html       # macOS
start index.html      # Windows
xdg-open index.html   # Linux
```

### C++ Terminal Version

**Requirements:** A C++17-compatible compiler (g++, clang++, MSVC)

```bash
# Compile
g++ -std=c++17 -o quiz quiz_app.cpp

# Run
./quiz          # Linux / macOS
quiz.exe        # Windows
```

> **Windows note:** ANSI color codes require Windows 10+ with Virtual Terminal enabled, or use Windows Terminal / Git Bash.

---

## 🎮 How to Play

1. Enter your name and press **Start Quiz**
2. Read each question carefully
3. Select your answer **before** the timer runs out
4. Earn points for correct answers (late = 0 pts)
5. View your final grade and score breakdown

### Grading Scale

| Grade | Range | Label |
|---|---|---|
| **A+** | 90–100% | Excellent! |
| **B** | 75–89% | Good Job! |
| **C** | 50–74% | Keep Trying |
| **F** | 0–49% | Need Practice |

---

## 🛠️ Tech Stack

| Layer | Technology |
|---|---|
| Terminal App | C++17, STL, ANSI escape codes |
| Web Markup | HTML5 (semantic) |
| Web Styles | CSS3 (custom properties, grid, animations) |
| Web Logic | Vanilla JavaScript (ES6+) |
| Fonts | Google Fonts — Space Mono + DM Sans |

---

## 📸 Screenshots

> _Add screenshots of your terminal output and web UI here._

---

## 🤝 Contributing

Pull requests are welcome! To add questions, edit the `QUESTIONS` array in `quiz.js` (web) or the `getQuestions()` function in `quiz_app.cpp` (C++).

---

## 📄 License

MIT © 2024
