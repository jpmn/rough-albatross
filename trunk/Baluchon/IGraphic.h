/**
 * \file IGraphic.h
 * \brief Interface qui offre les signatures de fonctions pour un objet graphique.
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 * \version 1.0
 *
 * Interface qui offre les signatures de fonctions pour un objet graphique.
 *
 */

#pragma once

#include <vector>
#include "cv.h"

using namespace std;

namespace baluchon { namespace core { namespace services { namespace positioning { 

class IVisitor;

class IGraphic
{
public:

    /**
     * \fn virtual ~IGraphic(void)
     * \brief Destructeur virtuel de la classe.
     */
    virtual ~IGraphic(void) {};

    /**
     * \fn virtual void accept(IVisitor* v)
     * \brief Fonction d'acceptation d'un visiteur.
     * \param v Le visiteur.
     */
    virtual void accept(IVisitor* v) = 0;

    /**
     * \fn virtual void apply(CvMat* mul)
     * \brief Fonction qui applique une matrice aux points de l'objet graphique.
     * \param mul Matrice &agrave; multiplier.
     */
    virtual void apply(CvMat* mul)
    {
        while(mTemporaryTransformedPoints.size() != mTransformedPoints.size())
        {
            mTemporaryTransformedPoints.push_back(cvPoint3D32f(0,0,0));
        }
        
        for(unsigned int j = 0; j < mTransformedPoints.size(); j++)
        {
            mTemporaryTransformedPoints[j].x = (float) (cvmGet(mul, 0, 0) * mTransformedPoints[j].x + cvmGet(mul, 0, 1) * mTransformedPoints[j].y + cvmGet(mul, 0, 2) * mTransformedPoints[j].z + cvmGet(mul, 0, 3));
            mTemporaryTransformedPoints[j].y = (float) (cvmGet(mul, 1, 0) * mTransformedPoints[j].x + cvmGet(mul, 1, 1) * mTransformedPoints[j].y + cvmGet(mul, 1, 2) * mTransformedPoints[j].z + cvmGet(mul, 1, 3));
            mTemporaryTransformedPoints[j].z = (float) (cvmGet(mul, 2, 0) * mTransformedPoints[j].x + cvmGet(mul, 2, 1) * mTransformedPoints[j].y + cvmGet(mul, 2, 2) * mTransformedPoints[j].z + cvmGet(mul, 2, 3));
        }

        for(unsigned int j = 0; j < mTransformedPoints.size(); j++)
        {
            mTransformedPoints[j].x = mTemporaryTransformedPoints[j].x;
            mTransformedPoints[j].y = mTemporaryTransformedPoints[j].y;
            mTransformedPoints[j].z = mTemporaryTransformedPoints[j].z;
        }
    }

    /**
     * \fn virtual vector<CvPoint3D32f> getPoints()
     * \brief Fonction qui retourne les points de l'objet graphique.
     * \return mTransformedPoints Les points de l'objet graphique.
     */
    virtual vector<CvPoint3D32f> getPoints()
    {
        return mTransformedPoints;
    }

    /**
     * \fn virtual void reset()
     * \brief Fonction qui r&eacute;initialise les points de l'objet graphique.
     */
    virtual void reset()
    {
        mTransformedPoints.clear();
        for(unsigned int i = 0; i < mInitialPoints.size(); i++)
        {
            mTransformedPoints.push_back(mInitialPoints[i]);
        }
    }

protected:
    vector<CvPoint3D32f> mInitialPoints;
    vector<CvPoint3D32f> mTransformedPoints;
private:
    vector<CvPoint3D32f> mTemporaryTransformedPoints;
};

}}}};
