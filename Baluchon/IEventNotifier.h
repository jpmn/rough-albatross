/**
 * \file IEventNotifier.h
 * \brief Interface offrant les signatures de fonction d'un notifieur d'&eacute;v&egrave;nements.
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 * \version 1.0
 *
 * Interface qui offre les signatures de base pour un notifieur d'&eacute;v&egrave;nements de l'application.
 *
 */

#pragma once

#include "IEventHandler.h"
#include <vector>

using namespace std;

namespace baluchon { namespace core { namespace events {

class IEventNotifier
{
public:

    /**
     * \fn virtual ~IEventNotifier()
     * \brief Destructeur virtuel de la classe.
     */
    ~IEventNotifier(void) {};

    /**
     * \fn virtual void addEventHandler(IEventHandler* eventHandler)
     * \brief Fonction d'ajout d'un gestionnaire d'&eacute;v&egrave;nements.
     * \param eventHandler Le notifieur d'&eacute;v&egrave;nements.
     */
    virtual void addEventHandler(IEventHandler* eventHandler)
    {
        mEventHandlers.push_back(eventHandler);
    }

    /**
     * \fn virtual void notifyEventHandlers(IEvent* e)
     * \brief Fonction de notification des gestionnaires d'&eacute;v&egrave;nements.
     * \param e L'&eacute;v&egrave;nement &agrave; notifier.
     */
    virtual void notifyEventHandlers(IEvent* e)
    {
        for(unsigned int i = 0; i < mEventHandlers.size(); i++)
        {
            mEventHandlers[i]->handle(e);
        }
    }

private:
    vector<IEventHandler*> mEventHandlers;
};

}}};