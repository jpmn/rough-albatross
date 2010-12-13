/**
 * \file Scaling.h
 * \brief Classe qui offre les fonctionnalit&eacute;s pour une transformation de type mise &agrave l'&eacute;chelle.
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 * \version 1.0
 *
 * Classe qui offre les fonctionnalit&eacute;s pour une transformation de type mise &agrave l'&eacute;chelle.
 *
 */

#pragma once
#include "transform.h"

namespace baluchon { namespace core { namespace services { namespace positioning { 

class Scaling :
    public Transform
{
public:

    /**
     * \fn Scaling(CvPoint3D32f factors)
     * \brief Constructeur de la classe.
     * \param factors Les facteurs de mise &agrave; l'&eacute;chelle.
     */
    Scaling(CvPoint3D32f factors);

    /**
     * \fn ~Scaling(void)
     * \brief Destructeur de la classe.
     */
    ~Scaling(void);
};

}}}};
