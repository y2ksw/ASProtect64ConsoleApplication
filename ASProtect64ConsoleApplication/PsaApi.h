//
//	PsaApi.h
//
//	File description:
//		Header file for public API functions. These functions can be used in
//      initialization module as well as in protected application.
//

// Include this file only once
#pragma once

#ifdef NOIMPORTPSAPI
#define PSAPI __stdcall
#else
#define PSAPI __declspec(dllimport) __stdcall
#endif

// Additional headers
#ifndef PS_CONFIG_H_INCLUDED_7D7370D6_8681_4908_8C5F_D1152CF38653
#define PS_CONFIG_H_INCLUDED_7D7370D6_8681_4908_8C5F_D1152CF38653
#include "PsConfig.h"
#endif
#ifndef PS_CONSTANTS_H_INCLUDED_7990EBEC_1968_44FF_AF44_6800920821F1
#define PS_CONSTANTS_H_INCLUDED_7990EBEC_1968_44FF_AF44_6800920821F1
#include "PsConstants.h"
#endif

//
//	Common functions
//

//
//	Description:
//		Dummy reference (simply returns the control). Linker can exclude
//		protect.dll from import table if no functions are used. So, this
//		function can be inserted into any part of application code to
//		prevent this.
//
void PSAPI PSA_DummyFunction();

//
//	Description:
//		Uninitialize protection core resources before unloading of protect.dll
//		or before exit.
//		The protection core can create threads for periodical checking of
//		license expiration etc. If protect.dll will be unloaded using
//		FreeLibrary( someProtectedDllHandle ) these threads will be	stopped
//		by operating system and resources that are allocated in these threads
//		will not be freed. It can lead to resource leaks if	the protected .DLL
//		is loaded and unloaded many times.
//		If you protect only .EXE files or there are no multiple
//		loading/unloading of protected .DLL files the call to this function
//		is not mandatory.
//
//	Output:
//		Return value - PSC_STATUS_SUCCESS or error code
//
unsigned __int32 PSAPI PSA_Uninitialize();

#ifdef PS_USE_LICENSES

//
//	Description:
//		Get registry path and base handle for license.
//
//	Input:
//		pathBuffer					- buffer for path
//		pathBufferSizeInWideChars	- buffer size
//		registryBaseHandle			- buffer for base handle
//
//	Output:
//		Return value				- PSC_STATUS_SUCCESS or error code
//			(PSC_STATUS_BUFFER_TOO_SMALL if buffer is too small)
//		*pathBuffer					- path (Unicode zero-terminated string)
//		*pathBufferSizeInWideChars	- used buffer size (or required buffer
//			size is return value is PSC_STATUS_BUFFER_TOO_SMALL)
//		*registryBaseHandle			- buffer for base handle
//
unsigned __int32 PSAPI PSA_GetLicenseStoragePath(
	wchar_t *pathBuffer,
	size_t *pathBufferSizeInWideChars,
	HANDLE *registryBaseHandle );

// License version (see PSA_GetLicenseInformation)
#define LIC_VERSION_UNDEFINED								0xFFFFFFFF
#define LIC_VERSION_0_DISC									0
#define LIC_VERSION_1_HARDWARE								1
#define LIC_VERSION_5_HARDWARE								5
#define LIC_VERSION_6_HARDWARE								6
#define LIC_VERSION_7_HARDWARE								7

// License types (see PSA_GetLicenseInformation)
#define LIC_TYPE_UNDEFINED									0xFFFFFFFF
#define LIC_TYPE_HARDWARE									0
#define LIC_TYPE_HARDWARE_TRIAL								1
#define LIC_TYPE_HARDWARE_RESCUE							2
#define LIC_TYPE_HARDWARE_AUTOGENERATED_AFTER_DISC_CHECK	3
#define LIC_TYPE_DISC										4

//
//	Description:
//		Get special information for current license.
//
//	Input:
//		version			- buffer for license version
//		type			- buffer for license type
//		nonCommercial	- buffer for non-commercial flag
//
//	Output:
//		Return value	- PSC_STATUS_SUCCESS or error code
//		*version		- license version
//		*type			- license type
//		*nonCommercial	- non-commercial flag
//
//	Registry keys for debugging:
//		"LicenseVersion", "LicenseType", "IsNonCommercialLicense" of type
//		REG_DWORD (initialized at loading of protect.dll).
//
unsigned __int32 PSAPI PSA_GetLicenseInformation(
	unsigned __int32 *version,
	unsigned __int32 *type,
	bool *nonCommercial );

#endif

//
//	Limitation of functionality
//

#ifdef PS_USE_LICENSES

