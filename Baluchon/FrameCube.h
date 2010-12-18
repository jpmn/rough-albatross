/**
 * \file FrameCube.h
 * \brief Classe qui offre les fonctionnalit&eacute;s pour un squelette de cube.
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 * \version 1.0
 *
 * Classe qui offre les fonctionnalit&eacute;s pour un squelette de cube.
 *
 */

#pragma once

#include "IGraphic.h"
#include "IVisitor.h"
#include "IColorable.h"
#include "IAnimable.h"

using namespace baluchon::core::datas;
using namespace baluchon::core::datas::animation;

namespace baluchon { namespace core { namespace services { namespace positioning { 

class FrameCube : public IGraphic, public IColorable, public IAnimable
{
public:

    /**
     * \fn FrameCube(CvPoint3D32f pt1, float size, CvScalar color)
     * \brief Constructeur de la classe.
     * \param pt1 Le point de r&eacute;f&eacute;rence du cube.
     * \param size La taille d'un c&ocirc;t&eacute; du cube.
     * \param color La couleur du cube.
     */
    FrameCube(CvPoint3D32f pt1, float size, CvScalar color);

    /**
     * \fn ~FrameCube(void)
     * \brief Destructeur de la classe.
     */
    ~FrameCube(void);

    /**
     * \fn void accept(IVisitor* v)
     * \brief Fonction d'acceptation d'un visiteur.
     * \param v Le visiteur.
     */
    void accept(IVisitor* v);
};

}}}};
