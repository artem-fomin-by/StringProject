#include "pch.h"

#include <iostream>

#include "CppUnitTest.h"

#include <sstream>
#include <string>
#include <fstream>
#include <filesystem>
#include <random>

#include "Krit8.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Krit8Tests
{
	constexpr int Seed = 1000;

	TEST_CLASS(Krit8Tests)
	{
		public:
		TEST_CLASS_INITIALIZE(Krit8TestsInit)
		{
			setlocale(LC_ALL, "Russian");
		}

		TEST_METHOD(is_glTest)
		{
			const char gl1 = '\xC0';
			const char gl2 = '\xE0';

			const char nonGl1 = '\xC1';
			const char nonGl2 = '\xE1';

			Assert::IsTrue(is_gl(gl1));
			Assert::IsTrue(is_gl(gl2));
			Assert::IsFalse(is_gl(nonGl1));
			Assert::IsFalse(is_gl(nonGl2));
		}

		TEST_METHOD(is_soglTest)
		{
			const char nonSogl1 = '\xC0';
			const char nonSogl2 = '\xE0';

			const char sogl1 = '\xC1';
			const char sogl2 = '\xE1';

			Assert::IsFalse(is_sogl(nonSogl1));
			Assert::IsFalse(is_sogl(nonSogl2));
			Assert::IsTrue(is_sogl(sogl1));
			Assert::IsTrue(is_sogl(sogl2));
		}

		TEST_METHOD(is_wordTest)
		{
			const std::string nonWord1 = "À";
			const std::string nonWord2 = "123932901";
			const std::string word1 = "\xC0\xC0\xC0\xC0";
			const std::string word2 = "\xE1\xE1\xE1\xE1";

			Assert::IsFalse(is_word(nonWord1));
			Assert::IsFalse(is_word(nonWord2));
			Assert::IsTrue(is_word(word1));
			Assert::IsTrue(is_word(word2));
		}

		TEST_METHOD(parseTest)
		{
			const std::string word = "\xC0\xC0\xC0\xE1\xE1\xC0";
			const std::string nonWord = "fsd" + word + " !d";

			Assert::AreEqual(word.c_str(), parse(word).c_str());
			Assert::AreEqual(word.c_str(), parse(nonWord).c_str());
		}

		TEST_METHOD(check_beginTest)
		{
			const std::string word1 = (std::string)"\xE1\xC3\xE2" + "fkasdlds";
			const int expected1 = 3;
			const std::string word2 = ' ' + word1;
			const int expected2 = 0;

			Assert::AreEqual(expected1, check_begin(word1));
			Assert::AreEqual(expected2, check_begin(word2));
		}

		TEST_METHOD(check_endTest)
		{
			const std::string word1 = "fkasdlds\xE0\xC0";
			const int expected1 = 2;
			const std::string word2 = word1 + ' ';
			const int expected2 = 0;

			Assert::AreEqual(expected1, check_end(word1));
			Assert::AreEqual(expected2, check_begin(word2));
		}

		private:
		const std::string TextFilesRelLocation = "../TextFiles/";

		std::ofstream CreateTestFile(const std::string& filename) const
		{
			if(!std::filesystem::exists(TextFilesRelLocation))
			{
				std::filesystem::create_directory(TextFilesRelLocation);
			}

			return std::ofstream(TextFilesRelLocation + filename);
		}

		static std::string GenWord
			(int wordMinLength, int wordMaxLength, std::default_random_engine& gen, int& type)
		{
			const std::string gl = "\xC0";
			const std::string sogl = "\xC1";

			if(wordMaxLength < wordMinLength)
			{
				wordMaxLength = wordMinLength;
			}

			auto beginType1Dist = std::uniform_int_distribution<>(0, 3);
			auto endType1Dist = std::uniform_int_distribution<>(0, 3);
			auto letterDist = std::uniform_int_distribution<>('\xC0', '\xFF');
			auto wordLengthDist = std::uniform_int_distribution<>(wordMinLength, wordMaxLength);

			std::string word;
			type = 0;

			const int beginType = beginType1Dist(gen);
			switch(beginType)
			{
				case 1: word = sogl + gl; break;
				case 2: word = sogl + sogl + gl; type += 1; break;
				case 3: word = sogl + sogl + sogl + sogl + gl; break;
				default: word = gl;
			}

			std::string ending;
			const int endType = endType1Dist(gen);
			switch(endType)
			{
				case 1: ending = sogl + gl; break;
				case 2: ending = sogl + gl + gl; type += 2; break;
				case 3: ending = sogl + gl + gl + gl + gl; break;
				default: ending = sogl;
			}

			const int wordLength = wordLengthDist(gen);
			for(int i = word.size(); i < wordLength - ending.size(); i++)
			{
				word += (char)letterDist(gen);
			}

			return word + ending;
		}

		int GetTestFileReady
			(const std::string& filename, int length, int wordMinLength, int wordMaxLength, int& wordsCount) const
		{
			if(wordMinLength < 8)
			{
				wordMinLength = 8;
			}
			else if(wordMaxLength < wordMinLength)
			{
				wordMaxLength = wordMinLength;
			}

			auto testFile = CreateTestFile(filename);
			auto gen = std::default_random_engine(Seed);

			int prevType = 0;
			int correctPairsAmount = 0;
			wordsCount = 0;
			while(length >= wordMinLength)
			{
				int type;
				std::string word = GenWord(wordMinLength, wordMaxLength % length + 1, gen, type);
				testFile << word;
				testFile.flush();
				length -= word.size();

				if(length >= wordMinLength)
				{
					testFile << '\n';
					testFile.flush();
				}

				if(prevType >= 2 && type % 2 == 1)
				{
					correctPairsAmount++;
				}

				prevType = type;
				wordsCount++;
			}

			testFile.close();

			return correctPairsAmount;
		}

		public:
		TEST_METHOD(solveTest)
		{
			constexpr int fileLength = 1000;
			constexpr int wordMinLength = 10;
			constexpr int wordMaxLength = 20;

			const std::string filename = "1_s.txt";
			const std::string line1ExpectedBegin = "Parsing: ";
			const std::string line2ExpectedBegin = "Result: ";

			auto outputStream = std::stringstream();
			std::cout.rdbuf(outputStream.rdbuf());

			int wordsCount;
			int expected = GetTestFileReady(filename, fileLength, wordMinLength, wordMaxLength, wordsCount);
			solve(1);

			std::string output = outputStream.str();
			int lineSeparator = output.find('\n');
			std::string line1 = output.substr(0, lineSeparator);
			std::string line2 = output.substr(lineSeparator + 1);

			std::string expectedLine1 = line1ExpectedBegin + filename;
			Assert::AreEqual(expectedLine1.c_str(), line1.c_str());

			std::string result = std::to_string((double)expected / wordsCount);
			while(result.size() > 1 && result.back() == '0')
			{
				result.pop_back();
			}

			int comma = result.find(',');
			if(comma != std::string::npos)
			{
				result[comma] = '.';
			}

			std::string expectedLine2 = line2ExpectedBegin + result + '\n';
			Assert::AreEqual(expectedLine2.c_str(), line2.c_str());

			Assert::AreEqual(0, std::remove((TextFilesRelLocation + filename).c_str()));
		}
	};
}
