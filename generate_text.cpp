#include <iostream>
#include <string>
#include <random>
#include <fstream>

using namespace std;

string gen_random_string(int len) {
  // Use Mersenne Twister engine for better randomness
  random_device rd;
  mt19937 generator(rd());

  // Define character distribution limited to lowercase letters (a-z)
  uniform_int_distribution<char> distribution('a', 'z');

  string randomString;
  randomString.reserve(len);  // Optimize for performance

  for (int i = 0; i < len; ++i) {
    randomString += distribution(generator);
  }

  return randomString;
}

string gen_random_seq(int len, const vector<char>& alphabet) {
  // Use Mersenne Twister engine for better randomness
  random_device rd;
  mt19937 generator(rd());

  // Define character distribution limited to the provided alphabet
  uniform_int_distribution<int> distribution(0, alphabet.size() - 1);

  string randomString;
  randomString.reserve(len);  // Optimize for performance

  for (int i = 0; i < len; ++i) {
    int randomIndex = distribution(generator);
    randomString += alphabet[randomIndex];
  }

  return randomString;
}

int main() {

  // generating a random string a-z
  int len = 5000000;
  string randomString = gen_random_string(len);

  ofstream outputFile("input_files/random_string.txt");

  if (outputFile.is_open()) {
    outputFile << randomString << endl;
    cout << "Random string saved to file: random_string.txt" << endl;
  } else {
    cerr << "Error opening file for writing!" << endl;
  }

  outputFile.close();

  // genrating arandom string with alphabets {'A','T','C',;'G'}

  // vector<char> alphabet = {'A', 'T', 'C', 'G'};

  // string random_seq = gen_random_seq(len, alphabet);

  // ofstream outputFile("input_files/random_seq.txt");

  // if (outputFile.is_open()) {
  //   outputFile << random_seq << endl;
  //   cout << "Random sequence saved to file: random_seq.txt" << endl;
  // } else {
  //   cerr << "Error opening file for writing!" << endl;
  // }

  // outputFile.close();

  return 0;
}
