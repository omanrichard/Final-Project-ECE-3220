//
//  projectClasses.h
//  Final Project
//  Created by Richard Oman on 11/11/17.
//  Copyright © 2017 Richard Oman. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#ifndef projectClasses_h
#define projectClasses_h

using namespace std;
int i;
//----------- Frame Class ----------------

class frame{
    friend class signal;
    
private:
    short sensor_table[8][8];       // Stores row of sensor data
    /*
     0  1  2  3  4  5  6  7
     0  [] [] [] [] [] [] [] []
     1  [] [] [] [] [] [] [] []
     3  [] [] [] [] [] [] [] []
     3  [] [] [] [] [] [] [] []
     4  [] [] [] [] [] [] [] []
     5  [] [] [] [] [] [] [] []
     6  [] [] [] [] [] [] [] []
     7  [] [] [] [] [] [] [] []
     */
    void collect_data();
    
public:
    frame();
    ~frame();
    
    short access( short row, short col );
    virtual void display_frame();                  // Transmitting current values frame
    
};

class frame_mask : public frame {
private:
    vector< string > scale;
    
    string mask[8][8];
    
public:
    frame_mask();
    ~frame_mask();
    
    void display_frame();
    void set_mask();
};
// ---------- Signal Class ----------------
class signal{
private:
    vector< frame > data;
    short frameCount;
    
    /*------- Time Variable ---------*/
    
    
public:
    signal();
    ~signal();
    
    void transform( char opCode );
    void saveFile( string filename );
    void appendSig( string filename );
};

/* ------------- frame Methods ------------- */
//------- frame constructor -------
frame::frame(){
    this->collect_data(/* Data stuff */  );
    return;
}

void frame::collect_data(){
    
    
}

void frame::display_frame(){
    
}

short frame::access( short row, short col ){
    short temp = this->sensor_table[row][col];    //Accesses data point in data array
    return temp;
}

//------- frame destructor --------
frame::~frame(){
}
/* ----------- signal Methods -------------*/
signal::signal(){
    
}

void signal::saveFile( string filename ){
    fstream newOutput;  // Creates/Opens new output file
    newOutput.open( filename, ios::out );
    
    newOutput << "Number of frames: " << frameCount << " " << endl;    // Copies data from memory to file
    for( i = 0; i < frameCount; i++ )
        newOutput << this->data[i] << endl;
    
    newOutput.close( ); // Close file
    return;
}

#endif /* projectClasses.h */
