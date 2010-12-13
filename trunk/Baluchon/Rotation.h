/**
 * \file Rotation.h
 * \brief Classe qui offre les fonctionnalit&eacute;s pour une transformation de type rotation.
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 * \version 1.0
 *
 * Classe qui offre les fonctionnalit&eacute;s pour une transformation de type rotation.
 *
 */

#pragma once
#include "transform.h"

namespace baluchon { namespace core { namespace services { namespace positioning { 

class Rotation :
    public Transform
{
public:

    /**
     * \fn Rotation(float angle, CvPoint3D32f axis)
     * \brief Constructeur de la classe.
     * \param angle L'angle de la rotation.
     * \param axis L'axe de rotation.
     */
    Rotation(float angle, CvPoint3D32f axis);

    /**
     * \fn ~Rotation(void)
     * \brief Destructeur de la classe.
     */
    ~Rotation(void);
};

}}}};
