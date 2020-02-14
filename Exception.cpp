#include "Exception.h"

std::vector<std::string> Exception::exceptiontype_ = {
	"ESC",	// kPressEsc
	"�ùٸ� �޴� ��ȣ�� �Է��ϼ���. (���� : ESC)",	// kInvalidMenuInput
	"�������� �ʴ� ID �Դϴ�. ",	// kNotExistsInUserMap
	"�޸�����Դϴ�.",				// kDormant
	"��й�ȣ�� Ʋ�Ƚ��ϴ�.",		// kWrongPassword
	"���� ������ Ʋ�Ƚ��ϴ�.",	// kWrongLevel
	"���� ������ �޸�ó�� �Ǿ����ϴ�.",	// kFailedFiveTimes
	"������ �ڵ�� ��ġ���� �ʽ��ϴ�.",	// kInvalidAdminCode
	"�̹� �����ϴ� ID �Դϴ�.",	// kExistsInUsermap
	"�̹� ȸ������ ���� ������� ID �Դϴ�.",	// kExistInWaitingUsermap
	"��ȿ���� ���� �ֹι�ȣ�Դϴ�.",	// kInvalidRRN
	"��ȿ���� ���� ���ѷ����Դϴ�.",	// kInvalidLevel
	"��й�ȣ�� 8�� �̻��̾�� �մϴ�.",	// kShortPassword
	"��й�ȣ�� ���� ��ҹ��� �� ���ڸ� �����մϴ�.", // kIsNotAlphabetOrNumber
	"��й�ȣ�� ������� �ֹι�ȣ�� ���ԵǾ� �ֽ��ϴ�.",	// kRRNInPassword
	"�б⸸ �����մϴ�.",	// kReadOnly
	"���⸸ �����մϴ�.",	// kWriteOnly
	"�� �̻� �ϵ� �뷮�� �߰��� �� �����ϴ�. (�� 3ȸ �߰�)",	// kAddCapacityMaxCount
	"�Է��� �߸��Ǿ����ϴ�. �ٽ� �Է����ּ���.",	// kInvalidInput

	"���� ���� ��û�� ���εǾ����ϴ�.",	// kAcceptSignUpRequest
	"���� ���� ��û�� �����Ǿ����ϴ�.",	// kRejectSignUpRequest
};
