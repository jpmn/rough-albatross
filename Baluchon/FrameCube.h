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
#include "igraphic.h"
#include "ivisitor.h"

namespace baluchon { namespace core { namespace services { namespace positioning { 

class FrameCube :
    public IGraphic
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

    /**
     * \fn void setColor(CvScalar color)
     * \brief Fonction qui initialise la couleur du cube.
     * \param color La couleur du cube.
     */
    void setColor(CvScalar color);

    /**
     * \fn CvScalar getColor()
     * \brief Fonction qui retourne la couleur du cube.
     * \return La couleur du cube.
     */
    CvScalar getColor();

private:
    CvScalar mColor;
};

}}}};
