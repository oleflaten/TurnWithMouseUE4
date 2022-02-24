Echo deleting folders

@RD /S /Q "Binaries"
@RD /S /Q "Build"
REM delete Saved also, if rebuild still fails
REM @RD /S /Q "Saved"
@RD /S /Q "Intermediate"
REM delete DerivedDataCache also, if you have troubles with materials
REM @RD /S /Q "DerivedDataCache"
@RD /S /Q "Script"
@RD /S /Q ".vs"
@RD /S /Q ".idea"
DEL "*.code-workspace" /s /f /q
DEL "*.sln" /s /f /q
DEL "*.sln.DotSettings.user" /s /f /q