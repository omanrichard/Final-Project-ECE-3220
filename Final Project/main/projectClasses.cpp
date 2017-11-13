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

#define gridEyeAddr 0x68 // or 0x69 Address

//import processing.io.*;

using namespace std;
int i,j,k;
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
    int count = 0x80;   // First Pixel
    for( i=0 ; i < 64 ; i++ ){
        for( j=0 ; j<8 ;  j++){
            i2c.beginTransmission(gridEyeAddr);                 // Start transmission
            i2c.write( count );                                 // Command
            this->sensor_values[i][j] = i2c.read(gridEyeAddr);  // Receive value from device, end transmission
            count += 2;                                         // Increments to next pixel
        }
    }
    return;
}

void frame::display_frame(){
    
}

short frame::access( short row , short col ){
    return this->sensor_values[row][col];    //Accesses data point in data array
}

//------- frame destructor --------
frame::~frame(){
}
/* ----------- signal Methods -------------*/
signal::signal(){
    I2C i2c;
    frame* temp;
    
    for( i=0 ; i<frameCount ; i++){
        temp = new frame( i2c );
        this->data.push_back( temp );
    }
    return;
}

void signal::saveSignal( string filename ){
    fstream newOutput;  // Creates/Opens new output file
    newOutput.open( filename, ios::out );
    
    frame* temp;

    newOutput << "Number of frames: " << frameCount << " " << endl;    // Copies data from memory to file
    for( i = 0; i < frameCount; i++ ){
        newOutput << "Frame No. : " << i << endl;
        temp = this->data[i];
                                                                        // Example Output
        for( j=0 ; j < 8 ; j++){                                        // Frame No. : 1
                newOutput << "\t ["                                     // TAB [ 1] [ 2] [ 3] [ 4] [ 5] [ 6] [ 7] [ 8]
                          << temp->sensor_values[j][0] << "] "          // TAB [ 9] [10] [11] [12] [13] [14] [15] [16]
                          << "[" << temp->sensor_values[j][1] << "] "   // TAB [17] [18] [19] [20] [21] [22] [23] [24]
                          << "[" << temp->sensor_values[j][2] << "] "   // TAB [25] [26] [27] [28] [29] [30] [31] [32]
                          << "[" << temp->sensor_values[j][3] << "] "   // TAB [33] [34] [35] [36] [37] [38] [39] [40]
                          << "[" << temp->sensor_values[j][4] << "] "   // TAB [41] [42] [43] [44] [45] [46] [47] [48]
                          << "[" << temp->sensor_values[j][5] << "] "   // TAB [49] [50] [51] [52] [53] [54] [55] [56]
                          << "[" << temp->sensor_values[j][6] << "] "   // TAB [57] [58] [59] [60] [61] [62] [63] [64]
                          << "[" << temp->sensor_values[j][7] << "] " <<endl;
        }
    }
    newOutput.close( ); // Close file
    return;
}

void appendSig( string filename ){
    
}

