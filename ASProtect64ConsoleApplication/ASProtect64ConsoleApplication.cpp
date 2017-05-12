/*
ASProtect64ConsoleApplication.cpp

This sample application shows how to implement some of the features, which can 
be switched on and off, depending on your licensing properties.

IMPORTANT NOTE:
You would use:

#define ASPEXPORTAPI __declspec(dllexport)

in order to allow function protection with ASProtect. If this statement is
missing, functions are not exported to the linker and may or may not be
protected by ASProtect, depending on other settings of your project.

Without, you still can limit code from execution, but functions are static.
*/

#include "stdafx.h"

#define SubtractFeatureGranted PSA_GrantedFeature0	// CustomRight1 in Protection Studio
#define MultiplyFeatureGranted PSA_GrantedFeature1  // CustomRight2 in Protection Studio
#define DivideFeatureGranted PSA_GrantedFeature2    // CustomRight3 in Protection Studio

// PSA_GetLicenseLifeTimeLimit returns this value, if life time is not defined
#define UndefinedTimeValue ~0ui64

// Structure holding parameters of your license
struct License
{
	bool TrialMode;							// True if trial mode is presented, false otherwise
	bool IsLicenseActivatedAsTrial;         // True if license is activated as trial, false otherwise
	bool DemoMode;							// True if demo mode is presented, false otherwise
	bool Expired;                           // True if license is expired, false otherwise
	unsigned __int32 Features;				// Represents features granted by license
	unsigned __int64 LifeTimeLimit;         // Life time of license
	unsigned __int64 ExpirationDateTime;	// Time when license will expire
	unsigned __int64 TimeToExpiration;		// Left time to expiration of license
											// ...
											// You can add any other parameters that you need.
											// ...
};

/* ----------------------------------------------------------------------------
Retrieves license using ASProtect API methods.

Returns PSC_STATUS_SUCCESS if license was retrieved correctly, 
PSC_STATUS_UNSUCCESSFUL otherwise.
*/
__int32 RetrieveLicense(License *license)
{
	__int32 result = PSC_STATUS_SUCCESS;

	if (PSA_IsTrialMode(&license->TrialMode) != PSC_STATUS_SUCCESS)
	{
		printf("Error in PSA_IsTrialMode\n");
		result = PSC_STATUS_UNSUCCESSFUL;
	}

	if (PSA_IsLicenseActivatedAsTrial(&license->IsLicenseActivatedAsTrial) != PSC_STATUS_SUCCESS)
	{
		printf("Error in PSA_IsLicenseActivatedAsTrial\n");
		result = PSC_STATUS_UNSUCCESSFUL;
	}

	if (PSA_IsDemoMode(&license->DemoMode) != PSC_STATUS_SUCCESS)
	{
		printf("Error in PSA_IsDemoMode\n");
		result = PSC_STATUS_UNSUCCESSFUL;
	}

	if (PSA_IsLicenseExpired(&license->Expired, false) != PSC_STATUS_SUCCESS)
	{
		printf("Error in PSA_IsLicenseExpired\n");
		result = PSC_STATUS_UNSUCCESSFUL;
	}

	if (PSA_GetFeaturesGrantedByLicense(&license->Features) != PSC_STATUS_SUCCESS)
	{
		printf("Error in PSA_GetFeaturesGrantedByLicense\n");
		result = PSC_STATUS_UNSUCCESSFUL;
	}

	if (PSA_GetLicenseLifeTimeLimit(&license->LifeTimeLimit) != PSC_STATUS_SUCCESS)
	{
		printf("Error in PSA_GetLicenseLifeTimeLimit\n");
		result = PSC_STATUS_UNSUCCESSFUL;
	}

	if (PSA_GetLicenseExpirationDateTime(&license->ExpirationDateTime) != PSC_STATUS_SUCCESS)
	{
		printf("Error in PSA_GetLicenseExpirationDateTime\n");
		result = PSC_STATUS_UNSUCCESSFUL;
	}

	if (PSA_GetTimeToLicenseExpiration(&license->TimeToExpiration) != PSC_STATUS_SUCCESS)
	{
		printf("Error in PSA_GetTimeToLicenseExpiration\n");
		result = PSC_STATUS_UNSUCCESSFUL;
	}

	return result;
}

