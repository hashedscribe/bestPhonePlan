#include <iostream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

class Plan{
    public:
        string name;
        double price, cmb, mb; //base price (cents and mb)
        void setup(string iname, int iprice, double icmb, int imb){
            name = iname; 
            price = iprice; 
            cmb = icmb;
            mb = imb;
        }
        double calc(double tot, bool overcharge){
            double x = tot*1000;
            if(x < 0){
                x = 0;
            }
            if((x <= mb) && (!overcharge)){
                return price/x;
            }else{
                return (price + cmb*(x))/(x + mb);
            }
        }
        void inspect(bool overcharge){
            if(overcharge){
                double yint = calc(0, true);
                cout << "With your current usage, you will go over the given data." << endl << endl;
                cout << "There is no relevant x-intercept." << endl;// x intercept
                cout << "(" << calc(0, true) << ", 0) is the y-intercept of the overcharge and is the price of 1 mb there is no overcharge." << endl;// y intercept
                cout << "There is no relevant vertical asymptote." << endl;
                cout << "y = " << cmb << " is the horizontal asymptote. You cannot get more expensive than " << cmb << " cents per mb." << endl;// ha
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
            if((price + cmb*(tot-mb)) <= budget){
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
    int numOfPlan = 2;
    Plan plan[numOfPlan];
    for(int i = 0; i < numOfPlan/2; i++){
        plan[i].setup("A Good Plan", 1000, 15, 500);
        plan[i+1].setup("A Better Plan", 2500, 15, 1000);
    }

    Person bob;
    bob.name = "Bob";
    bob.mdata = 1; //in gb
    bob.budget = 40; //in dollars

    for(int i = 0; i < numOfPlan; i++){
        cout << plan[i].name << ": " << endl;
        cout << endl << "Price per mb (cents): " << plan[i].calc(bob.mdata, bob.mdata * 1000 > plan[i].mb) << endl;
        plan[i].inspect(bob.mdata * 1000 > plan[i].mb);
        if(plan[i].afford(bob.budget, bob.mdata)){
            cout << plan[i].name << " is within your budget and will be considered." << endl;
        }else{
            cout << plan[i].name << " exceeds your budget. Consider lowering your data usage or not being poor." << endl << endl;
        }
    }

    //for(int i = 0; i < numOfPlan)

}