/**
 * \file Transform.h
 * \brief Classe qui offre les fonctionnalit&eacute;s pour une transformation.
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 * \version 1.0
 *
 * Classe qui offre les fonctionnalit&eacute;s pour une transformation.
 *
 */

#pragma once
#include "ivisitor.h"
#include "igraphic.h"

namespace baluchon { namespace core { namespace services { namespace positioning {

class Transform :
    public IGraphic
{
public:

    /**
     * \fn Transform(void)
     * \brief Constructeur de la classe.
     */
    Transform(void);

    /**
     * \fn ~Transform(void)
     * \brief Destructeur de la classe.
     */
    ~Transform(void);

    /**
     * \fn virtual void add(IGraphic* child)
     * \brief Fonction d'ajout d'un graphique enfant.
     * \param child L'enfant &agrave; ajouter.
     */
    virtual void add(IGraphic* child);

    /**
     * \fn virtual void remove(IGraphic* child)
     * \brief Fonction de retrait d'un graphique enfant.
     * \param child L'enfant &agrave; ajouter.
     */
    virtual void remove(IGraphic* child);

    /**
     * \fn virtual vector<IGraphic*> getChildren()
     * \brief Retourne les enfants de la transformation.
     * \return Les enfants de la transformation.
     */
    virtual vector<IGraphic*> getChildren();

    /**
     * \fn virtual void apply(CvMat* mul)
     * \brief Fonction qui applique une matrice &agrave; la transformation.
     * \param mul Matrice &agrave; multiplier.
     */
    virtual void apply(CvMat* mul);

    /**
     * \fn virtual CvMat* getMatrix()
     * \brief Retourne la matrice de transformation.
     * \return La matrice de transformation.
     */
    virtual CvMat* getMatrix();

    /**
     * \fn virtual void setMatrix(CvMat* matrix)
     * \brief Initialise la matrice de transformation.
     * \param matrix La matrice de transformation.
     */
    virtual void setMatrix(CvMat* matrix);

    /**
     * \fn virtual void accept(IVisitor* v)
     * \brief Fonction d'acceptation d'un visiteur.
     * \param v Le visiteur.
     */
    virtual void accept(IVisitor* v);

    /**
     * \fn virtual void reset()
     * \brief Fonction qui r&eacute;initialise les points de l'objet graphique.
     */
    virtual void reset();

protected:
    vector<IGraphic*> mChildren;
    CvMat* mMat;
    CvMat* mTransformedMat;
};

}}}};
