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

        double calc(double tot){
            double x = tot - mb;
            if(x < 0){
                x = 0;
            }
            return (price + cmb*(x))/(x + mb);
        }
        void inspect(){
            cout << "There is no relevant x-intercept." << endl;// x intercept
            double yint = calc(0);
            cout << "(" << calc(0) << ", 0) is the y-intercept and is the price of 1 mb there is no overcharge." << endl;// y intercept
            // va
            cout << "y = " << cmb << " is the horizontal asymptote." << endl;// ha
            //range
            //domain
            //range
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
};

int main(){
    Plan a;
    a.setup("The Best Plan", 1000, 15, 500);
    Person bob;
    bob.name = "Bob";
    bob.mdata = 0.5;
    bob.budget = 10;

    cout << endl << "Price per mb (cents): " << a.calc(bob.mdata) << endl;
    a.inspect();
    if(a.afford(bob.budget, bob.mdata)){
        cout << endl << a.name << " is within your budget and will be considered." << endl;
    }else{
        cout << endl << a.name << " exceeds your budget. Consider lowering your data usage. Or stop being poor." << endl;
    }
}