//
//  main.cpp
//  CPP-PRG-09-13-Movie-Statistics
//
//  Created by Keith Smith on 10/31/17.
//  Copyright © 2017 Keith Smith. All rights reserved.
//
//  Write a program that can be used to gather statistical data about the number of movies
//  college students see in a month. The program should perform the following steps:
//
//      A)  Ask the user how many students were surveyed. An array of integers with this many
//          elements should then be dynamically allocated.
//      B)  Allow the user to enter the number of movies each student saw into the array.
//      C)  Calculate and display the average, median, and mode of the values entered. (Use the
//          functions you wrote in Programming Challenges 8 and 9 to calculate the median and
//          mode.)
//
//  Input Validation: Do not accept negative numbers for input.

#include <iostream>

using namespace std;

int *getArraySize();
int *fillArray(int *, int);
int *sortArray(int *, int);
float *calculateAverage(int *, int);
float *calculateMedian(int *, int);
int *calculateMode(int *, int);
int *generateArrayTally(int *, int);
int *sortArrayNumbers(int *, int *, int);
void testForNoModeCase(int *, int);

void displayResults(float *, float *, int *);
void displayArray(int *, int);

int main()
{
    int *intArrayMovies = nullptr;
    int *intArraySize = nullptr;
    int *intArrayMode = nullptr;
    
    float *fltArrayAverage = nullptr;
    float *fltArrayMedian = nullptr;
    
    int *intModeTally = nullptr;
    
    intArraySize = getArraySize();
    
    intArrayMovies = fillArray(intArrayMovies, *intArraySize);
    intArrayMovies = sortArray(intArrayMovies, *intArraySize);
    
    fltArrayAverage = calculateAverage(intArrayMovies, *intArraySize);
    fltArrayMedian = calculateMedian(intArrayMovies, *intArraySize);
    
    intModeTally = generateArrayTally(intArrayMovies, *intArraySize);
    
    testForNoModeCase(intModeTally, *intArraySize);
    
    intArrayMovies = sortArrayNumbers(intModeTally, intArrayMovies, *intArraySize);
    
    intArrayMode = &intArrayMovies[0];
    
    displayResults(fltArrayAverage, fltArrayMedian, intArrayMode);
    
    return 0;
}

int *getArraySize()
{
    int *intArrSize = nullptr;
    
    intArrSize = new int;
    
    cout << "Please enter the size of the array: ";
    cin >> *intArrSize;
    while(!cin || *intArrSize <= 1 || *intArrSize > 100)
    {
        cout << "Please enter an array size between 2 and 100: ";
        cin.clear();
        cin.ignore();
        cin >> *intArrSize;
    }
    
    return intArrSize;
}

int *fillArray(int *intArr, int intSize)
{
    intArr = new int[intSize];
    
    for (int i = 0 ; i < intSize ; i++)
    {
        cout << "Please enter value " << (i + 1) << " of " << intSize << ": ";
        cin >> intArr[i];
        while(!cin || intArr[i] < -100 || intArr[i] > 100)
        {
            cout << "Please enter a value between -100 and 100: ";
            cin.clear();
            cin.ignore();
            cin >> intArr[i];
        }
    }
    
    return intArr;
}

int *sortArray(int *intArr, int intSize)
{
    int intMax;
    int intIndex;
    
    for (intMax = (intSize -1) ; intMax > 0 ; intMax--)
    {
        for (intIndex = 0 ; intIndex < intMax ; intIndex++)
        {
            if (intArr[intIndex] > intArr[intIndex + 1])
            {
                swap(intArr[intIndex], intArr[intIndex + 1]);
            }
        }
    }
    
    return intArr;
}

void swap(int *intA, int *intB)
{
    int *intTemp = nullptr;
    
    intTemp = intA;
    intA = intB;
    intB = intTemp;
}

