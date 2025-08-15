// cmdANM_CreateDot.cpp
//

#include "stdafx.h"
#include "AnomalyFunctions.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN ANM_CreateDot command
//

#pragma region ANM_CreateDot command

class CCommandANM_CreateDot : public CRhinoCommand
{
public:
	CCommandANM_CreateDot() = default;
	UUID CommandUUID() override
	{
		// {2dbfc751-089e-472d-b8cd-15c7561c6b43}
		static const GUID ANM_CreateDotCommand_UUID =
		{0x2dbfc751,0x089e,0x472d,{0xb8,0xcd,0x15,0xc7,0x56,0x1c,0x6b,0x43}};
		return ANM_CreateDotCommand_UUID;
	}
	const wchar_t* EnglishCommandName() override { return L"ANM_CreateDot"; }
	CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandANM_CreateDot object
static class CCommandANM_CreateDot theANM_CreateDotCommand;

CRhinoCommand::result CCommandANM_CreateDot::RunCommand(const CRhinoCommandContext& context)
{
	ON_3dPointArray points;
	SelectPoints(points, L"Select points to create dots");

	for(int i = 0; i < points.Count(); i++)
	{
		ON_TextDot dot;
		ON_3dPoint pt = points[i];

		CString primText;
		primText.Format(L"Point %d", i);
		CString secText;
		secText.Format(L"Out of %d", points.Count());
		
		dot.SetCenterPoint(pt);
		dot.SetPrimaryText(primText);
		dot.SetSecondaryText(secText);

		CRhinoTextDot* dotObj = new CRhinoTextDot();
		dotObj->SetDot(dot);
		context.m_doc.AddObject(dotObj);

		//delete dotObj;
		//dotObj = nullptr;
	}

	return CRhinoCommand::success;
}

#pragma endregion

//
// END ANM_CreateDot command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
