/**
 * \file DetectedPattern.h
 * \brief Classe qui offre les fonctionnalit&eacute;s d'un patron d&eacute;tect&eacute; dans l'image.
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 * \version 1.0
 *
 * Classe qui offre les fonctionnalit&eacute;s d'un patron d&eacute;tect&eacute; dans l'image.
 *
 */

#pragma once
#include "idetectedpattern.h"

namespace baluchon { namespace core { namespace services { namespace patterndetection { 

class DetectedPattern :
    public IDetectedPattern
{
public:

    /**
     * \fn DetectedPattern(IPattern *mPattern)
     * \brief Constructeur de la classe.
     * \param mPattern Le patron associ&eacute; qui est d&eacute;tect&eacute;.
     */
    DetectedPattern(IPattern *mPattern);

    /**
     * \fn ~DetectedPattern(void)
     * \brief Destructeur de la classe.
     */
    ~DetectedPattern(void);

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
     * \fn bool decorates(IPattern *pattern)
     * \brief Identifie si le patron est d&eacute;cor&eacute; par celui-ci.
     * \param pattern Le patron &agrave; v&eacute;rifier.
     * \return Si le patron est d&eacute;cor&eacute; par celui-ci.
     */
    bool decorates(IPattern *pattern);

private:

    IPattern *mPattern;

    vector<vector<CvPoint2D32f>>* mImgPoints;
    vector<vector<CvPoint2D32f>>* mFramePoints;
};

}}}};