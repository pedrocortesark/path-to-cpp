#pragma once

#include "stdafx.h"
#include "AnomalyFunctions.h"

/* Get a line and draw a point on any of the defining points depending on a boolean*/
ON_3dPoint DrawPoint( ON_Line line, bool start) 
{
	return start ? line.from : line.to;
}

/* This function takes a pointer to a curve and a number of segments, divides the curve and returns true or false and an array of division points */
bool DivideCurve(ON_3dPointArray& points, ON_Curve* crv, int divNumber) 
{
	// Check input parameters
	if (divNumber < 2) return false; // We need at least two points to divide
	points.Destroy(); // Clear the point array

	// Compute the division points
	int divCount = divNumber + 1;

	ON_SimpleArray<double> t(divCount);
	t.SetCapacity(divCount);

	for (int i = 0; i < divCount; i++)
	{
		double param = (double)i / (double)(divNumber);
		t[i] = param;
	}

	if (crv->GetNormalizedArcLengthPoints(divCount, (double*)&t[0], (double*)&t[0]))
	{
		for (int i = 0; i < divCount; i++)
		{
			ON_3dPoint pt = crv->PointAt(t[i]);
			points.Append(pt);
		}
	}
	else
	{
		return false; // Failed to get normalized arc length points
	}

	return true;
}

/* This function will prompt the user to select points and will fill up the 3dPoint array */
void SelectPoints(ON_3dPointArray& points, CString msg)
{
	points.Destroy(); // Clear the point array

	CRhinoGetObject go;
	go.EnablePreSelect(false);
	go.SetCommandPrompt(msg);
	go.SetGeometryFilter(CRhinoGetObject::point_object);

	CRhinoGetObject::result res = go.GetObjects(1, 0);

	if (res == CRhinoGetObject::object)
	{
		for (int i = 0; i < go.ObjectCount(); i++)
		{
			const CRhinoObjRef& obj_ref = go.Object(i);
			const CRhinoPointObject* point_obj = CRhinoPointObject::Cast(obj_ref.Object());
			const ON_Point pt = point_obj->Point();
			ON_3dPoint point(pt.point.x, pt.point.y, pt.point.z);
			points.Append(pt);
		}
	}
}

/* This function will prompt the user to select curves and will fill up the simple array */
void SelectCurves(ON_SimpleArray<ON_Curve*>& curves, CString msg)
{
	curves.Destroy();

	CRhinoGetObject go;
	go.EnablePreSelect(false);
	go.SetCommandPrompt(msg);
	go.SetGeometryFilter(CRhinoGetObject::curve_object);

	CRhinoGetObject::result res = go.GetObjects(1, 0);
	int objectCount = go.ObjectCount();

	if (res == CRhinoGet::object) {
		for (int i = 0; i < objectCount; i++)
		{
			const CRhinoObjRef& obj_ref = go.Object(i);
			ON_Curve* crv = obj_ref.Curve()->Duplicate();
			if (crv) curves.Append(crv);
		}
	}
}

/* This function will prompt the user to select breps and will fill up the simple array */
void SelectBreps(ON_SimpleArray<ON_Brep*>& breps, CString msg)
{
	breps.Destroy();

	CRhinoGetObject go;
	go.EnablePreSelect(false);
	go.SetCommandPrompt(msg);
	go.SetGeometryFilter(CRhinoGetObject::object);

	CRhinoGetObject::result res = go.GetObjects(1, 0);
	int objectCount = go.ObjectCount();

	if (res == CRhinoGet::object) {
		for (int i = 0; i < objectCount; i++)
		{
			const CRhinoObjRef& obj_ref = go.Object(i);
			ON_Brep* brep = obj_ref.Brep()->BrepForm();
			if (brep) breps.Append(brep);
		}
	}
}


/* This function will create a nurbs curve through the passed points */
void CreateCurveFromPoints(ON_3dPointArray& points, int degree, CRhinoDoc* doc)
{
	ON_NurbsCurve* nurbscurve = RhinoInterpCurve(degree, points, 0, 0, 0);
	doc->AddCurveObject(*nurbscurve);
	doc->Redraw();
}

