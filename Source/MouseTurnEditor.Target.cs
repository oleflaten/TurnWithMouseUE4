// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class MouseTurnEditorTarget : TargetRules
{
	public MouseTurnEditorTarget(TargetInfo Target) : base (Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("MouseTurn");

        bUseUnityBuild = false;
        bUsePCHFiles = false;
	}
}