// Codes of independent features that can be granted by license
#define PSA_GrantedFeature0			0x00000001
#define PSA_GrantedFeature1			0x00000002
#define PSA_GrantedFeature2			0x00000004
#define PSA_GrantedFeature3			0x00000008
#define PSA_GrantedFeature4			0x00000010
#define PSA_GrantedFeature5			0x00000020
#define PSA_GrantedFeature6			0x00000040
#define PSA_GrantedFeature7			0x00000080
#define PSA_GrantedFeature8			0x00000100
#define PSA_GrantedFeature9			0x00000200
#define PSA_GrantedFeature10		0x00000400
#define PSA_GrantedFeature11		0x00000800
#define PSA_GrantedFeature12		0x00001000
#define PSA_GrantedFeature13		0x00002000
#define PSA_GrantedFeature14		0x00004000
#define PSA_GrantedFeature15		0x00008000
#define PSA_GrantedFeature16		0x00010000
#define PSA_GrantedFeature17		0x00020000
#define PSA_GrantedFeature18		0x00040000
#define PSA_GrantedFeature19		0x00080000
#define PSA_GrantedFeature20		0x00100000
#define PSA_GrantedFeature21		0x00200000
#define PSA_GrantedFeature22		0x00400000
#define PSA_GrantedFeature23		0x00800000
#define PSA_GrantedFeature24		0x01000000
#define PSA_GrantedFeature25		0x02000000
#define PSA_GrantedFeature26		0x04000000
#define PSA_GrantedFeature27		0x08000000
#define PSA_GrantedFeature28		0x10000000
#define PSA_GrantedFeature29		0x20000000
#define PSA_GrantedFeature30		0x40000000
#define PSA_GrantedFeature31		0x80000000

//
//	Description:
//		Get a set of features granted by license (bit mask).
//		For example, this function can return the value	*features = 9,
//		i.e. ( PSA_GrantedFeature0 | PSA_GrantedFeature3 ).
//		This function returns *features = 0 for demo mode (if demo mode has
//		been enabled).
//
//	Input:
//		features		- buffer for feature set
//
//	Output:
//		*features		- feature set
//		Return value	- PSC_STATUS_SUCCESS or error code
//
//	Registry keys for debugging:
//		"FeatureSetGrantedByLicense" of type REG_DWORD (initialized at
//		loading of protect.dll).
//
unsigned __int32 PSAPI PSA_GetFeaturesGrantedByLicense(
	unsigned __int32 *features );

//
//	Description:
//		Disable features granted by license for limitation of application
//		functionality "on the fly" e.g. after expiration of license (only
//		enabled features will be disabled, so, 0xFFFFFFFF is valid argument
//		for disabling of all features).
//
//	Input:
//		features		- buffer for feature set mask
//
//	Output:
//		Return value	- PSC_STATUS_SUCCESS or error code
//
unsigned __int32 PSAPI PSA_DisableFeaturesGrantedByLicense(
	unsigned __int32 features );

//
//	Description:
//		Check rights granted by license and display error dialog on error.
//		This function works only in SDK mode. In normal protected application
//		is does nothing.
//
//	Input:
//		features		- features mask to check (the check succeed if
//			at least one bit from the mask is set in current license)
//
//	Output:
//		Return value	- PSC_STATUS_SUCCESS if the check succeeds or fails
//			or error code on internal error
//
unsigned __int32 PSAPI PSA_CheckFeaturesGrantedByLicense(
	unsigned __int32 features );

#endif

//
//	Program start mode
//

#ifdef PS_USE_LICENSES

//
//	Description:
//		Check if the application is running in demo mode.
//
//	Input:
//		isDemoMode		- buffer for demo mode flag
//
//	Output:
//		Return value	- PSC_STATUS_SUCCESS or error code
//		*isDemoMode		- demo mode flag
//
//	Registry keys for debugging:
//		"IsDemoMode" of type REG_DWORD (initialized at loading of protect.dll).
//
unsigned __int32 PSAPI PSA_IsDemoMode(
	bool *isDemoMode );

//
//	Description:
//		Check if the application is running in trial mode.
//
//	Input:
//		isTrialMode		- buffer for trial mode flag
//
//	Output:
//		Return value	- PSC_STATUS_SUCCESS or error code
//		*isTrialMode	- trial mode flag
//
//	Registry keys for debugging:
//		"IsTrialMode" of type REG_DWORD (initialized at loading of protect.dll).
//
unsigned __int32 PSAPI PSA_IsTrialMode(
	bool *isTrialMode );

#endif

//
//	Expiration parameters of license
//

#ifdef PS_USE_LICENSES

//
//	Description:
//		Get license creation time
//
//	Input:
//		licenseCreationDateTime		- buffer for time
//
//	Output:
//		Return value				- PSC_STATUS_SUCCESS or error code
//		*licenseCreationDateTime	- license creation time in 100 ns intervals
//
//	Registry keys for debugging:
//		"LicenseCreationTime" of type REG_BINARY and length 8 bytes
//		(initialized at loading of protect.dll).
//
unsigned __int32 PSAPI PSA_GetLicenseCreationDateTime(
	unsigned __int64 *licenseCreationDateTime );

