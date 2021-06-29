/*****************************************************************************/
/*          This simple program managing information by linked list.         */
/*         in this program you can add, delete and show flights data.        */
/*****************************************************************************/
#include <iostream>
#include <cstring>
#include <map>
#include <sstream>
#include <ctime>
using namespace std;

//flight
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
    flight( string, string, string, int, int, int );                // constructor
    flight( string, string, string, int, int, int, int );           // constructor

    void setPreviousFlight( flight *previousFlight )
    { this -> previousFlight = previousFlight; }

    void  setNextFlight( flight *nextflight )
    { this -> nextFlight = nextflight; }

    flight *getPreviousFLight()
    { return previousFlight; }

    flight *getNextFlight() { return nextFlight; }
    string getTime();              // get time
    string getModel();             // get model
    string getType();              // get type
    int getPassengers();           // get number of passengers   
    int getRunway();               // get run way
    int getFlight_number();        // get flight number
    int getID();                   // get ID

    void setTime( string tm );      // set time
    void setModel( string mod );    // set model
    void setType( string tp );      // set type
    void setPassengers( int p );    // set number of passengers
    void setRunway( int rw );       //set run way
    void setFlight_number( int fl_num ) { flight_number = fl_num; }  // set flight number
    void setID( int i );            // set ID

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

//Airport
class Airport{

private:
    flight *first;
    flight *last;
    int number_of_flights = 0;

public:
    map <string, int> airplane_size;
    int runways[ 5 ][ 48 ];

    Airport () {
        first = NULL;
        last = NULL;

        for( int i = 0; i < 5; i++ )
            for( int j = 0; j < 48; j++ )
                runways[ i ][ j ] = 0;
    }

    void getAirplaneSizeFromUser();

    void insert();

    void sort();

    void print( int );

    void Delete();

    //search by ID
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

