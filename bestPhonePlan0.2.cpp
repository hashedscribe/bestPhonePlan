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

        double calc(double tot, bool overcharge){
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
        void inspect(bool overcharge){
            if(overcharge){
                double yint = calc(0, true);
                cout << "With your current usage, you will go over the given data." << endl << endl;
                cout << "There is no relevant x-intercept." << endl;// x intercept
                cout << "(" << calc(0, true) << ", 0) is the y-intercept of the overcharge and is the price of 1 mb there is no overcharge." << endl;// y intercept
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
class Person{
    public: 
        string name;
        double mdata; //monthly data usage in (gb)
        double budget; //max price ($)
        vector <double> deals;
};

int main(){
    Person bob;
    bob.name = "Bob";
    bob.mdata = 10; //in gb
    bob.budget = 70; //in dollars

    int numOfPlans;
    cin >> numOfPlans;
    Plan plan[numOfPlans];
    for(int i = 0; i < numOfPlans; i++){
        //take in inputs of each plan
        cin >> plan[i].company >> plan[i].planName >> plan[i].basePrice >> plan[i].rate >> plan[i].baseMb;
    }
    cout << endl;

    for(int i = 0; i < numOfPlans; i++){
        cout << plan[i].company << "'s " << plan[i].planName << ": " << endl;
        //bool if overcharge by seeing if data used each month exceeds the provided
        cout << "Price per mb (cents): " << plan[i].calc(bob.mdata, bob.mdata * 1000 > plan[i].baseMb) << endl;
        if(plan[i].afford(bob.budget, bob.mdata)){ //test if they can afford each plan
            cout << plan[i].company << "'s " << plan[i].planName << " is within your budget and will be considered." << endl << endl;
        }else{
            cout << plan[i].company << "'s " << plan[i].planName << " exceeds your budget. Consider lowering your data usage or not being poor." << endl << endl;
        }
    }
}