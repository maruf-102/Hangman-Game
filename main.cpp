#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

class HangmanGame {
private:
    vector<string> words;
    string secretWord;
    string guessedWord;
    int maxAttempts;
    int attemptsLeft;

public:
    HangmanGame(const string& filename, int maxAttempts) : maxAttempts(maxAttempts), attemptsLeft(maxAttempts) {
        // Read words from a file
        ifstream file(filename);
        if (file.is_open()) {
            string word;
            while (getline(file, word)) {
                words.push_back(word);
            }
            file.close();
        } else {
            cerr << "Error: Unable to open file " << filename << endl;
            exit(1);
        }

        // Seed the random number generator
        srand(time(0));

        // Select a random word from the list
        secretWord = words[rand() % words.size()];

        // Initialize guessedWord with underscores
        guessedWord = string(secretWord.length(), '_');
    }

    void play() {
        cout << "Welcome to Hangman!" << endl;

        while (attemptsLeft > 0) {
            displayHangman();
            displayGuessedWord();

            char guess;
            cout << "Guess a letter: ";
            cin >> guess;

            if (!isalpha(guess)) {
                cout << "Invalid input. Please enter a letter." << endl;
                continue;
            }

            if (guessedWord.find(guess) != string::npos) {
                cout << "You've already guessed that letter." << endl;
                continue;
            }

            bool correctGuess = false;
            for (size_t i = 0; i < secretWord.length(); ++i) {
                if (secretWord[i] == guess) {
                    guessedWord[i] = guess;
                    correctGuess = true;
                }
            }

            if (!correctGuess) {
                --attemptsLeft;
                cout << "Incorrect guess. " << attemptsLeft << " attempts left." << endl;
            }

            if (guessedWord == secretWord) {
                displayHangman();
                cout << "Congratulations! You guessed the word: " << secretWord << endl;
                break;
            }
        }

        if (attemptsLeft == 0) {
            displayHangman();
            cout << "You ran out of attempts. The word was: " << secretWord << endl;
        }
    }

    void displayHangman() {
        switch (attemptsLeft) {
            case 6:
                cout << "   ________" << endl;
                cout << "   |      |" << endl;
                cout << "          |" << endl;
                cout << "          |" << endl;
                cout << "          |" << endl;
                cout << "          |" << endl;
                cout << "__________|___" << endl;
                break;
            case 5:
                cout << "   ________" << endl;
                cout << "   |      |" << endl;
                cout << "   O      |" << endl;
                cout << "          |" << endl;
                cout << "          |" << endl;
                cout << "          |" << endl;
                cout << "__________|___" << endl;
                break;
            case 4:
                cout << "   ________" << endl;
                cout << "   |      |" << endl;
                cout << "   O      |" << endl;
                cout << "   |      |" << endl;
                cout << "          |" << endl;
                cout << "          |" << endl;
                cout << "__________|___" << endl;
                break;
            case 3:
                cout << "   ________" << endl;
                cout << "   |      |" << endl;
                cout << "   O      |" << endl;
                cout << "  /|      |" << endl;
                cout << "          |" << endl;
                cout << "          |" << endl;
                cout << "__________|___" << endl;
                break;
            case 2:
                cout << "   ________" << endl;
                cout << "   |      |" << endl;
                cout << "   O      |" << endl;
                cout << "  /|\\     |" << endl;
                cout << "          |" << endl;
                cout << "          |" << endl;
                cout << "__________|___" << endl;
                break;
            case 1:
                cout << "   ________" << endl;
                cout << "   |      |" << endl;
                cout << "   O      |" << endl;
                cout << "  /|\\     |" << endl;
                cout << "  /       |" << endl;
                cout << "          |" << endl;
                cout << "__________|___" << endl;
                break;
            case 0:
                cout << "   ________" << endl;
                cout << "   |      |" << endl;
                cout << "   O      |" << endl;
                cout << "  /|\\     |" << endl;
                cout << "  / \\     |" << endl;
                cout << "          |" << endl;
                cout << "__________|___" << endl;
                break;
        }
    }

    void displayGuessedWord() {
        cout << "Word to guess: ";
        for (char c : guessedWord) {
            cout << c << " ";
        }
        cout << endl;
    }
};

int main() {
    HangmanGame game("E:\\Programming\\C++ project\\hnagman\\hangman\\word.txt", 6);
    game.play();

    return 0;
}
