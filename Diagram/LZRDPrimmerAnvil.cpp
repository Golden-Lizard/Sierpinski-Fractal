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
//----- LZRDPrimmerAnvil.cpp : Implementation of LZRDPrimmerAnvil
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "LZRDPrimmerAnvil.h"

//-----------------------------------------------------------------------------
Adesk::UInt32 LZRDPrimmerAnvil::kCurrentVersionNumber =1 ;

double square_root(float x)
{
	auto x0 = x;
	for (auto iter = 0u; iter<0x20; x -= (x*x - x0) / (2.0f*x), ++iter);

	return x;
}


//-----------------------------------------------------------------------------
ACRX_DXF_DEFINE_MEMBERS (
	LZRDPrimmerAnvil, AcDbEntity,
	AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
	AcDbProxyEntity::kNoOperation, LZRDPRIMMERANVIL,
LZRDDIAGRAMAPP
|Product Desc:     A description for your object
|Company:          Your company name
|WEB Address:      Your company WEB site address
)

//-----------------------------------------------------------------------------
LZRDPrimmerAnvil::LZRDPrimmerAnvil () : AcDbEntity () {
}

LZRDPrimmerAnvil::LZRDPrimmerAnvil(std::pair<float,float> center, Adesk::Int32 length = 5, Adesk::Int16 flaps =2) : AcDbEntity(),
center(center),
length(length),
flaps(flaps)
{}

LZRDPrimmerAnvil::~LZRDPrimmerAnvil () {
}

//-----------------------------------------------------------------------------
//----- AcDbObject protocols
//- Dwg Filing protocol
Acad::ErrorStatus LZRDPrimmerAnvil::dwgOutFields (AcDbDwgFiler *pFiler) const {
	assertReadEnabled () ;
	//----- Save parent class information first.
	Acad::ErrorStatus es =AcDbEntity::dwgOutFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be saved first
	if ( (es =pFiler->writeUInt32 (LZRDPrimmerAnvil::kCurrentVersionNumber)) != Acad::eOk )
		return (es) ;
	//----- Output params
	//.....

	return (pFiler->filerStatus ()) ;
}

Acad::ErrorStatus LZRDPrimmerAnvil::dwgInFields (AcDbDwgFiler *pFiler) {
	assertWriteEnabled () ;
	//----- Read parent class information first.
	Acad::ErrorStatus es =AcDbEntity::dwgInFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be read first
	Adesk::UInt32 version =0 ;
	if ( (es =pFiler->readUInt32 (&version)) != Acad::eOk )
		return (es) ;
	if ( version > LZRDPrimmerAnvil::kCurrentVersionNumber )
		return (Acad::eMakeMeProxy) ;
	//- Uncomment the 2 following lines if your current object implementation cannot
	//- support previous version of that object.
	//if ( version < LZRDPrimmerAnvil::kCurrentVersionNumber )
	//	return (Acad::eMakeMeProxy) ;
	//----- Read params
	//.....

	return (pFiler->filerStatus ()) ;
}

//- Dxf Filing protocol
Acad::ErrorStatus LZRDPrimmerAnvil::dxfOutFields (AcDbDxfFiler *pFiler) const {
	assertReadEnabled () ;
	//----- Save parent class information first.
	Acad::ErrorStatus es =AcDbEntity::dxfOutFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	es =pFiler->writeItem (AcDb::kDxfSubclass, _RXST("LZRDPrimmerAnvil")) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be saved first
	if ( (es =pFiler->writeUInt32 (kDxfInt32, LZRDPrimmerAnvil::kCurrentVersionNumber)) != Acad::eOk )
		return (es) ;
	//----- Output params
	//.....

	return (pFiler->filerStatus ()) ;
}

Acad::ErrorStatus LZRDPrimmerAnvil::dxfInFields (AcDbDxfFiler *pFiler) {
	assertWriteEnabled () ;
	//----- Read parent class information first.
	Acad::ErrorStatus es =AcDbEntity::dxfInFields (pFiler) ;
	if ( es != Acad::eOk || !pFiler->atSubclassData (_RXST("LZRDPrimmerAnvil")) )
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
	if ( version > LZRDPrimmerAnvil::kCurrentVersionNumber )
		return (Acad::eMakeMeProxy) ;
	//- Uncomment the 2 following lines if your current object implementation cannot
	//- support previous version of that object.
	//if ( version < LZRDPrimmerAnvil::kCurrentVersionNumber )
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

//-----------------------------------------------------------------------------
//----- AcDbEntity protocols
Adesk::Boolean LZRDPrimmerAnvil::subWorldDraw (AcGiWorldDraw *mode) {
	assertReadEnabled () ;

	mode->geometry().ellipticalArc(AcGePoint3d(center.first, center.second, 0.0f),
		AcGeVector3d(1.0f, 1.0f, 0.0f), this->length, this->length, 3.14156592f / 2.0f,
		3.14156592f / 3.0f, 3.14156592f / 6.0f);

	return (AcDbEntity::subWorldDraw (mode)) ;
}


Adesk::UInt32 LZRDPrimmerAnvil::subSetAttributes (AcGiDrawableTraits *traits) {
	assertReadEnabled () ;
	return (AcDbEntity::subSetAttributes (traits)) ;
}


Acad::ErrorStatus LZRDPrimmerAnvil::setArea(void)
{
	this->area = Adesk::Int32(square_root(3.0) / 4 * this->length);
	return Acad::eOk;

}

Acad::ErrorStatus LZRDPrimmerAnvil::setLength(float const & lenght)
{
	try
	{
		if (length > 0x2 || length < 0x0)
			throw std::out_of_range("Error, invalid type");
		this->length = length;
	}
	catch (std::out_of_range e)
	{
		return Acad::eInvalidInput;
	}

	return Acad::eOk;
}

Acad::ErrorStatus LZRDPrimmerAnvil::setMaterial(std::wstring const & name)
{
	if (name.empty())
		return Acad::eNullPtr;

	this->material = name;
	return Acad::eOk;
}

Acad::ErrorStatus LZRDPrimmerAnvil::setMaterial(TCHAR * name)
{
	if (!name)
		return Acad::eNullPtr;

	this->material = (std::wstring(name));
	return Acad::eOk;
}

Acad::ErrorStatus LZRDPrimmerAnvil::setFlaps(const Adesk::Int16 & flaps)
{
	try
	{
		if (flaps > 3 || flaps < 1)
			throw std::out_of_range("Invalid number of flaps");

		this->flaps = flaps;
	}
	catch (std::out_of_range e)
	{
		return Acad::eInvalidInput;
	}

	return Acad::eOk;
}

std::wstring LZRDPrimmerAnvil::getName()
{
	return this->material;
}

std::wstring LZRDPrimmerAnvil::getMaterial()
{
	return this->material;
}

Adesk::Int32 LZRDPrimmerAnvil::getArea()
{
	return flaps * this->area;
}

Adesk::Int32 LZRDPrimmerAnvil::getLength()
{
	return this->length;
}

Adesk::Int16 LZRDPrimmerAnvil::getFlaps()
{
	return this->flaps;
}

std::pair<float, float> LZRDPrimmerAnvil::getCenter()
{
	return this->center;
}

void LZRDPrimmerAnvil::getCenter(float & x, float & y)
{
	AcDbPolyline::AcDbPolyline();
	x = center.first;
	y = center.second;
}
