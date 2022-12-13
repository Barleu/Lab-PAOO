#include <iostream>
#include <string>
#include <memory>
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

    static void parkVehicle(Vehicle *v){
        cout<<"Vehicle "<< v->manufacturer << " parked"<<endl;
    }

    static void unparkVehicle(Vehicle *v){
        cout<<"Vehicle "<< v->manufacturer << " unparked"<<endl;
    }

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

        //item 13
        static WaterVehicle* createWaterVehicle(const string& manufacturer, const int& weight){
			return new WaterVehicle(manufacturer, weight);
		}

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

class parkVehicle {
    private:
		shared_ptr<Vehicle> v;
	public:
		explicit parkVehicle(Vehicle *vehicle)
		: v(vehicle, Vehicle::unparkVehicle)
		{ 
            Vehicle::parkVehicle(v.get());
		} 
};

int main() {
    
    unique_ptr<WaterVehicle> wv1(WaterVehicle::createWaterVehicle("wv1",100));
    cout << wv1-> getWeight() << endl;

    shared_ptr<WaterVehicle> wv2(WaterVehicle::createWaterVehicle("wv2", 200));
    cout << wv2 -> getWeight() << endl;

    shared_ptr<WaterVehicle> wv3(wv2);
    cout << wv3 -> getWeight() << endl;

    Vehicle *v = new Vehicle("VO", 150);
    // user is locked when it's created
    parkVehicle pv(v);
    cout << v->getWeight() << endl;
	
    return 0;
}