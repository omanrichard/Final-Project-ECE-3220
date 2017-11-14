import processing.io.*;
I2C i2c;



/*
1 = SplashScreen
2 = live data
3 = Settings
*/

int currentWindow;         //Top left corner of data Array window
                           //Window is 326x326 pixels
int displayX = 40;         //Left most cordniate grid
int displayY = 100;        //Right most coordniate grid
int displayScale = 50;     //display pixels to be used per physical infrared pixel
int displayFrameX = displayX;
int displayFrameY = displayY - displayScale/2;


int count = 0;
int j = 0;
int i = 0;

// ----------- Start Setup ---------------
void setup() {
  size(700, 700);

  
  i2c = new I2C(I2C.list()[0]);//Setup device on I2C-1
  println("Atempting Transmission");
  i2c.beginTransmission(0x68); //GridEye i2c Address 
  println("Transmission Begun");

  
  //i2c.beginTransmission(0x68);
  i2c.write(0x04); //Command
  byte[] PixelL = i2c.read(1);
  
  i2c.beginTransmission(0x68);
  i2c.write(0x80);
  byte[] PixelH = i2c.read(1);
  
  printArray(PixelL);
  printArray(PixelH);
  
  //i2c.beginTransmission(0x69);
  println("Reading Pixel");

  i2c.endTransmission();
   println("Transmission Over");
   
    
}
// ----------- End Setup ---------------

// ----------- Start Draw --------------
void draw() {

  count = 0x80;
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      //println("Reading Register:",count);
   
      i2c.beginTransmission(0x68);
      i2c.write(count);
      byte[] lowData = i2c.read(1);
    
      i2c.beginTransmission(0x68);
      i2c.write(count+1);
      byte[] highData = i2c.read(1);
 
      updateBlock(i,j,lowData[0],highData[0]);
      count += 2;
    
      if (count > 0xFD) count = 0x80;
    }
  }
}
// ----------- End Draw -----------------

void updateDisplay(){
   for(int i = 0; i < 8; i++){
      for(int j = 0; j < 8; j++){
        //updateBlock(i,j,frame.access(i,j));
      }
   }
}

void updateBlock(int row, int col, byte tempValueL, byte tempValueH){
  //only draw within 8x8 grid  
  if(row < 8 && col < 8){
    
    int signHold = tempValueL & 128;
    int colorMask = tempValueL & 127;
    colorMask += signHold;
  
    println(colorMask);
    
//------------- 24-bit color ----------------
    int R1 = 0;
    int G1 = 0;
    int B1 = 0;
    int phase = 1;
  
    for(int i = 0; i < 255; i++){
      if(colorMask >= i && colorMask < i+1){
          fill(R1,G1,B1);
      }
    
      if(phase == 7){
          G1 += 7;
          B1 += 7;
      }
    
      if(phase == 6){
          G1 -= 7;
          if(G1 <= 0) phase = 7;
      }
    
      if(phase == 5){
          R1 += 7;
          if(R1 >= 252) phase = 6;
      }
     
      if(phase == 4){
          B1 -= 7;
          if(B1 <= 0) phase = 5;
      }
    
      if(phase == 3){
          G1 += 7;
          if( G1 >= 252) phase = 4;
      }
    
      if(phase == 2){
          R1 -= 7;
          if( R1 <= 0) phase = 3;
      }
     
      if(phase == 1){
           R1 += 7;
           B1 += 7;
           if( R1 >= 252) phase = 2;
      }
    } // end for
        
/* OLD Color Mask
    
   //println(colorMask);
   // int colorMaskH = 
   //set fill color based on mask
   //0 cold, 15 hot
   if(colorMask >= 0 && colorMask < 21) fill(255,153,153);
   if(colorMask > 21 && colorMask < 42) fill(255,0,0);
   if(colorMask > 42 && colorMask < 63) fill(255,153,51);
   if(colorMask > 63 && colorMask < 84) fill(255,255,0);
   if(colorMask > 84 && colorMask < 105) fill(0,153,51);
   if(colorMask > 105 && colorMask < 126) fill(102,255,204);
   if(colorMask > 126 && colorMask < 147) fill(0,0,255);
   if(colorMask > 168 && colorMask < 189) fill(0,0,153);
   if(colorMask > 189 && colorMask < 210) fill(255,0,255);
   if(colorMask > 210 && colorMask < 231) fill(102,0,102);
   if(colorMask > 231 && colorMask < 255) fill(0,0,0);
*/
  //draw block
    noStroke(); //No outline
    rect(displayX+displayScale*row+row+1, displayY+displayScale*col+col+1,displayScale,displayScale);
  }
}

void splashScreen(){
  textSize(32);
  fill(0, 102, 153);
  text("ECE 3220: Thermal Camera", 10, 30);
  text("Welcome", 10,50);
  
}

int liveStream(){ //Each square displayScalexdisplayScale pixels, line width 1 pixel.
  //Draw Header
  textSize(32);//Text Size
  fill(0,0,0);//Text Color
  text("Live View", 10, 30);
  textSize(16);
  text("Sensor Status:", 10,70);
  fill(255,0,0);
  text("Disconnected",110,70);
  stroke(204, 102, 0);
  line(0,90,700,90);
  
  //Draw Border
  fill(255,255,255);
  strokeWeight(1);//Line width 1 Pixel
  line(displayX,displayY,displayX+displayScale*8+8,displayY);//Top
  line(displayX,displayY,displayX,displayY+displayScale*8+8);//left Side
  line(displayX,displayY+displayScale*8+8,displayX+displayScale*8+8,displayY+displayScale*8+8);//Bottom
  line(displayX+displayScale*8+8,displayY+displayScale*8+8,displayX+displayScale*8+8,displayY);//Right side
  //Draw grid Lines
  for(int i = 1; i < 8; i++){
  line(displayX,displayY+(i*displayScale)+i,displayX+displayScale*8+8,displayY+(i*displayScale)+i);//row
  line(displayX+(i*displayScale)+i,displayY, displayX+(i*displayScale)+i, displayY+displayScale*8+8);//Column
  }

 return 1;
}
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  

      
  
  
  
  

  
  
 