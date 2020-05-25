#include <cstdio>
#include <cstdlib>
#include "timer.h"
#include "ppb_ppm.h"
#include <cmath>
#include <algorithm>

#define OUT_FILENAME "convout2.ppm"
#define MAXK 11
double knl[MAXK][MAXK]={{0}};

void makegauss(int k){
  int hk = k/2;
  double s = (k/2.0-1.0)*0.3+0.8;
  double s2 = s*s;
  for(int y = 0;y <= hk;++y){
    for(int x = 0;x <= hk; ++x){
      double gf = exp(-(x*x+y*y)/(2.0*s2))/(2.0*M_PI*s2);
      knl[hk+y][hk+x] = gf;
      knl[hk-y][hk+x] = gf;
      knl[hk-y][hk-x] = gf;
      knl[hk+y][hk-x] = gf;
    }
  }
  printf("Kernel\n");

  for(int y = 0;y < k;++y){
    for(int x = 0;x < k;++x){
      printf("%f ",knl[y][x]);
    }
    printf("\n");
  }
}

int main(int ac,char *av[]){
  image_t image,outimg;
  double tm[5];
  //read image file
  tm[0] = dgettime();
    if((read_ppm(&image,av[1])) != 0){ //first paramater:input image
    printf("can't open image : %s\n",av[1]);
    return -1;
  }
  tm[1] = dgettime();
  int sk = 5;// kernel size default
  if(ac > 2){  //second parameter: kernel size
    sk = atoi(av[2]);
  }
  int hsk = sk/2;
  makegauss(sk);
  new_image(&outimg, image.width,image.height);
  
  tm[2] = dgettime();
  for(int y = hsk;y < image.height-hsk;++y){
    for(int x = hsk;x < image.width-hsk;++x){
      float rr = 0.0f;
      float gg = 0.0f;
      float bb = 0.0f;
      int ix = (x)+(y)*image.width;
      for(int j = -hsk;j <= hsk;++j){
	for(int i = -hsk;i <= hsk;++i){
	  int index = (x+i)+(y+j)*image.width;
	  rr += image.buf[index].r * knl[j+hsk][i+hsk];
	  gg += image.buf[index].g * knl[j+hsk][i+hsk];
	  bb += image.buf[index].b * knl[j+hsk][i+hsk];
	}
      }
      outimg.buf[ix].r = std::min(255.0f,std::max(0.0f,rr));
      outimg.buf[ix].g = std::min(255.0f,std::max(0.0f,gg));
      outimg.buf[ix].b = std::min(255.0f,std::max(0.0f,bb));
    }
  }
  tm[3] = dgettime();
  //write out image
  write_ppm(&outimg,(char*)OUT_FILENAME);
  tm[4] = dgettime();
  delete_image(&image);
  delete_image(&outimg);
  printf("Read time=%e  Process time=%e Write time=%e\n",
	 tm[1]-tm[0],tm[3]-tm[2],tm[4]-tm[3]);
  return 0;
}
	 