/* ----------------------------------------------------------------------------
Converts time value to string representation using specified format.

Available formats you can see at MSDN:

http://msdn.microsoft.com/en-us/library/aa272978(v=vs.60).aspx
*/
char* StringFromTime(unsigned __int64 rawtime, const char* format)
{
	time_t        seconds;
	tm                time;

	char* result = new char[100];

	seconds = (time_t)(rawtime / 10000000);
	_localtime64_s(&time, &seconds);
	strftime(result, 100, format, &time);

	return result;
}

/* ----------------------------------------------------------------------------
Shows detailed information about a license
*/
void ShowInformationAbout(License license)
{
	char* lpszLifeTimeLimit;
	char* lpszTimeToExpiration;

	// License information
	if (license.Expired)
	{
		/*
		Happens if:
		- the current date is greater than the expiration date
		- the number of executions/runs exceeds the limit
		*/
		printf("License is expired\n");
	}
	else if (license.DemoMode) 
	{
		/*
		Happens if:
		- the user has chosen to run in demo mode rather than inserting a 
		  license
		*/
		printf("Demo mode\n");
	}
	else if (license.TrialMode)
	{
		/*
		Expires after the settings in your ASProtect Project.

		Happens if:
		- there is no demo mode available and no license either
		*/
		printf("Trial mode\n");
	}
	else if (license.IsLicenseActivatedAsTrial) 
	{
		/*
		Happens if:
		- the user has chosen to run the program as trial.
		*/
		printf("License is activated as trial\n");
	}
	else if (license.LifeTimeLimit != UndefinedTimeValue)
	{
		/*
		Happens if:
		- the license has a start and stop life time (rent mode).
		*/
		lpszLifeTimeLimit = StringFromTime(license.LifeTimeLimit, "%X");
		lpszTimeToExpiration = StringFromTime(license.TimeToExpiration, "%X");
		printf(
			"Current license life time is %s, %s left.\n", 
			lpszLifeTimeLimit, 
			lpszTimeToExpiration
		);

		delete[] lpszLifeTimeLimit;
		delete[] lpszTimeToExpiration;
	}
	printf("\n");

	printf("Granted features:\n");
	printf("- Addition\n");
	if (license.Features & SubtractFeatureGranted) 
	{
		printf("- Subtraction\n");
	}
	if (license.Features & MultiplyFeatureGranted)
	{
		printf("- Multiplication\n");
	}
	if (license.Features & DivideFeatureGranted)
	{
		printf("- Division\n");
	}
}

/* ----------------------------------------------------------------------------
Adds two numbers and shows the result. This method works with any license.
*/
ASPEXPORTAPI void Add(int x, int y, License license)
{
	printf("%d + %d = %d\n", x, y, x + y);
}

/* ----------------------------------------------------------------------------
Subtracts one number by another and shows the result.
This method works only when SubtractFeatureGranted bit is enabled.
It is recommended to protect this method with PSA_GrantedFeature0 set:
CustomRight1 in Protection Studio.
*/
ASPEXPORTAPI void Subtract(int x, int y, License license)
{
	if (license.Features & SubtractFeatureGranted)
	{
		printf("%d - %d = %d\n", x, y, x - y);
	}
	else 
	{
		printf("Operation is not allowed!\n");
	}
}

/* ----------------------------------------------------------------------------
Multiplies one number by another and shows the result.
This method works only when MultiplyFeatureGranted bit is enabled.
It is recommended to protect this method with PSA_GrantedFeature1 set (CustomRight2 in Protection Studio)
(it will increase the protection quality).
*/
ASPEXPORTAPI void Multiply(int x, int y, License license)
{
	if (license.Features & MultiplyFeatureGranted)
		printf("%d * %d = %d\n", x, y, x * y);
	else printf("Operation is not allowed!\n");
}

