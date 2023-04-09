#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

// struct type for single booking info
struct Booking {
    int reservationNumber = 00000;
    string fullName;
    string roomType;
    int roomNumber = 0;
    int numberOfNights = 0;
    double totalAmountOfInvoice = 0.0;
    double saving = 0.0;
};

// struct type for single room info
struct Room {
    int roomNumber = 0;
    bool isAvailable = true; // by default, all room are available.
    string roomType;
};

// struct type for single order info
struct Order {
    int reservationNumber = 00000;
    int orderNumber = 00000;
    string fullName;
    string roomType;
    int roomNumber = 0;
    int numberOfNights = 0;
    double totalAmountOfInvoice = 0.0;
    double saving = 0.0;
};

// struct type for single invoice info
struct Invoice {
    string invoiceNumber;
    int orderNumber = 00000;
    string fullName;
    double taxFee = 0;
    double totalAmountOfInvoice = 0.0;
};

// remove whitespaces from the beginning of a string
string ltrim(const string &s) {
    size_t start = s.find_first_not_of(" \n\r\t\f\v");
    return (start == string::npos) ? "" : s.substr(start);
}

// remove whitespaces from the end of a string
string rtrim(const string &s) {
    size_t end = s.find_last_not_of(" \n\r\t\f\v");
    return (end == string::npos) ? "" : s.substr(0, end + 1);
}

// remove whitespaces from both ends of a string
string trim(const string &s) {
    return rtrim(ltrim(s));
}

// show system operation options
void show_customer_menu() {
    cout << "---------------------------------------------------------\n";
    cout << "1. BOOKING\n"
            "2. HOTEL ROOM INFORMATION\n"
            "3. ORDER INFORMATION\n"
            "4. INVOICE\n"
            "5. EXIT\n";
    cout << "---------------------------------------------------------\n";
}

// check if a string represents a number
bool isNumber(string &isNumber) {
    int len = isNumber.length();

    if (len == 0) {
        return false;
    }

    bool isaNumber = false;

    for (int i = 0; i < len; i++) {
        if (isdigit(isNumber[i])) {
            isaNumber = true;
        } else {
            isaNumber = false;
            break;
        }
    }

    return isaNumber;
}

// generate discount values
double Discount(int i) {
    double discount[3] = {1, 0.9, 0.8};
    return discount[i];
}

// ask user for next operation
void customer_next_step(bool &selectionCheck) {
    string nextStepChoice;

    cout << "---------------------------------------------------------\n";
    cout << "WHAT DO YOU WANT TO DO NEXT: \n"
            "1. BACK TO MENU \n";
    cout << "---------------------------------------------------------\n";

    bool isAValidNumber = false;

    while (!isAValidNumber) { // loop for user input for next step
        getline(cin, nextStepChoice);

        if (nextStepChoice == "1") {
            isAValidNumber = true;
            selectionCheck = true;
        } else {
            cin.clear();
            cout << "INVALID INPUT, PLEASE TRY AGAIN!\n";
        }
    }
}

