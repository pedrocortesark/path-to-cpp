#pragma once

#include "stdafx.h"

ON_3dPoint DrawPoint(ON_Line line, bool start);

bool DivideCurve(ON_3dPointArray& points, ON_Curve* crv, int divNumber);

void SelectPoints(ON_3dPointArray& points, CString msg);

void SelectCurves(ON_SimpleArray<ON_Curve*>& curves, CString msg);

void SelectBrep(ON_Brep* &brep, CString msg);

void SelectBreps(ON_SimpleArray<ON_Brep*>& breps, CString msg);

void CreateCurveFromPoints(ON_3dPointArray& points, int degree, CRhinoDoc* doc);

ON_Polyline CreatePolylineFromPoints(ON_3dPointArray& points);

void CreateCircle(ON_3dPointArray& points, CRhinoDoc* doc);

void CreateArc(ON_3dPointArray& points, CRhinoDoc* doc);

ON_Brep* CreateBrepFromPlanarCurves(ON_SimpleArray<ON_Curve*>& curves);

ON_SimpleArray<ON_Brep*> CreateSeveralBrepsFromPlanarCurves(ON_SimpleArray<ON_Curve*>& curves);

ON_Brep* CreateBrepFromEdgeCurves(ON_SimpleArray<ON_Curve*>& curves);

ON_SimpleArray<ON_Brep*> JoinBreps (CRhinoDoc* doc, ON_SimpleArray<ON_Brep*>& breps, bool deleteOriginal);