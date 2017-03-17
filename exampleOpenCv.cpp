#include "opencv2/highgui/highgui.hpp"
using namespace std;
struct point {
    int x,y;
};
void dibujar_Tri(IplImage *img,point a,point b,point c){
 
    cvLine(img,cvPoint(a.x, a.y),cvPoint(b.x, b.y),cvScalar(0, 255, 0, 0));
    cvLine(img,cvPoint(b.x, b.y),cvPoint(c.x, c.y),cvScalar(0, 255, 0, 0));
    cvLine(img,cvPoint(a.x, a.y),cvPoint(c.x, c.y),cvScalar(0, 255, 0, 0));
 
}
point mitad(point a,point b){
    point resul;
    resul.x=(a.x+b.x)/2;
    resul.y=(a.y+b.y)/2;
    return resul;
}
void Triangulo(IplImage *img,point a,point b, point c,int iter){
    if(iter==0){
        dibujar_Tri(img,a,b,c);
        return;
    }
    point AB=mitad(a,b);
    point BC=mitad(b,c);
    point CA=mitad(c,a);
    Triangulo(img,a,AB,CA,iter-1);
    Triangulo(img,AB,b,BC,iter-1);
    Triangulo(img,CA,BC,c,iter-1);
}
 
int main( int argc, char** argv ) {
    int npower = 4;
    point A,B,C;
    if(argc>1) npower = atoi(argv[1]);
 
    unsigned long nsize =(unsigned long)(pow(3,npower)*3);
    IplImage *img = cvCreateImage(cvSize(nsize+2, nsize+2), IPL_DEPTH_8U, 3);
    cvNamedWindow("sierpinsky", CV_WINDOW_AUTOSIZE);
    A.x=0;
    A.y=nsize;
    B.x=nsize/2;
    B.y=0;
    C.x=nsize;
    C.y=nsize;
    Triangulo(img,A,B,C,npower);
 
    cvSaveImage("salida.png",img);
    cvShowImage("sierpinsky", img);
    cvWaitKey(0);
    cvDestroyWindow("sierpinsky");
    cvReleaseImage(&img);
 
    return 0;
}
