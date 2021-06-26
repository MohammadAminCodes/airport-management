#include <iostream>
#include <cstring>
#include <map>
#include <sstream>
using namespace std;

//node

class flight{
private:
    string time;
    string model;
    string type;
    int passengers;
    int runway;
    int flight_number;
    int id;

    flight *nextFlight = nullptr;
    flight *previousFlight = nullptr;

public:
    flight( string, string, string, int, int, int );
    flight( string, string, string, int, int, int, int );

    void setPreviousFlight( flight *previousFlight )
    { this -> previousFlight = previousFlight; }

    void  setNextFlight( flight *nextflight )
    { this -> nextFlight = nextflight; }

    //    flight *getPreviousFLight()
    //    { return previousFlight; }

    flight *getNextFlight() { return nextFlight; }
    string getTime();
    string getModel();
    string getType();
    int getPassengers();
    int getRunway();
    int getFlight_number();
    int getID();

    void setTime( string tm );
    void setModel( string mod );
    void setType( string tp );
    void setPassengers( int p );
    void setRunway( int rw );
    void setFlight_number( int fl_num ) { flight_number = fl_num; }
    void setID( int i );

};

flight::flight( string tm, string m, string tp, int p, int fl_nu, int i )
{
    this -> time = tm;
    this -> model = m;
    this -> type = tp;
    this -> passengers = p;
    this -> flight_number = fl_nu;
    this -> id = i;
}

flight::flight( string tm, string m, string tp, int p, int fl_nu, int i, int run )
{
    this -> time = tm;
    this -> model = m;
    this -> type = tp;
    this -> passengers = p;
    this -> flight_number = fl_nu;
    this -> id = i;
    this -> runway = run;
}

string flight::getTime()
{ return time; }

string flight::getModel()
{ return model; }

string flight::getType()
{ return type; }

int flight::getPassengers()
{ return passengers; }

int flight::getRunway()
{ return runway; }

int flight::getFlight_number()
{ return flight_number; }

int flight::getID()
{ return id; }

void flight::setTime( string t )
{ this -> time = t; }

void flight::setModel( string mod )
{ this -> model = mod; }

void flight::setType( string tp )
{ this -> type = tp; }

void flight::setPassengers( int p )
{ this -> passengers = p; }

void flight::setRunway( int rw )
{ this -> runway = rw; }

void flight::setID( int i )
{ this -> id = i; }

//DoublyLinkedList
class Airport{

private:
    flight *first = nullptr;
    flight *last = nullptr;
    int number_of_flights = 0;

public:
    map <string, int> airplane_size;
    int runways[ 5 ][ 48 ] = { 0 };
    Airport () {

    }

    void getAirplaneSizeFromUser();

    //    void getNumberOfFlightsFromUser();

    void insert();

    void sort();

    void print();

    void Delete();

    //    void getRunWaysFormUser();

    flight *searchById( int id )
    {
        flight *current = first;

        if( first == NULL )
            return NULL;

        while( current -> getID() != id )
        {
            if( current -> getNextFlight() == NULL )
                return NULL;
            else
                current -> getNextFlight();
        }

        return current;
    };

    flight *searchByFlightNumber( int fl_num )
    {
        flight *current = first;

        if( first == NULL )
            return NULL;
        while( current -> getFlight_number() != fl_num )
        {
            if( current -> getNextFlight() == NULL )
                return  NULL;

            else
                current = current -> getNextFlight();
        }
        return current;
    };

};

//void Airport::getNumberOfFlightsFromUser()
//{ cin >> number_of_flights; }

void Airport::getAirplaneSizeFromUser()
{
    string ModelOfAirplane;
    int FirstLine;

    for ( int i = 0; i < 5; i++ )
    {
        cout << "Please Enter model of airplane: ";
        cin >> ModelOfAirplane;

        cout << "Please Enter the first line that airplane can take off or landing on it: ";
        cin >> FirstLine;

        airplane_size.insert( pair< string, int >( ModelOfAirplane, FirstLine ) );
    }
}

//void Airport::getRunWaysFormUser()
//{
//      cout << "Please Enter runway of this flight: ";
//      cin >> *runways[ i ];
//}

