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
                cout << "There is no relevant x-intercept." << endl;// x intercept
                double yint = calc(0, true);
                cout << "(" << calc(0, true) << ", 0) is the y-intercept of the overcharge and is the price of 1 mb there is no overcharge." << endl;// y intercept
                // va
                cout << "y = " << cmb << " is the horizontal asymptote." << endl;// ha
                //range
                //domain
                //range
            }else{
                
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
};

int main(){
    Plan a;
    a.setup("The Best Plan", 1000, 15, 500);
    Person bob;
    bob.name = "Bob";
    bob.mdata = 0.1; //in gb
    bob.budget = 100; //in dollars

    cout << endl << "Price per mb (cents): " << a.calc(bob.mdata, false) << endl;
    a.inspect();
    if(a.afford(bob.budget, bob.mdata)){
        cout << endl << a.name << " is within your budget and will be considered." << endl;
    }else{
        cout << endl << a.name << " exceeds your budget. Consider lowering your data usage or not being poor." << endl;
    }
}