/* ----------------------------------------------------------------------------
Divides one number by another and shows the result.
This method works only when DivideFeatureGranted bit is enabled.
It is recommended to protect this method with PSA_GrantedFeature2 set (CustomRight3 in Protection Studio)
(it will increase the protection quality).
*/
ASPEXPORTAPI void Divide(int x, int y, License license)
{
	if (license.Features & DivideFeatureGranted)
		printf("%d / %d = %d\n", x, y, x / y);
	else printf("Operation is not allowed!\n");
}

/* ----------------------------------------------------------------------------
Ask user if he wants to continue calculations and returns true if so (otherwise false).
*/
bool RequestContinuation()
{
	printf("Do you want to calculate another expression? (Y/N)");
	int key = _getche();

	printf("\n\n");

	if (toupper(key) == 'Y') return true;
	else return false;
}

/* ----------------------------------------------------------------------------
All operations except addition can be performed only one time for each launch of application.
*/
void ModifyCurrentLicenseState(License license, char lastOperation)
{
	switch (lastOperation)
	{
	case '-':
		if (license.Features & SubtractFeatureGranted)
		{
			// Debugging ( for more information on this method see documentation )
			PSA_CheckFeaturesGrantedByLicense(SubtractFeatureGranted);
			// Remove subtraction feature from granted features
			printf("Only one subtraction is allowed, so it will be removed from granted features.\n");
			PSA_DisableFeaturesGrantedByLicense(SubtractFeatureGranted);
		}
		break;
	case '*':
		if (license.Features & MultiplyFeatureGranted)
		{
			// Debugging ( for more information on this method see documentation )
			PSA_CheckFeaturesGrantedByLicense(MultiplyFeatureGranted);
			// Remove multiplication feature from granted features
			printf("Only one multiplication is allowed, so it will be removed from granted features.\n");
			PSA_DisableFeaturesGrantedByLicense(MultiplyFeatureGranted);
		}
		break;
	case '/':
		if (license.Features & DivideFeatureGranted)
		{
			// Debugging ( for more information on this method see documentation )
			PSA_CheckFeaturesGrantedByLicense(DivideFeatureGranted);
			// Remove division feature from granted features
			printf("Only one division is allowed, so it will be removed from granted features.\n");
			PSA_DisableFeaturesGrantedByLicense(DivideFeatureGranted);
		}
		break;
	}

	// ...
	// You can use any other logic here.
	// ...
}

/* ----------------------------------------------------------------------------
Calculation method
1) Read expression to be calculated.
2) Parse it and call appropriate method.
3) Modify current license state.
*/
void ProcessCalculation(License license)
{
	int x, y;
	char operation;

	printf("Enter operation string and press Enter key (sample: 2 + 2)\n");

	// Break execution of method if expression is not valid
	if (3 != scanf_s("%d %c %d", &x, &operation, 1, &y))
	{
		printf("Invalid operation string\n");
		return;
	}

	switch (operation)
	{
	case '+':        Add(x, y, license);                break;
	case '-':        Subtract(x, y, license);        break;
	case '*':        Multiply(x, y, license);        break;
	case '/':        Divide(x, y, license);        break;

	default:        printf("Invalid operation\n");
	}

	ModifyCurrentLicenseState(license, operation);
}

/* ----------------------------------------------------------------------------
Method serves to check license.
Returns true if license is valid, false otherwise.
*/
bool CheckIfLicenseIsValid(License license)
{
	if (license.Expired) return false;

	// ...
	// Here can be any other checks that you need
	// ...

	return true;
}

/* ----------------------------------------------------------------------------
Main procedure.
1) Retrieve license to local variable
2) Show information about it
3) If license is valid, call ProcessCalculation method
4) Ask user for continuation and go to first step if they agreed
*/
int main()
{
	License license;
	__int32 result = PSC_STATUS_SUCCESS;

	if (RetrieveLicense(&license) != PSC_STATUS_SUCCESS)
	{
		// Stop execution if the license retrieval failed.
		return 0;
	}

	// Show license information
	ShowInformationAbout(license);

	while(true)
	{
		if (!license.Expired)
		{
			// Run code
			ProcessCalculation(license);
		}

		// Ask user action
		if (!RequestContinuation())
		{
			// User chose N
			break;
		}
	}
	
	return 0;
}

