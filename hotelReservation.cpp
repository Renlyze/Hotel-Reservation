#include <iostream>
#include <cstring>
#include <string>

using namespace std;

// This is the Customer class that holds the details of a customer
class Customer {
public:
    string name;
    string address;
    string phone;
    string from_date;
    string to_date;
    float payment_advance;
    int booking_id;
};

// This is the Room class that holds the details of a room
class Room {
public:
    char type;
    char stype;
    char ac;
    int roomNumber;
    int rent;
    int status;

    Customer cust;  // Customer details for booked room
    Room* next;     // Pointer to the next room in the linked list

    Room(int rno) : roomNumber(rno), next(nullptr) {}

    // This function displays the details of a room
    void displayRoom();
};

// This is the HotelMgnt class that contains functions to manage the hotel
class HotelMgnt {
private:
    Room* head; // Pointer to the first room in the linked list

public:
    HotelMgnt() : head(nullptr) {}

    // This function allows checking in a customer to a room
    void checkIn();
    // This function displays all available rooms
    void getAvailRoom();
    // This function searches for a customer by name and displays their booking details
    void searchCustomer(const string&);
    // This function allows checking out a customer from a room
    void checkOut(int);
    // This function generates a summary report of all the guests currently in the hotel
    void guestSummaryReport();
    // This function allows managing rooms, including adding new rooms and searching for a room
    void manageRooms();
    ~HotelMgnt();
};

// Function to display room details
void Room::displayRoom() {
    cout << "\nRoom Number: \t" << roomNumber;
    cout << "\nType AC/Non-AC (A/N): " << ac;
    cout << "\nType Comfort (S/N): " << type;
    cout << "\nType Size (S/M/L): " << stype;
    cout << "\nRent: " << rent;
}

/* Implementation of checkIn function
    code for checking in a customer*/
void HotelMgnt::checkIn() {
    int rno;
    cout << "\nEnter Room number: ";
    cin >> rno;

    Room* current = head;
    while (current != nullptr) {
        if (current->roomNumber == rno) {
            if (current->status == 1) {
                cout << "\nRoom is already Booked";
                return;
            }

            cout << "\nEnter booking id: ";
            cin >> current->cust.booking_id;

            cout << "\nEnter Customer Name (First Name): ";
            cin >> current->cust.name;

            cout << "\nEnter Address (only city): ";
            cin >> current->cust.address;

            cout << "\nEnter Phone: ";
            cin >> current->cust.phone;

            cout << "\nEnter From Date: ";
            cin.ignore();
            getline(cin, current->cust.from_date);
            

            cout << "\nEnter to Date: ";
            cin.ignore();
            getline(cin, current->cust.to_date);

            cout << "\nEnter Advance Payment: ";
            cin >> current->cust.payment_advance;

            current->status = 1;

            cout << "\nCustomer Checked-in Successfully..\n" << endl;
            return;
        }
        current = current->next;
    }

    cout << "\nRoom not found\n" << endl;
}

// Implementation of getAvailRoom function
void HotelMgnt::getAvailRoom() {
    Room* current = head;
    bool found = false;

    while (current != nullptr) {
        if (current->status == 0) {
            current->displayRoom();
            cout << "\n\nPress enter for the next room";
            found = true;
        }
        current = current->next;
    }

    if (!found){
        cout << "All rooms are booked!\n" << endl;
    }
}

// Implementation of searchCustomer function
void HotelMgnt::searchCustomer(const string& pname) {
    Room* current = head;
    bool found = false;

    while (current != nullptr){
        if(current->status == 1 && current->cust.name == pname){
            cout << "\nCustomer name: " << current->cust.name;
            cout << "\nRoom number: " << current->roomNumber << endl;
            cout << endl;
            found = true;
        }

        current = current->next;
    }

    if (!found){
        cout << "\nPerson not found\n";
    }
}

