/* ════════════════════════════════════════════════════════
   Online Quiz Application — quiz.js
   ════════════════════════════════════════════════════════ */

'use strict';


const QUESTIONS = [
  {
    text: 'What does OOP stand for?',
    options: ['Object-Oriented Programming', 'Open Output Protocol', 'Operator Overloading Process', 'Object Output Parsing'],
    correct: 0, timeLimit: 20, points: 10
  },
  {
    text: 'Which of the following is NOT a C++ data type?',
    options: ['int', 'float', 'real', 'char'],
    correct: 2, timeLimit: 20, points: 10
  },
  {
    text: 'What is the output of: cout << 10 % 3 ?',
    options: ['3', '1', '0', '2'],
    correct: 1, timeLimit: 15, points: 15
  },
  {
    text: 'Which keyword prevents a class from being inherited in C++?',
    options: ['static', 'sealed', 'final', 'const'],
    correct: 2, timeLimit: 25, points: 15
  },
  {
    text: 'What is the time complexity of Binary Search?',
    options: ['O(n)', 'O(n²)', 'O(log n)', 'O(1)'],
    correct: 2, timeLimit: 20, points: 20
  },
  {
    text: 'Which operator accesses members of a class through a pointer?',
    options: ['.', '->', '::', '&'],
    correct: 1, timeLimit: 20, points: 10
  },
  {
    text: 'What does STL stand for in C++?',
    options: ['Standard Template Library', 'Static Type Language', 'Simple Transfer Layer', 'System Template Link'],
    correct: 0, timeLimit: 20, points: 10
  },
  {
    text: 'Which loop always executes its body at least once?',
    options: ['for', 'while', 'do-while', 'foreach'],
    correct: 2, timeLimit: 15, points: 10
  },
  {
    text: 'What is a constructor in C++?',
    options: ['A function that destroys objects', 'A special function called when an object is created', 'A static method', 'A virtual function'],
    correct: 1, timeLimit: 20, points: 15
  },
  {
    text: 'Which header is required for string operations in C++?',
    options: ['<stdio.h>', '<stdlib.h>', '<string>', '<text>'],
    correct: 2, timeLimit: 15, points: 10
  }
];

const TOTAL_POINTS = QUESTIONS.reduce((s, q) => s + q.points, 0);
const LABELS = ['A', 'B', 'C', 'D'];
const CIRCUMFERENCE = 2 * Math.PI * 18; // r=18

let state = {
  playerName: '',
  currentQ: 0,
  score: 0,
  correct: 0,
  totalTime: 0,
  timerId: null,
  timeLeft: 0,
  answered: false,
  questionStart: 0,
};


const screens = {
  welcome:      document.getElementById('screen-welcome'),
  instructions: document.getElementById('screen-instructions'),
  quiz:         document.getElementById('screen-quiz'),
  result:       document.getElementById('screen-result'),
};

function showScreen(name) {
  Object.values(screens).forEach(s => s.classList.remove('active'));
  screens[name].classList.add('active');
}

const ringArc  = document.getElementById('ring-arc');
const timerNum = document.getElementById('timer-num');

function setRing(fraction, urgent) {
  const offset = CIRCUMFERENCE * (1 - fraction);
  ringArc.style.strokeDashoffset = offset;
  ringArc.style.stroke = urgent ? '#f87171' : fraction > 0.4 ? '#4ade80' : '#facc15';
  timerNum.textContent = Math.ceil(fraction * state.timeLeft + (state.timeLeft * (1 - fraction)));
}

function startTimer(seconds) {
  clearInterval(state.timerId);
  state.timeLeft = seconds;
  timerNum.textContent = seconds;
  ringArc.style.strokeDasharray = CIRCUMFERENCE;
  ringArc.style.strokeDashoffset = 0;
  ringArc.style.stroke = '#4ade80';

  const total = seconds;
  let elapsed = 0;

  state.timerId = setInterval(() => {
    elapsed++;
    const left = total - elapsed;
    const frac = left / total;
    ringArc.style.strokeDashoffset = CIRCUMFERENCE * (1 - frac);
    timerNum.textContent = left;
    ringArc.style.stroke = left <= 5 ? '#f87171' : left <= total * 0.4 ? '#facc15' : '#4ade80';

    if (left <= 0) {
      clearInterval(state.timerId);
      if (!state.answered) handleTimeout();
    }
  }, 1000);
}

