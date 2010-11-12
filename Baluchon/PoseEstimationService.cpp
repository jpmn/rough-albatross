#include "PoseEstimationService.h"
#include "PatternDetectionService.h"
#include "IServiceLayer.h"
#include "IPattern.h"

namespace baluchon { namespace core { namespace services { namespace poseestimation { 

PoseEstimationService::PoseEstimationService(void)
{
}


PoseEstimationService::~PoseEstimationService(void)
{
}

void PoseEstimationService::init(void) {
    mPatternDetectionService= new PatternDetectionService();
    mPatternDetectionService = (IPatternDetectionService*) mServiceLayer->findService(mPatternDetectionService);
}

void PoseEstimationService::initDone(void) {

}

void PoseEstimationService::execute(void) {
    /*vector<IPattern*> patterns = mPatternDetectionService->getPatterns();
    vector<CvPoint2D32f> imagePoints;
    for(int i = 0; i < patterns.size(); i++)
    {
        CvPoint3D32f *modelPoints = (CvPoint3D32f *) malloc(patterns[i]->getPointCount()*sizeof(CvPoint3D32f));

        for(int j = 0; j < patterns[i]->getImagePoints()->size(); j++)
        {
            imagePoints.clear();

            for(int k = 0; k < patterns[i]->getPointCount(); k++)
            {
                modelPoints[k] = cvPoint3D32f(patterns[i]->getSourcePointAt(k, (*patterns[i]->getImageOrientations())[j]).x, patterns[i]->getSourcePointAt(k, (*patterns[i]->getImageOrientations())[j]).y, ((k == 0) ? 1.0f : 0.0f));
            }

            imagePoints = (*patterns[i]->getImagePoints())[j];

            CvPOSITObject *positObject = cvCreatePOSITObject(modelPoints, patterns[i]->getPointCount());

            CvMatr32f rotation_matrix = new float[9];
            CvVect32f translation_vector = new float[3];
            CvTermCriteria criteria = cvTermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 100, 1.0e-4f);
            cvPOSIT( positObject, &imagePoints[0], 760, criteria, rotation_matrix, translation_vector);

            printf("\coords: ");
            for(int k = 0; k < patterns[i]->getPointCount(); k++)
            {
                printf("[%f %f] [%f %f]\n", modelPoints[k].x, modelPoints[k].y, imagePoints[k].x, imagePoints[k].y);
            }

            printf("\nrotation: ");
            for(int k = 0; k < 9; k++)
            {
                printf("%f ", rotation_matrix[k]);
            }

            printf("\ntranslation: ");
            for(int k = 0; k < 3; k++)
            {
                printf("%f ", translation_vector[k]);
            }

            cvReleasePOSITObject(&positObject);
            
            delete rotation_matrix;
            delete translation_vector;
        }

        free(modelPoints);
    }*/
}

void PoseEstimationService::reset(void) {

}

void PoseEstimationService::dispose(void) {
}

}}}};