//
//	Description:
//		Check if the license is already expired.
//
//	Input:
//		isLicenseExpired	- buffer for license expired flag
//
//	Output:
//		Return value		- PSC_STATUS_SUCCESS or error code
//		*isLicenseExpired	- license expired flag
//		updateRunTimeData	- flag for updating of license usage history
//
//	Registry keys for debugging:
//		"IsLicenseExpired" of type REG_DWORD (reinitialized at each call).
//
unsigned __int32 PSAPI PSA_IsLicenseExpired(
	bool *isLicenseExpired, bool updateRunTimeData );

//
//	Description:
//		Get the time before expiration of license.
//
//	Input:
//		timeToLicenseExpiration		- buffer for time
//
//	Output:
//		Return value				- PSC_STATUS_SUCCESS or error code
//		*timeToLicenseExpiration	- time before expiration of license in
//			100 ns intervals (0 - license expired, ~0ui64 - undefined or
//			infinite)
//
//	Registry keys for debugging:
//		"TimeToLicenseExpiration" of type REG_BINARY and length 8 bytes
//		(reinitialized at each call).
//
unsigned __int32 PSAPI PSA_GetTimeToLicenseExpiration(
	unsigned __int64 *timeToLicenseExpiration );

//
//	Description:
//		Get date and time of license expiration.
//
//	Input:
//		licenseExpirationDateTime	- buffer for date and time
//
//	Output:
//		Return value				- PSC_STATUS_SUCCESS or error code
//		*licenseExpirationDateTime	- date and time of license expiration in
//			file time format, i.e. number of 100 ns intervals elapsed since
//			January 1, 1601 (~0ui64 - undefined or infinite)
//
//	Registry keys for debugging:
//		"LicenseExpirationDateTime" of type REG_BINARY and length 8 bytes
//		(initialized at loading of protect.dll).
//
unsigned __int32 PSAPI PSA_GetLicenseExpirationDateTime(
	unsigned __int64 *licenseExpirationDateTime );

//
//	Description:
//		Get life time limit of license (i.e. time before expiration of license
//		from the moment of license creation, as assigned by e.g. activation
//		key).
//
//	Input:
//		licenseLifeTimeLimit	- buffer for life time limit
//
//	Output:
//		Return value			- PSC_STATUS_SUCCESS or error code
//		*licenseLifeTimeLimit	- life time limit in 100 ns intervals
//			(~0ui64 - undefined or infinite).
//
//	Registry keys for debugging:
//		"LicenseLifeTimeLimit" of type REG_BINARY and length 8 bytes
//		(initialized at loading of protect.dll).
//
unsigned __int32 PSAPI PSA_GetLicenseLifeTimeLimit(
	unsigned __int64 *licenseLifeTimeLimit );

//
//	Description:
//		Get remaining number of runs.
//
//	Input:
//		remainingNumberOfRuns	- buffer for remaining number of runs
//
//	Output:
//		Return value			- PSC_STATUS_SUCCESS or error code
//		*remainingNumberOfRuns	- remaining number of runs (~0ui32 - undefined
//			or infinite)
//
//	Registry keys for debugging:
//		"RemainingNumberOfRuns" of type REG_DWORD (initialized at loading of
//		protect.dll).
//
unsigned __int32 PSAPI PSA_GetRemainingNumberOfRuns(
	unsigned __int32 *remainingNumberOfRuns );

//
//	Description:
//		Get limit for number of runs (i.e. total allowed number of runs, as
//		assigned by e.g. activation key).
//
//	Input:
//		remainingNumberOfRuns	- buffer for limit of number of runs
//
//	Output:
//		Return value			- PSC_STATUS_SUCCESS or error code
//		*remainingNumberOfRuns	- limit of number of runs (~0ui32 - undefined
//			or infinite)
//
//	Registry keys for debugging:
//		"LicenseNumberOfRunsLimit" of type REG_DWORD (initialized at loading of
//		protect.dll).
//
unsigned __int32 PSAPI PSA_GetLicenseNumberOfRunsLimit(
	unsigned __int32 *licenseNumberOfRunsLimit );

//
//	Description:
//		Get remaining execution time of application, calculated in the current
//		moment.
//
//	Input:
//		remainingExecutionTime	- buffer for remaining execution time
//
//	Output:
//		Return value			- PSC_STATUS_SUCCESS or error code
//		*remainingExecutionTime	- remaining execution time in 100 ns intervals
//			(0 - license expired, ~0ui64 - undefined or infinite)
//
//	Registry keys for debugging:
//		"RemainingExecutionTime" of type REG_BINARY and length 8 bytes
//		(reinitialized at each call).
//
unsigned __int32 PSAPI PSA_GetRemainingExecutionTime(
	unsigned __int64 *remainingExecutionTime );

