
//http://www.cs.iit.edu/~agam/cs512/lect-notes/opencv-intro/opencv-intro.html

namespace Baluchon { namespace Utils {

template<class T> class ImageWrapper
{
  private:
  IplImage* imgp;
  public:
  ImageWrapper(IplImage* img=0) {imgp=img;}
  ~ImageWrapper(){imgp=0;}
  void operator=(IplImage* img) {imgp=img;}
  inline T* operator[](const int rowIndx) {
    return ((T *)(imgp->imageData + rowIndx*imgp->widthStep));}
};

typedef struct{
  unsigned char b,g,r;
} RgbPixel;

typedef struct{
  float b,g,r;
} RgbPixelFloat;

typedef ImageWrapper<RgbPixel>       RgbImage;
typedef ImageWrapper<RgbPixelFloat>  RgbImageFloat;
typedef ImageWrapper<unsigned char>  BwImage;
typedef ImageWrapper<float>          BwImageFloat;

}};