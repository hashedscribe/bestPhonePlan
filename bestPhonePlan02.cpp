#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

class Plan{
    public:
        string company, planName;
        double basePrice, rate, baseMb; //base price (cents and mb)

        double calcx(double tot, bool overcharge){
            tot = tot*1000;
            if(tot < 0){
                tot = 0;
            }
            if((tot <= baseMb) && (overcharge == false)){
                return basePrice/tot;
            }else{
                return (basePrice + rate*(tot))/(tot + baseMb);
            }
        }
        double calcy(double cpmb, double overcharge){
            if(overcharge){
                return (cpmb * baseMb - basePrice)/(rate - cpmb);
            }else{
                return basePrice/cpmb;
            }
        }
        void inspect(){
            cout << "Without overcharge: " << endl; 
            cout << "There is no x or y intercept." << endl; //x int
            cout << "VA: y = 0. You cannot find an average cost per mb if no mb is used." << endl; //va
            cout << "HA: y = 0. The data will never be free." << endl; //ha
            cout << "Domain: {xER || 0 < x <= " << baseMb << "}" << endl;
            cout << "Range: {yER || " << calcx(0, true) << " <= y }" << endl;
            cout << endl;

            cout << "With overcharge: " << endl;
            cout << "There is no relelvant x intercept." << endl;
            cout << "y intercept: " << calcx(0, true) << ". This is the price of 1 mb when there is no overcharge" << endl;
            cout << "There is no relevant vertical asymptote." << endl;
            cout << "HA: y = " << rate << ". You cannot get more expensive than " << rate << " cents per mb." << endl;// ha
            cout << "Domain: {xER || " << 0 << " < x }" << endl;
            cout << "Range: {yER || " << calcx(0, true) << " < y < " << rate << "}" << endl;
            cout << endl;
        }
        bool afford(double budget, double tot){
            budget = budget * 100; //turning dollars into cents
            tot = tot*1000; //turning gb into mb
            if(basePrice <= budget){
                if((basePrice + rate*(tot-baseMb)) <= budget){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }

        }
};
class PersonsPlan{
    public:
        string company, planName;
        double calcx, calcy;
        
        void setup(string icompany, string iplanName, double icalcx, double icalcy){
            company = icompany;
            planName = iplanName;
            calcx = icalcx;
        }
};
class Person{
    public: 
        string name;
        double used; //monthly data usage in (gb)
        double budget; //max price ($)
        double ripoff;
        vector <PersonsPlan> deals;

