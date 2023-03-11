#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

//declare functions
double grade(string keys, string answer);
char getLetterGrade(double score);
void report(ofstream& fout, string firstName, string lastName, string keys, string answers, double score);


int main(int argc, char* argv[])
{
    //check if we have correct number of command line arguments
    if (argc != 3)
    {
        cout << "Please, provide input and output files as command line arguments!" << endl;
        return 0;
    }
    // declare an stream object reading/writing file
    ifstream fin;
    ofstream fout;

    //declare file name variables
    string inFileName=argv[1];
    string outFileName = argv[2];
   

    // try to open the file 
    fin.open(inFileName);

    //check if success
    if (!fin)
    {
        cout << inFileName<< " file could not be opened for reading..." << endl;
        return 0;
    }

    // try to open the file 
    fout.open(outFileName);

    //check if success
    if (!fout)
    {
        cout << outFileName << " file could not be opened for writing..." << endl;
        return 0;
    }

    //read keys
    string keys;
    getline(fin, keys);
   
    double score,sumScore=0,maxScore=0;   
    int numStudents = 0;
    string names[100];
    double scores[100];

    //declare string variables for each student
    string firstName, lastName, answers;
    //loop as long as there is a student
    while (fin >> firstName >> lastName)
    {     
        //now read answers
        getline(fin, answers);
        //it turns out it reads with first space, so move one space left
        for (unsigned int i = 0; i < answers.length() - 1; i++)
            answers.at(i) = answers.at(i + 1);
        //calculate grade
        score = grade(keys, answers);
        //sum scores
        sumScore += score;

        //write report
        report(fout, firstName, lastName, keys, answers, score);  

        //remember names and scores
        names[numStudents] = firstName + " " + lastName;
        scores[numStudents] = score;

        //count number of students
        numStudents++;
        //remember max score
        if (maxScore < score) maxScore = score;

    }
    //calculate average score
    double avgScore = sumScore / numStudents;
    //write average
    cout << "Class average: " << setprecision(1) << fixed << avgScore<< "% "
        <<getLetterGrade(avgScore)<<endl;
    fout << "Class average: " << setprecision(1) << fixed << avgScore << "% "
        << getLetterGrade(avgScore) << endl;
    cout << "-----------------------------------------------------" << endl;
    fout << "-----------------------------------------------------" << endl;

    //write max score
    cout << "Students with the highest grade ("<<maxScore <<"%):" << endl;
    for (int i = 0; i < numStudents; i++)
    {
        if (maxScore == scores[i])
        {
            cout << names[i] << endl;
            fout << names[i] << endl;
        }
    }

    //close files    
    fout.close();
    fin.close();

	return 0;
}

//Write a function that grades a single student score and returns the score.
double grade(string keys, string answers)
{
    //result of grade
    int result = 0;
    //loop to take wach question
    for (unsigned int i = 0; i < keys.length(); i++)
    {
        //if keys and answers are same, add point to result
        if (tolower(keys.at(i)) == tolower(answers.at(i))) result++;
    }
    //return result
    return result*100.0 / keys.length();
}

//Write a function that returns a letter grade for a score.
char getLetterGrade(double score)
{
    char letterGrade;
    //determine letter grade
    if (score >= 90) letterGrade = 'A';
    else if (score >= 80) letterGrade = 'B';
    else if (score >= 70) letterGrade = 'C';
    else if (score >= 60) letterGrade = 'D';
    else letterGrade = 'F';

    return letterGrade;
}

//Write a function that outputs a single student's report to the screen
void report(ofstream& fout, string firstName, string lastName, string keys, string answers, double score)
{
    //we display and write to file each time
    //write names
    cout << lastName << ", " << firstName << endl;
    fout << lastName << ", " << firstName << endl;
    cout << "-----------------------------------------------------" << endl;
    fout << "-----------------------------------------------------" << endl;
    cout << "Answers, correct answer in parenthesis" << endl;
    fout << "Answers, correct answer in parenthesis" << endl;
    char answer,key;
    //write answers
    for (unsigned int i = 0; i < keys.length(); i++)
    {
        answer = tolower(answers.at(i));
        key = tolower(keys.at(i));
        if (answer == ' ') answer = '-';
        cout << setw(2) << i + 1 << ": " << answer << "(" << key << ")   ";
        fout << setw(2) << i + 1 << ": " << answer << "(" << key << ")   ";
        if ((i + 1) % 5 == 0)
        {
            cout << endl;
            fout << endl;
        }
    }
    //write score and grade
    cout << endl << endl<<"Score: "<<score<<"% "<<getLetterGrade(score)<<endl;
    fout << endl << endl << "Score: " << score << "% " << getLetterGrade(score) << endl;
    cout << "-----------------------------------------------------" << endl << endl;
    fout << "-----------------------------------------------------" << endl << endl;

}
