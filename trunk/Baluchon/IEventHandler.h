/**
 * \file IEventHandler.h
 * \brief Interface offrant les signatures de fonction d'un gestionnaire d'&eacute;v&egrave;nements.
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 * \version 1.0
 *
 * Interface qui offre les signatures de base pour un gestionnaire d'&eacute;v&egrave;nements de l'application.
 *
 */

#pragma once

#include "IEvent.h"

namespace baluchon { namespace core { namespace events {

class IEventHandler
{
public:

    /**
     * \fn virtual ~IEventHandler()
     * \brief Destructeur virtuel de la classe.
     */
    virtual ~IEventHandler(void) {};

    /**
     * \fn virtual void handle(IEvent* e)
     * \brief Fonction de gestion d'un &eacute;v&egrave;nement.
     * \param e L'&eacute;v&egrave;nement &agrave; g&eacute;rer.
     */
    virtual void handle(IEvent* e) = 0;
};

}}};