#include "PositioningVisitor.h"
#include "FrameCube.h"
#include "Transform.h"

namespace baluchon { namespace core { namespace services { namespace positioning { 

PositioningVisitor::PositioningVisitor(CvMat* intrinsicMat, CvMat* distortionMat)
{
    mIntrinsicMat = intrinsicMat;
    mDistortionMat = distortionMat;
    mRotationMat = 0;
    mTranslationMat = 0;
}


PositioningVisitor::~PositioningVisitor(void)
{
}

void PositioningVisitor::visit(Transform *t)
{
    if(t->getMatrix() != 0)
    {
        for(unsigned int i = 0; i < t->getChildren().size(); i++)
        {   
            t->getChildren()[i]->apply(t->getMatrix());
        }
    }
}

void PositioningVisitor::visit(FrameCube *cube)
{
    CvMat *srcPoints3D = cvCreateMat (8, 1, CV_32FC3);
    srcPoints3D->data.fl[0] = 50;
    srcPoints3D->data.fl[1] = 50;
    srcPoints3D->data.fl[2] = -150;
    for(int i = 0; i < 8; i++)
    {
        srcPoints3D->data.fl[i*3] = cube->getPoints()[i].x;
        srcPoints3D->data.fl[i*3+1] = cube->getPoints()[i].y;
        srcPoints3D->data.fl[i*3+2] = cube->getPoints()[i].z;
    }

    CvMat *dstPoints2D = cvCreateMat (8, 1, CV_32FC3);
    cvProjectPoints2(srcPoints3D, mRotationMat, mTranslationMat, mIntrinsicMat, mDistortionMat, dstPoints2D);

    if(dstPoints2D != 0)
    {
        for(int k = 1; k < 8; k++)
        {
            if(k != 4)
            {
                cvLine(mSrcImg,cvPoint((int) dstPoints2D->data.fl[3*(k-1)], (int) dstPoints2D->data.fl[3*(k-1)+1]), cvPoint((int) dstPoints2D->data.fl[3*k], (int) dstPoints2D->data.fl[3*k+1]), cube->getColor(), 5);
            }
        }
        cvLine(mSrcImg,cvPoint((int) dstPoints2D->data.fl[3*(0)], (int) dstPoints2D->data.fl[3*(0)+1]), cvPoint((int) dstPoints2D->data.fl[3*3], (int) dstPoints2D->data.fl[3*3+1]), cube->getColor(), 5);
        cvLine(mSrcImg,cvPoint((int) dstPoints2D->data.fl[3*(7)], (int) dstPoints2D->data.fl[3*(7)+1]), cvPoint((int) dstPoints2D->data.fl[3*4], (int) dstPoints2D->data.fl[3*4+1]), cube->getColor(), 5);

        for(int k = 0; k < 4; k++)
        {
            cvLine(mSrcImg,cvPoint((int) dstPoints2D->data.fl[3*(k)], (int) dstPoints2D->data.fl[3*(k)+1]), cvPoint((int) dstPoints2D->data.fl[3*(k+4)], (int) dstPoints2D->data.fl[3*(k+4)+1]), cube->getColor(), 5);
        }

        cvReleaseMat(&srcPoints3D);
        cvReleaseMat(&dstPoints2D);
    }


    //transformation avec les matrices de rotation et translation

    /*for(int i = 0; i < 8; i++)
    {
        dessin
    }*/


    //reviens aux points du début de la méthode
}

void PositioningVisitor::setImage(IplImage *img)
{
    mSrcImg = img;
}

void PositioningVisitor::setRotationMat(CvMat* rotation)
{
    mRotationMat = rotation;
}

void PositioningVisitor::setTranslationMat(CvMat* translation)
{
    mTranslationMat = translation;
}

}}}};