// Implementation of checkOut function
void HotelMgnt::checkOut(int roomNum) {
    Room* current = head;
    bool found = false;

    while (current != nullptr){
        if(current->status = 1 && current->roomNumber == roomNum){
            int days;
            float billAmount = 0;

            cout << "\nEnter the total Days checked-in: ";
            cin >> days;

            billAmount = days * current->rent;

            cout << "\n\t######## CheckOut Details ########\n";
            cout << "\nCustomer Name : " << current->cust.name;
            cout << "\nRoom Number : " << current->roomNumber;
            cout << "\nAddress : " << current->cust.address;
            cout << "\nPhone : " << current->cust.phone;
            cout << "\nTotal Amount Due : " << billAmount << " /";
            cout << "\nAdvance Paid: " << current->cust.payment_advance << " /";
            cout << "\n*** Total Payable: " << billAmount - current->cust.payment_advance << "/ only";
            cout << endl;
            current->status = 0;
            found = true;
        }
        current = current->next;
    }

    if(!found){
        cout << "\nRoom not found\n";
    }

}

// Implementation of guestSummaryReport function
void HotelMgnt::guestSummaryReport() {
    Room* current = head;
    bool found = false;

    while (current != nullptr){
        if(current->status == 1){
            cout << "\nCustomer First Name: " << current->cust.name;
            cout << "\nRoom Number: " << current->roomNumber;
            cout << "\nAddress: " << current->cust.address;
            cout << "\nPhone: " << current->cust.phone;
            cout << "\n---------------------------------------\n" << endl;
            found = true;
        }

        current = current->next;
    }

    if(!found){
            cout <<"\nSummary Report not Available\n";
        }
}

// Implementation of manageRooms function
void HotelMgnt::manageRooms() {
    int opt, rno, flag = 0;
    char ch;
    Room* newRoom = nullptr;

    do {
        cout << "\n### Manage Rooms ###";
        cout << "\n1. Add Room";
        cout << "\n2. Search Room";
        cout << "\n3. Back to Main Menu";
        cout << "\nChoose what you want to do(1-3): ";
        cin >> opt;

        switch (opt){
            case 1: 
                cout << "\nEnter Room Number: ";
                cin >> rno;
                newRoom = new Room(rno);

                cout << "\nType AC/Non-Ac (A/N): ";
                cin >> newRoom->ac;

                cout <<"\nType Comfort (S/N): ";
                cin >> newRoom->type;

                cout << "\nRoom Size (S/M/L): ";
                cin >> newRoom->stype;

                cout << "\nRent per night: ";
                cin >> newRoom->rent;


                newRoom->next = head;
                head = newRoom;
                cout << "\nRoom Added!";
                break;
            case 2:
                cout << "\nEnter Room Number: ";
                cin >> rno;
                newRoom->displayRoom();
                break;
            case 3:
                break;    
            default:
                cout << "Please select a proper option.";
                break;
        }   

    } while(opt != 3);
}

/*This is the destructor for the HotelMgnt class
 It frees the memory occupied by the rooms*/
HotelMgnt::~HotelMgnt() {
    Room* current = head;
    while (current != nullptr) {
        Room* next = current->next;
        delete current;
        current = next;
    }
}

/* This is the main function of the program
It initializes a HotelMgnt object and repeatedly calls its functions based on user input*/
int main() {
    HotelMgnt hm;
    int opt;
    string pname;
     int rno;

    do {
        cout << "######## Hotel Management #########\n";
        cout << "\n1. Manage Rooms";
        cout << "\n2. Check-In Room";
        cout << "\n3. Available Rooms";
        cout << "\n4. Search Customer";
        cout << "\n5. Check-Out Room";
        cout << "\n6. Guest Summary Report";
        cout << "\n7. Exit";
        cout << "\n\nEnter Option: ";
        cin >> opt;

        switch (opt) {
            case 1:
                hm.manageRooms();
                break;
            case 2:
                hm.checkIn();
                break;
            case 3:
                hm.getAvailRoom();
                break;
            case 4:
                cout << "Enter Customer Name: ";
                cin >> pname;
                hm.searchCustomer(pname);
                break;
            case 5:
                cout << "Enter Room Number : ";
                cin >> rno;
                hm.checkOut(rno);
                break;
            case 6:
                hm.guestSummaryReport();
                break;
            case 7:
                cout << "\nTHANK YOU! FOR USING SOFTWARE\n";
                break;
            default:
                cout << "\nPlease Enter correct option";
                break;
        }
    } while (opt != 7);

    return 0;
}