        void printPlans(){
            if(deals.size() == 0){
                cout << name << " cannot afford any of the plans. Consider using less data or just stop being poor." << endl << endl;
            }else{
                for(int i = 0; i < deals.size(); i++){
                    cout << deals[i].company << "'s " << deals[i].planName << ": " << endl;
                    cout << "Price per mb (cents): " << deals[i].calcx << endl;
                    cout << deals[i].company << "'s " << deals[i].planName << " is within " << name << "'s budget and will be considered." << endl << endl;
                }
            }
        }
        void rank(){
            PersonsPlan temp;
            for(int i = 0; i < deals.size(); i++){
                for(int j = 0; j < deals.size(); j++){
                    if(deals[i].calcx < deals[j].calcx){
                        temp = deals[j];
                        deals[j] = deals[i];
                        deals[i] = temp;
                    }
                }
            }
        }
        void rank(){
            for(int i = 0; i < deals.size(); i++){
                for(int j = 0; j < deals.size(); j++){
                    
                }
            }
        }
};

int main(){
    int numOfPeople;
    cout << "Please enter the number of people considering phone plans: ";
    cin >> numOfPeople;
    Person person[numOfPeople];
    cout << "Please enter each person's name, data used, budget, ripoff number: " << endl;
    for(int i = 0; i < numOfPeople; i++){
        cin >> person[i].name >> person[i].used >> person[i].budget >> person[i].ripoff;
    }

    int numOfPlans;
    cout << "Please enter the number of plans to be considered: ";
    cin >> numOfPlans;
    Plan plan[numOfPlans];
    cout << "Please enter each plan's company, name, base price, overcharge rate, and mb provided: " << endl;
    for(int i = 0; i < numOfPlans; i++){
        //take in inputs of each plan
        cin >> plan[i].company >> plan[i].planName >> plan[i].basePrice >> plan[i].rate >> plan[i].baseMb;
    }
    cout << endl;

    double tempCalcx;
    bool tempAfford;

    for(int j = 0; j < numOfPeople; j++){
        for(int i = 0; i < numOfPlans; i++){
            tempAfford = plan[i].afford(person[j].budget, person[j].used);
            tempCalcx = plan[i].calcx(person[j].used, false);

            if(tempAfford){ //test if they can afford each plan
                person[j].deals.push_back(PersonsPlan());
                person[j].deals[person[j].deals.size()-1].setup(plan[i].company, plan[i].planName, tempCalcx);
            }
        }
    }
    for(int i = 0; i < numOfPeople; i++){
        person[i].rank();
    }

    int choice;
    string opt[5] = {"See Rankings", "Inspect Plans", "See Ripoff"};
    for(int i = 0; i < 3; i++){
        cout << i+1 << ". " << opt[i] << endl;
    }
    cout << "Type in the corresponding number for the action you'd like to take: ";
    cin >> choice; cout << endl;
    switch(choice){
        case 1:
            for(int i = 0 ; i < numOfPeople; i++){
                cout << i + 1 << ". " << person[i].name << endl;
            }
            int rankChoice;
            cout << "Please select a person you'd like to view rankings for. Alternatively, enter 0 to see all." << endl;
            cin >> rankChoice;
            if(rankChoice == 0){
                for(int i = 0; i < numOfPeople; i++){
                    person[i].printPlans();
                    cout << "--------------------" << endl << endl;
                }
            }else{
                person[rankChoice - 1].printPlans();
                cout << "--------------------" << endl << endl;
            }
            cin >> choice; cout << endl;
        case 2:
            int inspectChoice;
            for(int i = 0; i < numOfPlans; i++){
                cout << i + 1 << ". " << plan[i].company << " " << plan[i].planName << endl;
            }
            cout << "Please select a plan you'd like to inspect. Alternatively, enter 0 to see all." << endl;
            cin >> inspectChoice;
            if(inspectChoice == 0){
                for(int i = 0; i < numOfPlans; i++){
                    cout << plan[i].company << "'s " << plan[i].planName << endl;
                    plan[i].inspect();
                    cout << "--------------------" << endl << endl;
                }
            }else{
                cout << plan[inspectChoice -1].company << "'s " << plan[inspectChoice -1].planName << endl;
                plan[inspectChoice -1].inspect();
                cout << "--------------------" << endl << endl;
            }
            cin >> choice; cout << endl;
        case 3:
            for(int i = 0 ; i < numOfPeople; i++){
                cout << i + 1 << ". " << person[i].name << endl;
            }
            for(int i = 0; i < numOfPlans; i++){
                cout << i + 1 << ". " << plan[i].company << " " << plan[i].planName << endl;
            }
            int personRangeStart, personRangeEnd, planRangeStart, planRangeEnd;
            cout << "Please enter the start and end of the people you'd like to include in the ripoff judgement (inclusive): ";
            cin >> personRangeStart >> personRangeEnd;
            cout << "Please enter the start and end of the plans you'd like to include in the ripoff judgement (inclusive): ";
            cin >> planRangeStart >> planRangeEnd;

            cout << endl;

            for(int i = 0; i < personRangeEnd + 1 - personRangeStart; i++){
                cout << person[i].name << " thinks anything above " << person[i].ripoff << " cents/mb is a ripoff." << endl;
                cout << "To " << person[i].name << ": " << endl;
                for(int j = 0; j < planRangeEnd + 1 - planRangeStart; j++){
                    cout << plan[j].company << "'s " << plan[j].planName << " will be worth it when " << person[i].name << " uses " << plan[j].calcy(person[i].ripoff, false);
                    if(plan[j].calcy(person[i].ripoff, true) == 0){
                        cout << " mb of data exactly." << endl;
                    }else if(plan[j].calcy(person[i].ripoff, true) < 0 || isinf(plan[j].calcy(person[i].ripoff, true))){
                        cout << " at the very least." << endl;
                    }else{
                        cout << " to " << plan[j].calcy(person[i].ripoff, true) << " mb of data." << endl;
                    }
                }
                cout << endl << "--------------------" << endl;
            }
            cin >> choice; cout << endl;
    }
}