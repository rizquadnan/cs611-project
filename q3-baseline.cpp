#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <cmath>

using namespace std;

struct refer {
    int prefixCounter;
    vector<string> stringValues;
};

bool check(string * arr, int n)
{
   int i, j;
   bool result = true;;
   for (i = 0; i < n-1; i++)
   {
     for (j = 0; j < n-i-1; j++)
     {
        if (arr[j] > arr[j+1])
        {
           swap(arr[j], arr[j+1]);
           result = false;
           break;
        }
     }
 
     // IF no two elements were swapped
     // by inner loop, then break
     if (result)
     {
         return result;
     }
   }

   return result;
}

inline string& rtrim(string& s)
{
  const char* ws = " \t\n\r\f\v";

    s.erase(s.find_last_not_of(ws) + 1);
    return s;
}

// trim from beginning of string (left)
inline string& ltrim(string& s)
{
  const char* ws = " \t\n\r\f\v";

    s.erase(0, s.find_first_not_of(ws));
    return s;
}

// trim from both ends of string (right then left)
inline string& trim(string& s)
{
  const char* ws = " \t\n\r\f\v";

  return ltrim(rtrim(s));
}

void heapifyDn(vector<string>& arr, int n, int i) {
    // Find largest among root, left child and right child
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
  
    if (left < n && arr[left] > arr[largest])
      largest = left;
  
    if (right < n && arr[right] > arr[largest])
      largest = right;
  
    // Swap and continue heapifying if root is not largest
    if (largest != i) {
      swap(arr[i], arr[largest]);
      heapifyDn(arr, n, largest);
    }
  }
  
// main function to do heap sort
void heapSortDn(vector<string>& arr, int n) {
  // Build max heap
  for (int i = n / 2 - 1; i >= 0; i--)
    heapifyDn(arr, n, i);

  // Heap sort
  for (int i = n - 1; i >= 0; i--) {
    swap(arr[0], arr[i]);

    // Heapify root element to get highest element at root again
    heapifyDn(arr, i, 0);
  }
}

// An iterative binary search function.
int binarySearchDn(const vector<string>& arr, const string& x, int n)
{
    int l = 0;
    int r = n - 1;

    while (l <= r) {
        int m = l + (r - l) / 2;

        if (x == arr[m])
            return m;

        if (x > arr[m])
            l = m + 1;
        else
            r = m - 1;
    }

    return -1;
}


int table_based(string myText, int** tableBased)
{
    int myNumber = 0;
    string safeText = trim(myText);

    for (size_t i = 0; i < safeText.length(); i++)
    {
        if (safeText[i] == '@') {
            myNumber += 0;
        } else {
            myNumber += tableBased[i][safeText[i]] * pow(27, i);
        }
    }
    return myNumber;
}

