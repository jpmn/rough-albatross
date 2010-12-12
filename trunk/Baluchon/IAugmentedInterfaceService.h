/**
 * \file IAugmentedInterfaceService.h
 * \brief Interface qui offre les signatures de fonctions pour le service d'interface augment&eacute;e.
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 * \version 1.0
 *
 * Interface qui offre les signatures de fonctions du service d'interface utilisateur augment&eacute;e.
 *
 */

#pragma once
#include "iservice.h"
#include "iaugmentedcomponent.h"

namespace baluchon { namespace core { namespace services { namespace augmentedinterface {

class IAugmentedInterfaceService :
    public IService
{
public:

    /**
     * \fn virtual ~IAugmentedInterfaceService(void)
     * \brief Destructeur virtuel de la classe.
     */
    virtual ~IAugmentedInterfaceService(void) {};

    /**
     * \fn virtual void addAugmentedComponent(IAugmentedComponent* component)
     * \brief Fonction qui ajoute un composant &agrave; l'interface.
     * \param component Composant de l'interface.
     */
    virtual void addAugmentedComponent(IAugmentedComponent *component) = 0;

    /**
     * \fn virtual void removeAugmentedComponent(IAugmentedComponent* component)
     * \brief Fonction qui retire un composant &agrave; l'interface.
     * \param component Composant de l'interface.
     */
    virtual void removeAugmentedComponent(IAugmentedComponent *component) = 0;
};

}}}};