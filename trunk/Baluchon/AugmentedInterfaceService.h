/**
 * \file AugmentedInterfaceService.h
 * \brief Service d'interface augment&eacute;e.
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 * \version 1.0
 *
 * Classe qui offre le service d'interface utilisateur augment&eacute;e.
 *
 */

#pragma once
#include "iaugmentedinterfaceservice.h"
#include "icaptureservice.h"

using namespace baluchon::core::services::capture;

namespace baluchon { namespace core { namespace services { namespace augmentedinterface {

class AugmentedInterfaceService :
    public IAugmentedInterfaceService
{
public:

    /**
     * \fn AugmentedInterfaceService(void)
     * \brief Constructeur de la classe.
     */
    AugmentedInterfaceService(void);

    /**
     * \fn ~AugmentedInterfaceService(void)
     * \brief Destructeur de la classe.
     */
    ~AugmentedInterfaceService(void);

    /**
     * \fn virtual void addAugmentedComponent(IAugmentedComponent* component)
     * \brief Fonction qui ajoute un composant &agrave; l'interface.
     * \param component Composant de l'interface.
     */
    virtual void addAugmentedComponent(IAugmentedComponent* component);

    /**
     * \fn virtual void removeAugmentedComponent(IAugmentedComponent* component)
     * \brief Fonction qui retire un composant &agrave; l'interface.
     * \param component Composant de l'interface.
     */
    virtual void removeAugmentedComponent(IAugmentedComponent* component);

    /**
     * \fn virtual void init(void)
     * \brief Fonction d'initialisation.
     */
    virtual void init(void);

    /**
     * \fn virtual void initDone(void)
     * \brief Fonction de fin d'initialisation.
     */
	virtual void initDone(void);

    /**
     * \fn virtual void execute(void)
     * \brief Fonction d'ex&eacute;cution.
     */
	virtual void execute(void);

    /**
     * \fn virtual void reset(void)
     * \brief Fonction de r&eacute;initialisation.
     */
	virtual void reset(void);

    /**
     * \fn virtual void dispose(void)
     * \brief Fonction de nettoyage.
     */
	virtual void dispose(void);

private:
    ICaptureService* mCaptureService;
    vector<IAugmentedComponent*> mAugmentedComponents;
};

}}}};