//
//	Description:
//		Get remaining execution time of application, calculated in the moment
//		of start of application.
//
//	Input:
//		remainingExecutinTimeAtStart	- buffer for remaining execution time
//
//	Output:
//		Return value					- PSC_STATUS_SUCCESS or error code
//		*remainingExecutinTimeAtStart	- remaining execution time in 100 ns
//			intervals (0 - license expired, ~0ui64 - undefined or infinite)
//
//	Registry keys for debugging:
//		"RemainingExecutionTimeAtStart" of type REG_BINARY and length 8 bytes
//		(initialized at loading of protect.dll).
//
unsigned __int32 PSAPI PSA_GetRemainingExecutionTimeAtStart(
	unsigned __int64 *remainingExecutinTimeAtStart );

//
//	Description:
//		Get limit for execution time of application(i.e. total allowed
//		execution time assigned by e.g. activation key).
//
//	Input:
//		licenseExecutionTimeLimit	- buffer for limit of execution time
//
//	Output:
//		Return value				- PSC_STATUS_SUCCESS or error code
//		*licenseExecutionTimeLimit	- limit of execution time in 100 ns
//			intervals (~0ui64 - undefined or infinite)
//
//	Registry keys for debugging:
//		"LicenseExecutionTimeLimit" of type REG_BINARY and length 8 bytes
//		(initialized at loading of protect.dll).
//
unsigned __int32 PSAPI PSA_GetLicenseExecutionTimeLimit(
	unsigned __int64 *licenseExecutionTimeLimit );

#endif

//
//	Miscellaneous data in the key
//

#ifdef PS_USE_LICENSES

//
//	Description:
//		Get user-defined field.
//
//	Input:
//		userDefinedField	- buffer for user-defined field
//
//	Output:
//		Return value		- PSC_STATUS_SUCCESS or error code
//		*userDefinedField	- user-defined field (0xFFFF if undefined)
//
//	Registry keys for debugging:
//		"UserDefinedField16Bits" of type REG_DWORD (initialized at loading
//		of protect.dll).
//
unsigned __int32 PSAPI PSA_GetUserDefinedField16Bits(
	unsigned __int16 *userDefinedField );

//
//	Description:
//		Get number of connections.
//
//	Input:
//		numberOfConnections		- buffer for user-defined field
//
//	Output:
//		Return value			- PSC_STATUS_SUCCESS or error code
//		*numberOfConnections	- number of connections (~0ui32 if undefined)
//
//	Registry keys for debugging:
//		"NumberOfConnections" of type REG_DWORD (initialized at loading
//		of protect.dll).
//
unsigned __int32 PSAPI PSA_GetNumberOfConnections(
	unsigned __int32 *numberOfConnections );


//
//	Description:
//		Check if license is activated as trial.
//
//	Input:
//		licenseIsActivatedAsTrial		- buffer for license trial mode flag
//
//	Output:
//		Return value	- PSC_STATUS_SUCCESS or error code
//		*licenseIsActivatedAsTrial	- license trial mode flag
//
//	Registry keys for debugging:
//		"LicenseIsActivatedAsTrial" of type REG_DWORD (initialized at loading of protect.dll).
//
unsigned __int32 PSAPI PSA_IsLicenseActivatedAsTrial(
	bool *licenseIsActivatedAsTrial );

#endif

//
//	Specific functions for disc binding
//

#ifdef BINDING_DISC

//	Description:
//		Get the label of disc with that the check was passed.
//
//	Input:
//		labelBuffer					- buffer for disc label
//		labelBufferSizeInWideChars	- buffer size
//
//	Output:
//		Return value				- PSC_STATUS_SUCCESS or error code
//			(PSC_STATUS_BUFFER_TOO_SMALL if buffer is too small)
//		*labelBuffer				- label (Unicode zero-terminated string)
//		*labelBufferSizeInWideChars	- used buffer size (or required buffer
//			size is return value is PSC_STATUS_BUFFER_TOO_SMALL)
//
//	Registry keys for debugging:
//		"DiscLabel" of type REG_SZ (initialized at loading of protect.dll).
//
unsigned __int32 PSAPI PSA_GetDiscLabel(
	wchar_t *labelBuffer,
	size_t *labelBufferSizeInWideChars );

#endif

// 
//	Specific functions for external binding
// 

#ifdef PS_EXTERNAL_BASED_INITIALIZATION_SUPPORTED

//
//	Description:
//		Set external binding check success flag. By default flag 
//		is cleared.
//
//	Output:
//		Return value				- PSC_STATUS_SUCCESS or error code
//
unsigned __int32 PSAPI PSA_ExternalBindingCheckSetSucceedFlag();

