import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class main extends PApplet {

int rectX, rectY;      // Position of square button
int circleX, circleY;  // Position of circle button
int rectSize = 90;     // Diameter of rect
int circleSize = 93;   // Diameter of circle
int rectColor, circleColor, baseColor;
int rectHighlight, circleHighlight;
int currentColor;

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

public void setup() {
  
  rectColor = color(0);
  rectHighlight = color(51);
  circleColor = color(255);
  circleHighlight = color(204);
  baseColor = color(102);
  currentColor = baseColor;
  circleX = width/2+circleSize/2+10;
  circleY = height/2;
  rectX = width/2-rectSize-10;
  rectY = height/2-rectSize/2;
  ellipseMode(CENTER);
  
}


public void draw() {
  
  
  
  
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

 public void updateDisplay(){
   for(int i = 0; i < 8; i++){
      for(int j = 0; j < 8; j++){
        //updateBlock(i,j,frame.access(i,j));
      }
   }
}



public void updateBlock(int row, int col, int temperatureValue){
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

public void splashScreen(){
  textSize(32);
  fill(0, 102, 153);
  text("ECE 3220: Thermal Camera", 10, 30);
  text("Welcome", 10,50);
  
}

public int liveStream(){ //Each square displayScalexdisplayScale pixels, line width 1 pixel.
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
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  

      
  
  
  
  

  
  
 
  public void settings() {  size(700, 700); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "main" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
