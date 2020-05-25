#ifndef _PPB_PPM_H
#define _PPB_PPM_H
#include <cstring>

#define PPM_MAGIC "P6"

/* 画像の1点をあらわすRGB値構造体 */
typedef struct _rgb_t {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} rgb_t;

/* 画像をあらわす構造体 */
typedef struct _image_t {
    int width;
    int height;
    rgb_t *buf;
} image_t;

/* -----------------------------
 * PPMの操作関数
 * ----------------------------- */

/* fnameのPPM(P6形式)からimage構造体を生成する */
int read_ppm(image_t* img, char* fname) {
    char *token, *pc;
    char *buf;
    char *del = (char*)" \t\n";
    
    long begin, end;
    int filesize;
    int i, w, h, luma, pixs, k;

    rgb_t *dot;
    FILE *fp;

    if ((fp = fopen(fname, "r")) == NULL) {
        printf("Failed to open file\n");
        return -1;
    }

    /* ファイルサイズの取得 */
    fseek(fp, 0, SEEK_SET);
    begin = ftell(fp);
    fseek(fp, 0, SEEK_END);
    end = ftell(fp);
    filesize = (int)(end - begin);


    buf = (char *)malloc(filesize * sizeof(char));

    fseek(fp, 0, SEEK_SET);
    fread(buf, filesize * sizeof(char), 1, fp);

    fclose(fp);
    
    token = (char *)strtok(buf, del);
    if (strncmp(token, PPM_MAGIC, 2) != 0) {
        return -1;
    }
    k = 2;
    /* Skip one line of comment */
    if(buf[3] == '#') {
	for(k = 4 ;; k++){
	    if(buf[k] == '\n') break;
	}
    }
    /* 幅・高さ・最大輝度を読む */
    token = (char *)strtok(&buf[k+1], del);
    w = strtoul(token, &pc, 10);
    token = (char *)strtok(NULL, del);
    h = strtoul(token, &pc, 10);
    token = (char *)strtok(NULL, del);
    luma = strtoul(token, &pc, 10);
    
    token = pc + 1;
    pixs = w * h;
    printf("%c%c %d %d %d\n",buf[0], buf[1], w, h, luma);
    /* rgbバッファをアロケート */
    img->buf = (rgb_t *)malloc(pixs * sizeof(rgb_t));

    /* ピクセルを読む */
    dot = img->buf;
    for (i = 0; i < pixs; i++, dot++) {
        dot->r = *token++;
        dot->g = *token++;
        dot->b = *token++;
    }

    img->width = w;
    img->height = h;
    return 0;
}

/* image構造体をfnameのPPM(P6形式)に書き込む */
int write_ppm(image_t* img, char* fname) {
    int i, w, h, pixs;
    FILE *fp;
    rgb_t *dot;

    /* 初期化 */
    w = img->width;
    h = img->height;
    pixs = w * h;

    /* ファイルオープン */
    if ((fp = fopen(fname, "wb+")) == NULL) {
        printf("Failed to open file\n");
        return -1;
    }
    
    /* ヘッダと画像情報を書き出す */
    fprintf(fp, "%s\n%d %d\n255\n", PPM_MAGIC, w, h);
    dot = img->buf;
    for (i = 0; i < pixs; i++, dot++) {
        putc((int)dot->r, fp);
        putc((int)dot->g, fp);
        putc((int)dot->b, fp);
    }
    fclose(fp);
    return 0;
}

/* 新しい画像領域を作成 */
void new_image(image_t* img, int w, int h) {
    img->width  = w;
    img->height = h;
    img->buf = (rgb_t*)malloc(w*h*sizeof(rgb_t));
}

/* image構造体を解放する */
void  delete_image(image_t *img) {
    free(img->buf);
    return;
}

#endif /* PPB_PPM_H */
