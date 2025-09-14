#include<bits/stdc++.h>
using namespace std;
class Schedule {
    private:
    string namevehicle;
    string starttime;
    string endtime;
    public:
    Schedule(string na, string st, string e) :
    namevehicle(na), starttime(st), endtime(e) {}
    string getnamevehicle () {
        return namevehicle;
    }
    string getstarttime() {
        return starttime;
    }
    string getendtime() {
        return endtime;
    }
    void display() {
        cout << "Vehicle: " << namevehicle << endl;
        cout << "Start time: " << starttime << endl;
        cout << "End time: " << endtime << endl;
    }

};
class Station {
    private:
    string name;
    string location;
    string type;
    vector<Schedule* >schedule;
    public:
    Station(string n, string l, string t) : 
    name(n) , location(l), type(t){}
    string gettype() {
        return type;
    }
    void addschedule(Schedule* sc) {
        if(schedule.size() <= 10) {
          schedule.push_back(sc);
        }
        else cout << "Cannot add schedule. Limit reached" << endl;
    } 
    void removeschedule(Schedule* sc) {
        auto it = find(schedule.begin(), schedule.end(), sc);
        if(it != schedule.end()) {
            schedule.erase(it);
        }
    }
    void displayschedule() {
       cout << "Station: "  << name << endl;
       cout << "Location: " << location << endl;
       cout << "Type: " << type << endl;
       for(int i = 0; i < schedule.size() ; i++) {
         cout << i + 1 << ". " ;
         schedule[i]->display() ;
       }
    }
};
class Vehicle {
    private:
    string route;
    int capacity;
    string status;
    public:
    Vehicle(string r, int c, string s) :
    route(r), capacity(c), status(s) {}
    void updatestatus ( string st) {
        status = st;
    }
    int getcapacity() {
        return capacity;
    }
    string getroute() {
        return route;
    }

    void reducecapacity() {
        if(capacity > 0) capacity--;
    }
    void increasecapacity() {
        capacity++;
    }
    void assignToStation( Station &st ,string starttime, string endtime) {
    Schedule *sch = new Schedule( st.gettype() ,starttime,  endtime );
    st.addschedule(sch); 
    }
    virtual void calculateTravelTime(double distance) {
        double speed = 50.0 ;
        double time = distance/speed ;
        cout << "Travel Time: " << time << " h" << endl;
    }
    void displayInfo() {
       cout << "-------Vehicle infomation-------" << endl; 
       cout << "Route: " << route << endl;
       cout << "Capacity: " << capacity << endl;
       cout << "Status: " << status << endl;
    }
};

class Expressbus: public Vehicle {
    private: 
    double speed;
    public:
    Expressbus(string r, int c, string s, int sp ) :
    Vehicle(r,c,s), speed(sp) {}
    void calculateTravelTime(double distance) override {
        double time = distance/speed;
        cout << "Travel Time: " << time <<" h"<< endl;
    }
    void displayInfo2() {
        Vehicle :: displayInfo();
        cout << "Speed: " << speed << endl;
    }
};


class Ticket {
    private:
    string namepassenger;
    string route;
    string vehicletype;
    string starttime;
    string endtime;
    public:
    Ticket(string na, string r, string v, string s, string e ) :
    namepassenger(na), route(r), vehicletype(v), starttime(s), endtime(e) {}

    void displayticket() {
        cout << "-----Ticket-----" << endl;
        cout << "Name passenger: " << namepassenger << endl;
        cout << "Route: " << route << endl;
        cout << "Vehicle type: " << vehicletype << endl;
        cout << "Start time:  " << starttime << endl;
        cout << "End time: " << endtime << endl;
    }
};
class Passenger {
    private:
    string name;
    string id;
    vector<Ticket*>ticket;
    public:
    Passenger(string n, string i) :
    name(n), id(i) {}
    void addticket(Ticket* ti) {
        ticket.push_back(ti);
    }
    void bookTicket(Vehicle* veh, Schedule* sc) {
        if(veh->getcapacity() <= 0) {
           cout << "Vehicle is full for passenger " << endl;
        }
        else {
            cout << "Booked successfully" << endl;
            Ticket* ti = new Ticket(name, veh->getroute(), sc->getnamevehicle(), sc->getstarttime(), sc->getendtime() );
            ticket.push_back(ti);
            veh->reducecapacity();
        }
    }
    void cancelTicket(Ticket* ti, Vehicle * veh) {
        auto it = find(ticket.begin(), ticket.end(), ti);
        if( it != ticket.end() ) {
            ticket.erase(it);
            delete *it;
            veh->increasecapacity();
            cout << "Ticket cancel successfully" << endl ;
        }

    }
    void displaypa() {
        cout << "Passenger Information" << endl;
        cout << "Name: " << name << endl;
        cout << "Id: " << id << endl; 
    }

    void displaytk() {
        for(auto a : ticket){
            a->displayticket();
        }
    }
};

int main () {

   Station st1("Central Station", "Downtown", "Bus");

   Schedule* sch1 = new Schedule("Bus-01", "08:00", "10:00");
   Schedule* sch2 = new Schedule("Bus-02", "10:30", "12:00");

   st1.addschedule(sch1);
   st1.addschedule(sch2);

   cout << "\n=== Station Schedule ===\n";
    st1.displayschedule();

   
    Vehicle bus("Route A", 2, "Available");   
    Expressbus express("Route B", 1, "Available", 80); 

    cout << "\n=== Vehicle Info ===\n";
    bus.displayInfo();
    express.displayInfo2();

    cout << "\n=== Travel Time Test ===\n";
    bus.calculateTravelTime(100);      
    express.calculateTravelTime(100);   
    Passenger p1("Alice", "P001");
    Passenger p2("Bob", "P002");
    Passenger p3("Charlie", "P003");

    
    cout << "\n=== Booking Ticket ===\n";
    p1.bookTicket(&bus, sch1);  
    p2.bookTicket(&bus, sch1); 

    p3.bookTicket(&bus, sch1); 

    p1.bookTicket(&express, sch2); 
    p2.bookTicket(&express, sch2); 
    cout << "\n=== Cancel Ticket ===\n";
   
   Ticket* t = new Ticket("Alice", express.getroute(), sch2->getnamevehicle(),
                           sch2->getstarttime(), sch2->getendtime());
    
    p1.cancelTicket(t, &express);
    
    cout << "\n=== Passenger Info ===\n";
    p1.displaypa();
    p2.displaypa();
    p3.displaypa();
    
    p1.displaytk();
    p2.displaytk();
}