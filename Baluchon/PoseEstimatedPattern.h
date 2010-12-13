/**
 * \file PoseEstimatedPattern.h
 * \brief Classe qui offre les fonctionnalit&eacute;s d'un patron d&eacute;tect&eacute; dont la position et l'orientation sont estim&eacute;es dans l'image.
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 * \version 1.0
 *
 * Classe qui offre les fonctionnalit&eacute;s d'un patron d&eacute;tect&eacute; dont la position et l'orientation sont estim&eacute;es dans l'image.
 *
 */

#pragma once
#include "iposeestimatedpattern.h"
#include "idetectedpattern.h"

namespace baluchon { namespace core { namespace services { namespace poseestimation { 

class PoseEstimatedPattern :
    public IPoseEstimatedPattern
{
public:

    /**
     * \fn PoseEstimatedPattern(IDetectedPattern *mPattern)
     * \brief Constructeur de la classe.
     * \param mPattern Le patron d&eacute;tect&eacute; associ&eacute;.
     */
    PoseEstimatedPattern(IDetectedPattern *mPattern);

    /**
     * \fn ~PoseEstimatedPattern(void)
     * \brief Destructeur de la classe.
     */
    ~PoseEstimatedPattern(void);

    /**
     * \fn int getWidth()
     * \brief Retourne la largeur du patron.
     * \return La largeur du patron.
     */
    int getWidth();

    /**
     * \fn int getHeight()
     * \brief Retourne la hauteur du patron.
     * \return La hauteur du patron.
     */
    int getHeight();

    /**
     * \fn int getPointCount()
     * \brief Retourne le nombre de points du patron.
     * \return Le nombre de points du patron.
     */
    int getPointCount();

    /**
     * \fn CvPoint2D32f getSourcePointAt(int pos, int orientation = 0)
     * \brief Retourne un point dans l'une des quatres orientations.
     * \param pos La position du point.
     * \param orientation L'orientation du point.
     * \return Le point d&eacute;sir&eacute;.
     */
    CvPoint2D32f getSourcePointAt(int pos, int orientation = 0);

    /**
     * \fn vector<vector<CvPoint2D32f>>* getImagePoints()
     * \brief Retourne les points d&eacute;tect&eacute;s dans l'image.
     * \return Les points d&eacute;tect&eacute;s dans l'image.
     */
    vector<vector<CvPoint2D32f>>* getImagePoints();

    /**
     * \fn vector<vector<CvPoint2D32f>>* getImageFramePoints()
     * \brief Retourne les points du cadre d&eacute;tect&eacute;s dans l'image.
     * \return Les points du cadre d&eacute;tect&eacute;s dans l'image.
     */
    vector<vector<CvPoint2D32f>>* getImageFramePoints();

    /**
     * \fn vector<int>* getImageOrientations()
     * \brief Retourne les orientations des patrons d&eacute;tect&eacute;s dans l'image.
     * \return Les orientations des patrons d&eacute;tect&eacute;s dans l'image.
     */
    vector<int>* getImageOrientations();

    /**
     * \fn vector<CvMat*>* getRotationMatrices()
     * \brief Retourne les matrices de rotation des instances des patrons.
     * \param Les matrices de rotation des instances des patrons.
     */
    vector<CvMat*>* getRotationMatrices();

    /**
     * \fn vector<CvMat*>* getTranslationMatrices()
     * \brief Retourne les matrices de translation des instances des patrons.
     * \param Les matrices de translation des instances des patrons.
     */
    vector<CvMat*>* getTranslationMatrices();

    /**
     * \fn bool decorates(IPattern *pattern)
     * \brief Identifie si le patron est d&eacute;cor&eacute; par celui-ci.
     * \param pattern Le patron &agrave; v&eacute;rifier.
     * \return Si le patron est d&eacute;cor&eacute; par celui-ci.
     */
    bool decorates(IPattern *pattern);

private:

    IDetectedPattern *mPattern;
    vector<CvMat*>* mRotationMatrices;
    vector<CvMat*>* mTranslationMatrices;

};

}}}};