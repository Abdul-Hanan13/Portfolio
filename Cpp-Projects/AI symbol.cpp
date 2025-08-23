#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib> // For system("cls")

using namespace std;

// Global arrays instead of vectors
const int MAX_SIZE = 100;
string positiveSymbols[MAX_SIZE] = {"water", "light", "praying", "mosque", "quran"};
int posCount = 5;

string negativeSymbols[MAX_SIZE] = {"snake", "fire", "death", "blood", "falling"};
int negCount = 5;

string emotionSymbols[MAX_SIZE] = {"happy", "fear", "crying"};
int emoCount = 3;

string lifeEventSymbols[MAX_SIZE] = {"exam", "school", "marriage", "money"};
int lifeCount = 4;

string dreamHistory[MAX_SIZE];
int historyCount = 0;

// Utility functions
string toLower(string str) {
    for (int i = 0; i < str.length(); i++)
        str[i] = tolower(str[i]);
    return str;
}

bool containsWord(string sentence, string word) {
    sentence = " " + toLower(sentence) + " ";
    word = " " + toLower(word) + " ";
    return sentence.find(word) != string::npos;
}

bool isEmpty(string str) {
    for (int i = 0; i < str.length(); i++)
        if (!isspace(str[i])) return false;
    return true;
}

void pause() {
    cout << "\nPress Enter to continue...";
    cin.get();
}

void clearScreen() {
    system("cls"); // For Linux/Mac use "clear"
}

// Dream analysis logic
string analyzeDream(string dream) {
    bool foundPositive = false, foundNegative = false, foundEmotion = false, foundEvent = false;

    cout << "\n-- DREAM ANALYSIS --\n";

    cout << "\nPositive Symbols:\n";
    for (int i = 0; i < posCount; i++) {
        if (containsWord(dream, positiveSymbols[i])) {
            cout << positiveSymbols[i] << ": Positive sign\n";
            foundPositive = true;
        }
    }

    cout << "\nNegative Symbols:\n";
    for (int i = 0; i < negCount; i++) {
        if (containsWord(dream, negativeSymbols[i])) {
            cout << negativeSymbols[i] << ": Warning sign\n";
            foundNegative = true;
        }
    }

    cout << "\nEmotions:\n";
    for (int i = 0; i < emoCount; i++) {
        if (containsWord(dream, emotionSymbols[i])) {
            cout << emotionSymbols[i] << ": Detected emotion\n";
            foundEmotion = true;
        }
    }

    cout << "\nLife Events:\n";
    for (int i = 0; i < lifeCount; i++) {
        if (containsWord(dream, lifeEventSymbols[i])) {
            cout << lifeEventSymbols[i] << ": Life event symbol\n";
            foundEvent = true;
        }
    }

    cout << "\nOverall Interpretation:\n";
    if (foundPositive && !foundNegative)
        return "good";
    else if (!foundPositive && foundNegative)
        return "bad";
    else if (!foundPositive && !foundNegative && !foundEmotion && !foundEvent)
        return "random";
    else
        return "mixed";
}

// Islamic guidance
void showIslamicTips(string type) {
    cout << "\n-- ISLAMIC GUIDANCE --\n";
    if (type == "good")
        cout << "Say Alhamdulillah. Keep it private and thank Allah.\n";
    else if (type == "bad")
        cout << "Seek refuge from Shaytan. Don't share it and pray.\n";
    else if (type == "mixed")
        cout << "Do dhikr, reflect, and pray for guidance.\n";
    else
        cout << "Make wudu, do dua, and sleep peacefully.\n";
}

// ADMIN MENU
void adminMenu() {
    int choice;
    string cat, word, oldWord, newWord;

    do {
        clearScreen();
        cout << "ADMIN MENU\n1. Insert Symbol\n2. Update Symbol\n3. Delete Symbol\n4. Back\nEnter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 4) return;

        cout << "Enter category (positive/negative/emotion/life): ";
        getline(cin, cat);
        cat = toLower(cat);

        if (choice == 1) {
            cout << "Enter new symbol: ";
            getline(cin, word);

            if (cat == "positive" && posCount < MAX_SIZE)
                positiveSymbols[posCount++] = word;
            else if (cat == "negative" && negCount < MAX_SIZE)
                negativeSymbols[negCount++] = word;
            else if (cat == "emotion" && emoCount < MAX_SIZE)
                emotionSymbols[emoCount++] = word;
            else if (cat == "life" && lifeCount < MAX_SIZE)
                lifeEventSymbols[lifeCount++] = word;
            else
                cout << "Invalid category or full.\n";

        } else if (choice == 2) {
            cout << "Old symbol: "; getline(cin, oldWord);
            cout << "New symbol: "; getline(cin, newWord);
            bool found = false;

            string* arr = NULL;
            int* count = NULL;

            if (cat == "positive") { arr = positiveSymbols; count = &posCount; }
            else if (cat == "negative") { arr = negativeSymbols; count = &negCount; }
            else if (cat == "emotion") { arr = emotionSymbols; count = &emoCount; }
            else if (cat == "life") { arr = lifeEventSymbols; count = &lifeCount; }

            if (arr != NULL) {
                for (int i = 0; i < *count; i++) {
                    if (arr[i] == oldWord) {
                        arr[i] = newWord;
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Symbol not found.\n";
                else cout << "Updated successfully.\n";
            }

        } else if (choice == 3) {
            cout << "Enter symbol to delete: ";
            getline(cin, word);
            bool found = false;

            string* arr = NULL;
            int* count = NULL;

            if (cat == "positive") { arr = positiveSymbols; count = &posCount; }
            else if (cat == "negative") { arr = negativeSymbols; count = &negCount; }
            else if (cat == "emotion") { arr = emotionSymbols; count = &emoCount; }
            else if (cat == "life") { arr = lifeEventSymbols; count = &lifeCount; }

            if (arr != NULL) {
                for (int i = 0; i < *count; i++) {
                    if (arr[i] == word) {
                        for (int j = i; j < *count - 1; j++) {
                            arr[j] = arr[j + 1];
                        }
                        (*count)--;
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Symbol not found.\n";
                else cout << "Deleted successfully.\n";
            }

        } else {
            cout << "Invalid choice.\n";
        }

        pause();
    } while (true);
}

// USER MENU
void userMenu() {
    int choice;

    do {
        clearScreen();
        cout << "USER MENU\n1. Enter Your Dream\n2. View Dream History\n3. Back\nEnter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string dream;
            cout << "Describe your dream: ";
            getline(cin, dream);
            if (isEmpty(dream)) {
                cout << "Dream cannot be empty.\n";
            } else {
                string result = analyzeDream(dream);
                showIslamicTips(result);
                if (historyCount < MAX_SIZE) {
                    dreamHistory[historyCount++] = dream;
                }
            }
        } else if (choice == 2) {
            cout << "\n-- DREAM HISTORY --\n";
            for (int i = 0; i < historyCount; i++) {
                cout << i + 1 << ". " << dreamHistory[i] << "\n";
            }
        } else if (choice == 3) {
            return;
        } else {
            cout << "Invalid option.\n";
        }

        pause();
    } while (true);
}

// MAIN MENU
int main() {
    int choice;

    do {
        clearScreen();
        cout << "AI DREAM THERAPIST\n==================\n";
        cout << "1. Admin\n2. User\n3. Exit\nEnter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1)
            adminMenu();
        else if (choice == 2)
            userMenu();
        else if (choice == 3) {
            cout << "Thank you for using the Dream Therapist.\n";
            break;
        } else {
            cout << "Invalid choice.\n";
            pause();
        }

    } while (true);

    return 0;
}