//
//	Description:
//		Clear external binding check success flag. By default flag 
//		is cleared.
//
//	Output:
//		Return value				- PSC_STATUS_SUCCESS or error code
//
unsigned __int32 PSAPI PSA_ExternalBindingCheckSetFailedFlag();

#endif

//
//	Crypted traffic API
//

#ifdef PS_SUPPORT_CRYPTED_TRAFFIC

// Public RSA key
struct PSA_CryptedTrafficKey
{
	size_t KeySizeInBytes;			// Size of RSA key (current implementation
									// support only 128-byte or 256-byte keys)
	unsigned char *Modulus;					// Little-endian, size is KeySizeInBytes
	unsigned char *Exponent;					// Public exponent, little-endian, size is
									// KeySizeInBytes
};

//
//  Description:
//		Open strem of crypted traffic. The function creates initialization
//		block that should be sent to the remote server as first portion of
//		data.
//
//  Input:
//		randomSeed				    - random seed for session key (can be NULL)
//      randomSeedSize				- size of random seed in bytes (can be 0)
//		key							- public key structure to encrypt
//			initialization block
//		initializationBlock			- initialization block buffer
//		initializationBlockSize		- size of buffer
//
//	Output:
//		Return value				- PSC_STATUS_SUCCESS or error code
//			(PSC_STATUS_BUFFER_TOO_SMALL if buffer is too small)
//  	streamHandle				- stream handle
//		initializationBlockSize		- really used (or required, if return value
//			is PSC_STATUS_BUFFER_TOO_SMALL) size of initialization block
//
//	Note:
//		1.	If randomSeed is NULL or randomSeedSize is 0, the session key will be
//			initialized from timer.
//		2. 	Multiple streams are not supported in current implementation.
//
unsigned __int32 PSAPI PSA_CryptedTrafficOpen(
	const char *randomSeed,
	size_t randomSeedSize,
	PSA_CryptedTrafficKey *key,
	void** streamHandle,
	char *initializationBlock,
	size_t *initializationBlockSize);

//
//  Description:
//		Encrypt byte sequence.
//
//  Input:
//		streamHandle				- stream handle to encrypt bytes for
//      inputData					- input data buffer
//		outputData					- output data buffer
//		dataSize					- length of data in bytes
//
//	Output:
//		Return value				- PSC_STATUS_SUCCESS or error code
//
unsigned __int32 PSAPI PSA_CryptedTrafficEncrypt(
	void *streamHandle,
	char *inputData,
	char *outputData,
	size_t dataSize);

//
//  Description:
//		Decrypt byte sequence.
//
//  Input:
//		streamHandle				- stream handle to decrypt bytes for
//      inputData					- input data buffer
//		outputData					- output data buffer
//		dataSize					- length of data in bytes
//
//	Output:
//		Return value				- PSC_STATUS_SUCCESS or error code
//
unsigned __int32 PSAPI PSA_CryptedTrafficDecrypt(
	void *streamHandle,
	char *inputData,
	char *outputData,
	size_t dataSize);

//
//	Description:
//		Close stream of crypted traffic.
//
//  Input:
//		streamHandle				- stream handle to close
//
//	Output:
//		Return value				- PSC_STATUS_SUCCESS or error code
//
unsigned __int32 PSAPI PSA_CryptedTrafficClose(
	void *streamHandle );

	
#endif

//
//	Additional checks
//

#ifdef PS_SUPPORT_FILE_CHECK_API

//  Description:
//		Return result of integrity checks of loaded files.
//
//  Input:
//		fileCheckResultOk 			- pointer to output variable set to true if
//			all of protected files loaded not corrupted set to false if hash
//			check for one or more files failed
//
//	Output:
//		Return value				- PSC_STATUS_SUCCESS or error code
//
unsigned __int32 PSAPI PSA_GetCheckFilesHashResult( 
	bool *fileCheckResultOk );
#endif

#ifdef PS_SUPPORT_MEMORY_CHECK_API
//
//  Description:
//		Check read-only memory regions of protected modules, calculates hash
//		and compare to hash value stored in protection library
//
//  Input:
//		memCheckResultOk 			- pointer to output variable, set to true
//			if read only memory for all protected modules remains unchanged,
//			set to false if memory changed for one or more modules
//
//	Output:
//		Return value				- PSC_STATUS_SUCCESS or error code
//
unsigned __int32 PSAPI PSA_CheckProtectedModulesReadOnlyMem( 
	bool *memCheckResultOk );

#endif

#ifdef PS_SUPPORT_CERTIFICATE_CHECK

