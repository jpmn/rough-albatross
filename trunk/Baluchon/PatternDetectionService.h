/**
 * \file PatternDetectionService.h
 * \brief Classe qui offre les fonctionalit&eacute;s du service de d&eacute;tection de patrons.
 * \author Mathieu Plourde
 * \author Jean-Philippe Morin
 * \version 1.0
 *
 * Classe qui offre les fonctionalit&eacute;s du service de d&eacute;tection de patrons.
 *
 */

#pragma once
#include "ipatterndetectionservice.h"
#include "ICaptureService.h"
#include <vector>

using namespace std;
using namespace baluchon::core::services::capture;

namespace baluchon { namespace core { namespace services { namespace patterndetection { 

class PatternDetectionService :
    public IPatternDetectionService
{
public:

    /**
     * \fn PatternDetectionService(void)
     * \brief Constructeur de la classe.
     */
    PatternDetectionService(void);

    /**
     * \fn ~PatternDetectionService(void)
     * \brief Destructeur de la classe.
     */
    ~PatternDetectionService(void);

    /**
     * \fn void addPattern(IPattern* pattern)
     * \brief M&eacute;thode d'ajout d'un patron.
     * \param pattern Le patron &agrave; ajouter.
     */
    void addPattern(IPattern* pattern);

    /**
     * \fn IPattern* addPattern(char patternName[])
     * \brief M&eacute;thode d'ajout d'un patron.
     * \param patternName Le chemin du patron &agrave; ajouter.
     * \return L'instance du patron ajout&eacute;.
     */
    IPattern* addPattern(char patternName[]);

    /**
     * \fn vector<IDetectedPattern*> getPatterns()
     * \brief M&eacute;thode qui retourne les patrons.
     * \return Le vecteur des patrons.
     */
    vector<IDetectedPattern*> getPatterns();

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
    ICaptureService* mCaptureService;
    vector<IDetectedPattern*> mPatterns;


    IplImage *mInitial;
    IplImage* mFrame;
    CvMemStorage* mStorage;
    CvSeq* mContours;
    CvSeq* mChildContours;
    CvPoint2D32f mImagePoints[4];
    CvPoint2D32f mModelPoints[4];

    CvSeq* mResult;
    CvMat* mMat;
    CvMat* mSrcPts;
    CvMat* mDstPts;
};

}}}};