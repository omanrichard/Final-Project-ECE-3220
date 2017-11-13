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

//------------------------ Frame Class -------------------------
class frame{                        //      Stores sensor data
friend class session;               //     0  1  2  3  4  5  6  7
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
    short get_max();
    float get_mean();
    
    virtual void print();                  
    void get_data( I2C i2c );

};

class frame_mask : public frame {
private:
    vector< string > scale;
    string mask[8][8];
    
public:
    frame_mask();
    ~frame_mask();
    
    void print();
    void set_mask();
    
};
//------------------------ End Frame Class -------------------------

//------------------------ Signal Class -------------------------
class signal : public frame{
private:
    short frameCount;
    vector< frame* > data;
    
public:
    signal();
    ~signal();
    
    void saveSignal( string filename );
    void print();
};
//------------------------ End Signal Class -------------------------

//------------------------ Session Class -------------------------
class session{
private:
    vector< class signal* > currentSession;
    
public:
    session();
    ~session();
    
    void print();
};

#endif /* projectClasses_h */

