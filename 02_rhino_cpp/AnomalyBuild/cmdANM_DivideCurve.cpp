// cmdANM_DivideCurve.cpp
//

#include "stdafx.h"
#include "AnomalyFunctions.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN ANM_DivideCurve command
//

#pragma region ANM_DivideCurve command

class CCommandANM_DivideCurve : public CRhinoCommand
{
public:
	CCommandANM_DivideCurve() = default;
	UUID CommandUUID() override
	{
		// {f1df845f-4630-4a41-9a50-5e54b1ed0371}
		static const GUID ANM_DivideCurveCommand_UUID =
		{0xf1df845f,0x4630,0x4a41,{0x9a,0x50,0x5e,0x54,0xb1,0xed,0x03,0x71}};
		return ANM_DivideCurveCommand_UUID;
	}
	const wchar_t* EnglishCommandName() override { return L"ANM_DivideCurve"; }
	CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandANM_DivideCurve object
static class CCommandANM_DivideCurve theANM_DivideCurveCommand;

CRhinoCommand::result CCommandANM_DivideCurve::RunCommand(const CRhinoCommandContext& context)
{
	ON_SimpleArray<ON_Curve*> arrCurves; // This is the array of curves the user will select
	ON_3dPointArray divPtArray; // This will hold a temporary array of division points for every curve
	int divNumber;  // The number of division (segments) of the curves

	//Select some curves -----------------------------------------------
	SelectCurves(arrCurves, L"Select curves to divide");

	//Check if we have the curves -----------------------------------------------
	if (arrCurves.Count() < 1) return CRhinoCommand::failure;

	//Continue dividing the curves ----------------------------------------------
	for (int i = 0; i < arrCurves.Count(); i++)
	{
		ON_3dPointArray divisionPoints;
		DivideCurve(divisionPoints, arrCurves[i], 10);

		for (int j = 0; j < divisionPoints.Count(); j++)
		{
			context.m_doc.AddPointObject(divisionPoints[j]);
		}
	}

	context.m_doc.Redraw();

	return CRhinoCommand::success;
}

#pragma endregion

//
// END ANM_DivideCurve command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
