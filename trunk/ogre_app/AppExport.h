#ifndef _____AppExport_H
#define _____AppExport_H

#define App_Export_API

#ifdef __cplusplus
extern "C" { 
#endif

#define App_Export
#	ifdef  App_Export
#		undef App_Export_API
#		define App_Export_API _declspec(dllexport)
#	else
#		define App_Export_API _declspec(dllimport)
#endif

#ifdef __cplusplus
}
#endif


#endif