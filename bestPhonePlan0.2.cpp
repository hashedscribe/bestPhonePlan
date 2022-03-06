#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Plan{
    public:
        string company, planName;
        double basePrice, rate, baseMb; //base price (cents and mb)

        double calcx(double tot, bool overcharge){
            double x = tot*1000;
            if(x < 0){
                x = 0;
            }
            if((x <= baseMb) && (!overcharge)){
                return basePrice/x;
            }else{
                return (basePrice + rate*(x))/(x + baseMb);
            }
        }
        double calcy(double cpmb, bool overcharge){
            if(overcharge){
                return (cpmb * baseMb + basePrice)/rate - cpmb;
            }else{
                return basePrice/cpmb;
            }
        }
        void inspect(bool overcharge){
            if(overcharge){
                double yint = calcx(0, true);
                cout << "With your current usage, you will go over the given data." << endl << endl;
                cout << "There is no relevant x-intercept." << endl;// x intercept
                cout << "(" << calcx(0, true) << ", 0) is the y-intercept of the overcharge and is the price of 1 mb there is no overcharge." << endl;// y intercept
                cout << "There is no relevant vertical asymptote." << endl;
                cout << "y = " << rate << " is the horizontal asymptote. You cannot get more expensive than " << rate << " cents per mb." << endl;// ha
                //range
                //domain
            }else{
                cout << "Your current usage is within the given data." << endl << endl; 
                cout << "There is no relevant x-intercept." << endl; //x int
                cout << "There is no relevant y-intercept." << endl; //y int
                cout << "The vertical asymptote is at x = 0. You cannot find an average cost per mb if no mb is used." << endl; //va
                cout << "The horizontal asymptote is 0. The data will never be free." << endl; //ha
                //range
                //domain
            }
        }
        bool afford(double budget, double tot){
            budget = budget * 100; //turning dollars into cents
            tot = tot*1000; //turning gb into mb
            if((basePrice + rate*(tot-baseMb)) <= budget){
                return true;
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
            calcy = icalcy;
        }
};
class Person{
    public: 
        string name;
        double used; //monthly data usage in (gb)
        double budget; //max price ($)
        double ripoff;
        vector <PersonsPlan> deals;
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
    cout << endl;

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

    double tempCalcx, tempCalcy;
    bool tempAfford;

    for(int j = 0; j < numOfPeople; j++){
        for(int i = 0; i < numOfPlans; i++){
            tempAfford = plan[i].afford(person[j].budget, person[j].used);
            tempCalcx = plan[i].calcx(person[j].used, tempAfford);
            tempCalcy = plan[i].calcy(person[j].ripoff, tempAfford);

            cout << plan[i].company << "'s " << plan[i].planName << ": " << endl;
            //bool if overcharge by seeing if data used each month exceeds the provided
            cout << "Price per mb (cents): " << tempCalcx << endl;
            if(tempAfford){ //test if they can afford each plan
                person[j].deals.push_back(PersonsPlan());
                person[j].deals[person[j].deals.size()-1].setup(plan[i].company, plan[i].planName, tempCalcx, tempCalcy);
                cout << plan[i].company << "'s " << plan[i].planName << " is within " << person[j].name << "'s budget and will be considered." << endl << endl;
            }else{
                cout << plan[i].company << "'s " << plan[i].planName << " exceeds " << person[j].name << "'s budget. Consider lowering your data usage or not being poor." << endl << endl;
            }
        }
    }
}