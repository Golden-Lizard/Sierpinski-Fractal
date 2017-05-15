// (C) Copyright 2002-2007 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- SierpinskiTriangle.cpp : Implementation of SierpinskiTriangle
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "SierpinskiTriangle.h"

//-----------------------------------------------------------------------------
Adesk::UInt32 SierpinskiTriangle::kCurrentVersionNumber =1 ;

//-----------------------------------------------------------------------------
ACRX_DXF_DEFINE_MEMBERS (
	SierpinskiTriangle, AcDbEntity,
	AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
	AcDbProxyEntity::kNoOperation, SIERPINSKITRIANGLE,
LZRDDIAGRAMAPP
|Product Desc:     A description for your object
|Company:          Your company name
|WEB Address:      Your company WEB site address
)

//-----------------------------------------------------------------------------
SierpinskiTriangle::SierpinskiTriangle () : AcDbEntity () {
}

SierpinskiTriangle::SierpinskiTriangle(AcGePoint2d const & p1, AcGePoint2d const & p2, AcGePoint2d const & p3, Adesk::UInt32 const & iterations) : 
	AcDbEntity(),
	triangle {p1, p2, p3},
	samples(iterations)
{
}

SierpinskiTriangle::~SierpinskiTriangle () {
}

//-----------------------------------------------------------------------------
//----- AcDbObject protocols
//- Dwg Filing protocol
Acad::ErrorStatus SierpinskiTriangle::dwgOutFields (AcDbDwgFiler *pFiler) const {
	assertReadEnabled () ;
	//----- Save parent class information first.
	Acad::ErrorStatus es =AcDbEntity::dwgOutFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be saved first
	if ( (es =pFiler->writeUInt32 (SierpinskiTriangle::kCurrentVersionNumber)) != Acad::eOk )
		return (es) ;
	//----- Output params
	//.....

	return (pFiler->filerStatus ()) ;
}

Acad::ErrorStatus SierpinskiTriangle::dwgInFields (AcDbDwgFiler *pFiler) {
	assertWriteEnabled () ;
	//----- Read parent class information first.
	Acad::ErrorStatus es =AcDbEntity::dwgInFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be read first
	Adesk::UInt32 version =0 ;
	if ( (es =pFiler->readUInt32 (&version)) != Acad::eOk )
		return (es) ;
	if ( version > SierpinskiTriangle::kCurrentVersionNumber )
		return (Acad::eMakeMeProxy) ;
	//- Uncomment the 2 following lines if your current object implementation cannot
	//- support previous version of that object.
	//if ( version < SierpinskiTriangle::kCurrentVersionNumber )
	//	return (Acad::eMakeMeProxy) ;
	//----- Read params
	//.....

	return (pFiler->filerStatus ()) ;
}

//- Dxf Filing protocol
Acad::ErrorStatus SierpinskiTriangle::dxfOutFields (AcDbDxfFiler *pFiler) const {
	assertReadEnabled () ;
	//----- Save parent class information first.
	Acad::ErrorStatus es =AcDbEntity::dxfOutFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	es =pFiler->writeItem (AcDb::kDxfSubclass, _RXST("SierpinskiTriangle")) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be saved first
	if ( (es =pFiler->writeUInt32 (kDxfInt32, SierpinskiTriangle::kCurrentVersionNumber)) != Acad::eOk )
		return (es) ;
	//----- Output params
	//.....

	return (pFiler->filerStatus ()) ;
}

