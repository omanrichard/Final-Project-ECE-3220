#ifndef thermalGraphics
#define thermalGraphiics

class progressBar{

	private: 
		progressBar(int x, int y, int length, int width);
		progressBar(int x, int y, int length, int width, int time);
		int xMin,yMin,xSize,ySize
		int progress;
		void drawFrame;

	public:
		void update(int percent);
}















#endif 
