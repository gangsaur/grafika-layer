#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <bits/stdc++.h>
using namespace std;

class framebuffer {

	private:
		int fbfd = 0;
	    struct fb_var_screeninfo vinfo;
	    struct fb_fix_screeninfo finfo;
	    long int screensize = 0;
	    char *fbp = 0;
	    int x = 0, y = 0;
	    long int location = 0;

	public:
		framebuffer() {
		    // Open the file for reading and writing
		    fbfd = open("/dev/fb0", O_RDWR);
		    if (fbfd == -1) {
		        perror("Error: cannot open framebuffer device");
		        exit(1);
		    }

		    // Get fixed screen information
		    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
		        perror("Error reading fixed information");
		        exit(2);
		    }

		    // Get variable screen information
		    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
		        perror("Error reading variable information");
		        exit(3);
		    }

		    // Figure out the size of the screen in bytes
		    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

		    // Map the device to memory
		    if (!(fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0))) {
		        perror("Error: failed to map framebuffer device to memory");
		        exit(4);
		    }
		}

		~framebuffer(){
			//cout << "Close\n";
			close(fbfd);
		}

		void putPixel(int x, int y, int red, int green, int blue) {
            location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (y+vinfo.yoffset) * finfo.line_length;
            if (vinfo.bits_per_pixel == 32) {
                *(fbp + location + 0) = blue;        
                *(fbp + location + 1) = green;     
                *(fbp + location + 2) = red;    
                *(fbp + location + 3) = 0;      
            } else  {
                int b = blue;
                int g = green;
                int r = red;
                unsigned short int t = r<<11 | g << 5 | b;
                *((unsigned short int*)(fbp + location)) = t;
            }
		}
		
		void insertLine(float x1, float y1,float x2, float y2, int r, int g, int b) {
		    // Bresenham's line algorithm
			const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
			if(steep)
			{
			  std::swap(x1, y1);
			  std::swap(x2, y2);
			}
			 
			if(x1 > x2)
			{
			  std::swap(x1, x2);
			  std::swap(y1, y2);
			}
			 
			const float dx = x2 - x1;
			const float dy = fabs(y2 - y1);
			 
			float error = dx / 2.0f;
			const int ystep = (y1 < y2) ? 1 : -1;
			int y = (int)y1;
			 
			const int maxX = (int)x2;
			
			for(int x=(int)x1; x<maxX; x++)
			{
			  if(steep)
			  {
			      putPixel(y,x,r,g,b);
			  }
			  else
			  {
			      putPixel(x,y,r,g,b);
			  }
			 
			  error -= dy;
			  if(error < 0)
			  {
			      y += ystep;
			      error += dx;
			  }
			}	
		}
};

#endif
