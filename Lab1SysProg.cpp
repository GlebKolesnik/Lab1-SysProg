#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int MAX_WORD_LENGTH = 30;

// Функция для проверки, является ли символ согласной буквой (без учета регистра)
bool isConsonant(char c) {
    c = tolower(c); // Преобразование символа к строчной букве
    return (c >= 'b' && c <= 'z' && c != 'e' && c != 'i' && c != 'o' && c != 'u');
}

int main() {
    setlocale(LC_ALL, "Russian");
    ifstream file;
    map<string, int> wordCountMap; // Map для хранения слов и их количества вхождений
    string line; // Строка для чтения из файла

    // Открытие файла для чтения
    file.open("C:\\Shit\\SysProg\\data.txt");

    if (!file.is_open()) {
        cout << "Не удалось открыть файл." << endl;
        return 1;
    }

    while (getline(file, line)) { // Чтение каждой строки из файла
        size_t len = line.length();
        size_t i = 0;

        while (i < len) {
            size_t j = 0;
            string word;

            // Извлечение слова из текущей строки
            while (i < len && isalpha(line[i])) {
                if (j < MAX_WORD_LENGTH) {
                    word.push_back(tolower(line[i])); // Преобразование символа к строчной букве и добавление к слову
                    j++;
                }
                i++;
            }

            if (!word.empty()) {
                // Проверка, содержит ли слово двойные согласные буквы
                bool hasDoubleConsonants = false;
                size_t wordLength = word.length();
                for (size_t k = 0; k < wordLength - 1; k++) {
                    if (isConsonant(word[k]) && word[k] == word[k + 1]) {
                        hasDoubleConsonants = true;
                        break; // Нет необходимости продолжать проверку
                    }
                }

                // Если слово содержит двойные согласные буквы, добавить его в wordCountMap
                if (hasDoubleConsonants) {
                    wordCountMap[word]++;
                }
            }

            // Перейти к следующему слову или не-алфавитному символу
            while (i < len && !isalpha(line[i])) {
                i++;
            }
        }
    }

    // Вывести слова с двойными согласными буквами и их количество вхождений
    cout << "Слова с двойными согласными буквами и их количество вхождений:" << endl;
    for (const auto& pair : wordCountMap) {
        cout << pair.first << ": " << pair.second << endl;
    }

    file.close();
    return 0;
}
