#include <iostream>
#include <string>
using namespace std;

class Vehicle {
    protected:
        string manufacturer;
        int weight;
    public:
    
    Vehicle();
    Vehicle(const string& manufacturer, const int& weight);
    ~Vehicle();
    Vehicle(const Vehicle& v);
    Vehicle& operator=(const Vehicle& v);

    int getWeight(){
        return weight;
    }
};

Vehicle::Vehicle()
    :manufacturer(),
    weight()
    {
        cout<<"Vehicle created"<<endl;
    }

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

Vehicle::Vehicle(const Vehicle& v)
    :manufacturer(v.manufacturer),
    weight(v.weight)
    {
        cout<<"Copy constructor called"<<endl;
    }

Vehicle& Vehicle::operator=(const Vehicle& v)
{
    cout<<"Assignment operator called"<<endl;
    if(this == &v) return *this;
    manufacturer = v.manufacturer;
    weight = v.weight;
    return *this;
}

class GroundVehicle : public Vehicle {
    public:
        GroundVehicle();
        GroundVehicle(const string& manufacturer, const int& weight);
        GroundVehicle(const GroundVehicle&) = delete;
        GroundVehicle& operator= (const GroundVehicle&) = delete;

        void drive(){
            cout<< "Vehicle moving" << endl;
        }
};

GroundVehicle::GroundVehicle()
    :Vehicle(){}
    
GroundVehicle::GroundVehicle(const string& manufacturer, const int& weight)
    :Vehicle(manufacturer,weight){}

class WaterVehicle : public Vehicle{
    public:
        WaterVehicle();
        WaterVehicle(const string& manufacturer, const int& weight);
        WaterVehicle(const WaterVehicle& v);
        WaterVehicle& operator=(const WaterVehicle& v);
        void sail(){
            cout<< "Vehicle sailing" << endl;
        }
};

WaterVehicle::WaterVehicle()
    :Vehicle(){}
    
WaterVehicle::WaterVehicle(const string& manufacturer, const int& weight)
    :Vehicle(manufacturer,weight){}

WaterVehicle::WaterVehicle(const WaterVehicle& wv)
    :Vehicle(wv){}

WaterVehicle& WaterVehicle::operator=(const WaterVehicle& wv)
{
    if(this==&wv) return *this;
    Vehicle::operator=(wv);
    return *this;
}

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
    
    //self assignment operator
    watervehicle1 = watervehicle1;

    //assignment in chain
    watervehicle=watervehicle1=watervehicle2;
    
    return 0;
}