// make room booking, and generate order & invoice info
void customer_booking(bool &selectionCheck, vector<Booking> &bookings, vector<Room> &rooms, vector<Order> &orders,
                      vector<Invoice> &invoices) {

    bool bookingFinalConfirmationFlag = true;

    while (bookingFinalConfirmationFlag) { // loop for room booking
        Booking booking;
        Order order;
        Invoice invoice;

        double discount;

        bool roomTypeFlag = true;

        while (roomTypeFlag) { // loop for user selection for room type
            string roomType, roomNumber, numberOfNights, roomNumberGeneratingMethod;
            int digitRoomNumber, digitNumberOfNights;

            cout << "---------------------------------------------------------\n";
            cout << "PLEASE SELECT ROOM TYPE : \n"
                    "1. SINGLE ROOM    2. DOUBLE ROOM\n";

            getline(cin, roomType);

            if (roomType == "1") { // single room
                roomTypeFlag = false;

                booking.roomType = "SINGLE ROOM";

                cout << "---------------------------------------------------------\n";
                cout << "DO YOU WANT TO SELECT ROOM NUMBER BY YOURSELF OR GENERATE BY MACHINE?\n"
                        "1. SELF-SELECTION,                          2. GENERATING BY MACHINE.\n";

                bool roomNumberGeneratingMethodFlag = true;

                while (roomNumberGeneratingMethodFlag) { // loop for room number generation

                    getline(cin, roomNumberGeneratingMethod);

                    if (roomNumberGeneratingMethod == "1") { // branch for self-selected room number
                        roomNumberGeneratingMethodFlag = false;

                        bool roomNumberFlag = true;

                        while (roomNumberFlag) { // loop for user input for single room number
                            cout << "---------------------------------------------------------\n";
                            cout << "PLEASE ENTER ROOM NUMBER, ROOM NUMBER SHOULD BE BETWEEN 1-150.\n";

                            getline(cin, roomNumber);

                            if (isNumber(roomNumber)) { // check input for room number
                                digitRoomNumber = stoi(roomNumber);

                                if (digitRoomNumber > 0 && digitRoomNumber < 151) { // process valid room number

                                    for (int i = 0; i < 300; i++) {

                                        if (rooms[i].roomNumber == digitRoomNumber && rooms[i].isAvailable) { // if the corresponding room is available
                                            roomNumberFlag = false;

                                            booking.roomNumber = digitRoomNumber;

                                            cout << "\nGOOD! THIS ROOM IS AVAILABLE!\n";
                                            cout << "---------------------------------------------------------\n";

                                            do { // process user input for full name
                                                cout << "PLEASE ENTER YOUR FULL NAME:\n";

                                                getline(cin, booking.fullName);
                                                booking.fullName = trim(booking.fullName);

                                                if (booking.fullName.empty()) {
                                                    cout << "INVALID INPUT, PLEASE ENTER AGAIN.\n";
                                                }
                                            } while (booking.fullName.empty());

                                            bool numberOfNightsFlag = true;

                                            while (numberOfNightsFlag) { // loop for user input for number of nights
                                                cout << "---------------------------------------------------------\n";
                                                cout << "HOW MANY NIGHTS DO YOU WANT TO STAY? "
                                                        "(ENTER NUMBER, NO MORE THAN 150 NIGHTS)\n";

                                                getline(cin, numberOfNights);

                                                if (isNumber(numberOfNights)) { // check input for number of nights
                                                    digitNumberOfNights = stoi(numberOfNights);

                                                    if (digitNumberOfNights > 0 && digitNumberOfNights < 151) { // process valid number of nights
                                                        numberOfNightsFlag = false;

                                                        booking.numberOfNights = digitNumberOfNights;

                                                        // generate discount
                                                        discount = Discount(rand() % 3);
                                                        booking.totalAmountOfInvoice =
                                                                100 * booking.numberOfNights * discount;
                                                    } else { // invalid number of nights
                                                        cin.clear();
                                                        cout << "INVALID INPUT, PLEASE ENTER A NUMBER BETWEEN 1 AND 150.\n";
                                                    }
                                                } else { // invalid number of nights
                                                    cin.clear();
                                                    cout << "INVALID INPUT, PLEASE ENTER A NUMBER BETWEEN 1 AND 150.\n";
                                                }
                                            }
                                        } else if (rooms[i].roomNumber == digitRoomNumber && !rooms[i].isAvailable) { // if the corresponding room is not available
                                            cin.clear();
                                            cout << "THIS ROOM IS OCCUPIED, PLEASE SELECT ANOTHER ROOM!\n";
                                            break;
                                        }
                                    }
                                } else { // invalid room number input
                                    cin.clear();
                                    cout << "ROOM NUMBER EXCEED RANGE, PLEASE ENTER A NUMBER BETWEEN 1 AND 150.\n";
                                }
                            } else { // invalid room number input
                                cin.clear();
                                cout << "INVALID INPUT, PLEASE ENTER A NUMBER BETWEEN 1 AND 150.\n";
                            }
                        }
                    } else if (roomNumberGeneratingMethod == "2") { // branch for machine-generated room number
                        roomNumberGeneratingMethodFlag = false;

                        bool roomNumberFlag = true;

                        while (roomNumberFlag) { // loop for room number generation

                            digitRoomNumber = rand() % 150 + 1;

                            if (digitRoomNumber > 0 && digitRoomNumber < 151) { // process machine-generated room number

                                for (int i = 0; i < 300; i++) {

                                    if (rooms[i].roomNumber == digitRoomNumber && rooms[i].isAvailable) { // if the corresponding room is available
                                        roomNumberFlag = false;

                                        cout << digitRoomNumber;

                                        booking.roomNumber = digitRoomNumber;

                                        cout << "\nGOOD! THIS ROOM IS AVAILABLE!\n";
                                        cout << "---------------------------------------------------------\n";

                                        do { // process user input for full name
                                            cout << "PLEASE ENTER YOUR FULL NAME:\n";

                                            getline(cin, booking.fullName);
                                            booking.fullName = trim(booking.fullName);

                                            if (booking.fullName.empty()) {
                                                cout << "INVALID INPUT, PLEASE ENTER AGAIN.\n";
                                            }
                                        } while (booking.fullName.empty());

                                        bool numberOfNightsFlag = true;

                                        while (numberOfNightsFlag) { // loop for user input for number of nights

                                            cout << "---------------------------------------------------------\n";
                                            cout << "HOW MANY NIGHTS DO YOU WANT TO STAY? "
                                                    "(ENTER NUMBER, NO MORE THAN 150 NIGHTS)\n";

                                            getline(cin, numberOfNights);

                                            if (isNumber(numberOfNights)) { // check input for number of nights

                                                digitNumberOfNights = stoi(numberOfNights);

                                                if (digitNumberOfNights > 0 && digitNumberOfNights < 151) { // process valid number of nights
                                                    numberOfNightsFlag = false;

                                                    booking.numberOfNights = digitNumberOfNights;

                                                    // generate discount
                                                    discount = Discount(rand() % 3);
                                                    booking.totalAmountOfInvoice =
                                                            100 * booking.numberOfNights * discount;
                                                } else { // invalid number of nights
                                                    cin.clear();
                                                    cout << "INVALID INPUT, PLEASE ENTER A NUMBER BETWEEN 1 AND 150.\n";
                                                }
                                            } else { // invalid number of nights
                                                cin.clear();
                                                cout << "INVALID INPUT, PLEASE ENTER A NUMBER BETWEEN 1 AND 150.\n";
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else { // invalid input for room number generation
                        cin.clear();
                        cout << "INVALID INPUT, PLEASE TRY AGAIN\n";
                    }
                }
            } else if (roomType == "2") { // double room
                roomTypeFlag = false;

                booking.roomType = "DOUBLE ROOM";

                cout << "---------------------------------------------------------\n";
                cout << "DO YOU WANT TO SELECT ROOM NUMBER BY YOURSELF OR GENERATE BY MACHINE?\n"
                        "1. SELF-SELECTION,                          2. GENERATING BY MACHINE.\n";
                cout << "---------------------------------------------------------\n";

                bool roomNumberGeneratingMethodFlag = true;

                while (roomNumberGeneratingMethodFlag) { // loop for room number generation

                    getline(cin, roomNumberGeneratingMethod);

                    if (roomNumberGeneratingMethod == "1") { // branch for self-selected room number
                        roomNumberGeneratingMethodFlag = false;

                        bool roomNumberFlag = true;

                        while (roomNumberFlag) { // loop for user input for single room number
                            cout << "---------------------------------------------------------\n";
                            cout << "PLEASE ENTER ROOM NUMBER, ROOM NUMBER SHOULD BE BETWEEN 151-300.\n";

                            getline(cin, roomNumber);

                            if (isNumber(roomNumber)) { // check input for room number
                                digitRoomNumber = stoi(roomNumber);

                                if (digitRoomNumber > 150 && digitRoomNumber < 301) { // process valid room number

                                    for (int i = 0; i < 300; i++) {

                                        if (rooms[i].roomNumber == digitRoomNumber && rooms[i].isAvailable) { // if the corresponding room is available
                                            roomNumberFlag = false;

                                            booking.roomNumber = digitRoomNumber;

                                            cout << "\nGOOD! THIS ROOM IS AVAILABLE!\n";
                                            cout << "---------------------------------------------------------\n";

                                            do { // process user input for full name
                                                cout << "PLEASE ENTER YOUR FULL NAME:\n";

                                                getline(cin, booking.fullName);
                                                booking.fullName = trim(booking.fullName);

                                                if (booking.fullName.empty()) {
                                                    cout << "INVALID INPUT, PLEASE ENTER AGAIN.\n";
                                                }
                                            } while (booking.fullName.empty());

                                            bool numberOfNightsFlag = true;

                                            while (numberOfNightsFlag) { // loop for user input for number of nights
                                                cout << "---------------------------------------------------------\n";
                                                cout << "HOW MANY NIGHTS DO YOU WANT TO STAY? "
                                                        "(ENTER NUMBER, NO MORE THAN 150 NIGHTS)\n";

                                                getline(cin, numberOfNights);

                                                if (isNumber(numberOfNights)) { // check input for number of nights
                                                    digitNumberOfNights = stoi(numberOfNights);

                                                    if (digitNumberOfNights > 0 && digitNumberOfNights < 151) { // process valid number of nights
                                                        numberOfNightsFlag = false;

                                                        booking.numberOfNights = digitNumberOfNights;

                                                        // generate discount
                                                        discount = Discount(rand() % 3);
                                                        booking.totalAmountOfInvoice =
                                                                150 * booking.numberOfNights * discount;
                                                    } else { // invalid number of nights
                                                        cin.clear();
                                                        cout << "INVALID INPUT, PLEASE ENTER A NUMBER BETWEEN 1 AND 150.\n";
                                                    }
                                                } else { // invalid number of nights
                                                    cin.clear();
                                                    cout << "INVALID INPUT, PLEASE ENTER A NUMBER BETWEEN 1 AND 150.\n";
                                                }
                                            }
                                        } else if (rooms[i].roomNumber == digitRoomNumber && !rooms[i].isAvailable) { // if the corresponding room is not available
                                            cin.clear();
                                            cout << "THIS ROOM IS OCCUPIED, PLEASE SELECT ANOTHER ROOM!\n";
                                            break;
                                        }
                                    }
                                } else { // invalid room number input
                                    cin.clear();
                                    cout << "ROOM NUMBER EXCEED RANGE, PLEASE ENTER A NUMBER BETWEEN 151 AND 300.\n";
                                }
                            } else { // invalid room number input
                                cin.clear();
                                cout << "INVALID INPUT, PLEASE ENTER A NUMBER BETWEEN 151 AND 300.\n";
                            }
                        }
                    } else if (roomNumberGeneratingMethod == "2") { // branch for machine-generated room number
                        roomNumberGeneratingMethodFlag = false;

                        bool roomNumberFlag = true;

                        while (roomNumberFlag) { // loop for room number generation

                            digitRoomNumber = rand() % 151 + 150;

                            if (digitRoomNumber > 150 && digitRoomNumber < 301) { // process machine-generated room number

                                for (int i = 0; i < 300; i++) {

                                    if (rooms[i].roomNumber == digitRoomNumber && rooms[i].isAvailable) { // if the corresponding room is available
                                        roomNumberFlag = false;

                                        cout << digitRoomNumber;

                                        booking.roomNumber = digitRoomNumber;

                                        cout << "\nGOOD! THIS ROOM IS AVAILABLE!\n";
                                        cout << "---------------------------------------------------------\n";

                                        do { // process user input for full name
                                            cout << "PLEASE ENTER YOUR FULL NAME:\n";

                                            getline(cin, booking.fullName);
                                            booking.fullName = trim(booking.fullName);

                                            if (booking.fullName.empty()) {
                                                cout << "INVALID INPUT, PLEASE ENTER AGAIN.\n";
                                            }
                                        } while (booking.fullName.empty());

                                        bool numberOfNightsFlag = true;

                                        while (numberOfNightsFlag) { // loop for user input for number of nights

                                            cout << "---------------------------------------------------------\n";
                                            cout << "HOW MANY NIGHTS DO YOU WANT TO STAY? "
                                                    "(ENTER NUMBER, NO MORE THAN 150 NIGHTS)\n";

                                            getline(cin, numberOfNights);

                                            if (isNumber(numberOfNights)) { // check input for number of nights

                                                digitNumberOfNights = stoi(numberOfNights);

                                                if (digitNumberOfNights > 0 && digitNumberOfNights < 151) { // process valid number of nights
                                                    numberOfNightsFlag = false;

                                                    booking.numberOfNights = digitNumberOfNights;

                                                    // generate discount
                                                    discount = Discount(rand() % 3);
                                                    booking.totalAmountOfInvoice =
                                                            150 * booking.numberOfNights * discount;
                                                } else { // invalid number of nights
                                                    cin.clear();
                                                    cout << "INVALID INPUT, PLEASE ENTER A NUMBER BETWEEN 1 AND 150.\n";
                                                }
                                            } else { // invalid number of nights
                                                cin.clear();
                                                cout << "INVALID INPUT, PLEASE ENTER A NUMBER BETWEEN 1 AND 150.\n";
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else { // invalid input for room number generation
                        cin.clear();
                        cout << "INVALID INPUT, PLEASE TRY AGAIN\n";
                    }
                }
            } else { // invalid selection for room type
                cin.clear();
                cout << "INVALID INPUT, PLEASE TRY AGAIN\n";
            }
        }

        // generate reservation number
        int reservationNumber = rand() % 90000 + 10000;
        booking.reservationNumber = reservationNumber;

        // print reservation info
        cout << "---------------------------------------------------------\n";
        cout << "BOOKING INFORMATION CONFIRM: \n";
        cout << "\tRESERVATION NUMBER: " << booking.reservationNumber << ".\n";
        cout << "\tROOM NUMBER: " << booking.roomNumber << ".\n";
        cout << "\tROOM TYPE: " << booking.roomType << ".\n";
        cout << "\tDAYS: " << booking.numberOfNights << ".\n";
        cout << "\tNAME: " << booking.fullName;

        if (discount == 1) {
            booking.saving = 0;
            cout << "\nSORRY, YOU HAVE NOT BEEN DRAWN A DISCOUNT\n";
            cout << "\tTOTAL AMOUNT: " << booking.totalAmountOfInvoice << " EUROS\n";
        } else if (discount == 0.9) {
            booking.saving = (booking.totalAmountOfInvoice / 0.9) - booking.totalAmountOfInvoice;
            cout << "\nCONGRATS! YOU HAVE BEEN DRAWN A 10% DISCOUNT WHICH IS HELP YOU SAVE "
                 << booking.saving << " EUROS!!!\n";
            cout << "\tTOTAL AMOUNT AFTER DISCOUNT: " << booking.totalAmountOfInvoice << " EUROS\n";
        } else if (discount == 0.8) {
            booking.saving = (booking.totalAmountOfInvoice / 0.8) - booking.totalAmountOfInvoice;
            cout << "\nCONGRATS! YOU HAVE BEEN DRAWN A 20% DISCOUNT WHICH IS HELP YOU SAVE "
                 << booking.saving << " EUROS!!!\n";
            cout << "\tTOTAL AMOUNT AFTER DISCOUNT: " << booking.totalAmountOfInvoice << " EUROS\n";
        }

        string confirm;
        bool confirmFlag = true;
        while (confirmFlag) { // loop for user input for booking confirmation
            cout << "---------------------------------------------------------\n";
            cout << "PLEASE CONFIRM YOUR BOOKING INFORMATION: \n"
                    "1. CONFIRM                     2.CANCEL\n";

            getline(cin, confirm);

            if (confirm == "1") { // confirm booking

                // update room info
                for (int i = 0; i < 300; i++) {
                    if (rooms[i].roomNumber == booking.roomNumber) {
                        rooms[i].isAvailable = false;
                    }
                }

                confirmFlag = false;
                bookingFinalConfirmationFlag = false;

                // generate order info
                order.orderNumber = rand() % 90000 + 10000;
                order.reservationNumber = booking.reservationNumber;
                order.roomType = booking.roomType;
                order.fullName = booking.fullName;
                order.roomNumber = booking.roomNumber;
                order.numberOfNights = booking.numberOfNights;
                order.totalAmountOfInvoice = booking.totalAmountOfInvoice;
                order.saving = booking.saving;

                // generate invoice info
                int invoiceNumber = rand() % 9000000000 + 1000000000;
                invoice.invoiceNumber = 'T' + to_string(invoiceNumber);
                invoice.totalAmountOfInvoice = booking.totalAmountOfInvoice;
                invoice.taxFee = invoice.totalAmountOfInvoice * 0.17;
                invoice.orderNumber = order.orderNumber;
                invoice.fullName = booking.fullName;

                cout << "---------------------------------------------------------\n";
                cout << "YOU ORDER NUMBER IS : " << order.orderNumber;
                cout << "\nYOU CAN FIND YOUR ORDER INFORMATION IN ORDER MENU LATER.\n";

                bookings.push_back(booking);
                orders.push_back(order);
                invoices.push_back(invoice);
            } else if (confirm == "2") { // cancel booking
                confirmFlag = false;
                cout << "PLEASE FILL YOUR BOOKING INFORMATION AGAIN.\n";
            } else { // invalid input
                cin.clear();
                cout << "INVALID INPUT, PLEASE TRY AGAIN.\n";
            }
        }
    }

    customer_next_step(selectionCheck);
}

// print hotel & room info
void hotel_room_information(bool &selectionCheck) {
    cout << "---------------------------------------------------------\n";
    cout << "WELCOME TO EASY HOTEL! \n"
            "WE OWN 150 SINGLE ROOMS AND 150 DOUBLE ROOMS, IN TOTAL 300 ROOMS\n"
            "BELOW IS OUR ROOM INFORMATION\n"
            "1. SINGLE ROOM : 100 EUROS/NIGHT\n"
            "2. DOUBLE ROOM : 150 EUROS/NIGHT\n"
            "MAY I GET YOUR ATTENTION BY OFFERING A DISCOUNT: \n"
            "EVERYONE WHO BOOK OUR ROOMS WILL BE ENTITLED A CHANCE FOR DRAWING A DISCOUNT BY OUR SYSTEM\n";
    cout << "DO NOT HESITATE TO STAY WITH US, BOOKING NOW!\n";
    customer_next_step(selectionCheck);
}

// search for order info
void customer_order_information(bool &selectionCheck, vector<Order> &orders) {

    cout << "---------------------------------------------------------\n";
    cout << "WELCOME!\n";

    bool orderCheckingMethodFlag = true;

    while (orderCheckingMethodFlag) { // loop for user input for order info search

        cout << "PLEASE SELECT ONE OF BELOW TWO METHODS TO CHECK YOUR ORDER INFORMATION: \n";
        cout << "1. FULLNAME                                  2.RESERVATION NUMBER \n";

        string orderCheckingMethod;
        getline(cin, orderCheckingMethod);

        if (orderCheckingMethod == "1") { // search for order info with full name
            orderCheckingMethodFlag = false;

            bool fullNameFlag = true;

            while (fullNameFlag) { // loop for user input for full name

                cout << "---------------------------------------------------------\n";
                cout << "PLEASE ENTER YOUR FULLNAME:\n";

                string fullName;
                getline(cin, fullName);

                fullName = trim(fullName);

                if (!fullName.empty()) { // process valid input
                    fullNameFlag = false;

                    int count = 0;

                    for (int i = 0; i < orders.size(); i++) { // search for order info
                        if (fullName == orders[i].fullName) {
                            cout << "---------------------------------------------------------\n";
                            cout << "ORDER INFORMATION: \n";
                            cout << "\tORDER NUMBER: " << orders[i].orderNumber << ".\n";
                            cout << "\tRESERVATION NUMBER: " << orders[i].reservationNumber << ".\n";
                            cout << "\tROOM NUMBER: " << orders[i].roomNumber << ".\n";
                            cout << "\tROOM TYPE: " << orders[i].roomType << ".\n";
                            cout << "\tDAYS: " << orders[i].numberOfNights << ".\n";
                            cout << "\tNAME: " << orders[i].fullName << ".\n";
                            cout << "\tDISCOUNT: " << orders[i].saving << ".\n";
                            cout << "\tTOTAL AMOUNT: " << orders[i].totalAmountOfInvoice << ".\n";
                            cout << "---------------------------------------------------------\n\n";
                            count++;
                        }
                    }

                    if (count == 0) {
                        cin.clear();
                        cout << "SORRY, NO ORDER FOUND.\n";
                    }
                } else { // invalid input for full name
                    cin.clear();
                    cout << "INVALID INPUT, PLEASE TRY AGAIN.\n";
                }
            }

            customer_next_step(selectionCheck);

        } else if (orderCheckingMethod == "2") { // search for order info with reservation number
            orderCheckingMethodFlag = false;

            cout << "---------------------------------------------------------\n";
            cout << "PLEASE ENTER YOUR RESERVATION NUMBER:\n";

            string reservationNumber;
            getline(cin, reservationNumber);

            bool reservationNumberFlag = true;

            while (reservationNumberFlag) { // loop for user input for reservation number

                if (isNumber(reservationNumber)) { // process valid input
                    reservationNumberFlag = false;

                    int isReservationNumber = stoi(reservationNumber);

                    int count = 0;

                    for (int i = 0; i < orders.size(); i++) { // search for order info
                        if (isReservationNumber == orders[i].reservationNumber) {
                            cout << "---------------------------------------------------------\n";
                            cout << "ORDER INFORMATION: \n";
                            cout << "\tORDER NUMBER: " << orders[i].orderNumber << ".\n";
                            cout << "\tRESERVATION NUMBER: " << orders[i].reservationNumber << ".\n";
                            cout << "\tROOM NUMBER: " << orders[i].roomNumber << ".\n";
                            cout << "\tROOM TYPE: " << orders[i].roomType << ".\n";
                            cout << "\tDAYS: " << orders[i].numberOfNights << ".\n";
                            cout << "\tNAME: " << orders[i].fullName << ".\n";
                            cout << "\tDISCOUNT: " << orders[i].saving << ".\n";
                            cout << "\tTOTAL AMOUNT: " << orders[i].totalAmountOfInvoice << ".\n";
                            cout << "---------------------------------------------------------\n";
                            count++;
                        }
                    }

                    if (count == 0) {
                        cin.clear();
                        cout << "SORRY, NO ORDER FOUND.\n";
                    }
                } else { // invalid input for reservation number
                    cin.clear();
                    cout << "INVALID INPUT, PLEASE TRY AGAIN.\n";
                }
            }

            customer_next_step(selectionCheck);
        } else { // invalid input
            cin.clear();
            cout << "INVALID INPUT, PLEASE TRY AGAIN.\n";
        }
    }
}

// search for invoice info
void customer_invoice(bool &selectionCheck, vector<Invoice> &invoices) {

    bool fullNameFlag = true;

    while (fullNameFlag) { // loop for user input for invoice search with full name
        cout << "---------------------------------------------------------\n";
        cout << "PLEASE CHECK YOUR INVOICE BY ENTERING FULLNAME:\n";

        string fullName;
        getline(cin, fullName);

        fullName = trim(fullName);

        if (!fullName.empty()) { // process valid input
            fullNameFlag = false;

            int count = 0;

            for (int i = 0; i < invoices.size(); i++) { // search for invoice info
                if (fullName == invoices[i].fullName) {
                    cout << "---------------------------------------------------------\n";
                    cout << "INVOICE NUMBER: " << invoices[i].invoiceNumber << ".\n";
                    cout << "\tORDER NUMBER: " << invoices[i].orderNumber << ".\n";
                    cout << "\tOWNER NAME: " << invoices[i].fullName << ".\n";
                    cout << "\tINVOICE NAME: HOTEL FEE.\n";
                    cout << "\tHOTEL FEE IN TOTAL: " << invoices[i].totalAmountOfInvoice << " EUROS.\n";
                    cout << "\tTAX FEE (17%): " << invoices[i].taxFee << " EUROS.\n";
                    cout << "\tTOTAL AMOUNT IN INVOICE: " << invoices[i].totalAmountOfInvoice + invoices[i].taxFee
                         << " EUROS.\n";
                    count++;
                }
            }

            if (count == 0) {
                cin.clear();
                cout << "SORRY, NO INVOICE INFORMATION FOUND.\n";
            }
        } else { // invalid input for full name
            cin.clear();
            cout << "INVALID INPUT, PLEASE TRY AGAIN.\n";
        }
    }

    customer_next_step(selectionCheck);
}

// execute system functions
void customer_menu_function_select(int &customerSelection, bool &selectionCheck, vector<Booking> &bookings,
                                   vector<Room> &rooms, vector<Order> &orders, vector<Invoice> &invoices) {
    switch (customerSelection) {
        case 1: // room booking
            customer_booking(selectionCheck, bookings, rooms, orders, invoices);
            break;
        case 2: // hotel & room info
            hotel_room_information(selectionCheck);
            break;
        case 3: // order info search
            customer_order_information(selectionCheck, orders);
            break;
        case 4: // invoice info search
            customer_invoice(selectionCheck, invoices);
            break;
        case 5: // system exit
            selectionCheck = false;
            cout << "THANK YOU FOR USING THE RELAX HOTEL BOOKING SYSTEM!\n";
            break;
    }
}

int main() {
    srand(time(0));

    // initialize system variables
    vector<Booking> bookings;
    vector<Invoice> invoices;
    vector<Order> orders;
    vector<Room> rooms;
    for (int i = 0; i < 300; i++) {
        if (i < 150) {
            Room roomObj;
            roomObj.roomNumber = i + 1;
            roomObj.roomType = "SINGLE ROOM";
            rooms.push_back(roomObj);
        } else {
            Room roomObj;
            roomObj.roomNumber = i + 1;
            roomObj.roomType = "DOUBLE ROOM";
            rooms.push_back(roomObj);
        }
    }

    cout << "---------------------------------------------------------\n";
    cout << "WELCOME TO RELAX HOTEL BOOKING SYSTEM!\n";

    string selection;
    bool selectionCheck = true;

    // the main loop for system operations
    while (selectionCheck) {

        show_customer_menu(); // print system menu

        getline(cin, selection);

        if (isNumber(selection)) { // check if user selection is valid. If it is valid, then go into the corresponding function
            int customerSelection = stoi(selection);

            if (customerSelection > 0 && customerSelection < 6) {
                customer_menu_function_select(customerSelection, selectionCheck, bookings, rooms, orders, invoices);
            } else {
                cin.clear();
                cout << "INVALID INPUT, PLEASE TRY AGAIN.\n";
            }
        } else { // error msg for invalid input
            cin.clear();
            cout << "INVALID INPUT, PLEASE TRY AGAIN.\n";
        }
    }

    return 0;
}