    //search by flight number
    flight *searchByFlightNumber( int fl_num )
    {
        flight *current = first;

        if( first == NULL )
            return NULL;

        while( current -> getFlight_number() != fl_num )
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

//get first line which each model can dlight on that
void Airport::getAirplaneSizeFromUser()
{
    string ModelOfAirplane;
    int FirstLine;

    system("color 0a");                // change screen color to green
    for ( int i = 0; i < 5; i++ )
    {
        cout << "Please Enter model of airplane: ";          
        cin >> ModelOfAirplane;        //get model of airplane 
        cin.ignore();
        cout << "Please Enter the first line that airplane can take off or landing on it: ";
        cin >> FirstLine;              //get first line
        cin.ignore();
        airplane_size.insert( pair< string, int >( ModelOfAirplane, FirstLine ) );
    }
    system("color 07");                         // switch to default color
}

// insert the flights
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
    getline( cin, typ );                   //get type

    cout << "Please Enter time of flight: ";
    getline( cin, time );                  //get time

    cout << "Please Enter model of this airplane: ";
    cin >> mdl;                            //get model
    cin.ignore();

    cout << "Please Enter number of passengers for this flight: ";
    cin >> passen_n;                       //get number of passengers
    cin.ignore();

    cout << "Please Enter flight number: ";
    cin >> fl_num;                         //get flight number
    cin.ignore();

    cout << "Please Eneter ID number of this flight: ";
    cin >> id;                             //get id
    cin.ignore();

    //Arrival flight or Exit flight
    if( typ == "Arrival Flight" )
    {
        cout << "Please Enter run way of this flight: ";
        cin >> r_w;                   //get run way
        cin.ignore();
    }

    else if( typ == "Exit Flight" )
    {
        system("color 0b");         // change text color to aqua
        flight *exi = searchById( id );
        r_w = exi -> getRunway();
    }

    //convert time to minunte and hour
    istringstream iss( time );
    string token;
    getline( iss, token, ':' );
    int hour = stoi( token );

    getline( iss, token, ':' );
    int minute = stoi( token );

    //find second element of array
    if ( minute > 0 )
        minute = 1;
    hour = ( hour * 2 ) + minute;

    if( runways[ r_w - 1 ][ hour ] == 0 )
        runways[ r_w - 1 ][ hour ] = 1;

    else
    {
        int counter = 0;
        int f = airplane_size[ mdl ];   //find first runway which each model can flight on that

        for( int i = f - 1; i < 5; i++ )
        {
            if( runways[ i ][ hour ] == 0 )
            {
                runways[ i ][ hour ] = 1;        //run way is full now
                r_w = i + 1;
                break;
            }
            else
                counter++;
        }

        int checker = r_w;
        if( counter == 6 - f )
        {
            while( runways[ checker - 1 ][ hour ] == 1 )
            {
                hour++;
                for( int i = f - 1; i < 5; i++ )
                    if( runways[ i ][ hour ] == 0 )
                    {
                        runways[ i ][ hour ] = 1;       // run way is full now
                        checker = i;
                        r_w = i + 1;
                        break;           //exit from for loop
                    }
            }
            system("color 0b");         // change text color to aqua
            if( hour == 48 )
                cout << "\nUnfortunately All airport runways are full for today!!!";
            system("color 07");         // switch to default color
        }
    }

    //find time and convert it to string
    int m = hour % 2;
    hour /= 2;

    time = to_string( hour );          //convert int to string
    time += ':';

    if( m != 0 )
    {
        minute = 30;
        time += to_string( minute );
    }

    else
        time += "00";                    //if minute = 0, add 00 to time

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

    if( current == NULL )
        return;

    else
    {
        while( current != NULL )
        {
            //flight next will point to flight next to current
            next = current -> getNextFlight();

            while ( next != NULL )
            {
        
                if ( ( current -> getTime() ).compare( next -> getTime() ) > 0  )
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
}

//print flights
void Airport::print( int choose )
{
    flight *temp = first;

    system("color 0c");
    if( !temp )
    {
        cout << "_____________________________________________\n";
        cout << "There isn't any flight!!!";
        cout << "\n_____________________________________________\n";
        cout << '\a';
    }

    else
    {
        sort();
        sort();

        cout << "_____________________________________________\n";
        for( int i = 0; i < number_of_flights; i++ )
        {
            system("color 0e");                         // change text color to yellow

            if( choose == 0 )
            {
                //TIME
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
                //TIME
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
        cout << '\a';             //make noise
    }

    // declaring argument of time()
    time_t my_time = time(NULL);

    // ctime() used to give the present time
    cout << "Now time is: " << ctime( &my_time );
    cout << "_____________________________________________\n";

    //see menu
    cout<<"press any key to continue...";
    cin.get();                        // show message and pause

    system("color 07");              // switch to default color
}

//Delete flight
void Airport::Delete()
{
    system("color 0c");                // change screen color to red
    cout << "Please Enter the flight number you want to delete it: ";

    int fl_num;
    cin >> fl_num;
    cin.ignore();

    flight *del = searchByFlightNumber( fl_num );
    flight *temp = first;
    flight *tmp = first;
    int not_exit_in_list = 0;

    istringstream iss( del -> getTime() );
    string token;

    getline( iss, token, ':' );
    int hour = stoi( token );            //seprate hour

    getline( iss, token, ':' );
    int minute = stoi( token );          //seprate minute

    if ( minute > 0 )
        minute = 1;
    hour = ( hour * 2 ) + minute;

    if( runways[ del -> getRunway() ][ hour ] == 1 )
        runways[ del -> getRunway() ][ hour ] = 0;             //empty run way

    if(first == del )
    {
        temp = first;
        first = first -> getNextFlight();
        delete temp;
        cout << "Flight with flight number " << fl_num << " was successfully removed." << endl;
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
                cout << "Flight with flight number "<< fl_num << " was successfully removed." << endl;
            }
            tmp = tmp -> getNextFlight();
        }

        if( not_exit_in_list == 0 )
        {
            cout << "There is not flight with flight number = " << fl_num << " in flights." << endl;
            number_of_flights++;
        }
    }
    cout << '\a';                           //make sound
    cin.get();
    system("color 07");                         // switch to default color

    number_of_flights--;
}

void func()
{
    Airport a;

    system("color 0b");         // change text color to aqua

    cout << "Welcome to the flight management menu of Isfahan Airport:\n"
         << "/////--------------------------------------------------------/////\n"
         << "press any key to continue...";

    cin.get();

    system("color 07");         // switch to default color

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

        if( choose == "airplane_size" )      //set airplane and runway
            a.getAirplaneSizeFromUser();
        else if( choose == "insert" )        //add flight
            a.insert();
        else if( choose == "delete" )        //delete flight
            a.Delete();
        else if( choose == "arrange" )       //sort flights with time
            a.sort();
        else if( choose == "print" )         //print flights
        {
            //choose runway
            cout << "Please Enter runway which you want to print its flights:( if you want print all flights enter << 0 >> )";
            int choose_runway;
            cin >> choose_runway;
            cin.ignore();

            a.print( choose_runway );
        }
        else if( choose == "exit" )
        {
            system("cls");                 // clear screen
            system("color 3e");            // change text color to aqua
            cout<<"\n  Programming by"<<endl<<endl<<endl;
            cout<<"\t\t\tMohammad Amin\n\n\n";
            break;
            cin.get();                       // show programmer data & pause
        }
    }
}

int main( void )
{
    func();  //show menu

    return 0;
}
/*****************************************************************************/
