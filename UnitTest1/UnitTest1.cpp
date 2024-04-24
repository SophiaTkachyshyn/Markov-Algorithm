#include "pch.h"
#include "CppUnitTest.h"
#include <map>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

std::string processText(const std::string& inputText, const std::map<std::string, std::string>& keys) {
    std::string result = inputText;

    for (size_t i = 0; i < result.length(); ++i) {
        for (const auto& keyPair : keys) {
            const std::string& key = keyPair.first;
            const std::string& value = keyPair.second;

            if (result.substr(i, key.length()) == key) {
                result.replace(i, key.length(), value);
                i += value.length() - 1;
                break;
            }
        }
    }

    return result;
}

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:
        TEST_METHOD(TestTextProcessing)
        {
            std::map<std::string, std::string> keys = {
                {"1", "one"},
                {"3", "three"},
                {"two", "2"},
                {"four", "4"},
            };

            std::string inputText = "1s two 3 fours";
            std::string expectedOutput = "ones 2 three 4s";

            std::string actualOutput = processText(inputText, keys);

            Assert::AreEqual(expectedOutput, actualOutput);
        }

        TEST_METHOD(TestTextWithNoKeys)
        {
            std::map<std::string, std::string> keys = {
                {"1", "one"},
                {"3", "three"},
                {"two", "2"},
                {"four", "4"},
            };

            std::string inputText = "There are no keys here.";
            std::string expectedOutput = inputText; // Очікуємо, що результат не зміниться

            std::string actualOutput = processText(inputText, keys);

            Assert::AreEqual(expectedOutput, actualOutput);
        }

        TEST_METHOD(TestEmptyText)
        {
            std::map<std::string, std::string> keys = {
                {"1", "one"},
                {"3", "three"},
                {"two", "2"},
                {"four", "4"},
            };

            std::string inputText = "";
            std::string expectedOutput = inputText; // Очікуємо, що результат не зміниться

            std::string actualOutput = processText(inputText, keys);

            Assert::AreEqual(expectedOutput, actualOutput);
        }
    };
}
