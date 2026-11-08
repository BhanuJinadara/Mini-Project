#include <iostream>
#include <string>
#include "hashtable.h"

using namespace std;

struct seat{
    int row;
    int col;
    bool isBooked;
    string customerName = "";

};

struct ticket{

    string ticketID;
    string customerName;
    int row;
    int col;

};

class seatBookingSystem {
    private:
        static const int ROWS = 5;
        static const int COLS = 5;
        seat hall[ROWS][COLS];
        HashTable ticketTable; // Hash Table for O(1) Lookup & Cancellation
        int tickercounter = 1000;

    public:
        seatBookingSystem(){
            for(int i = 0; i<ROWS; i++){
                for (int j = 0; j<COLS; j++){
                    hall[i][j].row = i;
                    hall[i][j].col = j;
                }
            }
        }
        void displaySeatingChart(){
            cout<<"\n   --- SCREEN THIS WAY ---\n\n      ";
            for (int i = 0; i<COLS; i++){
                
            }
        }

};

int main(){

    return 0;
}