//
//	Description:
//		Generate certificate request packet for sending to the server.
//
//	Input:
//		requestBuffer	 	- buffer for request
//		requestBufferSize	- size of buffer in bytes
//
//	Output:
//		Return value				- PSC_STATUS_SUCCESS or error code
//			(PSC_STATUS_BUFFER_TOO_SMALL if buffer is too small)
//		*requestBuffer				- certificate request
//		*requestBufferSize			- used buffer size in bytes (or required
//			buffer size if return value is PSC_STATUS_BUFFER_TOO_SMALL)
//
unsigned __int32 PSAPI PSA_CertificateGenerateRequest(
	char *requestBuffer,
	size_t *requestBufferSize );

//
//	Description:
//		Validate certificate sent from server.
//
//	Input:
//		responseBuffer				- buffer with response from the server
//		responseBufferSize			- size of buffer in bytes
//
//	Output:
//		returnValue					- PSC_STATUS_SUCCESS of error code
//			(PSC_STATUS_INVALID_PARAMETER if arguments are invalid,
//			PSC_STATUS_CERTIFICATE_INVALID_FORMAT
//				if format of certificate is invalid or validation is failed,
//			PSC_STATUS_CERTIFICATE_NOT_VALID_YET
//				if validity period of certificate is in future,
//			PSC_STATUS_CERTIFICATE_NOT_VALID_ALREADY
//				if validity period of certificate is in past )
//
unsigned __int32 PSAPI PSA_CertificateValidate(
	char *responseBuffer,
	size_t responseBufferSize );

#endif

//
// File System API
//

#ifdef PS_FILE_SYSTEM_USER_MODE

// File position moving origin definition.
#define PSA_FS_SEEK_SET	0
#define PSA_FS_SEEK_CUR	1
#define PSA_FS_SEEK_END	2

//	Description:
//		Open a protected file.
//
//	Input:
//		fileName		- File name to open.
//		fileHandle		- Pointer to output handle of opened file if call succeed.
//
//	Output:
//		Return value	- PSC_STATUS_SUCCESS if success, other PSC_STATUS code if failure.
//
unsigned __int32 PSAPI PSA_FsOpenFile(
	const wchar_t *fileName,
	void **fileHandle );

//	Description:
//		Close a protected file.
//
//	Input:
//		fileHandle		- File handle.
//
//	Output:
//		Return value	- PSC_STATUS_SUCCESS if success, other PSC_STATUS code if failure.
//
unsigned __int32 PSAPI PSA_FsCloseFile(
	void *fileHandle );

//	Description:
//		Retrieve size of the specified protected file.
//
//	Input:
//		fileHandle		- File handle.
//		fileSize		- Pointer to a variable that receives the file size.
//
//	Output:
//		Return value	- PSC_STATUS_SUCCESS if success, other PSC_STATUS code if failure.
//
unsigned __int32 PSAPI PSA_FsGetFileSize(
	void *fileHandle,
	__int64 *fileSize );

//	Description:
//		Move file position of the specified protected file.
//
//	Input:
//		fileHandle		- File handle.
//		origin			- Starting point for the file position move.
//						  This parameter can be one of the following values:
//						    PSA_FS_SEEK_SET - Starting point is the beginning of the file.
//						    PSA_FS_SEEK_CUR - Starting point is the current value of the file position.
//						    PSA_FS_SEEK_END - Starting point is the current end-of-file position.
//		offset			- Distance to move file position from the origin.
//		newOffset		- Pointer to a variable that receives new file position. Can be null.
//
//	Output:
//		Return value	- PSC_STATUS_SUCCESS if success, other PSC_STATUS code if failure.
//
unsigned __int32 PSAPI PSA_FsSetFilePosition(
	void *fileHandle,
	unsigned __int32 origin,
	__int64 offset,
	__int64 *newOffset );

//	Description:
//		Read data from the specified protected file starting at the current file position.
//
//	Input:
//		fileHandle			- File handle.
//		buffer				- Pointer to a buffer that receives the data.
//		numberOfBytesToRead	- Maximum number of bytes to be read.
//		numberOfBytesRead	- Pointer to a variable that receives number of bytes actually read. Can be null.
//
//	Output:
//		Return value		- PSC_STATUS_SUCCESS if success, other PSC_STATUS code if failure.
//
unsigned __int32 PSAPI PSA_FsReadFile(
	void *fileHandle,
	void *buffer,
	size_t numberOfBytesToRead,
	size_t *numberOfBytesRead );

//	Description:
//		Verify digital signature of the specified real file.
//
//	Input:
//		fileName		- File name.
//		valid			- Pointer to a variable that receives result of verification.
//							Nonzero if digital signature of the file is valid, zero if invalid.
//
//	Output:
//		Return value	- PSC_STATUS_SUCCESS if success, other PSC_STATUS code if failure.
//
unsigned __int32 PSAPI PSA_FsVerifyFileSignature(
	const wchar_t *fileName,
	int *valid );

#endif

#ifdef OPTION_ENABLE_EMBEDDED_USER_DATA

