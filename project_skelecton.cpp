#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

// --- 1. SEAT STRUCTURE ---
struct Seat {
    int row;
    int col;
    bool isBooked = false;
    string customerName = "";
};

// --- 2. TICKET DATA FOR HASH TABLE ---
struct Ticket {
    string ticketID;
    string customerName;
    int row;
    int col;
};

// --- 3. CINEMA SYSTEM CLASS ---
class CinemaBookingSystem {
private:
    static const int ROWS = 5;
    static const int COLS = 5;
    Seat hall[ROWS][COLS];
    
    // Data Structures
    unordered_map<string, Ticket> ticketTable; // Hash Table for O(1) Lookup & Cancellation
    queue<string> waitingList;                 // Queue for Waiting List
    
    int ticketCounter = 1000;

public:
    CinemaBookingSystem() {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                hall[i][j].row = i;
                hall[i][j].col = j;
            }
        }
    }

    // Display the Seating Chart
    void displaySeatingChart() {
        cout << "\n   --- SCREEN THIS WAY --- \n\n    ";
        for (int j = 0; j < COLS; ++j) cout << j + 1 << " ";
        cout << "\n";

        for (int i = 0; i < ROWS; ++i) {
            char rowLabel = 'A' + i;
            cout << rowLabel << " | ";
            for (int j = 0; j < COLS; ++j) {
                if (hall[i][j].isBooked) {
                    cout << "[X]"; // Booked
                } else {
                    cout << "[O]"; // Available
                }
            }
            cout << "\n";
        }
        cout << "\n[O] Available   [X] Booked\n";
    }

    // Book a Seat
    void bookSeat(char rowChar, int colNum, const string& name) {
        int r = rowChar - 'A';
        int c = colNum - 1;

        if (r < 0 || r >= ROWS || c < 0 || c >= COLS) {
            cout << "Invalid seat position!\n";
            return;
        }

        if (hall[r][c].isBooked) {
            cout << "Seat " << rowChar << colNum << " is already booked!\n";
            cout << "Adding " << name << " to the waiting list...\n";
            waitingList.push(name); // Queue enqueue
            return;
        }

        // Mark seat booked
        hall[r][c].isBooked = true;
        hall[r][c].customerName = name;

        // Generate Ticket ID & Store in Hash Table
        string tID = "TKT-" + to_string(ticketCounter++);
        Ticket newTicket = {tID, name, r, c};
        ticketTable[tID] = newTicket; // Hash Table Insert

        cout << "\nSuccess! Ticket ID: " << tID << " reserved for " << name << " at Seat " << rowChar << colNum << ".\n";
    }

    // Cancel Any Ticket by ID (Using Hash Table)
    void cancelTicket(const string& tID) {
        // Check if ticket exists in Hash Table
        if (ticketTable.find(tID) == ticketTable.end()) {
            cout << "\nTicket ID " << tID << " not found!\n";
            return;
        }

        // Retrieve ticket details to know which seat to free up
        Ticket t = ticketTable[tID];
        int r = t.row;
        int c = t.col;

        // Free up the seat on the 2D grid
        hall[r][c].isBooked = false;
        hall[r][c].customerName = "";

        // Remove from Hash Table
        ticketTable.erase(tID);

        cout << "\nSuccess! Ticket " << tID << " for " << t.customerName 
             << " (Seat " << (char)('A' + r) << (c + 1) << ") has been cancelled.\n";

        // If someone is waiting in the queue, notify them
        if (!waitingList.empty()) {
            string nextCustomer = waitingList.front();
            waitingList.pop(); // Queue Dequeue
            cout << "-> Notification: Customer '" << nextCustomer << "' from the waiting list can now book a seat!\n";
        }
    }

    // Search Ticket using Hash Table
    void searchTicket(const string& tID) {
        if (ticketTable.find(tID) != ticketTable.end()) {
            Ticket t = ticketTable[tID];
            cout << "\n--- Ticket Details ---\n";
            cout << "Ticket ID : " << t.ticketID << "\n";
            cout << "Customer  : " << t.customerName << "\n";
            cout << "Seat      : " << (char)('A' + t.row) << (t.col + 1) << "\n";
        } else {
            cout << "\nTicket ID " << tID << " not found!\n";
        }
    }

    // View Waiting List Queue
    void displayWaitingList() {
        if (waitingList.empty()) {
            cout << "\nWaiting List is currently empty.\n";
            return;
        }

        cout << "\n--- Current Waiting List (Queue) ---\n";
        queue<string> tempQueue = waitingList;
        int pos = 1;
        while (!tempQueue.empty()) {
            cout << pos++ << ". " << tempQueue.front() << "\n";
            tempQueue.pop();
        }
    }
};

// --- MAIN FUNCTION (Interactive Menu) ---
int main() {
    CinemaBookingSystem system;
    int choice;

    do {
        cout << "\n========== CINEMA BOOKING SYSTEM ==========\n";
        cout << "1. Display Seating Chart\n";
        cout << "2. Book a Seat\n";
        cout << "3. Cancel Ticket by ID (Hash Table)\n";
        cout << "4. Search Ticket by ID (Hash Table)\n";
        cout << "5. View Waiting List (Queue)\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            system.displaySeatingChart();
        } else if (choice == 2) {
            char row;
            int col;
            string name;
            cout << "Enter Row (A-E): ";
            cin >> row;
            cout << "Enter Seat Number (1-5): ";
            cin >> col;
            cout << "Enter Customer Name: ";
            cin >> name;
            system.bookSeat(toupper(row), col, name);
        } else if (choice == 3) {
            string tID;
            cout << "Enter Ticket ID to Cancel (e.g., TKT-1000): ";
            cin >> tID;
            system.cancelTicket(tID);
        } else if (choice == 4) {
            string tID;
            cout << "Enter Ticket ID to Search (e.g., TKT-1000): ";
            cin >> tID;
            system.searchTicket(tID);
        } else if (choice == 5) {
            system.displayWaitingList();
        }
    } while (choice != 6);

    cout << "Exiting system. Goodbye!\n";
    return 0;
}