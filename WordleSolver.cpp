
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
using namespace std;
class WordleSolver {
    vector<string> ignoreWords;
    vector<string> board;
public:
    void display(const vector<string> currentBoard) {
      cout << "[";
      for (size_t i = 0; i < currentBoard.size(); ++i) {
          cout << currentBoard[i];
          if (i < currentBoard.size() - 1) {
              cout << ", ";
          }
      }
    cout << "]";
    }
    void resetBoard() {
      board.clear();
      for (int i = 0; i < 5; ++i) {
          board.push_back("_");
      }
    }
    /*void play() {
      resetBoard();
      display(board);
    }*/
    string getInput(string prompt) {
      cout << prompt << " ";
      string input;
      getline(cin, input);
      return input;
    }
    int userEntry(int location) {
      string initialState = board[location];
      board[location] = "=";
      display(board);
      string userInput = getInput("");
        if (userInput == " " || userInput.empty()) {
          board[location] = initialState;
          return location + 1;
      } else if (userInput == "0") {
          board[location] = initialState;
          return 5;
      } else if (userInput == "1") {
        board[location] = "_";
        return max(location - 1, 0);
      } else {
          board[location] = userInput;
          return location + 1;
      }
    }
    void initializeBoard() {
      int i = 0;
      while (i < 5) {
          i = userEntry(i);
      }
      display(board);
      cout << endl;
    }
  vector<string> letterWords() {
    vector<string> rows;
      fstream file("Wordle_Solver/words.txt");
      if (file.is_open()) {
        string line;
        while (getline(file, line)) {
          rows.push_back(line);
        }
        file.close();
      } else {
          cerr << "Unable to open file";
      }
      return rows;
  }
  vector<string> matcher(vector<string> bigList, vector<string> target) {
    vector<string> results;

    for (const string word : bigList) {
        bool isMatch = true;
        for (int i = 0; i < 5; i++) {
          if (target[i] != "_" && target[i] != string(1, word[i])) {
            isMatch = false;
              break;
          }
        }
          if (isMatch) {
            results.push_back(word);
          }
    }

        return results;
  }
  vector<string> remover(const vector<string> bigList, const string ignore) {
    vector<string> newList;
    for (const auto word : bigList) {
      bool flag = true;
      for (char ch : ignore) {
        if (word.find(ch) != std::string::npos) {
          flag = false;
          break;
        }
      }
      if (flag) {
        newList.push_back(word);
      }
    }
    return newList;
  }  
  vector<string> mustHave(const vector<string> bigList) {
    string must = getInput("Type in the letters to include but not sure of location: ");
    vector<string> newList;
    for (const auto& word : bigList) {
      bool flag = true;
      for (char ch : must) {
        if (word.find(ch) == std::string::npos) {
          flag = false;
            break;
          }
        }
        if (flag) {
          newList.push_back(word);
        }
      }
    return newList;
    }
  void play() {
    resetBoard();
    initializeBoard();
    while (true) {
      vector<string> rows = letterWords();
      string ignore = getInput("Type in the letters to ignore (if any): ");
      istringstream iss(ignore);
      ignoreWords = vector<string>((istream_iterator<string>(iss)), istream_iterator<string>());
      if (!ignoreWords.empty() && !ignoreWords[0].empty()) {
        rows = remover(rows, ignoreWords[0]);
      }
      vector<std::string> results = matcher(rows, board);
      results = mustHave(results);
      cout << "Here are the results of the matches:" << endl;
      if (results.empty()) {
        cout << "[]" << std::endl;
      } else {
        cout << "[";
        if (results.size() <= 10) {
          for (size_t i = 0; i < results.size(); ++i) {
            cout << results[i];
            if (i < results.size() - 1) {
              cout << ", ";
            }
          }
        } else {
          for (size_t i = 0; i < 10; ++i) {
            cout << results[i];
            if (i < 9) {
              cout << ", ";
            }
          }
        }
        cout << "]" << std::endl;
        }
      }
  }
};

int main() {
  WordleSolver solver;
  solver.play();

  return 0;
}