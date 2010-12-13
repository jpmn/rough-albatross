/**
 * \file IPoseEstimationService.h
 * \brief Interface qui offre les signatures de fonctions pour le service d'estimation de la position et de l'orientation de patrons.
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 * \version 1.0
 *
 * Interface qui offre les signatures de fonctions pour le service d'estimation de la position et de l'orientation de patrons.
 *
 */

#pragma once

#include "IService.h"
#include "IPoseEstimatedPattern.h"

namespace baluchon { namespace core { namespace services { namespace poseestimation { 

class IPoseEstimationService : public IService
{
public:

    /**
     * \fn virtual ~IPoseEstimationService(void)
     * \brief Destructeur virtuel de la classe.
     */
    virtual ~IPoseEstimationService(void) {};

    /**
     * \fn virtual vector<IPoseEstimatedPattern*> getPatterns()
     * \brief Retourne les patrons dont l'orientation et la position sont estim&eacute;es.
     * \return Les patrons dont l'orientation et la position sont estim&eacute;es.
     */
    virtual vector<IPoseEstimatedPattern*> getPatterns() = 0;
};

}}}};