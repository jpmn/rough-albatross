/**
 * \file IPositioningService.h
 * \brief Classe qui offre les fonctionnalit&eacute;s pour le service de positionnement 3D.
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 * \version 1.0
 *
 * Classe qui offre les fonctionnalit&eacute;s pour le service de positionnement 3D.
 *
 */

#pragma once
#include "ipositioningservice.h"
#include "IPoseEstimationService.h"
#include "IPoseEstimatedPattern.h"
#include "IObjectDetectionService.h"
#include "ICaptureService.h"
#include "PositioningVisitor.h"
#include <vector>
#include <map>

using namespace baluchon::core::services::objectdetection;
using namespace baluchon::core::services::poseestimation;
using namespace baluchon::core::services::capture;

namespace baluchon { namespace core { namespace services { namespace positioning { 

class PositioningService :
    public IPositioningService
{
public:

    /**
     * \fn PositioningService(char* intrinsicPath, char* distortionPath)
     * \brief Constructeur de la classe.
     * \param intrinsicPath Le chemin des param&egrave;tres intrins&egrave;ques de la cam&eacute;ra.
     * \param distortionPath Le chemin des param&egrave;tres de distortion de la cam&eacute;ra.
     */
    PositioningService(char* intrinsicPath, char* distortionPath);

    /**
     * \fn ~PositioningService(void)
     * \brief Destructeur de la classe.
     */
    ~PositioningService(void);

    /**
     * \fn void addSceneGraph(IPattern *pattern, IGraphic *root)
     * \brief M&eacute;thode qui ajoute un graphe de sc&egrave;ne &agrave; un patron.
     */
    void addSceneGraph(IPattern *pattern, IGraphic *root);

    /**
     * \fn virtual void init(void)
     * \brief Fonction d'initialisation.
     */
    virtual void init(void);

    /**
     * \fn virtual void initDone(void)
     * \brief Fonction de fin d'initialisation.
     */
	virtual void initDone(void);

    /**
     * \fn virtual void execute(void)
     * \brief Fonction d'ex&eacute;cution.
     */
	virtual void execute(void);

    /**
     * \fn virtual void reset(void)
     * \brief Fonction de r&eacute;initialisation.
     */
	virtual void reset(void);

    /**
     * \fn virtual void dispose(void)
     * \brief Fonction de nettoyage.
     */
	virtual void dispose(void);

private:
    IPoseEstimationService* mPoseEstimationService;
	IObjectDetectionService* mObjectDetectionService;
    ICaptureService* mCaptureService;
    PositioningVisitor* mVisitor;
    char* mIntrinsicPath;
    char* mDistortionPath;
    map<IPattern*, IGraphic*> mInitialSceneGraphs;
    map<IPoseEstimatedPattern*, IGraphic*> mSceneGraphs;
};

}}}};