ON_Polyline CreatePolylineFromPoints(ON_3dPointArray& points)
{
	return ON_Polyline(points);
}

void CreateCircle(ON_3dPointArray& points, CRhinoDoc* doc)
{
	double radius;
	ON_RandomNumberGenerator rnd;

	for (int i = 0; i < points.Count(); i++)
	{
		radius = rnd.RandomDouble(5.0, 25.0);

		ON_Circle circle(points[i], radius);
		doc->AddCurveObject(circle);
	}
	doc->Redraw();
}

void CreateArc(ON_3dPointArray& points, CRhinoDoc* doc)
{
	double radius;
	ON_RandomNumberGenerator rnd;
	

	ON_3dVector xAxis(5.0, 9.0, 7.0);
	ON_3dVector yAxis(8.0, 1.0, -5.0);

	for (int i = 0; i < points.Count(); i++)
	{
		ON_Plane plane(points[i], xAxis, yAxis);

		radius = rnd.RandomDouble(5.0, 10.0);
		ON_Line xLine(points[i], points[i] + plane.xaxis * radius);
		ON_Line yLine(points[i], points[i] + plane.yaxis * radius);
		doc->AddCurveObject(xLine);
		doc->AddCurveObject(yLine);

		ON_Arc arc(plane, radius, ON_PI);
		doc->AddCurveObject(arc);
	}
}

/* Will create a brep from planar curves and will retirn a Brep pointer */
ON_Brep* CreateBrepFromPlanarCurves(ON_SimpleArray<ON_Curve*>& curves)
{
	if (curves.Count() < 1) return nullptr;

	ON_SimpleArray<const ON_Curve*> inputCurves;
	for (int i = 0; i < curves.Count(); i++)
		inputCurves.Append(curves[i]);
	
	ON_Brep* brep = nullptr;
	ON_SimpleArray<ON_Brep*> outBreps;

	bool result = RhinoMakePlanarBreps(inputCurves, outBreps, 0.001);

	if (result)
		brep = outBreps[0];
	else
		RhinoApp().Print(L"Planar brep creation failed.\n");

	return brep;
}

/* Will create a brep from each planar curves and will return an array of Brep pointers */
ON_SimpleArray<ON_Brep*> CreateSeveralBrepsFromPlanarCurves(ON_SimpleArray<ON_Curve*>& curves)
{
	ON_SimpleArray<const ON_Curve*> inputCurves;
	for (int i = 0; i < curves.Count(); i++)
	{
		const ON_Curve* crv = curves[i];
		inputCurves.Append(crv);
	}

	ON_SimpleArray<ON_Brep*> outBreps;

	bool sc = RhinoMakePlanarBreps(inputCurves, outBreps, 0.001);
	if (!sc)
	{
		RhinoApp().Print(L"Planar brep creation failed.\n");
	}
	
	return outBreps;
}

/* Will create a brep from edge curves and will retirn a Brep pointer */
ON_Brep* CreateBrepFromEdgeCurves(ON_SimpleArray<ON_Curve*>& curves)
{
	ON_SimpleArray<const ON_Curve*> inputCurves;
	for (int i = 0; i < curves.Count(); i++)
		inputCurves.Append(curves[i]);

	int curvesCount = curves.Count();

	if (curvesCount < 2 || curvesCount > 4)
		return nullptr;
	else 
		return RhinoCreateEdgeSrf(curvesCount, inputCurves);
}

/* Will create a brep by joining other input breps and return an array of Brep pointers */
ON_SimpleArray<ON_Brep*> JoinBreps(CRhinoDoc* doc, ON_SimpleArray<ON_Brep*>& breps, bool deleteOriginal)
{
	ON_SimpleArray<ON_Brep*> outBreps;
	bool sc = RhinoJoinBreps(breps, outBreps, doc->AbsoluteTolerance());

	if(deleteOriginal)
	{
		for (int i = 0; i < breps.Count(); i++)
		{
			delete breps[i];
			breps[i] = 0;
		}

		breps.Destroy();
	}

	return outBreps;
}