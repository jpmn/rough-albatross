/** \mainpage Baluchon
 *
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 *
 * \section presentation Pr&eacute;sentation
 *
 * Baluchon est une plateforme logicielle qui offre des services de r&eacute;alit&eacute; augment&eacute;e.
 * Elle permet donc de faciliter l'impl&eacute;mentation d'une application de r&eacute;alit&eacute; augment&eacute;e gr&acirc;ce &agrave;
 * son architecture &eacute;v&eacute;nementielle orient&eacute;e service. Le cadre de l'application est optimis&eacute; pour satisfaire
 * des normes strictes d'extensibilit&eacute; et de performance.
 *
 * \section modules Modules
 * <ul>
 * <li>D&eacute;tection de patrons</li>
 * <li>D&eacute;tection de marqueurs de couleur</li>
 * <li>Estimation et positionnement 3D</li>
 * <li>Animation 3D</li>
 * <li>D&eacute;tection d'objets r&eacute;els</li>
 * <li>Interface usager augment&eacute;e</li>
 * </ul>
 * En plus de ces diff&eacute;rents modules, une preuve de concept est propos&eacute;e dans la plateforme sous forme d'un jeu simple.
 */

/**
 * \file IEngine.c
 * \brief Interface de l'engin de r&eacute;alit&eacute; augment&eacute;e.
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 * \version 1.0
 *
 * Interface qui offre les fonctions de bases pour la gestion de services de r&eacute;alit&eacute; augment&eacute;e.
 *
 */
#pragma once

#include "IServiceLayer.h"

using namespace baluchon::core::services;

namespace baluchon { namespace core { namespace engine {

class IEngine
{
public:
	virtual ~IEngine() {}

    /**
     * \fn virtual void init(void)
     * \brief Fonction d'initialisation.
     */
	virtual void init(void) = 0;

    /**
     * \fn virtual void run(void)
     * \brief Fonction d'ex&eacute;cution.
     */
	virtual void run(void) = 0;

    /**
     * \fn virtual void reset(void)
     * \brief Fonction de r&eacute;initialisation.
     */
	virtual void reset(void) = 0;

    /**
     * \fn virtual void dispose(void)
     * \brief Fonction de nettoyage.
     */
	virtual void dispose(void) = 0;

    /**
     * \fn virtual void setExitKey(char exitKey)
     * \brief Fonction qui initialise la touche de fin d'application.
     */
	virtual void setExitKey(char exitKey) = 0;

    /**
     * \fn virtual void addServiceLayer(IServiceLayer* serviceLayer)
     * \brief Fonction qui ajoute une couche de services &agrave; l'engin.
     */
	virtual void addServiceLayer(IServiceLayer* serviceLayer) = 0;
};

}}};