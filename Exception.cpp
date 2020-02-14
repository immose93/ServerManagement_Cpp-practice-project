#include "Exception.h"

std::vector<std::string> Exception::exceptiontype_ = {
	"ESC",	// kPressEsc
	"올바른 메뉴 번호를 입력하세요. (종료 : ESC)",	// kInvalidMenuInput
	"존재하지 않는 ID 입니다. ",	// kNotExistsInUserMap
	"휴면계정입니다.",				// kDormant
	"비밀번호가 틀렸습니다.",		// kWrongPassword
	"권한 레벨이 틀렸습니다.",	// kWrongLevel
	"님의 계정이 휴면처리 되었습니다.",	// kFailedFiveTimes
	"관리자 코드와 일치하지 않습니다.",	// kInvalidAdminCode
	"이미 존재하는 ID 입니다.",	// kExistsInUsermap
	"이미 회원가입 승인 대기중인 ID 입니다.",	// kExistInWaitingUsermap
	"유효하지 않은 주민번호입니다.",	// kInvalidRRN
	"유효하지 않은 권한레벨입니다.",	// kInvalidLevel
	"비밀번호는 8자 이상이어야 합니다.",	// kShortPassword
	"비밀번호는 영어 대소문자 및 숫자만 가능합니다.", // kIsNotAlphabetOrNumber
	"비밀번호에 사용자의 주민번호가 포함되어 있습니다.",	// kRRNInPassword
	"읽기만 가능합니다.",	// kReadOnly
	"쓰기만 가능합니다.",	// kWriteOnly
	"더 이상 하드 용량을 추가할 수 없습니다. (총 3회 추가)",	// kAddCapacityMaxCount
	"입력이 잘못되었습니다. 다시 입력해주세요.",	// kInvalidInput

	"님의 가입 요청이 승인되었습니다.",	// kAcceptSignUpRequest
	"님의 가입 요청이 거절되었습니다.",	// kRejectSignUpRequest
};
