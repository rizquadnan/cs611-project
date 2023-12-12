#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

// trim from end of string (right)
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

int linearSearch(string *arr, string target, int begin, int end)
{
  for (int i = begin; i < end; i++)
  {
    // cout << "i " << i << endl;
    // cout << "arr[i] " << arr[i] << endl;
    // cout << "target " << target << endl;

    if (trim(arr[i]) == trim(target))
    {
      // cout << "KETEMUU" << endl;
      return i;
    }
    // cout << "" << endl;
  }

  return -1;
}

string *getRandomStringsFromFile(string inFile, int numOfRandomStrings)
{
  // seed random generator
  srand(time(NULL));

  string myText;
  ifstream myReadFile(inFile);

  vector<string> datas;
  string *res = new string[numOfRandomStrings];

  while (getline(myReadFile, myText))
  {
    datas.push_back(myText);
  }

  myReadFile.close();

  int arrSize = datas.size();

  for (size_t looper = 0; looper < numOfRandomStrings; looper++)
  {
    int randomIndex = rand() % arrSize;
    res[looper] = trim(datas[randomIndex]);

    // cout << "looper :" << looper << endl;
    // cout << "randomIndex :" << randomIndex << endl;
    // cout << "datas[randomIndex] :" << datas[randomIndex] << endl;
    // cout << "" << endl;
  }

  return res;
}

void driver(string inFile)
{
  // cout << "searchTarget: " << searchTarget << endl;

  string myText;
  ifstream myReadFile(inFile);
  // ofstream myFile(outFile);

  vector<string> datas;

  // create ascii table with empty value for counter
  int asciiSize = 128;
  int **markers = new int *[asciiSize];

  for (size_t looper = 0; looper < asciiSize; looper++)
  {
    markers[looper] = new int[3]{0};
  }

  // put textfile data to vector
  // this step should not be timed
  while (getline(myReadFile, myText))
  {
    datas.push_back(myText);
  }

  myReadFile.close();

  int arrSize = datas.size();
  string *newArr = new string[arrSize];
  string *inlineArr = new string[arrSize];

  // convert vector to array
  // this step should not be timed
  for (size_t looper = 0; looper < arrSize; looper++)
  {
    newArr[looper] = datas[looper];
  }

  // start counting each word by the first letter
  auto begin1 = chrono::high_resolution_clock::now();
  for (size_t looper = 0; looper < arrSize; looper++)
  {
    markers[int(newArr[looper][0])][1] += 1;
  }

  // add begin and end for each array
  for (size_t looper = 0; looper < asciiSize; looper++)
  {

    if (looper == 0)
    {
      markers[looper][0] = 0;
      markers[looper][1] = markers[looper][1];
    }
    else
    {
      markers[looper][0] = markers[looper - 1][1];
      markers[looper][1] = markers[looper][0] + markers[looper][1];
    }
  }

  for (size_t looper = 0; looper < arrSize; looper++)
  {
    int ascii = int(newArr[looper][0]);
    int start = markers[ascii][0];
    int count = start + markers[ascii][2];
    inlineArr[count] = newArr[looper];
    markers[ascii][2] += 1;
  }

  // for (size_t looper = 0; looper < arrSize; looper++) {
  //     cout << "looper: " << looper << endl;
  //     cout << "inlineArr[looper]: " << inlineArr[looper] << endl;
  //     cout << "" << endl;
  // }

  auto end1 = chrono::high_resolution_clock::now();
  // cout << "Data preparation:" << chrono::duration<double>(end1 - begin1).count() << endl;
  // cout << chrono::duration<double>(end1 - begin1).count() << endl;

  auto begin2 = chrono::high_resolution_clock::now();

  bool checker = true;

  for (size_t looper = 0; looper < arrSize; looper++)
  {
    string searchTarget = inlineArr[looper];
    char firstLetter = searchTarget[0];
    int asciiKey = int(firstLetter);
    int begin = markers[asciiKey][0];
    int end = markers[asciiKey][1];

    const int targetIndex = linearSearch(inlineArr, searchTarget, begin, end);

    if (targetIndex == -1)
    {
      checker = false;
    }
  }

  auto end2 = chrono::high_resolution_clock::now();

  if (checker)
  {
    // cout << "Data sorting:" << chrono::duration<double>(end2 - begin2).count() << endl;
    cout << chrono::duration<double>(end2 - begin2).count() << endl;
    // cout << "Total time:" << chrono::duration<double>(end2 - begin1).count() << endl;
  }
  else
  {
    cout << "Not Found" << endl;
    cout << chrono::duration<double>(end2 - begin2).count() << endl;
  }

  // for (size_t looper = 0; looper < arrSize; looper++)
  // {
  //     myFile << inlineArr[looper] << endl;
  // }

  // // myFile.close();
}

int main()
{

  // cout << "Gutenberg" << endl;
  // cout << "2.3m" << endl;
  // for (size_t i = 0; i < 10; i++)
  // {
  //   driver("./datasets/GutenbergWordsFile.txt");
  // }

  cout << "1k" << endl;
  for (size_t i = 0; i < 10; i++)
  {
    driver("./datasets/1k.txt");
  }

  cout << "10k" << endl;
  for (size_t i = 0; i < 10; i++)
  {
    driver("./datasets/10k.txt");
  }

  cout << "100k" << endl;
  for (size_t i = 0; i < 10; i++)
  {
    driver("./datasets/100k.txt");
  }

  cout << "1m" << endl;
  for (size_t i = 0; i < 10; i++)
  {
    driver("../1m.txt");
  }

  // cout << "2m" << endl;
  // for (size_t i = 0; i < 10; i++)
  // {
  //     driver("../2m.txt");
  // }
  // cout << "3m" << endl;
  // for (size_t i = 0; i < 10; i++)
  // {
  //     driver("../3m.txt");
  // }
  // cout << "10m" << endl;
  // randomStrings = getRandomStringsFromFile("../1k.txt", 10);
  // for (size_t i = 0; i < 10; i++)
  // {
  //     driver("../10m.txt");
  // }

  // system("pause");
}