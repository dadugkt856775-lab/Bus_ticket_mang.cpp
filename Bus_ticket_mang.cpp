
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Bus {
public:
    int busNumber;
    string source;
    string destination;
    int totalSeats;
    int availableSeats;
    double fare;

    Bus(int number, string from, string to, int seats, double price) {
        busNumber = number;
        source = from;
        destination = to;
        totalSeats = seats;
        availableSeats = seats;
        fare = price;
    }

    void displayBus() const {
        cout << left << setw(12) << busNumber
             << setw(18) << source
             << setw(18) << destination
             << setw(12) << availableSeats
             << fixed << setprecision(2) << fare << endl;
    }
};

class Passenger {
public:
    int ticketId;
    string name;
    int age;
    int busNumber;
    int seatsBooked;
    double totalFare;

    Passenger(int id, string passengerName, int passengerAge,
              int busNo, int seats, double fare) {
        ticketId = id;
        name = passengerName;
        age = passengerAge;
        busNumber = busNo;
        seatsBooked = seats;
        totalFare = fare;
    }

    void displayTicket() const {
        cout << "\n========== BUS TICKET ==========\n";
        cout << "Ticket ID       : " << ticketId << endl;
        cout << "Passenger Name  : " << name << endl;
        cout << "Passenger Age   : " << age << endl;
        cout << "Bus Number      : " << busNumber << endl;
        cout << "Seats Booked    : " << seatsBooked << endl;
        cout << fixed << setprecision(2);
        cout << "Total Fare      : Rs. " << totalFare << endl;
        cout << "================================\n";
    }
};

class BusBookingSystem {
private:
    vector<Bus> buses;
    vector<Passenger> passengers;
    int nextTicketId;

    Bus* findBus(int number) {
        for (auto& bus : buses) {
            if (bus.busNumber == number)
                return &bus;
        }
        return nullptr;
    }

public:
    BusBookingSystem() {
        nextTicketId = 1001;

        buses.emplace_back(101, "Davanagere", "Bengaluru", 40, 350);
        buses.emplace_back(102, "Davanagere", "Mysuru", 35, 450);
        buses.emplace_back(103, "Ballari", "Bengaluru", 40, 400);
        buses.emplace_back(104, "Kudligi", "Davanagere", 30, 120);
    }

    void displayBuses() const {
        cout << "\n========== AVAILABLE BUSES ==========\n";
        cout << left << setw(12) << "Bus Number"
             << setw(18) << "Source"
             << setw(18) << "Destination"
             << setw(12) << "Seats"
             << "Fare (Rs.)\n";

        for (const auto& bus : buses)
            bus.displayBus();
    }

    void bookTicket() {
        int busNo, age, seats;
        string name;

        displayBuses();

        cout << "\nEnter bus number: ";
        cin >> busNo;

        Bus* bus = findBus(busNo);

        if (bus == nullptr) {
            cout << "Invalid bus number!\n";
            return;
        }

        cout << "Enter passenger name: ";
        getline(cin >> ws, name);

        cout << "Enter passenger age: ";
        cin >> age;

        cout << "Enter number of seats: ";
        cin >> seats;

        if (age <= 0 || age > 120 || seats <= 0) {
            cout << "Invalid passenger details or seat count!\n";
            return;
        }

        if (seats > bus->availableSeats) {
            cout << "Sorry! Not enough seats available.\n";
            return;
        }

        double total = seats * bus->fare;

        Passenger passenger(nextTicketId++, name, age,
                            busNo, seats, total);

        passengers.push_back(passenger);
        bus->availableSeats -= seats;

        cout << "\nTicket booked successfully!\n";
        passenger.displayTicket();
    }

    void cancelTicket() {
        int id;
        cout << "\nEnter ticket ID to cancel: ";
        cin >> id;

        for (auto it = passengers.begin();
             it != passengers.end(); ++it) {

            if (it->ticketId == id) {
                Bus* bus = findBus(it->busNumber);

                if (bus != nullptr)
                    bus->availableSeats += it->seatsBooked;

                cout << "Ticket cancelled successfully for "
                     << it->name << ".\n";

                passengers.erase(it);
                return;
            }
        }

        cout << "Ticket ID not found!\n";
    }

    void searchTicket() const {
        int id;
        cout << "\nEnter ticket ID: ";
        cin >> id;

        for (const auto& passenger : passengers) {
            if (passenger.ticketId == id) {
                passenger.displayTicket();
                return;
            }
        }

        cout << "No ticket found with that ID.\n";
    }

    void displayAllTickets() const {
        if (passengers.empty()) {
            cout << "\nNo tickets have been booked yet.\n";
            return;
        }

        cout << "\n========== ALL BOOKINGS ==========\n";

        for (const auto& passenger : passengers)
            passenger.displayTicket();
    }

    void displaySummary() const {
        int totalBookedSeats = 0;
        double totalRevenue = 0;

        for (const auto& passenger : passengers) {
            totalBookedSeats += passenger.seatsBooked;
            totalRevenue += passenger.totalFare;
        }

        cout << "\n========== BOOKING SUMMARY ==========\n";
        cout << "Total buses              : " << buses.size() << endl;
        cout << "Active tickets           : " << passengers.size() << endl;
        cout << "Total seats booked       : " << totalBookedSeats << endl;
        cout << fixed << setprecision(2);
        cout << "Total booking revenue    : Rs. "
             << totalRevenue << endl;
    }

    void run() {
        int choice;

        do {
            cout << "\n\n===== BUS TICKET MANAGEMENT =====\n";
            cout << "1. Display Available Buses\n";
            cout << "2. Book Ticket\n";
            cout << "3. Cancel Ticket\n";
            cout << "4. Search Ticket\n";
            cout << "5. Display All Tickets\n";
            cout << "6. Booking Summary\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";

            if (!(cin >> choice)) {
                cout << "Invalid input. Please enter a number.\n";
                break;
            }

            switch (choice) {
                case 1:
                    displayBuses();
                    break;
                case 2:
                    bookTicket();
                    break;
                case 3:
                    cancelTicket();
                    break;
                case 4:
                    searchTicket();
                    break;
                case 5:
                    displayAllTickets();
                    break;
                case 6:
                    displaySummary();
                    break;
                case 0:
                    cout << "Thank you for using the system!\n";
                    break;
                default:
                    cout << "Invalid choice! Try again.\n";
            }

        } while (choice != 0);
    }
};

int main() {
    BusBookingSystem system;
    system.run();
    return 0;
}