void driver(string inFile)
{
    // start initate code to convert string to number
    int asciiSize = 128;
    int* asciiIndex = new int [asciiSize];

    for (size_t looper = 0; looper < asciiSize; looper++)
    {
        if (looper >= 64 && looper <= 90)
        {
            asciiIndex[looper] = looper - 63;
        }
        else if (looper >= 97 && looper <= 122)
        {
            asciiIndex[looper] = looper - 95;
        }
    }

    int tableBasedSize = 6;
    int** tableBased = new int* [tableBasedSize];

    for (size_t looper = 0; looper < tableBasedSize; looper++)
    {
        tableBased[looper] = new int[asciiSize]{0};
    }

    for (size_t tabloop = 0; tabloop < tableBasedSize; tabloop++)
    {
        for (size_t looper = 0; looper < asciiSize; looper++)
        {
            tableBased[tabloop][looper] = asciiIndex[looper];
        }
    }
    // end initate code to convert string to number

    string myText;
    ifstream myReadFile(inFile);

    vector<string> datas;
    // put textfile data to vector
    // this step should not be timed
    while (getline(myReadFile, myText))
    {
        datas.push_back(myText);
    }

    myReadFile.close();

    int arrSize = datas.size();
    string* newArr = new string[arrSize];

    // convert vector to array
    // this step should not be timed
    for (size_t looper = 0; looper < arrSize; looper++)
    {
        newArr[looper] = datas[looper];
    }

    // data prep start
    auto begin1 = chrono::high_resolution_clock::now();

    // fill in reference array
    int referenceArraySize = pow(27, 1) + pow(27, 2) + pow(27, 3) + 1;;
    refer* referenceArray = new refer[referenceArraySize];
    string stringVal;
    string firstThree;
    int integerRepresentation;

    for (size_t looper = 0; looper < referenceArraySize; looper++)
    {
      referenceArray[looper].prefixCounter = 0;
    } 

    for (size_t looper = 0; looper < arrSize; looper++)
    {
        stringVal = newArr[looper];
        firstThree = stringVal.substr(0, 3);
        integerRepresentation = table_based(firstThree, tableBased);

        referenceArray[integerRepresentation].prefixCounter += 1;
        referenceArray[integerRepresentation].stringValues.push_back(stringVal);
        // cout << "stringVal: " << stringVal << endl;
        // cout << "firstThree: " << firstThree << endl;
        // cout << "integerRepresentation: " << integerRepresentation << endl;
        // cout << "" << endl;
    }

    
    // code to see reference array
    // for (size_t looper = 0; looper < referenceArraySize; looper++)
    // {
    //   if (referenceArray[looper].prefixCounter > 0)
    //   {
    //     cout << "looper: " << looper << endl; 
    //     cout << "referenceArray[looper].prefixCounter: " << referenceArray[looper].prefixCounter << endl;
    //     int size = referenceArray[looper].stringValues.size();
    //     cout << "referenceArray[looper].stringValues.size(): " << size << endl;
    //     cout << "stringValues: " << endl;
        
    //     for (size_t looperIn = 0; looperIn < size; looperIn++) {
    //       cout << "referenceArray[looper].stringValues[looperIn]: " << referenceArray[looper].stringValues[looperIn] << endl;
    //     }

    //     cout << "" << endl;
    //   }
    // }

    // fill in indexed sorting array
    vector<refer> indexedSortingArray;
    for (size_t looper = 0; looper < referenceArraySize; looper++)
    {
      if (referenceArray[looper].prefixCounter > 0)
      {
        indexedSortingArray.push_back(referenceArray[looper]);
      }
    }

    // code to see indexed sorting array
    // int isaSize = indexedSortingArray.size();
    // for (size_t looper = 0; looper < isaSize; looper++)
    // {
    //   cout << "looper: " << looper << endl;
    //   cout << "indexedSortingArray[looper].prefixCounter: " << indexedSortingArray[looper].prefixCounter << endl;
    //   int size = indexedSortingArray[looper].stringValues.size();
    //   cout << "indexedSortingArray[looper].size(): " << size << endl;
    //   cout << "stringValues: " << endl;
      
    //   for (size_t looperIn = 0; looperIn < size; looperIn++) {
    //     cout << "indexedSortingArray[looper].stringValues[looperIn]: " << indexedSortingArray[looper].stringValues[looperIn] << endl;
    //   }

    //   cout << "" << endl;
    // }

    // sort this for binary search prep
    for (size_t looper = 0; looper < referenceArraySize; looper++)
    {
      if (referenceArray[looper].prefixCounter > 0)
      {
        heapSortDn(referenceArray[looper].stringValues, referenceArray[looper].stringValues.size());
      }
    } 

    auto end1 = chrono::high_resolution_clock::now();

    // start searching
    auto begin2 = chrono::high_resolution_clock::now();
    
    bool checker = true;

    string searchTarget;
    string targetFirstThree;
    int searchTargetInInt;
    refer targetRecord;
    int searchResultIndex;
    string notFoundString;

    for (size_t looper = 0; looper < arrSize; looper++)
    {
    //   cout << "MAsuk" << endl;
      searchTarget = newArr[looper];
      targetFirstThree = searchTarget.substr(0, 3);
      searchTargetInInt = table_based(targetFirstThree, tableBased);
      targetRecord = referenceArray[searchTargetInInt];

    //   cout << "looper: " << looper << endl;
    //   cout << "searchTarget: " << searchTarget << endl;
    //   cout << "targetFirstThree: " << targetFirstThree << endl;
    //   cout << "searchTargetInInt: " << searchTargetInInt << endl;
    //   cout << "targetRecord.prefixCounter: " << targetRecord.prefixCounter << endl;
    //   int size = targetRecord.stringValues.size();
    //   cout << "stringValues:" << endl;
    //   for (size_t looperIn = 0; looperIn < size; looperIn++) 
    //   {
    //     cout << "targetRecord.stringValues[looperIn]: " << targetRecord.stringValues[looperIn] << endl;
    //   }

    //   cout << "" << endl;

      int targetIndex = binarySearchDn(targetRecord.stringValues, searchTarget, targetRecord.stringValues.size());

      if (targetIndex == -1) {
        checker = false;
        notFoundString = searchTarget;
        break;
      }
    }

    auto end2 = chrono::high_resolution_clock::now();

    if (checker)
    {
        cout << chrono::duration<double>(end2 - begin2).count() << endl;
    }
    else
    {
        cout << "Something went wrong" << endl;
        cout << notFoundString << endl;
        cout << chrono::duration<double>(end2 - begin2).count() << endl;
    }
}

int main()
{
    int numOfIterations = 10;

    cout << "1k" << endl;
    for (size_t i = 0; i < numOfIterations; i++)
    {
        driver("../datasets/1k.txt");
    }

    cout << "10k" << endl;
    for (size_t i = 0; i < numOfIterations; i++)
    {
        driver("../datasets/10k.txt");
    }

    cout << "100k" << endl;
    for (size_t i = 0; i < numOfIterations; i++)
    {
        driver("./datasets/100k.txt");
    }

    // cout << "1m" << endl;
    // for (size_t i = 0; i < numOfIterations; i++)
    // {
    //     driver("./datasets/1m.txt");
    // }

    // cout << "10m" << endl;
    // for (size_t i = 0; i < numOfIterations; i++)
    // {
    //     driver("./datasets/10m.txt");
    // }
}