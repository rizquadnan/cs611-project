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

  // convert vector to array
  // this step should not be timed
  for (size_t looper = 0; looper < arrSize; looper++)
  {
    newArr[looper] = datas[looper];
  }

  auto begin = chrono::high_resolution_clock::now();

  bool checker = true;

  for (size_t looper = 0; looper < arrSize; looper++)
  {
    const string searchTarget = newArr[looper];
    // cout << "searchTarget " << searchTarget << endl;

    const int targetIndex = linearSearch(newArr, searchTarget, 0, arrSize);
    // cout << "targetIndex " << targetIndex << endl;
    // cout << "" << endl;

    if (targetIndex == -1)
    {
      checker = false;
    }
  }
  
  auto end = chrono::high_resolution_clock::now();

  if (checker)
  {
    cout << chrono::duration<double>(end - begin).count() << endl;
  }
  else
  {
    cout << "Not Found" << endl;
    cout << chrono::duration<double>(end - begin).count() << endl;
  }
}

int main()
{

  cout << "Gutenberg" << endl;
  cout << "2.3m" << endl;
  for (size_t i = 0; i < 10; i++)
  {
    driver("./datasets/GutenbergWordsFile.txt");
  }

  // cout << "1k" << endl;
  // for (size_t i = 0; i < 10; i++)
  // {
  //   driver("./datasets/1k.txt");
  // }

  // cout << "10k" << endl;
  // for (size_t i = 0; i < 10; i++)
  // {
  //   driver("./datasets/10k.txt");
  // }

  // cout << "100k" << endl;
  // for (size_t i = 0; i < 10; i++)
  // {
  //   driver("./datasets/100k.txt");
  // }

  // cout << "1m" << endl;
  // for (size_t i = 0; i < 10; i++)
  // {
  //   driver("./datasets/1m.txt");
  // }

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