void Airport::insert()
{
    string time;
    string mdl;
    string typ;
    int passen_n;
    int r_w = 0;
    int fl_num;
    int id;

    cout << "Please Enter type of this flight:( <<Arrival Flight>> OR <<Exit Flight>> )";
    getline( cin, typ );

    cout << "Please Enter time of flight: ";
    getline( cin, time );

    cout << "Please Enter model of this airplane: ";
    cin >> mdl;

    cout << "Please Enter number of passengers for this flight: ";
    cin >> passen_n;

    cout << "Please Enter flight number: ";
    cin >> fl_num;

    cout << "Please Eneter ID number of this flight: ";
    cin >> id;

    if( typ == "Arrival Flight" )
    {
        cout << "Please Enter run way of this flight: ";
        cin >> r_w;
    }

    else if( typ == "Exit Flight" )
    {
        flight *exi = searchById( id );
        r_w = exi -> getRunway();
    }

    istringstream iss( time );
    string token;

    getline( iss, token, ':' );
    int hour = stoi( token );

    getline( iss, token, ':' );
    int minute = stoi( token );

    //hour -= 1;
    if ( minute > 0 )
        minute = 1;
    hour = ( hour * 2 ) + minute;

    if( runways[ r_w ][ hour ] == 0 )
        runways[ r_w ][ hour ] = 1;
    else
    {
        int counter = 0;
        int first = airplane_size[ mdl ];
        //  cout << "First is:" << first << endl;

        for( int i = first; i < 5; i++ )
        {
            if( runways[ i ][ hour ] == 0 )
            {
                runways[ i ][ hour ] = 1;
                r_w = i;
                break;
            }
            else
                counter++;
        }

        if( counter == 5 - first )
        {
            while( runways[ r_w ][ hour ] == 1 )
            {
                hour++;
                for( int i = first; i < 5; i++ )
                    if( runways[ i ][ hour ] == 0 )
                    {
                        runways[ i ][ hour ] = 1;
                        r_w = i;
                        break;
                    }

                if( hour == 48 )
                    cout << "\nUnfortunately All airport runways are full for today!!!";
            }
        }
    }

    int m = hour % 2;
    hour /= 2;

    time = to_string( hour );
    time += ':';

    if( m != 0 )
    {
        minute = 30;
        time += to_string( minute );
    }

    else
        time += "00";

    cout << "Time is: " << time << endl;

    flight *temp = new flight( time, mdl, typ, passen_n, fl_num, id, r_w );

    if( first )
        temp -> setNextFlight( first );
    if( !last )
        last = temp;

    first = temp;
    number_of_flights++;
}

void Airport::sort()
{
    flight *current = first;
    flight *next;

    //int k = number_of_flights;

    while( current -> getNextFlight() != NULL )
    {
        next = current -> getNextFlight();
        while ( next != NULL )
        {
            if( ( current -> getTime() ).compare( next -> getTime() ) > 0 )
            {
                cout << "BAAAAANGGG!\n";
                //time
                string temp = next -> getTime();
                next -> setTime( current -> getTime() );
                current -> setTime( temp );

                //model
                temp = next -> getModel();
                next -> setModel( current -> getModel() );
                current -> setModel( temp );

                //type
                temp = next -> getType();
                next -> setType( current -> getType() );
                current -> setType( temp );

                //passengers
                int tmp = next -> getPassengers();
                next -> setPassengers( current -> getPassengers() );
                current -> setPassengers( tmp );

                //Runway
                tmp = next -> getRunway();
                next -> setRunway( current -> getRunway() );
                current -> setRunway( tmp );

                //Flight Number
                tmp = next -> getFlight_number();
                next -> setFlight_number( current -> getFlight_number() );
                current -> setFlight_number( tmp );

                //ID
                tmp = next -> getID();
                next -> setID( current -> getID() );
                current -> setID( tmp );
            }
            next = next -> getNextFlight();
        }
        current = current -> getNextFlight();
    }
}

void Airport::print()
{
    int choose_sort;
    cout << "If you want to sort flights before print them enter 0 and if you don't want"
            " to sort enter another number: ";
    cin >> choose_sort;

    if( choose_sort == 0 )
        sort();

    flight *temp = first;

    if( !temp )
        cout << "There isn't any flight!!!\n";
    for( int i = 0; i < number_of_flights; i++ )
    {
        //TIME;
        cout << "Time of flight is: " << temp -> getTime();

        //MODEL
        cout << "\nModel of airplane is: " << temp -> getModel();

        //TYPE
        cout << "\nType of this flight is: " << temp -> getType();

        //NUMBER OF PASSENGERS
        cout << "\nNumber of passengers is: " << temp -> getPassengers();

        //RUN WAY
        cout << "\nRun way number of flight is: " << temp -> getRunway();

        //FLIGHT NUMBER
        cout << "\nFlight number is: " << temp -> getFlight_number();

        //ID
        cout << "\nID: " << temp -> getID() << endl;

        temp = temp -> getNextFlight();
    }
}

void Airport::Delete()
{
    int fl_num;
    cout << "Please Enter the flight number you want to delete it: ";
    cin >> fl_num;
    flight *del = searchById( fl_num );

    if( del == first )
        first = first -> getNextFlight();

    else
        del = del -> getNextFlight();

    number_of_flights--;
}

void func()
{
    Airport a;

    cout << "Welcome to the flight management menu of Isfahan Airport:\n"
         << "/////--------------------------------------------------------/////\n";

    while( true )
    {
        cout << "Please Enter << airplane_size >> for profile registration.\n";
        cout << "Please Enter << insert >> to add a flight.\n";
        cout << "Please Enter << delete >> to delete a flight.\n";
        cout << "Please Enter << arrange >> to sort the flights( sort by time ).\n";
        cout << "Please Enter << print >> to print all the flights.\n";

        string choose;
        cout << "Enter your choice please: ";
        getline( cin, choose );

        if( choose == "airplane_size" )
            a.getAirplaneSizeFromUser();
        else if( choose == "insert" )
            a.insert();
        else if( choose == "delete" )
            a.Delete();
        else if( choose == "arrange" )
            a.sort();
        else if( choose == "print" )
            a.print();
    }
}

int main( void )
{
    func();

    return 0;
}
