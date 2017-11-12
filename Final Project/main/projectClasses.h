//
//  projectClasses.h
//  Project
//
//  Created by Richard Oman on 11/11/17.
//  Copyright © 2017 Richard Oman. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define gridEyeAddr 0x68 // or 0x669 Address

#ifndef projectClasses_h
#define projectClasses_h

using namespace std;
int i,j;

//----------- Frame Class ----------------

class frame{
    friend class signal;
    
private:
    short sensor_table[8][8];       // Stores row of sensor data
    
    /*    0  1  2  3  4  5  6  7
     0  [] [] [] [] [] [] [] []
     1  [] [] [] [] [] [] [] []
     3  [] [] [] [] [] [] [] []
     3  [] [] [] [] [] [] [] []
     4  [] [] [] [] [] [] [] []
     5  [] [] [] [] [] [] [] []
     6  [] [] [] [] [] [] [] []
     7  [] [] [] [] [] [] [] [] */
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
    byte f_r;
    
    
public:
    signal();
    ~signal();
    
    void transform( char opCode );
    void saveFile( string filename );
    void appendSig( string filename );
};


#endif /* projectClasses_h */

