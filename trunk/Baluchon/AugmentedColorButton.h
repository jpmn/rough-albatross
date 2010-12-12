/**
 * \file AugmentedColorButton.h
 * \brief Bouton activ&eacute; par un marqueur de couleur.
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 * \version 1.0
 *
 * Contr&ocirc;le de bouton de l'interface augment&eactuge;e qui est activ&eacute; par un marqueur de couleur.
 *
 */

#pragma once
#include "iaugmentedcomponent.h"
#include "icolordetectionservice.h"

using namespace baluchon::core::services::colordetection;

namespace baluchon { namespace core { namespace services { namespace augmentedinterface {

class AugmentedColorButton :
    public IAugmentedComponent
{
public:

    /**
     * \fn AugmentedColorButton(IColorDetectionService* colorDetectionService, CvPoint pos, int width, int height)
     * \brief Constructeur de la classe.
     * \param colorDetectionService Service de d&eacute;tection de couleurs.
     * \param pos Position du bouton.
     * \param width Largeur du bouton.
     * \param height Hauteur du bouton.
     */
    AugmentedColorButton(IColorDetectionService* colorDetectionService, CvPoint pos, int width, int height);

    /**
     * \fn ~AugmentedColorButton(void)
     * \brief Destructeur de la classe.
     */
    ~AugmentedColorButton(void);

    /**
     * \fn void execute()
     * \brief Fonction d'ex&eacute;cution.
     */
    void execute();

    /**
     * \fn void execute()
     * \brief Fonction d'affichage du contr&ocirc;le.
     * \param img L'image dans laquelle le contr&ocirc;le est affich&eacute;.
     */
    void draw(IplImage* img);

private:
    IColorDetectionService* mColorDetectionService;
    bool mHover;
    int mCpt;
};

}}}};