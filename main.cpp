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
        int ticketCounter = 1000;

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
                cout<<i+1<<" "<<"\n";
            }
            for (int j =0; j<COLS; j++){
                char rowLabel = 'A' + j;
                cout<<rowLabel<<" | ";
                for (int k = 0;k<COLS;k++){
                    if (hall[j][k].isBooked){
                        cout<<"[X]"<<endl;

                    }
                    else{
                        cout<<"[O]"<<endl;
                    }

                }
                cout<<"\n[o] Avaliable   [X] Booked\n";
            }

        }

        void bookSeat(char row, int col, const string& name){

                int r = row - 'A';
                int c = col - 1;

                if(r < 0 || r>= ROWS || c<0 || c>=COLS){
                    cout<<"Invalid seat position!"<<endl;
                    // return;
                }


                if (hall[r][c].isBooked){
                    cout<<"Seat"<<row<<col<<"is already booked!"<<endl; 
                    //return;           
                }

                //
                hall[r][c].isBooked = true;
                hall[r][c].customerName = name;

                //Generating the ticket ID to store in the hash table
                string tID = "TKT"+ to_string(ticketCounter++);
                ticket newTicket = {tID,name,r,c};
                //the ticket info need to store in the hash table

                cout<<"\nSuccess! Ticket ID: "<<tID<<" reseved for "<<name<<" at seat"<<r<<c<<".\n";
                



        }


        

};

int main(){

    return 0;
}