Acad::ErrorStatus SierpinskiTriangle::dxfInFields (AcDbDxfFiler *pFiler) {
	assertWriteEnabled () ;
	//----- Read parent class information first.
	Acad::ErrorStatus es =AcDbEntity::dxfInFields (pFiler) ;
	if ( es != Acad::eOk || !pFiler->atSubclassData (_RXST("SierpinskiTriangle")) )
		return (pFiler->filerStatus ()) ;
	//----- Object version number needs to be read first
	struct resbuf rb ;
	pFiler->readItem (&rb) ;
	if ( rb.restype != AcDb::kDxfInt32 ) {
		pFiler->pushBackItem () ;
		pFiler->setError (Acad::eInvalidDxfCode, _RXST("\nError: expected group code %d (version #)"), AcDb::kDxfInt32) ;
		return (pFiler->filerStatus ()) ;
	}
	Adesk::UInt32 version =(Adesk::UInt32)rb.resval.rlong ;
	if ( version > SierpinskiTriangle::kCurrentVersionNumber )
		return (Acad::eMakeMeProxy) ;
	//- Uncomment the 2 following lines if your current object implementation cannot
	//- support previous version of that object.
	//if ( version < SierpinskiTriangle::kCurrentVersionNumber )
	//	return (Acad::eMakeMeProxy) ;
	//----- Read params in non order dependant manner
	while ( es == Acad::eOk && (es =pFiler->readResBuf (&rb)) == Acad::eOk ) {
		switch ( rb.restype ) {
			//----- Read params by looking at their DXF code (example below)
			//case AcDb::kDxfXCoord:
			//	if ( version == 1 )
			//		cen3d =asPnt3d (rb.resval.rpoint) ;
			//	else 
			//		cen2d =asPnt2d (rb.resval.rpoint) ;
			//	break ;
			//.....
			case 1:
			default:
				//----- An unrecognized group. Push it back so that the subclass can read it again.
				pFiler->pushBackItem () ;
				es =Acad::eEndOfFile ;
				break ;
		}
	}
	//----- At this point the es variable must contain eEndOfFile
	//----- - either from readResBuf() or from pushback. If not,
	//----- it indicates that an error happened and we should
	//----- return immediately.
	if ( es != Acad::eEndOfFile )
		return (Acad::eInvalidResBuf) ;

	return (pFiler->filerStatus ()) ;
}

std::pair<double, double> SierpinskiTriangle::getXbds()
{
	double pts_x[] = { triangle[0].x, triangle[1].x, triangle[2].x};
	std::sort(pts_x, pts_x + sizeof(pts_x)/sizeof(pts_x[0]));

	return std::make_pair(pts_x[0], pts_x[2]);
}

std::pair<double, double> SierpinskiTriangle::getYbds()
{
	double pts_y[] = { triangle[0].y, triangle[1].y, triangle[2].y };
	std::sort(pts_y, pts_y + sizeof(pts_y) / sizeof(pts_y[0]));

	return std::make_pair(pts_y[0], pts_y[2]);
}


bool SierpinskiTriangle::isInside(AcGePoint2d const & point)
{
	double alpha = ((triangle[1].y - triangle[2].y)*(point.x - triangle[2].x) + (triangle[2].x - triangle[1].x)*(point.y - triangle[2].y)) /
		((triangle[1].y - triangle[2].y)*(triangle[0].x - triangle[2].x) + (triangle[2].x - triangle[1].x)*(triangle[0].y - triangle[2].y));

	double beta = ((triangle[2].y - triangle[0].y)*(point.x - triangle[2].x) + (triangle[0].x - triangle[2].x)*(point.y - triangle[2].y)) /
		((triangle[1].y - triangle[2].y)*(triangle[0].x - triangle[2].x) + (triangle[2].x - triangle[1].x)*(triangle[0].y - triangle[2].y));

	double gamma = 1.0f - alpha - beta;

	if (gamma > 0.0 && beta > 0.0 && alpha > 0.0)
		return true;
	else
		return false;
}

AcGePoint2d SierpinskiTriangle::getRandomPoint()
{
	std::random_device random;
	
	return AcGePoint2d(random()%(int(x_bounds.second-x_bounds.first-1))+x_bounds.first, 
		               random()%(int(y_bounds.second-y_bounds.first-1))+y_bounds.first);
}

double SierpinskiTriangle::getDistance(AcGePoint2d const & a, AcGePoint2d const & b)
{
	return sqrt(pow(a.x-b.x,2.0f)+pow(a.y-b.y,2.0f));
}

