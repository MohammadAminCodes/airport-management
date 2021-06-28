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

    flight *getPreviousFLight()
    { return previousFlight; }

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

    void print( int );

    void Delete();

    //    void getRunWaysFormUser();

    flight *searchById( int id )
    {
        flight *current = first;

        while( current != NULL )
        {
            if( current -> getID() == id )
            {
                return current;
                break;
            }
            current = current -> getNextFlight();
        }
        return NULL;
    };

    flight *searchByFlightNumber( int fl_num )
    {
        cout << "BBBBBBBBBBBBB\n";
        flight *current = first;

        if( first == NULL )
            return NULL;

        while(current -> getFlight_number() != fl_num )
        {
            //if it is last node
            if( current -> getNextFlight() == NULL)
                return NULL;
            else
                current = current -> getNextFlight();
            //go to next link

        }

        //if data found, return the current Link
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
        cin.ignore();
        cout << "Please Enter the first line that airplane can take off or landing on it: ";
        cin >> FirstLine;
        cin.ignore();
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
    cin.ignore();

    cout << "Please Enter number of passengers for this flight: ";
    cin >> passen_n;
    cin.ignore();

    cout << "Please Enter flight number: ";
    cin >> fl_num;
    cin.ignore();

    cout << "Please Eneter ID number of this flight: ";
    cin >> id;
    cin.ignore();

    if( typ == "Arrival Flight" )
    {
        cout << "Please Enter run way of this flight: ";
        cin >> r_w;
        cin.ignore();
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

    //    cout << "Time is: " << time << endl;

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

void Airport::print( int choose )
{
    sort();
    flight *temp = first;
    system("color 0c");
    if( !temp )
        cout << "There isn't any flight!!!\n";

    for( int i = 0; i < number_of_flights; i++ )
    {
        system("color 0e");                         // change text color to yellow

        if( choose == 0 )
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

            cout << "_____________________________________________\n";
        }

        else if( choose != 0 & temp -> getRunway() == choose )
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

            cout << "_____________________________________________\n";
        }
        temp = temp -> getNextFlight();
    }

    //see menu
    cout << "Please enter << y >> to see the menu:";
    char n;
    cin >> n;
    cin.ignore();

    system("color 07");              // switch to default color
}

void Airport::Delete()
{
    int fl_num;
    cout << "Please Enter the flight number you want to delete it: ";
    cin >> fl_num;
    cin.ignore();

    flight *del = searchByFlightNumber( fl_num );
    cout << del -> getID();
    flight *temp = first;
    flight *tmp = first;
    int not_exit_in_list=0;

    istringstream iss( del -> getTime() );
    string token;

    getline( iss, token, ':' );
    int hour = stoi( token );

    getline( iss, token, ':' );
    int minute = stoi( token );

    if ( minute > 0 )
        minute = 1;
    hour = ( hour * 2 ) + minute;

    if( runways[ del -> getRunway() ][ hour ] == 1 )
        runways[ del -> getRunway() ][ hour ] = 0;

    if(first == del )
    {
        temp = first;
        first = first -> getNextFlight();
        delete temp;
    }

    else
    {
        while( tmp != last )
        {
            temp = tmp -> getNextFlight();
            if( temp == del )
            {
                if( temp == last )
                {
                    tmp -> setNextFlight( NULL );
                    delete temp;
                    last = tmp;
                    not_exit_in_list = 1;
                    break;
                }
                else
                {
                    tmp -> setNextFlight( temp -> getNextFlight() );
                    delete temp;
                    not_exit_in_list = 1;
                    break;
                }
            }
            tmp = tmp -> getNextFlight();
        }

        if( not_exit_in_list == 0 )
        {
            cout<<"There is not flight with flight number = "<< fl_num <<" in flights."<<endl;
            number_of_flights++;
        }
    }

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
        cout << "Please Enter << exit >> to close program.\n";

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
        {
            //choose runway
            cout << "Please Enter runway which you want to print its flights: ";
            int choose_runway;
            cin >> choose_runway;
            cin.ignore();

            a.print( choose_runway );
        }
        else if( choose == "close" )
            break;
    }
}

int main( void )
{
    func();

    return 0;
}
