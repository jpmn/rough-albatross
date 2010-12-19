/**
 * \file PositioningVisitor.h
 * \brief Interface qui offre les signatures de fonctions pour un visiteur.
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 * \version 1.0
 *
 * Interface qui offre les signatures de fonctions pour un visiteur.
 *
 */

#pragma once

#include <cv.h>

#include "IVisitor.h"

namespace baluchon { namespace core { namespace services { namespace positioning { 

class AnimatedTransform;
class Transform;
class FrameCube;
class FrameBox;

class PositioningVisitor : public IVisitor
{
public:

    /**
     * \fn PositioningVisitor(CvMat* intrinsicMat, CvMat* distortionMat)
     * \brief Constructeur de la classe.
     * \param intrinsicMat La matrice intris&egrave;que de la cam&eacute;ra.
     * \param distortionMat La matrice de distortion de la cam&eacute;ra.
     */
    PositioningVisitor(CvMat* intrinsicMat, CvMat* distortionMat);

    /**
     * \fn ~PositioningVisitor(void)
     * \brief Destructeur de la classe.
     */
    ~PositioningVisitor(void);

    /**
     * \fn void visit(Transform *t)
     * \brief Fonction de visite d'une transformation.
     * \param t La transformation &agrave; visiter.
     */
	void visit(Transform *t);
    void visit(AnimatedTransform *t);
	void visit(FrameBox *fb);

    /**
     * \fn void visit(FrameCube *fc)
     * \brief Fonction de visite d'un squelette de cube.
     * \param t Le cube &agrave; visiter.
     */
    void visit(FrameCube *fc);

    /**
     * \fn void setImage(IplImage* img)
     * \brief Fonction qui initialise l'image actuelle.
     * \param img L'image actuelle.
     */
    void setImage(IplImage* img);

    /**
     * \fn void setRotationMat(CvMat* rotation)
     * \brief Fonction qui initialise la matrice de rotation actuelle.
     * \param rotation La matrice de rotation actuelle.
     */
    void setRotationMat(CvMat* rotation);

    /**
     * \fn void setTranslationMat(CvMat* translation)
     * \brief Fonction qui initialise la matrice de translation actuelle.
     * \param rotation La matrice de translation actuelle.
     */
    void setTranslationMat(CvMat* translation);

protected:
    IplImage* mSrcImg;
    CvMat* mIntrinsicMat;
    CvMat* mDistortionMat;
    CvMat* mRotationMat;
    CvMat* mTranslationMat;
};

}}}};