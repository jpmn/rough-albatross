/**
 * \file Translation.h
 * \brief Classe qui offre les fonctionnalit&eacute;s pour une transformation de type translation.
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 * \version 1.0
 *
 * Classe qui offre les fonctionnalit&eacute;s pour une transformation de type translation.
 *
 */

#pragma once

#include "Transform.h"

namespace baluchon { namespace core { namespace services { namespace positioning { 

class Translation : public Transform
{
public:

    /**
     * \fn Translation(CvPoint3D32f vector)
     * \brief Constructeur de la classe.
     * \param factors Le vecteur de translation.
     */
    Translation(CvPoint3D32f vector);

    /**
     * \fn ~Translation(void)
     * \brief Destructeur de la classe.
     */
    ~Translation(void);
};

}}}};
