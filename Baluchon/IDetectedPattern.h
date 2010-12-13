/**
 * \file IDetectedPattern.h
 * \brief Interface qui offre les fonctionnalit&eacute;s d'un patron d&eacute;tect&eacute; dans l'image.
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 * \version 1.0
 *
 * Interface qui offre les fonctionnalit&eacute;s d'un patron d&eacute;tect&eacute; dans l'image.
 *
 */

#pragma once
#include "ipattern.h"

namespace baluchon { namespace core { namespace services { namespace patterndetection { 

class IDetectedPattern :
    public IPattern
{
public:

    /**
     * \fn virtual ~IDetectedPattern(void)
     * \brief Destructeur virtuel de la classe.
     */
    virtual ~IDetectedPattern(void) {};

    /**
     * \fn virtual vector<vector<CvPoint2D32f>>* getImagePoints()
     * \brief Retourne les points d&eacute;tect&eacute;s dans l'image.
     * \return Les points d&eacute;tect&eacute;s dans l'image.
     */
    virtual vector<vector<CvPoint2D32f>>* getImagePoints() = 0;

    /**
     * \fn virtual vector<vector<CvPoint2D32f>>* getImageFramePoints()
     * \brief Retourne les points du cadre d&eacute;tect&eacute;s dans l'image.
     * \return Les points du cadre d&eacute;tect&eacute;s dans l'image.
     */
    virtual vector<vector<CvPoint2D32f>>* getImageFramePoints() = 0;

    /**
     * \fn virtual bool decorates(IPattern *pattern)
     * \brief Identifie si le patron est d&eacute;cor&eacute; par celui-ci.
     * \param pattern Le patron &agrave; v&eacute;rifier.
     * \return Si le patron est d&eacute;cor&eacute; par celui-ci.
     */
    virtual bool decorates(IPattern *pattern) = 0;
};

}}}};