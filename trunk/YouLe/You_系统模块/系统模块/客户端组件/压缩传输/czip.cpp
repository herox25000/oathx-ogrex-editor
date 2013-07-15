

#define DLL_INTERNAL __declspec( dllexport )
#include "czip.h"
#include "tailor.h"


// global variables instancied in gzip 
extern "C" {

extern int dozip( int, int);
extern int dounzip( int, int );
extern long time_stamp;
extern char ifname[MAX_PATH_LEN]; 
extern int save_orig_name;

extern int ifd;
extern int ofd;

}

int inFile, outFile;

// this function is called by gzip when there is an error
// instead of doing an exit( .. )
extern "C" void do_exit_dll(int exitcode)
{
	close( inFile );
	close( outFile );
	//throw( CZipException( "problem with zipping/unzipping operation : %d", exitcode ) );    
}



CZipException::CZipException( const char* fm, ... )
{
	char *p = m_sMessage;
	va_list args;
	va_start( args, fm );
	p += vsprintf( p, fm, args);
	va_end( args );
}


int WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	return 1;
}



CMamaZip::CMamaZip( const char *sUnzippedFileName )
{
	strcpy( m_sSourceFileName, sUnzippedFileName );
}


// throw CZipException
void CMamaZip::SwapSize( const char *sTargetFileName )
{

	if (strcmp(m_sSourceFileName,sTargetFileName)==0)
		throw ( CZipException( "target name must be different than source name" ) );

	// try to open in unzipped file
	if ( ( inFile = open( m_sSourceFileName, _O_BINARY | _O_RDONLY ) ) == -1 )
		throw ( CZipException( "unable to open source file" ) );

	if ( ( outFile = open( sTargetFileName, _O_BINARY | _O_RDWR | _O_CREAT | _O_EXCL , _S_IREAD | _S_IWRITE  ) ) == -1 )
	{
		close(inFile);
		throw ( CZipException( "unable to create target file" ) );
	}

	ifd=inFile; ofd=outFile;
	int ret = HardWork( inFile, outFile );

	close( inFile );
	close( outFile );

	if (ret != 0)
		throw( CZipException( "problem while %s file", m_sOperation ) );
}
	

CZip::CZip( const char* sSourceFileName )
	: CMamaZip( sSourceFileName ) 
		
{ 
	m_sOperation = "zipping"; 	
	strcpy( ifname, m_sSourceFileName );
	save_orig_name = 1;
}


CUnzip::CUnzip( const char* sSourceFileName )
	: CMamaZip( sSourceFileName ) 
		
{ 
	m_sOperation = "unzipping"; 	
}

int CUnzip::HardWork( int inFile, int outFile )
{
	return dounzip( inFile, outFile );
}

			
int CZip::HardWork( int inFile, int outFile )
{
	return dozip( inFile, outFile );
}

