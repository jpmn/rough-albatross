/**
 * \file Engine.h
 * \brief Engin de r&eacute;alit&eacute; augment&eacute;e.
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 * \version 1.0
 *
 * Classe qui offre les fonctions de bases pour la gestion de services de r&eacute;alit&eacute; augment&eacute;e.
 *
 */

#pragma once

#include <vector>

#include "IEngine.h"
#include "IServiceLayer.h"

using namespace std;
using namespace baluchon::core::engine;
using namespace baluchon::core::services;

namespace baluchon { namespace core { namespace engine {

class Engine : public IEngine
{
public:

    /**
     * \fn Engine(void)
     * \brief Constructeur de la classe.
     */
	Engine(void);

    /**
     * \fn ~Engine(void)
     * \brief Destructeur de la classe.
     */
	~Engine(void);

    /**
     * \fn virtual void init(void)
     * \brief Fonction d'initialisation.
     */
	virtual void init(void);

    /**
     * \fn virtual void run(void)
     * \brief Fonction d'ex&eacute;cution.
     */
	virtual void run(void);

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

    /**
     * \fn virtual void setExitKey(char exitKey)
     * \brief Fonction qui initialise la touche de fin d'application.
     */
	virtual void setExitKey(char exitKey);

    /**
     * \fn virtual void addServiceLayer(IServiceLayer* serviceLayer)
     * \brief Fonction qui ajoute une couche de services &agrave; l'engin.
     */
	virtual void addServiceLayer(IServiceLayer* serviceLayer);

private:
	char mExitKey;
	vector<IServiceLayer*> mListServiceLayers;
};

}}};