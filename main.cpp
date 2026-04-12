#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>

using namespace std;

// the helper functions
string trim (string text)
{
    while (!text.empty() && (text [0] == ' ' || text [0] == '\t')) {
        text.erase(0, 1);
    }
while (!text.empty () &&
    (text[text.length () - 1] == ' '||
     text[ text.length () - 1] == '\t' ||
     text[text.length () - 1] == '\r' ||
     text[text.length () - 1] == '\n')) {
    text.erase(text.length() - 1, 1);
}
    return text;
}
vector<string> splitByComma(string line) {
    vector<string> parts;
    string part;
    stringstream ss(line);

    while (getline(ss, part, ','))  {
        parts.push_back(trim(part));
    }
return parts;
}
string getCurrentDate ()
{
    time_t now = time(0);
    tm *currentTime = localtime(&now);

    int year = 1900 + currentTime->tm_year;
    int month = 1 + currentTime->tm_mon;
    int day = currentTime->tm_mday;

    ostringstream out;
    out << year << "-";
    if (month < 10)
        {
    out << "0";
    }
    out << month << "-";
    if (day < 10)
        {
    out << "0";
    }
    out << day;
    return out.str();
}

int getBirthMonthFromSeason(string season) {
    if (season == "spring") {
        return 3;
    } else if (season == "summer") {
        return 6;
    } else if (season == "fall")
    {
        return 9;
    } else if (season == "winter")
    {
        return 12;
    } else
    {
        return 1; //this will be default for unknown brith seasons
    }
}
int getBirthDayFromSeason(string season)
{
    if (season=="spring")
    {
        return 21;
    } else if (season == "summer")
    {
        return 21;
    } else if (season == "fall")
    {
        return 21;
    } else if (season == "winter")
    {
        return 21;
    } else
    {
        return 1; //default for unknown birth season
    }
}

string genBirthDay(int ageInYears, int birthMonth, int birthDay)
{
  time_t now = time (0);
   tm * ltm = localtime(&now);
    int birthYear = (1900 + ltm -> tm_year) - ageInYears;

    ostringstream out;
    out << birthYear << "-";
    if (birthMonth < 10)
    {
        out << "0";
    }
    out << birthMonth << "-";
    if (birthDay < 10)
    {
        out << "0";
    }
    out << birthDay;
    return out.str();
}
//switching to animal class
class Animal
{
private:
    static int numOfAnimals;

public:
    string uniqueID;
    string name;
    string species;
    string sex;
    string color;
    string origin;
    string birthSeason;
    string birthDate;
    string arrivalDate;
    int weight;
    int age;

Animal(string animalSpecies)
{
    uniqueID = "";
    name = "no name";
    species = animalSpecies;
    sex = "";
    color = "";
    origin = "";
    birthSeason = "";
    birthDate = "";
    arrivalDate = "";
    weight = 99999;
    age = 0;

    numOfAnimals++;
}
static int getNumOfAnimals()
{
    return numOfAnimals;
}
};
int Animal::numOfAnimals = 0;
//Animal subclass

class Hyena : public Animal
{
public:
    Hyena () : Animal("hyena") {
    }
};
class Lion : public Animal
{
public:
    Lion() : Animal("lion")
    {

    }
};
class Tiger : public Animal
{
public:
    Tiger() : Animal("tiger")
    {
    }
};
class Bear : public Animal
{
public:
    Bear() : Animal("bear")
    {
    }
};
//switching to main

string getUniqueID(string species, int number)
{
    string prefix = "";
    if (species == "hyena")
    {
        prefix = "Hy";
    }
    else if (species == "lion")
    {
        prefix = "Li";
    }
    else if (species == "tiger")
    {
        prefix = "Ti";
    }
    else if (species == "bear")
    {
        prefix = "Be";
    }
    ostringstream out;
    out << prefix;
    if (number < 10)
    {
        out << "0";
    }
    out << number;

    return out.str();
}

