#pragma once
#include <vector>
#include <map>
#include <string>

class Exception
{
private:
	static std::vector<std::string> exceptiontype_;
public:
	enum ExceptionName {
		kPressEsc,
		kInvalidMenuInput,
		kNotExistsInUserMap,
		kDormant,
		kWrongPassword,
		kWrongLevel,
		kFailedFiveTimes,
		kInvalidAdminCode,
		kExistsInUsermap,
		kExistInWaitingUsermap,
		kInvalidRRN,
		kInvalidLevel,
		kShortPassword,
		kIsNotAlphabetOrNumber,
		kRRNInPassword,
		kReadOnly,
		kWriteOnly,
		kAddCapacityMaxCount,
		kInvalidInput,
		kAcceptSignUpRequest,
		kRejectSignUpRequest,
	};
	Exception(){}
	static std::string get_exceptiontype_(size_t i) { return exceptiontype_[i]; }
};
