#include "BoxDetector.h"

#include "MathUtility.h"

using namespace baluchon::utilities;

namespace baluchon { namespace core { namespace services { namespace objectdetection {

BoxDetector::BoxDetector(void) {
	mPrismFactory = new PrismFactory();
	mRectangleDetector = new RectangleDetector();
}

BoxDetector::~BoxDetector(void) {
	delete mPrismFactory;
	delete mRectangleDetector;
}

vector<IDetectable*> BoxDetector::find(IplImage* img, IplImage* src) {
	vector<BoxPrism*> mListBoxes;
	vector<IDetectable*> wListDetectableFacets = mRectangleDetector->find(img, src);

	vector<RectangularFacet*> mListFacets;//(wListDetectableFacets.begin(), wListDetectableFacets.end())

	for (unsigned int i = 0; i < wListDetectableFacets.size(); i++) {
		mListFacets.push_back(static_cast<RectangularFacet*>(wListDetectableFacets[i]));
	}

	if (mListFacets.size() >= 3) {
		// Trouver 3 faces avec un sommet commun
		for (unsigned int i = 0; i < mListFacets.size(); i++) {
			RectangularFacet* facet1 = mListFacets[i];

			for (unsigned int j = 0; j < mListFacets.size(); j++) {
				RectangularFacet* facet2 = mListFacets[j];

				for (unsigned int k = 0; k < mListFacets.size(); k++) {
					RectangularFacet* facet3 = mListFacets[k];

					if (facet1 != facet2 && facet2 != facet3 && facet3 != facet1) {
						CvPoint dpt = MathUtility::middle(facet1->getTopRightVertex(), facet2->getTopLeftVertex());

						if (facet3->getTopRightVertex().x < facet3->getBottomRightVertex().x)
							dpt = MathUtility::middle(dpt, facet3->getBottomLeftVertex());
						else 
							dpt = MathUtility::middle(dpt, facet3->getBottomRightVertex());

						double dt1 = MathUtility::sqrtdistance(facet1->getTopRightVertex(), dpt);
						double dt2 = MathUtility::sqrtdistance(facet2->getTopLeftVertex(), dpt);
						double dt3;
						
						if (facet3->getTopRightVertex().x < facet3->getBottomRightVertex().x)
							dt3 = MathUtility::sqrtdistance(facet3->getBottomLeftVertex(), dpt);
						else 
							dt3 = MathUtility::sqrtdistance(facet3->getBottomRightVertex(), dpt);

						if (dt1 < mDistanceTolerance && dt2 < mDistanceTolerance && dt3 < mDistanceTolerance) {
							
							BoxPrism* wBoxPrism = mPrismFactory->createBoxPrism(facet1, facet2, facet3);

							mListBoxes.push_back(wBoxPrism);

							// TODO : supprimer les faces utilisées.
						}
					}
				}
			}
		}
	}

	vector<IDetectable*> wListDetectables(mListBoxes.begin(), mListBoxes.end());

	return wListDetectables;
}

void BoxDetector::setDistanceTolerance(double distanceTolerance) {
	mDistanceTolerance = distanceTolerance;
}

}}}};