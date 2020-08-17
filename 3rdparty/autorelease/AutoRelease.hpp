///
/// AutoRelease system.
///
/// Enables the use of the RAII paradigm on arbitrary types.
/// Usage: AUTORELEASE(fp);               // looks for "void Release(FILE*& fp)"
/// Usage: AUTORELEASEF(fp, &tmp::close); // callback can be specified manually
/// Usage: AUTORELEASEL(fp, (FILE*& fp){ fclose(fp); fp = NULL; }); // lambda
///
/// Creates a hidden helper object, which runs user-provided code in its destructor,
/// either in the form of an matching callback or an inline fake-lambda function.
///
/// Inspired by the Loki library's ScopeGuard.h (https://loki-lib.sourceforge.net/)
///
#pragma once


/// Non-template dummy base class.
class AutoReleaseBase
{
private:
	AutoReleaseBase& operator =(const AutoReleaseBase&); // no copy operator
};

/// Main class. Performs release operation in destructor.
template<typename T> class AutoRelease : public AutoReleaseBase
{
public:
	typedef void (ReleaseFunc)(T& var);

	AutoRelease(T& var, ReleaseFunc& func)
	: var(var), func(func)
	{
	}

	~AutoRelease()
	{
		func(var);
	}

private:
	T& var;
	ReleaseFunc& func;
};

/// Constructs object on stack without having to manually specify template parameters.
template<typename T> AutoRelease<T> AutoReleaseObj(T& var, typename AutoRelease<T>::ReleaseFunc& rel)
{
	return AutoRelease<T>(var, rel);
}

/// Creates sort-of unique variable names.
#define AR_CONCATENATE(s1,s2)   s1##s2
#define AR_CONCATENATE2(s1,s2)  AR_CONCATENATE(s1,s2)
#define AR_ANONYMOUS_NAME(name) AR_CONCATENATE2(name, __LINE__)

/// Readability improvement macros.
#define AR_VARNAME     AR_ANONYMOUS_NAME(AutoReleaseVar)
#define AR_LAMBDANAME  AR_ANONYMOUS_NAME(AutoReleaseLambda)
#define AR_DUMMYREF(x) x // to silence unused variable warnings

/// The feature itself, in three useful forms.
#define AUTORELEASEF(var,func) const AutoReleaseBase& AR_VARNAME = AutoReleaseObj(var,func); AR_DUMMYREF(AR_VARNAME);
#define AUTORELEASEL(var,code) struct AR_LAMBDANAME { static void Release code }; AUTORELEASEF(var, &AR_LAMBDANAME::Release);
#define AUTORELEASE(var)       AUTORELEASEF(var, &Release);
