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

void driver(string inFile)
{
  // cout << "searchTarget: " << searchTarget << endl;

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

  int arrSize = datas.size();
  string *newArr = new string[arrSize];

  // convert vector to array
  // this step should not be timed
  for (size_t looper = 0; looper < arrSize; looper++)
  {
    newArr[looper] = datas[looper];
  }

  auto begin = chrono::high_resolution_clock::now();

  heapSort(newArr, arrSize);

  bool checker = true;

  for (size_t looper = 0; looper < arrSize; looper++)
  {
    const string searchTarget = newArr[looper];

    const int targetIndex = binarySearch(newArr, searchTarget, 0, arrSize - 1);
    // cout << "innerLooper " << innerLooper << endl;
    // cout << "searchTarget " << searchTarget << endl;
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
  // for (size_t i = 0; i < 10; i++)
  // {
  //     driver("../10m.txt");
  // }

  // system("pause");
}