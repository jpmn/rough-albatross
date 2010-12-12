/**
 * \file IEvent.h
 * \brief Interface offrant les signatures de fonction d'un &eacute;v&egrave;nement.
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 * \version 1.0
 *
 * Interface qui offre les signatures de base pour un &eacute;v&egrave;nement de l'application.
 *
 */

#pragma once

namespace baluchon { namespace core { namespace events {

class IEventNotifier;

class IEvent
{
public:

    /**
     * \fn virtual ~IEvent()
     * \brief Destructeur virtuel de la classe.
     */
    virtual ~IEvent() {};

    /**
     * \fn virtual int getState()
     * \brief Fonction qui retourne l'&eacute;tat de l'&eacute;v&egrave;nement.
     * \return mState L'&eacute;tat de l'&eacute;v&egrave;nement.
     */
    virtual int getState()
    {
        return mState;
    }

    /**
     * \fn virtual void setEventNotifier(IEventNotifier* eventNotifier)
     * \param eventNotifier Le notifieur &agrave; associer &agrave; l'&eacute;v&egrave;nement.
     * \brief Fonction qui retourne l'&eacute;tat de l'&eacute;v&egrave;nement.
     * \return mState L'&eacute;tat de l'&eacute;v&egrave;nement.
     */
    virtual void setEventNotifier(IEventNotifier* eventNotifier)
    {
        mEventNotifier = eventNotifier;
    }

    /**
     * \fn virtual IEventNotifier* getEventNotifier()
     * \brief Fonction qui retourne le notifieur de l'&eacute;v&egrave;nement.
     * \return mEventNotifier Le notifieur de l'&eacute;v&egrave;nement.
     */
    virtual IEventNotifier* getEventNotifier()
    {
        return mEventNotifier;
    }

protected:
    int mState;
    IEventNotifier* mEventNotifier;
};

}}};
