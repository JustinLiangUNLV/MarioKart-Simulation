#include "priorityQ.cpp"
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

string toLowerCase(const string& s); // function to lowercase strings

int main()
{
    priorityQ<string, double> marioKart; // create a custom priority object called marioKart
    unordered_map<string, bool> updatedAlready; // unordered map to hold racers that were updated already within each interval
    unordered_map<string, bool> finishedMap; // unordered map to hold every racer that finished
    vector<string> racers; // vector to hold all the names of the racers
    string racerName; // temp string variable for populating vector
    double initialPriority = 50; // initial priority variable

    while(cin >> racerName) // while reading inputs
    {
        if (racerName == "END") // if cin hits end
        {
            break; // break out of this while loop
        }
        racers.push_back(toLowerCase(racerName)); // otherwise push all the racers into the vector and lowercase their names
    }

    for(const auto& nameOfRacer : racers) // iterate through the vector using temp variable nameOfRacer
    {
        marioKart.push_back(nameOfRacer, initialPriority); // push back each name and their priority in the queue
    }
    
    string intervalRacerName; // temp variable to hold the racerNames within each interval
    double updatedPriority; // temp variable to hold the updated priorities for each racer
    int interval = 1; // set the interval variable to start at 1
    int rank = 1; // temp variable to hold the rank in which they finished the race
    int remainingRacers = racers.size(); // temp variiable to hold how many racers are left in the race

    while(!marioKart.isEmpty()) // while the queue is not empty
    {

        cout << endl;
        cout << "Interval " << interval << endl; // output the interval we are on
        cout << endl;

        while(marioKart.get_front_priority() <= 0) // check at the beginning of the loop if the front racer has a priority of 0 or less
        {
            string finishedRacerName = marioKart.get_front_key(); // if so, get the racers name and assign to temp string
            if(!finishedMap[finishedRacerName]) // checks if the front racer has already been accounted for
            { // if not
                string toUpper = finishedRacerName; // create a temp string
                for(int i = 0; i < 1; i++) // this for loop updates the first index of the string to be uppercase
                {
                    if(toUpper[i] >= 'a' && toUpper[i] <= 'z') // uppercase algorithm
                    {
                        toUpper[i] = toUpper[i] - 32; // similar to lowercase algorithm but opposite
                    }
                }
                cout << rank << " " << toUpper << endl; // output their rank/place in the race along with thier name
                finishedMap[finishedRacerName] = true; // set that racer to be true so it doesn't get accounted for again and if racer has finished output correct statement
                marioKart.pop_front(); // pop off the front racer from the queue
                remainingRacers--; // decrement the size of the amount of racers
                rank++; // increment the rank/place
                cout << endl;
                if(remainingRacers == 0) // if there are no more racers, this means everyone has crossed the finish line
                {
                    break; // break out of the loop
                }
            }
        }

        int updatedRacers = 0; // temp variable to see how many updates have been made within the current interval

        while(cin >> intervalRacerName) // while we are reading into the interval racer name
        {
            if(intervalRacerName == "DONE") // if it hits done, we are out of the interval
            {
                updatedAlready.clear(); // clear the map that has all the racers that have already been updated within the current interval
                break; // break out of the loop
            }
            
            string preLowerCase = intervalRacerName; // create a temp string to hold the original string passed to intervalRacerName
            intervalRacerName = toLowerCase(intervalRacerName); // lowercae their names

            if(updatedAlready[intervalRacerName]) // we have already updated their names within the current interval
            {
                cout << "Already updated " << preLowerCase << " in this interval!" << endl; // output according to the pdf
                cout << endl;
                continue; // continue to read the next racer
            }
            
            if(finishedMap[intervalRacerName]) // if the intervalRacerName is of a racer that has already finished the race
            {
                cout << "Racer has already finished the race!" << endl; // output according to the pdf
                cout << endl;
                continue; // continue to read the next racer
            }

            if (cin >> updatedPriority)  // now we read in the updated priority
            {
                cout << "Updating " << preLowerCase << endl; // output according to the pdf
                marioKart.decrease_priority(intervalRacerName, updatedPriority); // call decrease priority on that specific racer
                updatedAlready[intervalRacerName] = true; // and now set taht particular racer's name to have a true in the unordered map that holds all updated racers within the interval
                updatedRacers++; // increment the count of how many racers have been updated within the interval
            }

            if(updatedRacers == remainingRacers) // break out of loop to next interval if every racer in the interval has been updated
            {
                updatedAlready.clear(); // clear the updatedAlready map
                break;
            }
        }
        interval++; // increment interval and start over again
    }
    return 0;
}

string toLowerCase(const string& s) // function to lowercase strings
{
    string lowerCaseS = s;
    for(int i = 0; i < lowerCaseS.length(); i++)
    {
        if(lowerCaseS[i] >= 'A' && lowerCaseS[i] <= 'Z')
        {
            lowerCaseS[i] = lowerCaseS[i] + 32;
        }
    }
    return lowerCaseS;
}