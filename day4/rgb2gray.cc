#include <cstdio>
#include <cstdlib>
#include "timer.h"
#include "ppb_ppm.h"

#define IN_FILENAME "/share/data/picture/mandrill.ppm"
#define OUT_FILENAME "out.ppm"


int main() {
    image_t image;
    int i, npix;
    double tm[4];
    // read image file
    tm[0] = dgettime();
    if ((read_ppm(&image, (char*)IN_FILENAME)) != 0) {
        printf("can't open image : %s\n", IN_FILENAME);    
        return -1;
    }
    // number of pixels
    npix = image.width * image.height;

    tm[1] = dgettime();
    for (i = 0; i < npix ; i++) {
        // convert RGB to YIQ
	unsigned int y = (unsigned int)(
            0.299 * (double)image.buf[i].r
            + 0.587 * (double)image.buf[i].g
            + 0.114 * (double)image.buf[i].b );
        image.buf[i].r = image.buf[i].g = image.buf[i].b = y;
    }
    tm[2] = dgettime();

    // write out image
    write_ppm(&image, (char*)OUT_FILENAME);
    delete_image(&image);
    tm[3] = dgettime();
    printf("Read time=%e  Process time=%e Write time=%e\n", 
	   tm[1]-tm[0], tm[2]-tm[1],tm[3]-tm[2]);

    return 0;
}
