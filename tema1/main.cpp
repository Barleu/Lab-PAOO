#include <iostream>
#include <string>
using namespace std;

class Vehicle {
    protected:
        string manufacturer;
        int weight;
    public:
    
    Vehicle(){};
    Vehicle(const string& manufacturer, const int& weight);
    ~Vehicle();

    int getWeight(){
        return weight;
    }
};

//constructor definition + initialization
Vehicle::Vehicle(const string& manufacturer, const int& weight)
    :manufacturer(manufacturer),
     weight(weight)
    {
        cout<<"Vehicle created"<<endl;
    }

Vehicle::~Vehicle(){
    cout<<"Vehicle destroyed"<<endl;
}

class GroundVehicle : public Vehicle {
    public:
        GroundVehicle(const string& manufacturer, const int& weight):Vehicle(manufacturer, weight){}
        ~GroundVehicle(){};
        GroundVehicle(const GroundVehicle&) = delete;
        GroundVehicle& operator= (const GroundVehicle&) = delete;

        void drive(){
            cout<< "Vehicle moving" << endl;
        }
};

class WaterVehicle : public Vehicle{
    public:
        WaterVehicle(){};
        WaterVehicle(const string& manufacturer, const int& weight):Vehicle(manufacturer, weight){}
        ~WaterVehicle(){};

        void sail(){
            cout<< "Vehicle sailing" << endl;
        }
};


int main() {
    GroundVehicle groundvehicle("Renault", 1600);
    groundvehicle.drive();
    
    WaterVehicle watervehicle("Barca", 600);
    watervehicle.sail();


    //copy constructor
    WaterVehicle watervehicle1(watervehicle);
    cout << watervehicle1.getWeight() << endl;

    //copy assignment operator
    WaterVehicle watervehicle2;
    watervehicle2=watervehicle;
    cout << watervehicle2.getWeight() << endl;
    
    // nu o sa compileze; deleted copy constructor
    //GroundVehicle groundvehicle1(groundvehicle);
    
    return 0;
}