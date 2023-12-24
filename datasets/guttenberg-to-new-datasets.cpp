#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

inline string &rtrim(string &s)
{
  const char *ws = " \t\n\r\f\v";

  s.erase(s.find_last_not_of(ws) + 1);
  return s;
}

// trim from beginning of string (left)
inline string &ltrim(string &s)
{
  const char *ws = " \t\n\r\f\v";

  s.erase(0, s.find_first_not_of(ws));
  return s;
}

// trim from both ends of string (right then left)
inline string &trim(string &s)
{
  const char *ws = " \t\n\r\f\v";

  return ltrim(rtrim(s));
}

void clearFile(string path) {
  std::ofstream ofs;
  ofs.open(path, std::ofstream::out | std::ofstream::trunc);
  ofs.close();
}

void driver(string inFile)
{
  string myText;
  ifstream myReadFile(inFile);
  // ofstream myFile(outFile);

  vector<string> datas;

  // put textfile data to vector
  // this step should not be timed
  while (getline(myReadFile, myText))
  {
    datas.push_back(myText);
  }

  myReadFile.close();

  int initialArrSize = datas.size();
  vector<string> filteredDatas;
  int arrSize = 0;
  for (size_t looper = 0; looper < initialArrSize; looper++)
  {
    if (trim(datas[looper]).length() >= 4)
    {
      arrSize++;
      filteredDatas.push_back((datas[looper]));
    }
  }

  string *arr = new string[arrSize];

  // convert vector to array
  // this step should not be timed
  for (size_t looper = 0; looper < arrSize; looper++)
  {
    arr[looper] = filteredDatas[looper];
  }

  const int one_k = 1000;
  const int ten_k = 10000;
  const int one_hundred_k = 100000;
  const int one_million_k = 1000000;

  clearFile("./guttenberg_1k.txt");
  ofstream ofs_1("./guttenberg_1k.txt");
  for (size_t looper = 0; looper < one_k; looper++)
  {
    ofs_1 << arr[looper];
    ofs_1 << endl;
  }

  clearFile("./guttenberg_10k.txt");
  ofstream ofs_2("./guttenberg_10k.txt");
  for (size_t looper = 0; looper < ten_k; looper++)
  {
    ofs_2 << arr[looper];
    ofs_2 << endl;
  }

  clearFile("./guttenberg_100k.txt");
  ofstream ofs_3("./guttenberg_100k.txt");
  for (size_t looper = 0; looper < one_hundred_k; looper++)
  {
    ofs_3 << arr[looper];
    ofs_3 << endl;
  }

  clearFile("./guttenberg_1m.txt");
  ofstream ofs_4("./guttenberg_1m.txt");
  for (size_t looper = 0; looper < one_million_k; looper++)
  {
    ofs_4 << arr[looper];
    ofs_4 << endl;
  }
}

int main()
{
  driver("./new_gutenberg_wordfreq.txt");
}