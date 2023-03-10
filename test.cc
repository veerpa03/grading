/**
 *    @file: test.cc
 *  @author: viraj parmar
 *   @email: vp867022@ohio.edu  
 *    @date: 3/9/2023         
 *   @brief: This program take the input form the file name test.txt and grade according to the students ansers ansd store the result in the 
 *           output.txt file. Also this file shows the average of the class and alongwith that the highest in the class
 *  
 */





#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cctype>
#include<iomanip>
using namespace std;

//Function to grade a single student's score and return the score
int gradeScore(string answers, string key)
{
    int score = 0,lt;
    lt=answers.length();
    //Loop through each character in the student's answer string
    for(int i = 0; i < lt; i++)
    {
        if(answers[i]>='A' && answers[i]<='D' )
        {
            if(answers[i] == key[i])
            {
               score++;
            }
        }
        else if(answers[i]>='a' && answers[i]<='d')
        {
            answers[i]=answers[i]-32;
            if(answers[i] == key[i])
            {
               score++;
            }
            
        }
        
        //If the character is equal to the corresponding character in the key, increment the score
        
    }
    score=(score/lt)*100;
    return score;
}
//Function to return a letter grade for a score
string letterGrade(int score)
{
    string grade;
    if(score >= 90 && score <= 100)
    {
        grade = "A";
    }
    else if(score >= 80 && score <= 89)
    {
        grade = "B";
    }
    else if(score >= 70 && score <= 79)
    {
        grade = "C";
    }
    else if(score >= 60 && score <= 69)
    {
        grade = "D";
    }
    else
    {
        grade = "F";
    }
    return grade;
}
//Function to output a single student's report to the screen
void outputReport(string firstName, string lastName, string answers, string key)
{
    cout << lastName << ", " << firstName << endl;
    cout << "------------------------------------------------" << endl;
    cout << "Answers, correct answer in parenthesis" << endl;
    int lt;
    lt=answers.length();
    //Loop through each character in the student's answer string
    for(int i = 0; i < lt; i++)
    {
        //If the character is equal to the corresponding character in the key, print the correct answer
        if(answers[i] == key[i])
        {
            cout << i+1 << ": " << answers[i] << "(" << key[i] << ")  ";
        }
        //If the character is not equal to the corresponding character in the key, print the incorrect answer
        else
        {
            cout << i+1 << ": " << answers[i] << "(" << key[i] << ")  ";
        }
    }
    cout << endl;
    int score = gradeScore(answers, key);
    string grade = letterGrade(score);
    cout << "Score: " << score << "% " << grade << endl;
    cout << "------------------------------------------------" << endl;
}
int main()
{
    
    //Open input file
    ifstream inputFile;
    inputFile.open("tests.txt");
    if(inputFile.fail())
    {
        cout << "Error: Could not open input file!" << endl;
        return 0;
    }
    //Open output file
    ofstream outputFile;
    outputFile.open("output.txt");
    if(outputFile.fail())
    {
        cout << "Error: Could not open output file!" << endl;
        return 0;
    }
    
    //Read answer key from input file
    string key;
    getline(inputFile, key);
    //outputFile << "Class average: ";
    //Read each student record from the input file
    string firstName, lastName, answers;
    int totalScore = 0;
    int numStudents = 0;
    
    while(inputFile >> firstName >> lastName >> answers)
    {
        //Output student's report to the screen
        outputReport(firstName, lastName, answers, key);
        //Calculate student's score
        int score = gradeScore(answers, key);
        totalScore =totalScore+ score;
        numStudents++;
        int lt=answers.length();
        
        //Output student's report to the output file
        outputFile << lastName << ", " << firstName << endl;
        for(int i = 0; i < lt; i++)
        {
            if(answers[i] == key[i])
            {
                outputFile << i+1 << ": " << answers[i] << "(" << key[i] << ")  ";
            }
            else
            {
                outputFile << i+1 << ": " << answers[i] << "(" << key[i] << ")  ";
            }
        }
        outputFile << endl;
        outputFile << "Score: " << score << "% " << letterGrade(score) << endl;
        outputFile << "------------------------------------------------" << endl;
    }
    //Calculate and output average score to output file
    double averageScore = totalScore / (double)numStudents;
    outputFile << "Class average: " << averageScore << "% " << letterGrade(averageScore) << endl;
    outputFile << "------------------------------------------------" << endl;
    //Find and output students with highest grade to output file
    outputFile << "Students with the highest grade (100%):" << endl;
    inputFile.clear();
    //inputFile.seekg(0);
    getline(inputFile, key);
    while(inputFile >> firstName >> lastName >> answers)
    {
        int score = gradeScore(answers, key);
        if(score == 100)
        {
            outputFile << firstName << " " << lastName << endl;
        }
    }
    outputFile << "------------------------------------------------" << endl;
    
    //Close files
    inputFile.close();
    outputFile.close();
    return 0;
}