//-----------------------------------------------------------------------------
//----- AcDbEntity protocols
Adesk::Boolean SierpinskiTriangle::subWorldDraw (AcGiWorldDraw *mode) {
	assertReadEnabled () ;
	
	AcGePoint3d points[] = { AcGePoint3d(triangle[0].x, triangle[0].y, 0.0f),
						     AcGePoint3d(triangle[1].x, triangle[1].y, 0.0f),
		                     AcGePoint3d(triangle[2].x, triangle[2].y, 0.0f),
	                       };

	mode->geometry().polygon(3, points);
	
	uint32_t iter = 0u;

	static std::function<void(uint32_t, AcGePoint3d(&)[3])> subDraw 
		= [&](uint32_t depth, AcGePoint3d(&tri)[3]) -> void
	{
		mode->geometry().polygon(3,tri);

		if (depth < samples)
		{
			AcGePoint3d sub1[] =
			{
				AcGePoint3d((tri[0].x + tri[1].x) / 2 + (tri[1].x - tri[2].x) / 2,
							(tri[0].y + tri[1].y) / 2 + (tri[1].y - tri[2].y) / 2,
							 0.0f),
				AcGePoint3d((tri[0].x + tri[1].x) / 2 + (tri[0].x - tri[2].x) / 2,
							 (tri[0].y + tri[1].y) / 2 + (tri[0].y - tri[2].y) / 2,
							 0.0f),
				AcGePoint3d((tri[0].x + tri[1].x) / 2,
							 (tri[0].y + tri[1].y) / 2,
							 0.0f)
			};

			AcGePoint3d sub2[] =
			{
				AcGePoint3d((tri[2].x + tri[1].x) / 2 + (tri[1].x - tri[0].x) /2,
							(tri[2].y + tri[1].y) / 2 + (tri[1].y - tri[0].y) /2,
							0.0f),
				AcGePoint3d((tri[2].x + tri[1].x) / 2 + (tri[2].x - tri[0].x) /2,
							(tri[2].y + tri[1].y) / 2 + (tri[2].y - tri[0].y) /2,
							0.0f),
				AcGePoint3d((tri[2].x + tri[1].x) / 2,
							(tri[2].y + tri[1].y) / 2,
							0.0f)
			};

			AcGePoint3d sub3[] =
			{
				AcGePoint3d((tri[0].x + tri[2].x) / 2 + (tri[2].x - tri[1].x) /2,
							(tri[0].y + tri[2].y) / 2 + (tri[2].y - tri[1].y) /2,
							0.0f),
				AcGePoint3d((tri[0].x + tri[2].x) / 2 + (tri[0].x - tri[1].x) /2,
							(tri[0].y + tri[2].y) / 2 + (tri[0].y - tri[1].y) /2,
							0.0f),
				AcGePoint3d((tri[0].x + tri[2].x) / 2,
							(tri[0].y + tri[2].y) / 2,
							0.0f)
			};
	        
			subDraw(depth + 1, sub1);
			subDraw(depth + 1, sub2);
			subDraw(depth + 1, sub3);
		}

	};

	AcGePoint3d subTri[] =
	{
		AcGePoint3d((triangle[0].x + triangle[1].x) / 2, (triangle[0].y + triangle[1].y) / 2, 0.0f),
		AcGePoint3d((triangle[0].x + triangle[2].x) / 2, (triangle[0].y + triangle[2].y) / 2, 0.0f),
		AcGePoint3d((triangle[1].x + triangle[2].x) / 2, (triangle[1].y + triangle[2].y) / 2 ,0.0f)
	};

	subDraw(0, subTri);

	return (AcDbEntity::subWorldDraw (mode)) ;
}


Adesk::UInt32 SierpinskiTriangle::subSetAttributes (AcGiDrawableTraits *traits) {
	assertReadEnabled () ;
	return (AcDbEntity::subSetAttributes (traits)) ;
}

