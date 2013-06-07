#pragma once

enum{
	TARGET_FILEVIEW,
	TARGET_PROPERTY,
	TARGET_RESOURCE,
};

#define WM_NEWSCHEME		WM_USER + 1
struct wmNewScheme{
	char			szName[MAX_PATH];
	char			szPath[MAX_PATH];
};