//
// Embedded data files API
//

//  Description:
//		Get embedded data block from protection library
//	Input:
//		blockId 		- id of block to get, id must be in range 0..63
//		data			- pointer to data buffer
//		dataSize		- on input contains size of data buffer, on output size of data written to buffer,
//						if need to get block size pass 0
//	Output:	
//		return value 	- PSC_STATUS_SUCCESS if id is in allowed range, and data buffer is big enough, data is copied to output buffer
//						- PSC_STATUS_UNSUCCESSFUL if id is not in allowed range
//						- PSC_STATUS_BUFFER_TOO_SMALL if buffer is not big enough, dataSize contains size of buffer needed
//						- PSC_STATUS_INVALID_PARAMETER if dataSize or data is null pointer
//						or other error code

unsigned __int32 PSAPI PSA_GetEmbeddedDataBlock( 
	unsigned __int32 blockId, 
	char *data, 
	size_t *dataSize );
#endif

#ifdef OPTION_ENABLE_CLIENT_VALIDATION

//  Description:
//		Calculate hash on input buffer
//	Input:
//		input 	- buffer with input data, must have size PSA_VALIDATE_CLIENT_BUFFER_SIZE 
//		output	- pointer to buffer for hash calculated on input buffer, must be at least PSA_VALIDATE_CLIENT_BUFFER_SIZE
//
//	Output:	
//		return value 	- PSC_STATUS_SUCCESS or error code


unsigned __int32 PSAPI PSA_ValidateClient(
	char* input,
	char* output );
	
#endif

#ifdef OPTION_ENABLE_SYSTEM_LIBS_LOCATION_CHECK
//  Description:
//		Function performs check that system libraries(list of libraries is defined in protection options) are located in windows system catalog.
//		To get only fact of system libraries replacement call PSA_CheckSystemLibsLocation( null, null, &systemLibLocationChanged )
//		To get full paths to replaced system libraries pass also valid outBuffer and outBufferSizePtr parameters
//	Input:
//		outBuffer 		- 	Buffer that will contain check result - list of wide characters strings separated by zero wide character, each
//							string is full path to library( including module name ) that is not located in system catalog.
//							If outBuffer is null and outBufferSizePtr is not null, value of outBufferSizePtr will contain necessary buffer size on exit.
//		outBufferSizePtr	-	Pointer to size of outBuffer array, on input contains size of array, 
//								after function returns contains used buffer size.
//								If outBufferSizePtr is null, result is returned in systemLibLocationChangedPtr only.
//		systemLibLocationChangedPtr	-  	Pointer to boolean var that will contain check result. Must not be null.
//										Contains true on exit if one of system libraries( defined in protection options )
//										is located outside of windows system directory. Contains false otherwise. 
//	Output:	
//		return value 	- PSC_STATUS_SUCCESS if function performed successfully
//						- PSC_STATUS_BUFFER_TOO_SMALL if outBuffer is not big enough to save result, outBufferSizePtr will contain size of buffer needed, 
//							value of systemLibLocationChangedPtr is valid in this case
//						- PSC_STATUS_INVALID_PARAMETER if systemLibLocationChangedPtr is null
//						- PSC_STATUS_ERROR_IN_WINAPI if one of modules is not loaded or winapi error
//						- other errors
unsigned __int32 PSAPI PSA_CheckSystemLibsLocation(
	char* outBuffer,
	size_t* outBufferSizePtr,
	bool* systemLibLocationChangedPtr );
#endif

#ifdef OPTION_ENABLE_SYSTEM_LIBS_IAT_CHECK

