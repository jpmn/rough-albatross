/**
 * \file IPositioningService.h
 * \brief Interface qui offre les signatures de fonctions pour le service de positionnement 3D.
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 * \version 1.0
 *
 * Interface qui offre les signatures de fonctions pour le service de positionnement 3D.
 *
 */

#pragma once
#include "iservice.h"
#include "ipattern.h"
#include "igraphic.h"

using namespace baluchon::core::services::patterndetection;

namespace baluchon { namespace core { namespace services { namespace positioning { 

class IPositioningService :
    public IService
{
public:

    /**
     * \fn virtual ~IPositioningService(void)
     * \brief Destructeur virtuel de la classe.
     */
    virtual ~IPositioningService(void) {};

    /**
     * \fn virtual void addSceneGraph(IPattern *pattern, IGraphic *root)
     * \brief M&eacute;thode qui ajoute un graphe de sc&egrave;ne &agrave; un patron.
     */
    virtual void addSceneGraph(IPattern *pattern, IGraphic *root) = 0;
};

}}}};
