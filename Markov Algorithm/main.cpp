#include <iostream>
#include <string>
#include <map>

int main() {
    std::map<std::string, std::string> keys = {
        {"1", "one"},
        {"3", "three"},
        {"two", "2"},
        {"four", "4"},
    };

    std::string inputText = "1s two 3 fours";

    // Проходження крізь кожен символ у введеному тексті
    for (size_t i = 0; i < inputText.length(); ++i) {
        // Перевірка для кожного ключа
        for (const auto& keyPair : keys) {
            const std::string& key = keyPair.first;
            const std::string& value = keyPair.second;
            // Перевірка чи підстрічка, починаючи з поточної позиції, збігається з ключем
            if (inputText.substr(i, key.length()) == key) {
                // Якщо збіг, замінюємо ключ на відповідне значення
                inputText.replace(i, key.length(), value);
                // Зсув позиції, щоб уникнути втрати перевірених символів
                i += value.length() - 1;
                break; // Якщо знайдено збіг, переходимо до наступного символу
            }
        }
    }

    // Виведення зміненого тексту
    std::cout << inputText << std::endl;

    return 0;
}
