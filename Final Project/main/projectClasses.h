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

#ifndef projectClasses_h
#define projectClasses_h

using namespace std;

class I2C{
private:
    
public:
    short read( int temp);
    void write( int temp);
    void endTransmission();
    void beginTransmission( int temp );
    void close();
};

//--------------------- Frame Class -------------------------
class frame{                        //      Stores sensor data
friend class signal;                //     0  1  2  3  4  5  6  7
private:                            // 0  [] [] [] [] [] [] [] []
    float mean;                     // 1  [] [] [] [] [] [] [] []
    short max;                      // 3  [] [] [] [] [] [] [] []
    short sensor_values[8][8];      // 4  [] [] [] [] [] [] [] []
                                    // 4  [] [] [] [] [] [] [] []
    void set_max();                 // 5  [] [] [] [] [] [] [] []
    void set_mean();                // 6  [] [] [] [] [] [] [] []
                                    // 7  [] [] [] [] [] [] [] []
public:
    frame();
    frame(I2C i2c);
    ~frame();
    
    short access( short row , short col );         
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
// -------------------- End Frame Class -------------------------

// -------------------- Signal Class ----------------
class signal{
private:
    short frameCount;
    vector< frame* > data;
    
public:
    signal();
    ~signal();
    
    void saveSignal( string filename );
    
    virtual void print();
};


// -------- Session Class ----------
class session : public signal{
private:
    vector< signal* > currentSession;
    
public:
    session();
    ~session();
    
    void print();
};

#endif /* projectClasses_h */

