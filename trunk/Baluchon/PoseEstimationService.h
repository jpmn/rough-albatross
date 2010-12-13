/**
 * \file PoseEstimationService.h
 * \brief Classe qui offre les signatures de fonctions pour le service d'estimation de la position et de l'orientation de patrons.
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 * \version 1.0
 *
 * Classe qui offre les signatures de fonctions pour le service d'estimation de la position et de l'orientation de patrons.
 *
 */

#pragma once
#include "iposeestimationservice.h"
#include "IPatternDetectionService.h"
#include "ICaptureService.h"
#include "IPoseEstimatedPattern.h"
#include <vector>

using namespace baluchon::core::services::patterndetection;
using namespace baluchon::core::services::capture;

namespace baluchon { namespace core { namespace services { namespace poseestimation { 

class PoseEstimationService :
    public IPoseEstimationService
{
public:

    /**
     * \fn PoseEstimationService(char* intrisicPath, char* distortionPath)
     * \brief Constructeur de la classe.
     * \param intrinsicPath Le chemin des param&egrave;tres intrins&egrave;ques de la cam&eacute;ra.
     * \param distortionPath Le chemin des param&egrave;tres de distortion de la cam&eacute;ra.
     */
    PoseEstimationService(char* intrisicPath, char* distortionPath);

    /**
     * \fn ~PoseEstimationService(void)
     * \brief Destructeur de la classe.
     */
    ~PoseEstimationService(void);

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

    /**
     * \fn vector<IPoseEstimatedPattern*> getPatterns()
     * \brief Retourne les patrons dont l'orientation et la position sont estim&eacute;es.
     * \return Les patrons dont l'orientation et la position sont estim&eacute;es.
     */
    vector<IPoseEstimatedPattern*> getPatterns();

private:
    vector<IPoseEstimatedPattern*> mPatterns;
    IPatternDetectionService* mPatternDetectionService;
    ICaptureService* mCaptureService;
    CvMat* mIntrinsic;
	CvMat* mDistortion;
    char* mIntrinsicPath;
    char* mDistortionPath;
};

}}}};