//  Description:
//		Function performs check that IAT in system libraries(list of libraries is defined in protection options) are not modified
//		To get only fact of IAT modification call PSA_CheckSystemLibsIat( null, null, &systemLibIatModifiedPtr )
//		To get full info on IAT modifications found, pass also valid outBuffer and outBufferSize parameters
//	Input:
//		outBuffer 		- 	Buffer that will contain check result - format of result info is following:
//							
//								UInt16 NumberOfDllsWithIatModified -  16 bit value, number of ModifiedDllInfo structures 
//								followed by sequence of ModifiedDllInfo structure, number of elements in sequence is NumberOfDllsWithIatModified
//								
//								where each ModifiedDllInfo structure is serialized as followed:
//									struct
//									{
//										WideChar* NameOfDllWithModifiedIAT;					// Zero terminated wide string, name of library with IAT modified
//										UInt16 NumberOfIatModifications; 					// 16 bit value, number of modifications found in IAT
//										ModifiedIatEntryInfo[ NumberOfIatModifications ]	// array of of ModifiedIatEntryInfo structures, size is NumberOfIatModifications
//									}ModifiedDllInfo;
//
//									where ModifiedIatEntryInfo structure has following format:
//									struct
//									{
//										WideChar*	ImportedDllName;				// Zero terminated wide string, name of library, function imported from it was patched
//										UInt8		FuncIsImportedByOrdinal;		// 1 byte value, if not 0 indicates that modified entry in IAT was imported by ordinal 
//										// if FuncIsImportedByOrdinal == 0 next follows 
//										WideChar*	ImportedFunctionName;			// Zero terminated wide string, name of function that was pathced in IAT
//										// if FuncIsImportedByOrdinal != 0 next follows
//										UInt16		Ordinal						// 16 bit value, ordinal of function 
//									}ModifiedIatEntryInfo;
//									
//							If outBuffer is null and outBufferSize is not null, outBufferSize will contain necessary buffer size on exit.
//		outBufferSizePtr	-	Pointer to size of outBuffer array, on input contains size of array, after function returns contains used buffer size.
//								If outBufferSize is null, result is returned in systemLibIatModifiedPtr only.
//		systemLibIatModifiedPtr	-  	Pointer to boolean var that will contain check result. Must not be null.
//										Contains true on exit if IAT is modifies in one of system libraries(defined in protection options).
//										Contains false otherwise. 
//	Output:	
//		return value 	- PSC_STATUS_SUCCESS if function performed successfully
//						- PSC_STATUS_BUFFER_TOO_SMALL if outBuffer is not big enough to save result, outBufferSize will contain size of buffer needed, 
//							value of systemLibIatModified is valid in this case
//						- PSC_STATUS_INVALID_PARAMETER if systemLibIatModifiedPtr is null
//						- PSC_STATUS_ERROR_IN_WINAPI if one of modules is not loaded or winapi error
//						- other errors 
unsigned __int32 PSAPI PSA_CheckSystemLibsIat(
	char* outBuffer,
	size_t* outBufferSizePtr,
	bool* systemLibIatModifiedPtr );

#endif
	
#ifdef OPTION_ENABLE_SYSTEM_LIBS_CODE_SECTION_CHECK

//  Description:
//		Function performs check that read only sections are not modified in system DLLs( list of DLLs is defined in protection options )
//		To get only fact of sections modifications call PSP_CheckSystemLibsReadOnlySections( null, null, &readOnlySectionsModified )
//		To get full information on modified regions pass also valid outBuffer and outBufferSizePtr parameters
//	Input:
//		outBuffer 		- 	Buffer that will contain check result - serialized array of LibraryWithModifiedReadOnlySectionInfo structures 
// 							Format of output buffer is:
//
// 								UInt16 	NumLibsWithSectionsModified - 16 bit value, number of libraries with modified read only sections found
//								followed by sequence of LibraryWithModifiedReadOnlySectionInfo structures, 
//								number of elements in sequence is NumLibsWithSectionsModified
//								where each structure LibraryWithModifiedReadOnlySectionInfo is serialized as followed
//
// 									struct
// 									{
// 										WideChar* 	LibraryName; 			// Zero terminated wide char string, library name
//										UInt32		FileVersionLow;		// 32 bit value, file version low part
//										UInt32		FileVersionHigh;		// 32 bit value, file version high part
// 										UInt32		NumRegions;			// 32 bit value, size of modifications array that follows
//										ModifiedRegion[ NumRegions ];	// array of ModifiedRegion structures, size of array is NumRegions
// 									}
// 									LibraryWithModifiedReadOnlySectionInfo;
//
//									where each structure ModifiedRegion is serialized as followed
//
// 									struct
// 									{
//										UInt32 	RegionRva;  	// 32 bit value - rva of modified region
//										UInt32 	RegionSize;	// 32 bit value - size of modified region
// 									}
// 									ModifiedRegion;
//
//							If outBuffer is null and outBufferSizePtr is not null, outBufferSizePtr will contain necessary buffer size on exit.
//		outBufferSizePtr 	-	Pointer to size of outBuffer array, on input contains size of array, after function returns contains used buffer size.
//							If outBufferSizePtr is null, result is returned in readOnlySectionsModifiedPtr only.
//		readOnlySectionsModifiedPtr	-  	Pointer to boolean var that will contain check result. Must not be null.
//										Contains true on exit if read only sections are modified in one of system libraries(defined in protection options).
//										Contains false otherwise. 
//	Output:	
//		return value 	- PSC_STATUS_SUCCESS if function performed successfully
//						- PSC_STATUS_BUFFER_TOO_SMALL if outBuffer is not big enough to save result, outBufferSizePtr will contain size of buffer needed
//						- PSC_STATUS_INVALID_PARAMETER if readOnlySectionsModifiedPtr is null
//						- other errors 	
unsigned __int32 PSAPI PSA_CheckSystemLibsReadOnlySections(
	char* outBuffer,
	size_t* outBufferSizePtr,
	bool* readOnlySectionsModifiedPtr );
	
#endif