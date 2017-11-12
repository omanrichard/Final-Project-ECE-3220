import processing.io.*;
I2C i2c;

int rectX, rectY;      // Position of square button
int circleX, circleY;  // Position of circle button
int rectSize = 90;     // Diameter of rect
int circleSize = 93;   // Diameter of circle
color rectColor, circleColor, baseColor;
color rectHighlight, circleHighlight;
color currentColor;

/*
1 = SplashScreen
2 = live data
3 = Settings
*/
int currentWindow; 

//Top left corner of data Array window
//Window is 326x326 pixels
int displayX = 40;
int displayY = 100;
int displayScale = 50;
int count = 0;
int j = 0;
int i = 0;

void setup() {
  size(700, 700);
  rectColor = color(0);
  rectHighlight = color(51);
  circleColor = color(255);
  circleHighlight = color(204);
  baseColor = color(102);
  currentColor = baseColor;
  
  
  i2c = new I2C(I2C.list()[0]);//Setup device on I2C-1
  println("Atempting Transmission");
  i2c.beginTransmission(0x68); //GridEye i2c Address 
  println("Transmission Begun");
  /*
  //Power Control Register
  i2c.write(0x00); //Command
  
  i2c.write(0x00); //Normal Mode
    println("Power Control Mode: Normal Mode");
   
  //Reset Register
  i2c.write(0x01); //Command
  i2c.write(0x3F); //Software Reset
  println("Reset Device");
  
  //Frame Rate Register
  i2c.write(0x02); //Command
  i2c.write(0x00); //10 frames per second
  println("Set Frame Rate");
  
  //interupt Register
  i2c.write(0x03); //Command
  i2c.write(0x00); //Disabled
  println("Disabled Interupt");
  
  //Status Register
  i2c.write(0x04); //Command
  i2c.write(0x0E); //Clear Flags
  println("Cleared Flags");
  
  //Read Pixel
  */
  
 
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


void draw() {
  
  
  
  
//splashScreen();
//liveStream();

updateBlock(i,j,count);
i++;

count++;

if (count > 10) count = 0;
if (i > 9){
  i = 0;
  j++;
  if(j > 9){
    j = 0;
  }
}


 


}

 void updateDisplay(){
   for(int i = 0; i < 8; i++){
      for(int j = 0; j < 8; j++){
        //updateBlock(i,j,frame.access(i,j));
      }
   }
}



void updateBlock(int row, int col, int temperatureValue){
    if(row < 8 && col < 8){//only draw within 8x8 grid
    int colorMask = temperatureValue;
    
    //set fill color based on mask
    //0 cold, 15 hot
    switch (colorMask){
      case 0:
      fill(0,0,0);
      break;
       case 1:
      fill(102,0,102);
      break;
     case 2:
      fill(255,0,255);
      break;
     case 3:
      fill(0,0,153);
      break;
     case 4:
      fill(0,0,255);
      break;
     case 5:
      fill(102,255,204);
      break;
     case 6:
      fill(0,153,51);
      break;
     case 7:
    
      fill(204,255,51);
      break;
     case 8:
      fill(255,255,0);
      break;
     case 9:
      fill(255,153,51);
      break;
     case 10:
      fill(255,0,0);
      break;
     case 11:
      fill(255,153,153);
      break;
     case 12:
      fill(255,255,255);
      break;
     case 13:
      fill(255,255,255);
      break;
     case 14:
      fill(255,255,255);
      break;
     case 15:
      fill(255,255,255);
      break;
    }
    

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
  
  //Draw Boarder
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
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  

      
  
  
  
  

  
  
 