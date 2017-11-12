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

#define gridEyeAddr 0x68 // or 0x69 Address

#ifndef projectClasses_h
#define projectClasses_h

using namespace std;
int i,j;

class I2C{
private:
    
public:
    short read( int temp);
    void write( int temp);
    void endTransmission();
    void beginTransmission( int temp );
    void close();
};

//----------- Frame Class ----------------
class frame{
    friend class signal;
    
private:
    short sensor_values[64];       // Stores sensor data
    
public:
    frame();
    frame(I2C i2c);
    ~frame();
    
    short access( short row );
    virtual void display_frame();                  // Transmitting current values frame
    
};

class frame_mask : public frame {
private:
    vector< string > scale;
    string mask[64];
    
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
    
    
    
public:
    signal();
    ~signal();
    
    void transform( char opCode );
    void saveFile( string filename );
    void appendSig( string filename );
};


#endif /* projectClasses_h */

