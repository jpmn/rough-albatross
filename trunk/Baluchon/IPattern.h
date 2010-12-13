/**
 * \file IPattern.h
 * \brief Interface qui offre les fonctionnalit&eacute;s d'un patron.
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 * \version 1.0
 *
 * Interface qui offre les fonctionnalit&eacute;s d'un patron.
 *
 */

#pragma once

#include "cv.h"
#include "highgui.h"
#include <vector>

using namespace std;

namespace baluchon { namespace core { namespace services { namespace patterndetection { 

class IPattern
{
public:

    /**
     * \fn ~IPattern(void)
     * \brief Destructeur virtuel de la classe.
     */
    virtual ~IPattern(void) {};

    /**
     * \fn virtual int getWidth()
     * \brief Retourne la largeur du patron.
     * \return La largeur du patron.
     */
    virtual int getWidth() = 0;

    /**
     * \fn virtual int getHeight()
     * \brief Retourne la hauteur du patron.
     * \return La hauteur du patron.
     */
    virtual int getHeight() = 0;

    /**
     * \fn virtual int getPointCount()
     * \brief Retourne le nombre de points du patron.
     * \return Le nombre de points du patron.
     */
    virtual int getPointCount() = 0;

    /**
     * \fn virtual CvPoint2D32f getSourcePointAt(int pos, int orientation = 0)
     * \brief Retourne un point dans l'une des quatres orientations.
     * \param pos La position du point.
     * \param orientation L'orientation du point.
     * \return Le point d&eacute;sir&eacute;.
     */
    virtual CvPoint2D32f getSourcePointAt(int pos, int orientation = 0) = 0;

};

}}}};