REM We need at least 2 characters in the path.
IF [%DEVKITPRO:~0,1%]==[%DEVKITPRO%] (
	GOTO END_ABORT
)

IF [%DEVKITPRO:~0,1%]==[/] (
	ECHO DEVKITPRO_PATH=%DEVKITPRO:~1,1%:%DEVKITPRO:~2%#>>ConfigVars
) ELSE IF [%DEVKITPRO:~1,1%]==[:] (
	ECHO DEVKITPRO_PATH=%DEVKITPRO%#>>ConfigVars
) ELSE (
	GOTO END_ABORT
)

GOTO END

:END_ABORT
ECHO ERROR: Environment variable DEVKITPRO must be set to absolute devkitPro path.
DEL ConfigVars

:END
