/**
 * \file IVisitor.h
 * \brief Interface qui offre les signatures de fonctions pour un visiteur.
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 * \version 1.0
 *
 * Interface qui offre les signatures de fonctions pour un visiteur.
 *
 */

#pragma once

namespace baluchon { namespace core { namespace services { namespace positioning { 

class Transform;
class FrameCube;
class FrameBox;

class IVisitor
{
public:

    /**
     * \fn virtual ~IVisitor(void)
     * \brief Destructeur virtuel de la classe.
     */
    virtual ~IVisitor(void) {};

    /**
     * \fn virtual void visit(Transform *t)
     * \brief Fonction de visite d'une transformation.
     * \param t La transformation &agrave; visiter.
     */
    virtual void visit(Transform *t) = 0;

    /**
     * \fn virtual void visit(FrameCube *fc)
     * \brief Fonction de visite d'un squelette de cube.
     * \param t Le cube &agrave; visiter.
     */
    virtual void visit(FrameCube *fc) = 0;
	virtual void visit(FrameBox *fb) = 0;
};

}}}};
