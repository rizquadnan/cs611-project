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

inline string &trimPadding(string &s)
{
  const char *ws = "@";

  s.erase(s.find_last_not_of(ws) + 1);
  return s;
}

int linearSearchModified(string *arr, string target, int begin, int end)
{
  const string cleanTarget = trimPadding(trim(target));

  for (int i = begin; i < end; i++)
  {
    const string cleanString = trimPadding(trim(target));
    // cout << "i " << i << endl;
    // cout << "end " << end << endl;

    // cout << "trim(arr[i]).length(): " << trim(arr[i]).length() << endl;
    // cout << "i " << i << endl;

    // cout << "arr[i] " << arr[i] << endl;
    // cout << "target " << target << endl;

    // if length not equal no need to do string comparison
    if (cleanString.length() != cleanTarget.length())
    {
      continue;
    }

    if (cleanString == cleanTarget)
    {
      // cout << "KETEMUU" << endl;
      // cout << "arr[i] " << arr[i] << endl;
      // cout << "target " << target << endl;
      return i;
    }
    // cout << "" << endl;
  }

  return -1;
}

void heapify(string arr[], int n, int i)
{
  // Find largest among root, left child and right child
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < n && arr[left] > arr[largest])
    largest = left;

  if (right < n && arr[right] > arr[largest])
    largest = right;

  // Swap and continue heapifying if root is not largest
  if (largest != i)
  {
    swap(arr[i], arr[largest]);
    heapify(arr, n, largest);
  }
}

// main function to do heap sort
void heapSort(string arr[], int n)
{
  // Build max heap
  for (int i = n / 2 - 1; i >= 0; i--)
    heapify(arr, n, i);

  // Heap sort
  for (int i = n - 1; i >= 0; i--)
  {
    swap(arr[0], arr[i]);

    // Heapify root element to get highest element at root again
    heapify(arr, i, 0);
  }
}

int binarySearch(string arr[], string x, int l, int r)
{
  // Loop to implement Binary Search
  while (l <= r)
  {

    // Calculatiing mid
    int m = l + (r - l) / 2;

    // Some random value assigned
    // as 0 belongs to index
    int res = -1000;

    if (x == (arr[m]))
      res = 0;

    // Check if x is present at mid
    if (res == 0)
      return m;

    // If x greater, ignore left half
    if (x > (arr[m]))
      l = m + 1;

    // If x is smaller, ignore right half
    else
      r = m - 1;
  }

  return -1;
}

void driver(string inFile, int threshold)
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

  auto end1 = chrono::high_resolution_clock::now();

  auto begin2 = chrono::high_resolution_clock::now();

  heapSort(inlineArr, arrSize);

  bool checker = false;

  for (size_t looper = 0; looper < arrSize; looper++)
  {
    string searchTarget = inlineArr[looper];
    char firstLetter = searchTarget[0];
    int asciiKey = int(firstLetter);
    int begin = markers[asciiKey][0];
    int end = markers[asciiKey][1];

    int targetIndex = -1;
    if (end - begin > threshold)
    {
      targetIndex = binarySearch(inlineArr, searchTarget, begin, end);
    }
    else
    {
      targetIndex = linearSearchModified(inlineArr, searchTarget, begin, end);
    }
    // cout << "innerLooper " << innerLooper << endl;
    // cout << "searchTarget " << searchTarget << endl;
    // cout << "targetIndex " << targetIndex << endl;
    // cout << "" << endl;

    if (targetIndex != -1)
    {
      checker = true;
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
}

int main(int argc, char* argv[])
{
  if (argc == 1)
  {
    cout << "Please provide the maximum threshold to apply linear search" << endl;
    return 1;
  }

  cout << "Gutenberg" << endl;
  cout << "Linear Search Threshold: " << argv[1] << endl;
  cout << "2.3m" << endl;
  for (size_t i = 0; i < 3; i++)
  {
    driver("./datasets/GutenbergWordsFile.txt", atoi(argv[1]));
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
  // for (size_t i = 0; i < 10; i++)
  // {
  //     driver("../10m.txt");
  // }

  // system("pause");
}