float *calculateAverage(int *intArr, int intSize)
{
    float *fltAverage = nullptr;
    float *fltRunningTotal = nullptr;
    
    fltAverage = new float;
    fltRunningTotal = new float;
    
    *fltRunningTotal = 0.0f;
    
    for (int i = 0 ; i < intSize ; i++)
    {
        *fltRunningTotal += intArr[i];
    }
    
    *fltAverage = *fltRunningTotal / intSize;
    
    return fltAverage;
}

float *calculateMedian(int *intArr, int intSize)
{
    float *fltMedian = nullptr;
    
    fltMedian = new float;
    
    if(intSize % 2 != 0)
    {
        *fltMedian = intArr[intSize / 2];
    }
    else if(intSize % 2 == 0)
    {
        *fltMedian = intArr[intSize / 2 - 1] + intArr[intSize / 2];
        *fltMedian /= 2.0f;
    }
    
    return fltMedian;
}

int *generateArrayTally(int *intArrIntegers, int intArrSize)
{
    int *intArrSorted = nullptr;
    int *intArrTally = nullptr;
    
    intArrSorted = new int[intArrSize];
    intArrTally = new int[intArrSize];
    
    for (int i = 0 ; i < intArrSize ; i++)
    {
        intArrSorted[i] = intArrIntegers[i];
        intArrTally[i] = 0;
    }
    
    for (int i = 0 ; i < intArrSize ; i++)
    {
        for (int j = 0 ; j < intArrSize ; j++)
        {
            if (intArrIntegers[i] == intArrSorted[j])
            {
                intArrSorted[j] = intArrIntegers[i];
                intArrTally[j]++;
                break;
            }
        }
    }
    
    return intArrTally;
}

int *sortArrayNumbers(int *intArrTally, int *intArrIntegers, int intArrSize)
{
    int intStart;
    int intMinIndex;
    
    int *fltMinElement = nullptr;
    
    int *strMinElement = nullptr;
    
    for(intStart = 0 ; intStart < (intArrSize - 1) ; intStart++)
    {
        intMinIndex = intStart;
        fltMinElement = &intArrTally[intStart];
        
        for(int index = (intStart + 1) ; index < intArrSize ; index++)
        {
            if(intArrTally[index] > *fltMinElement)
            {
                fltMinElement = &intArrTally[index];
                strMinElement = &intArrIntegers[index];
                intMinIndex = index;
            }
        }
        swap(intArrTally[intMinIndex], intArrTally[intStart]);
        swap(intArrIntegers[intMinIndex], intArrIntegers[intStart]);
    }
    
//    cout << "Tally sorted: " << endl;
//    for (int i = 0 ; i < intArrSize ; i++)
//    {
//        cout << *(intArrTally + i) << endl;
//    }
//    cout << endl;
    
    return intArrIntegers;
}

void testForNoModeCase(int *intArrTally, int intArrSize)
{
//    bool booAreAllSame = false;
    int intCounter = 0;
    
    for(int i = 0 ; i < intArrSize ; i++)
    {
        if(intArrTally[i] == 1)
        {
            intCounter++;
        }
    }

//    if(intCounter == intArrSize)
//    {
//        cout << "There is no mode in that set." << endl;
//    }
    
//    if(booAreAllSame == true)
//    {
//        cout << "There is no mode in that set." << endl;
//        exit(0);
//    }
}

void displayResults(float *fltAverage, float *fltMedian, int *intMode)
{
    cout << "The average number of movies seen was: " << *fltAverage << endl;
    cout << "The median number of movies seen was: " << *fltMedian << endl;
    if (*intMode != 1)
    {
        cout << "The mode of the number of movies seen was: " << *intMode << endl;
    }
    else if(*intMode == 1)
    {
        cout << "There is no mode in that set." << endl;
    }
}

void displayArray(int *intArr, int intSize)
{
    for (int i = 0 ; i < intSize ; i++)
    {
        cout << intArr[i] << endl;
    }
}
