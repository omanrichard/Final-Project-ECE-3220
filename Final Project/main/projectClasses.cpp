//
//  projectClasses.cpp
//  Project
//
//  Created by Richard Oman on 11/11/17.
//  Copyright © 2017 Richard Oman. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "projectClasses.h"

//import processing.io.*;

using namespace std;

/* ------------- frame Methods ------------- */
//------- frame constructor -------
frame::frame(){
    for( i=0 ; i<8 ; i++ ){
        for( j=0 ; j<8 ;  j++){
            this->sensor_values[i][j] = -10;
        }
    }
    return;
}

frame::frame(I2C i2c){
    int count = 0x80;
    for( i=0 ; i < 64 ; i++ ){
        for( j=0 ; j<8 ;  j++){
            i2c.beginTransmission(0x68);
            // Thermistor Register
            i2c.write( count );        // Command
            this->sensor_values[i][j] = i2c.read(0x68);
            count += 2;
        }
    }
    return;
}

void frame::display_frame(){
    
}

short frame::access( short row , short col ){
    short temp = this->sensor_values[row][col];    //Accesses data point in data array
    return temp;
}

//------- frame destructor --------
frame::~frame(){
}
/* ----------- signal Methods -------------*/
signal::signal(){
    I2C i2c;
    
    for( i=0 ; i<frameCount ; i++){
        frame newFrame( I2C );
        data.push_back( newFrame );
    }
}

void signal::saveFile( string filename ){
    fstream newOutput;  // Creates/Opens new output file
    newOutput.open( filename, ios::out );
    
    newOutput << "Number of frames: " << frameCount << " " << endl;    // Copies data from memory to file
    for( i = 0; i < frameCount; i++ ){
        for( j=0 ; j < 64 ; )
        newOutput << this->data[i][j] << endl;
    }
    newOutput.close( ); // Close file
    return;
}

