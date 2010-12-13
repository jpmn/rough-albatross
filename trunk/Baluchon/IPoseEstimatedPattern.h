/**
 * \file IPoseEstimatedPattern.h
 * \brief Interface qui offre les fonctionnalit&eacute;s d'un patron d&eacute;tect&eacute; dont la position et l'orientation sont estim&eacute;es dans l'image.
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 * \version 1.0
 *
 * Interface qui offre les fonctionnalit&eacute;s d'un patron d&eacute;tect&eacute; dont la position et l'orientation sont estim&eacute;es dans l'image.
 *
 */

#pragma once
#include "idetectedpattern.h"

using namespace baluchon::core::services::patterndetection;

namespace baluchon { namespace core { namespace services { namespace poseestimation { 

class IPoseEstimatedPattern :
    public IDetectedPattern
{
public:

    /**
     * \fn virtual ~IPoseEstimatedPattern(void)
     * \brief Destructeur virtuel de la classe.
     */
    virtual ~IPoseEstimatedPattern(void) {};

    /**
     * \fn virtual vector<CvMat*>* getRotationMatrices()
     * \brief Retourne les matrices de rotation des instances des patrons.
     * \param Les matrices de rotation des instances des patrons.
     */
    virtual vector<CvMat*>* getRotationMatrices() = 0;

    /**
     * \fn virtual vector<CvMat*>* getTranslationMatrices()
     * \brief Retourne les matrices de translation des instances des patrons.
     * \param Les matrices de translation des instances des patrons.
     */
    virtual vector<CvMat*>* getTranslationMatrices() = 0;
};

}}}};