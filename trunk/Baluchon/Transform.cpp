#include "Transform.h"

namespace baluchon { namespace core { namespace services { namespace positioning { 

Transform::Transform(void)
{
    mMat = cvCreateMat(4, 4, CV_32FC1);
    mTransformedMat = cvCreateMat(4, 4, CV_32FC1);
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(i == j)
            {
                cvmSet(mMat,i,j,1);
                cvmSet(mTransformedMat,i,j,1);
            }
            else
            {
                cvmSet(mMat,i,j,0);
                cvmSet(mTransformedMat,i,j,0);
            }
        }
    }
}


Transform::~Transform(void)
{
    cvReleaseMat(&mTransformedMat);
    cvReleaseMat(&mMat);
}

void Transform::accept(IVisitor* v)
{
    v->visit(this);
    for(unsigned int i = 0; i < mChildren.size(); i++)
    {
        mChildren[i]->accept(v);
    }
}

void Transform::add(IGraphic* child)
{
    mChildren.push_back(child);
}

void Transform::remove(IGraphic* child)
{
    bool found = false;
    unsigned int cpt = 0;
    while(!found && cpt < mChildren.size())
    {
        if(mChildren[cpt] == child)
        {
            found = true;
        }
        else
        {
            cpt++;
        }
    }
    if(found)
    {
        mChildren.erase(mChildren.begin()+cpt);
    }
}

vector<IGraphic*> Transform::getChildren()
{
    return mChildren;
}

void Transform::apply(CvMat* mul)
{
    double temp;
    CvMat* matTemp = cvCreateMat(4, 4, CV_32FC1);

    for(int k = 0; k < 4; k++)
    {
        for(int i = 0; i < 4; i++)
        {
            temp = 0.0;
            for(int j = 0; j < 4; j++)
            {
                temp += cvmGet(mul,i,j) * cvmGet(mTransformedMat,j,k);
            }
            cvmSet(matTemp, i, k, temp);
        }
    }

    cvReleaseMat(&mTransformedMat);
    mTransformedMat = matTemp;
}

CvMat* Transform::getMatrix()
{
    return mTransformedMat;
}

void Transform::setMatrix(CvMat* matrix)
{
    cvReleaseMat(&mMat);
    mMat = matrix;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            cvmSet(mTransformedMat, i, j, cvmGet(mMat,i,j));
        }
    }
}

void Transform::reset()
{
    // used for animation
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            cvmSet(mTransformedMat, i, j, cvmGet(mMat, i, j));
        }
    }

    for(unsigned int i = 0; i < mChildren.size(); i++)
    {
        mChildren[i]->reset();
    }
}

}}}};