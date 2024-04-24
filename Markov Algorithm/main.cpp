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

    // ����������� ���� ����� ������ � ��������� �����
    for (size_t i = 0; i < inputText.length(); ++i) {
        // �������� ��� ������� �����
        for (const auto& keyPair : keys) {
            const std::string& key = keyPair.first;
            const std::string& value = keyPair.second;
            // �������� �� ��������, ��������� � ������� �������, �������� � ������
            if (inputText.substr(i, key.length()) == key) {
                // ���� ���, �������� ���� �� �������� ��������
                inputText.replace(i, key.length(), value);
                // ���� �������, ��� �������� ������ ���������� �������
                i += value.length() - 1;
                break; // ���� �������� ���, ���������� �� ���������� �������
            }
        }
    }

    // ��������� �������� ������
    std::cout << inputText << std::endl;

    return 0;
}