function renderQuestion() {
  const q = QUESTIONS[state.currentQ];
  state.answered = false;
  state.questionStart = Date.now();


  document.getElementById('q-label').textContent = `Q ${state.currentQ + 1} / ${QUESTIONS.length}`;
  document.getElementById('progress-fill').style.width =
    `${(state.currentQ / QUESTIONS.length) * 100}%`;
  document.getElementById('score-live').textContent = `Score: ${state.score}`;
  document.getElementById('q-points-badge').textContent = `+${q.points} pts`;

 
  document.getElementById('question-text').textContent = q.text;

  
  const grid = document.getElementById('options-grid');
  grid.innerHTML = '';
  q.options.forEach((opt, i) => {
  const btn = document.createElement('button');
  btn.className = 'option-btn';

  const label = document.createElement('span');
  label.className = 'opt-label';
  label.textContent = LABELS[i];

  btn.appendChild(label);

  const text = document.createTextNode(opt);
  btn.appendChild(text);

  btn.addEventListener('click', () => handleAnswer(i));

  grid.appendChild(btn);
});

  startTimer(q.timeLimit);
}


function handleAnswer(chosen) {
  if (state.answered) return;
  state.answered = true;
  clearInterval(state.timerId);

  const elapsed = (Date.now() - state.questionStart) / 1000;
  state.totalTime += elapsed;

  const q = QUESTIONS[state.currentQ];
  const buttons = document.querySelectorAll('.option-btn');

  buttons.forEach(btn => btn.disabled = true);

  if (chosen === q.correct) {
    state.score += q.points;
    state.correct++;
    buttons[chosen].classList.add('correct');
  } else {
    buttons[chosen].classList.add('wrong');
    buttons[q.correct].classList.add('correct');
  }

  document.getElementById('score-live').textContent = `Score: ${state.score}`;

  setTimeout(nextQuestion, 1200);
}

function handleTimeout() {
  state.answered = true;
  const q = QUESTIONS[state.currentQ];
  const buttons = document.querySelectorAll('.option-btn');
  buttons.forEach(btn => btn.disabled = true);
  buttons[q.correct].classList.add('correct');
  setTimeout(nextQuestion, 1200);
}

function nextQuestion() {
  state.currentQ++;
  if (state.currentQ < QUESTIONS.length) {
    renderQuestion();
  } else {
    showResult();
  }
}


function showResult() {
  const pct = Math.round((state.score / TOTAL_POINTS) * 100);

  let grade, title, gradeClass;
  if      (pct >= 90) { grade = 'A+'; title = 'Excellent!';       gradeClass = ''; }
  else if (pct >= 75) { grade = 'B';  title = 'Good Job!';        gradeClass = 'grade-b'; }
  else if (pct >= 50) { grade = 'C';  title = 'Keep Trying!';     gradeClass = 'grade-c'; }
  else                { grade = 'F';  title = 'Need Practice';    gradeClass = 'grade-f'; }

  const badge = document.getElementById('result-grade-badge');
  badge.textContent = grade;
  badge.className = 'result-grade ' + gradeClass;

  document.getElementById('result-title').textContent  = title;
  document.getElementById('result-name').textContent   = state.playerName;
  document.getElementById('stat-score').textContent    = `${state.score}/${TOTAL_POINTS}`;
  document.getElementById('stat-pct').textContent      = `${pct}%`;
  document.getElementById('stat-correct').textContent  = `${state.correct}/${QUESTIONS.length}`;
  document.getElementById('stat-time').textContent     = `${state.totalTime.toFixed(1)}s`;

  showScreen('result');


  setTimeout(() => {
    document.getElementById('score-bar-fill').style.width = pct + '%';
    document.getElementById('score-bar-label').textContent = pct + '%';
  }, 200);
}

function startQuiz() {
  const nameInput = document.getElementById('player-name');
  state.playerName = nameInput.value.trim() || 'Player';
  state.currentQ   = 0;
  state.score      = 0;
  state.correct    = 0;
  state.totalTime  = 0;
  state.answered   = false;

  showScreen('quiz');
  renderQuestion();
}


document.getElementById('btn-start').addEventListener('click', () => {
  startQuiz();
});

document.getElementById('player-name').addEventListener('keydown', e => {
  if (e.key === 'Enter') startQuiz();
});

document.getElementById('btn-instructions').addEventListener('click', () => {
  showScreen('instructions');
});

document.getElementById('btn-back').addEventListener('click', () => {
  showScreen('welcome');
});

document.getElementById('btn-retry').addEventListener('click', () => {
  startQuiz();
});

document.getElementById('btn-home').addEventListener('click', () => {
  clearInterval(state.timerId);
  showScreen('welcome');
});
