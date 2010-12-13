/**
 * \file Pattern.h
 * \brief Classe qui offre les fonctionnalit&eacute;s d'un patron.
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 * \version 1.0
 *
 * Classe qui offre les fonctionnalit&eacute;s d'un patron.
 *
 */

#pragma once
#include "ipattern.h"

namespace baluchon { namespace core { namespace services { namespace patterndetection { 

class Pattern :
    public IPattern
{
public:

    /**
     * \fn Pattern(char path[])
     * \brief Constructeur de la classe.
     * \param path Le chemin du fichier qui repr&eacute;sente le patron.
     */
    Pattern(char path[]);

    /**
     * \fn ~Pattern(void)
     * \brief Destructeur de la classe.
     */
    ~Pattern(void);

    /**
     * \fn int getWidth()
     * \brief Retourne la largeur du patron.
     * \return La largeur du patron.
     */
    int getWidth();

    /**
     * \fn int getHeight()
     * \brief Retourne la hauteur du patron.
     * \return La hauteur du patron.
     */
    int getHeight();

    /**
     * \fn int getPointCount()
     * \brief Retourne le nombre de points du patron.
     * \return Le nombre de points du patron.
     */
    int getPointCount();

    /**
     * \fn CvPoint2D32f getSourcePointAt(int pos, int orientation = 0)
     * \brief Retourne un point dans l'une des quatres orientations.
     * \param pos La position du point.
     * \param orientation L'orientation du point.
     * \return Le point d&eacute;sir&eacute;.
     */
    CvPoint2D32f getSourcePointAt(int pos, int orientation = 0);

private:
    /**
     * \fn void init()
     * \brief Fonction priv&eacute;e d'initialisation du patron.
     */
    void init();

    int mWidth;
    int mHeight;
    int mPointCount;
    char* mPath;
    CvPoint2D32f (*mSrcPoints)[4];
};

}}}};