int main ()
{
    ifstream arrivingFile("arrivingAnimals.txt");
    ifstream namesFile("animalNames.txt");

    if (!arrivingFile.is_open()){
        cout << "Could not open arrivingAnimals.txt" << endl;
        return 1;
    }
    if (!namesFile.is_open())
    {
        cout << "Could not open animalNames.txt" << endl;
        return 1;
    }
    cout << "Files opened successfully." << endl;
    cout << "Today's date:" << getCurrentDate() << endl << endl;
    vector<Animal*> zooAnimals;

    string line;
    while (getline(arrivingFile,line))
    {
        vector <string> parts = splitByComma(line);

        if (parts.size() < 4)
        {
            continue;
        }

        Animal* newAnimal = nullptr;
        string firstPart = parts[0];

        if (firstPart.find ("hyena") != string::npos)
        {
            newAnimal = new Hyena ();
        }
        else if (firstPart.find("lion") !=string::npos)
        {
            newAnimal = new Lion ();
        }
        else if (firstPart.find ("tiger") !=string::npos)
        {
            newAnimal = new Tiger ();
        }
        else if (firstPart.find ("bear") !=string::npos)
        {
            newAnimal = new Bear ();
        }
        if (newAnimal !=nullptr)
        {
            stringstream ss(firstPart);
            ss >> newAnimal ->age;
            if (firstPart.find("female") !=string::npos)
            {
                newAnimal ->sex = "female";
            }
            else if (firstPart.find("male") !=string::npos)
            {
                newAnimal ->sex = "male";
            }
            string seasonPart = parts[1];
            if (seasonPart.find("spring") !=string::npos)
            {
                newAnimal -> birthSeason = "spring";
            }
            else if (seasonPart.find ("summer") !=string::npos)
            {
                newAnimal->birthSeason = "summer";
            }
            else if (seasonPart.find("fall") !=string::npos)
            {
                newAnimal->birthSeason = "fall";
            }
            else if (seasonPart.find("winter") !=string::npos)
            {
                newAnimal->birthSeason = "winter";
            }
            else
            {
                newAnimal -> birthSeason = "unknown";
            }
            newAnimal ->color = parts[2];
            size_t colorPos = newAnimal ->color.find("color");
            if (colorPos != string::npos)
            {
                newAnimal->color.erase(colorPos, 6);
            }
            newAnimal->color = trim(newAnimal->color);

            stringstream weightStream(parts[3]);
            weightStream >> newAnimal -> weight;
            if (parts.size() >= 6)
            {
                newAnimal->origin = parts[4] + ", " + parts[5];
            }
            else if (parts.size() >=5)
            {
                newAnimal ->origin = parts[4];
            }
            if (newAnimal -> origin.find ("from") ==0)
            {
                newAnimal ->origin.erase(0, 5);
            }
            newAnimal->arrivalDate = getCurrentDate();
            if (newAnimal->birthSeason != "unknown")
            {
                int birthMonth = getBirthMonthFromSeason(newAnimal->birthSeason);
                int birthDay = getBirthDayFromSeason(newAnimal->birthSeason);
                newAnimal->birthDate = genBirthDay(newAnimal->age, birthMonth, birthDay);
            }
            else
            {
                newAnimal -> birthDate = "unknown";
            }
            zooAnimals.push_back(newAnimal);
        }
    }
    vector<string> hyenaNames;
    vector<string> lionNames;
    vector<string> bearNames;
    vector<string> tigerNames;

    vector <string>* currentVector = nullptr;
    string nameLine;

    while (getline(namesFile, nameLine))
    {
        nameLine = trim(nameLine);
        if (nameLine.empty())
        {
            continue;
        }
        if (nameLine.find("Hyena Names:") != string::npos)
        {
            currentVector = &hyenaNames;
        }
        else if (nameLine.find("Lion Names:") != string::npos)
        {
            currentVector = &lionNames;
        }
        else if (nameLine.find("Bear Names:") !=string::npos)
        {
            currentVector = &bearNames;
        }
        else if (nameLine.find("Tiger Names:") !=string::npos)
        {
            currentVector =&tigerNames;
        }
        else if (currentVector !=nullptr)
        {
            stringstream ss(nameLine);
            string oneName;
            while (getline(ss, oneName, ','))
            {
                oneName = trim(oneName);
                if (!oneName.empty())
                {
                    currentVector ->push_back(oneName);
                }
            }
        }
    }

    int hyenaIndex = 0;
    int lionIndex = 0;
    int bearIndex = 0;
    int tigerIndex = 0;

    for (Animal*animalPtr : zooAnimals)

    {
        if (animalPtr ->species =="hyena" && hyenaIndex < hyenaNames.size())
        {
            animalPtr->name = hyenaNames[hyenaIndex];
            hyenaIndex++;
        }
        else if (animalPtr ->species =="lion" && lionIndex < lionNames.size())
        {
            animalPtr->name= lionNames[lionIndex];
            lionIndex++;
        }
        else if (animalPtr->species =="bear" && bearIndex < bearNames.size())
        {
            animalPtr ->name = bearNames[bearIndex];
            bearIndex++;
        }
        else if (animalPtr ->species =="tiger" && tigerIndex < tigerNames.size())
        {
            animalPtr->name= tigerNames[tigerIndex];
            tigerIndex++;
        }
    }
    int hyenaID = 1;
    int lionID = 1;
    int bearID= 1;
    int tigerID = 1;

    for (Animal* animalPtr : zooAnimals)
    {
        if (animalPtr ->species == "hyena")
        {
            animalPtr ->uniqueID = getUniqueID("hyena", hyenaID);
            hyenaID++;
        }
        else if (animalPtr ->species == "lion")
        {
            animalPtr ->uniqueID = getUniqueID("lion", lionID);
            lionID++;
        }
        else if (animalPtr ->species == "bear")
        {
            animalPtr ->uniqueID = getUniqueID ("bear", bearID);
            bearID++;
        }
        else if (animalPtr ->species =="tiger")
        {
            animalPtr ->uniqueID = getUniqueID ("tiger", tigerID);
            tigerID++;
        }
    }

cout << "Animals loaded from file:" <<endl;
    for (Animal*animalPtr : zooAnimals)
    {
        cout << animalPtr->species << "|"
         << animalPtr->sex << "|"
         << animalPtr->age << "|"
         << animalPtr->color << "|"
         << animalPtr->weight << "|"
         << animalPtr->origin << "|"
         << animalPtr ->name << "|"
         << animalPtr->birthDate << "|"
         << animalPtr ->uniqueID << "|"
         << animalPtr -> arrivalDate << endl;
    }
ofstream zooFile("zooPopulation.txt");
    if (!zooFile.is_open())
    {
        cout << "Could not create zooPopulation.txt" << endl;
        return 1;
    }
    zooFile << "Hyena Habitat:" << endl;
    for (Animal* animalPtr : zooAnimals)
    {
        if (animalPtr ->species == "hyena")
        {
            zooFile << animalPtr ->uniqueID << "; "
            << animalPtr ->name << "; "
            << "birth date " << animalPtr->birthDate << "; "
            << animalPtr -> color << " color; "
            << animalPtr -> sex << "; "
            << animalPtr -> weight << " pounds; "
            << "from " << animalPtr ->origin << "; "
            << "arrived " << animalPtr -> arrivalDate
            << endl;

        }
    }

    zooFile << endl << "Lion Habitat:" << endl;
    for (Animal* animalPtr : zooAnimals)
    {
        if (animalPtr -> species == "lion")
        {
            zooFile << animalPtr ->uniqueID << "; "
            << animalPtr ->name << "; "
            << "birth date " << animalPtr->birthDate << "; "
            << animalPtr -> color << " color; "
            << animalPtr -> sex << "; "
            << animalPtr -> weight << " pounds; "
            << "from " << animalPtr ->origin << "; "
            << "arrived " << animalPtr -> arrivalDate
            << endl;
        }
    }

    zooFile << endl <<  "Bear Habitat:" << endl;
    for (Animal* animalPtr : zooAnimals)
    {
        if (animalPtr -> species == "bear")
        {
         zooFile << animalPtr ->uniqueID << "; "
            << animalPtr ->name << "; "
            << "birth date " << animalPtr->birthDate << "; "
            << animalPtr -> color << " color; "
            << animalPtr -> sex << "; "
            << animalPtr -> weight << " pounds; "
            << "from " << animalPtr ->origin << "; "
            << "arrived " << animalPtr -> arrivalDate
            << endl;
        }
    }
    zooFile << endl << "Tiger Habitat:" << endl;
    for (Animal* animalPtr : zooAnimals)
    {
        if (animalPtr -> species == "tiger")
        {
           zooFile << animalPtr ->uniqueID << "; "
            << animalPtr ->name << "; "
            << "birth date " << animalPtr->birthDate << "; "
            << animalPtr -> color << " color; "
            << animalPtr -> sex << "; "
            << animalPtr -> weight << " pounds; "
            << "from " << animalPtr ->origin << "; "
            << "arrived " << animalPtr -> arrivalDate
            << endl;
        }
    }

zooFile.close();
    arrivingFile.close();
        namesFile.close();
        cout << "Program finished without file errors." << endl;
    for (Animal* animalPtr : zooAnimals)
    {
        delete animalPtr;
    }
    return 0;
}