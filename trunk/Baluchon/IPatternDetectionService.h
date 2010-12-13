/**
 * \file IPatternDetectionService.h
 * \brief Interface qui offre les signatures de fonctions pour le service de d&eacute;tection de patrons.
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 * \version 1.0
 *
 * Interface qui offre les signatures de fonctions du service de d&eacute;tection de patrons.
 *
 */

#pragma once

#include "IService.h"
#include "IDetectedPattern.h"

namespace baluchon { namespace core { namespace services { namespace patterndetection { 

class IPatternDetectionService : public IService
{
public:

    /**
     * \fn virtual ~IPatternDetectionService(void)
     * \brief Destructeur virtuel de la classe.
     */
    virtual ~IPatternDetectionService(void) {};

    /**
     * \fn virtual void addPattern(IPattern* pattern)
     * \brief M&eacute;thode d'ajout d'un patron.
     * \param pattern Le patron &agrave; ajouter.
     */
    virtual void addPattern(IPattern* pattern) = 0;

    /**
     * \fn virtual IPattern* addPattern(char patternName[])
     * \brief M&eacute;thode d'ajout d'un patron.
     * \param patternName Le chemin du patron &agrave; ajouter.
     * \return L'instance du patron ajout&eacute;.
     */
    virtual IPattern* addPattern(char patternName[]) = 0;

    /**
     * \fn virtual vector<IDetectedPattern*> getPatterns()
     * \brief M&eacute;thode qui retourne les patrons.
     * \return Le vecteur des patrons.
     */
    virtual vector<IDetectedPattern*> getPatterns() = 0;
};

}}}};