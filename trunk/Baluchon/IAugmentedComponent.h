/**
 * \file IAugmentedComponent.h
 * \brief Interface qui offre les signatures pour un composant de l'interface augment&eacute;e..
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 * \version 1.0
 *
 * Interface offrant les signatures de fonctions pour les composants de l'interface utilisateur augment&eacute;e.
 *
 */

#pragma once
#include "ieventnotifier.h"
#include "cv.h"

using namespace baluchon::core::events;

namespace baluchon { namespace core { namespace services { namespace augmentedinterface {

class IAugmentedComponent :
    public IEventNotifier
{
public:

    /**
     * \fn ~IAugmentedComponent(void)
     * \brief Destructeur de la classe.
     */
    ~IAugmentedComponent(void) {};

    /**
     * \fn virtual void execute()
     * \brief Fonction d'ex&eacute;cution.
     */
    virtual void execute() {};

    /**
     * \fn virtual void draw(IplImage* img)
     * \brief Fonction d'affichage.
     * \param img L'image dans laquelle le contr&ocirc;le est affich&eacute;.
     */
    virtual void draw(IplImage* img) = 0;

    /**
     * \fn void setPosition(CvPoint pos)
     * \brief Fonction qui intialise la position du contr&ocirc;le.
     * \param pos La position du contr&ocirc;le.
     */
    void setPosition(CvPoint pos)
    {
        mPos = pos;
    }

    /**
     * \fn CvPoint getPosition()
     * \brief Fonction qui retourne la position du contr&ocirc;le.
     * \return mPos La position du contr&ocirc;le.
     */
    CvPoint getPosition()
    {
        return mPos;
    }

    /**
     * \fn void setSize(int width, int height)
     * \brief Fonction qui intialise la taille du contr&ocirc;le.
     * \param width La largeur du contr&ocirc;le.
     * \param height La hauteur du contr&ocirc;le.
     */
    void setSize(int width, int height)
    {
        mWidth = width;
        mHeight = height;
    }

    /**
     * \fn int getWidth()
     * \brief Fonction qui retourne la largeur du contr&ocirc;le.
     * \return mWidth La largeur du contr&ocirc;le.
     */
    int getWidth()
    {
        return mWidth;
    }

    /**
     * \fn int getHeight()
     * \brief Fonction qui retourne la hauteur du contr&ocirc;le.
     * \return mHeight La hauteur du contr&ocirc;le.
     */
    int getHeight()
    {
        return mHeight;
    }

protected:
    CvPoint mPos;
    int mWidth;
    int mHeight;
};

}}}};