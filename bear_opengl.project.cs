using BearBuildTool.Projects;
using System.IO;
using System;
public class bear_opengl :Project
{
	public bear_opengl(string ProjectPath)
	{
		PCHFile=Path.Combine(ProjectPath,"source","GLPCH.cpp");
		PCHIncludeFile="GLPCH.h";
		AddSourceFiles(Path.Combine(ProjectPath,"source"),true);
		Projects.Private.Add("bear_core");
		Projects.Private.Add("bear_graphics");
		LibrariesStatic.Private.Add("opengl32.lib");
	}
} 