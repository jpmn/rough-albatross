/**
 * \file ColorButtonEvent.h
 * \brief Classe repr&eacute;sentant l'&eacute;v&egrave;nement d'un bouton de couleur.
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 * \version 1.0
 *
 * Classe qui offre les fonctionnalit&eacute;s reli&eacute;es &agrave; un &eacute;v&egrave;nement d'un bouton de couleur.
 *
 */

#pragma once
#include "ievent.h"

using namespace baluchon::core::events;

namespace baluchon { namespace core { namespace services { namespace augmentedinterface {

class ColorButtonEvent :
    public IEvent
{
public:

    /**
     * \fn ColorButtonEvent(void)
     * \brief Constructeur de la classe.
     */
    ColorButtonEvent(void);

    /**
     * \fn ~ColorButtonEvent(void)
     * \brief Destructeur de la classe.
     */
    ~ColorButtonEvent(void);
};

}}}};