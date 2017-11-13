//
//  projectClasses.cpp
//  Project
//
//  Created by Grant Hilgert and Richard Oman on 11/11/17.
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

//------------------------ Frame Constructor ------------------------

frame::frame(){
    for( i=0 ; i<8 ; i++ ){
        for( j=0 ; j<8 ;  j++){
            this->sensor_values[i][j] = -10;
        }
    }
    this->mean = 0;
    this->max = 0;
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
    this->set_max();
    this->set_mean();
    return;
}

//------------------------ Frame Methods ------------------------

void frame::set_max(){
    short temp = 0;
    
    for( i=0 ; i < 8 ; i++ ){
        for( j=0 ; j < 8 ; j++ ){
            if( this->sensor_values[i][k] > temp )
                temp = this->sensor_values[i][j];
        }
    }
    return;
}

void frame::set_mean(){
    float sum = 0;
    
    for( i=0 ; i < 8 ; i++ ){
        for( j=0 ; j < 8 ; j++ ){
            sum += this->sensor_values[i][j];
        }
    }
    this->mean = sum/64;
}

void frame::get_data( I2C i2c ){
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

void frame::print(){
    
    for( j=0 ; j < 8 ; j++){                                        // Frame No. : 1
        cout << "\t"                                    // TAB [ 1] [ 2] [ 3] [ 4] [ 5] [ 6] [ 7] [ 8
        << "[ " << this->sensor_values[j][0] << " ] "   // TAB [ 9] [10] [11] [12] [13] [14] [15] [16]
        << "[ " << this->sensor_values[j][1] << " ] "   // TAB [17] [18] [19] [20] [21] [22] [23] [24]
        << "[ " << this->sensor_values[j][2] << " ] "   // TAB [25] [26] [27] [28] [29] [30] [31] [32]
        << "[ " << this->sensor_values[j][3] << " ] "   // TAB [33] [34] [35] [36] [37] [38] [39] [40]
        << "[ " << this->sensor_values[j][4] << " ] "   // TAB [41] [42] [43] [44] [45] [46] [47] [48]
        << "[ " << this->sensor_values[j][5] << " ] "   // TAB [49] [50] [51] [52] [53] [54] [55] [56]
        << "[ " << this->sensor_values[j][6] << " ] "   // TAB [57] [58] [59] [60] [61] [62] [63] [64]
        << "[ " << this->sensor_values[j][7] << " ] " << endl;
    }
    return;
}

short frame::access( short row , short col ){
        return this->sensor_values[row][col];    //Accesses data point in data array
}
//------- frame destructor --------
frame::~frame(){
}
//------------------------- End Frame ------------------------

//------------------------ maskFrame Methods ------------------------


//------------------------ signal Methods ------------------------
signal::signal(){
    I2C i2c;
    frame* temp;
    
    for( i=0 ; i<frameCount ; i++){
        temp = new frame( i2c );
        this->data.push_back( temp );
        this->frameCount++;
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
        for( j=0 ; j < 8 ; j++){                                    // Frame No. : 1
                newOutput << "\t[" << this->access( j, 0 ) << "] " // TAB [ 1] [ 2] [ 3] [ 4] [ 5] [ 6] [ 7] [ 8]
                          <<   "[" << this->access( j, 1 ) << "] " // TAB [ 9] [10] [11] [12] [13] [14] [15] [16]
                          <<   "[" << this->access( j, 2 ) << "] " // TAB [17] [18] [19] [20] [21] [22] [23] [24]
                          <<   "[" << this->access( j, 3 ) << "] " // TAB [25] [26] [27] [28] [29] [30] [31] [32]
                          <<   "[" << this->access( j, 4 ) << "] " // TAB [33] [34] [35] [36] [37] [38] [39] [40]
                          <<   "[" << this->access( j, 5 ) << "] " // TAB [41] [42] [43] [44] [45] [46] [47] [48]
                          <<   "[" << this->access( j, 6 ) << "] " // TAB [49] [50] [51] [52] [53] [54] [55] [56]
                          <<   "[" << this->access( j, 7 ) << "] " // TAB [57] [58] [59] [60] [61] [62] [63] [64]
                          << endl;
        }
        newOutput << "\tMax value: " << this->get_max() << endl
        << "\tAverage: " << this->get_mean() << endl << endl;
    }
    newOutput.close( ); // Close file
    return;
}
//------------------------ End Signal ------------------------

