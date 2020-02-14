#include "ServerInfo.h"

ServerInfo::ServerInfo(int t) :totalcapacity_(t), usedcapacity_(0), remaincapacity_(t)
{
	usermap_ = new UserMap;
	waiting_usermap_ = new UserMap;
	admininfo_ = new AdminInfo;
}

ServerInfo::ServerInfo(int t, UserMap usermap, UserMap waitingusermap): totalcapacity_(t), usedcapacity_(0), remaincapacity_(t)
{
	usermap_ = new UserMap;
	UserMap::iterator uiter = usermap.begin();
	for (; uiter != usermap.end(); uiter++)
		usermap_->insert({ uiter->first,uiter->second });

	waiting_usermap_ = new UserMap;
	UserMap::iterator witer = waitingusermap.begin();
	for (; witer != waitingusermap.end(); witer++)
		waiting_usermap_->insert({ witer->first,witer->second });

	admininfo_ = new AdminInfo;
}

ServerInfo::~ServerInfo()
{
	delete usermap_;
	delete waiting_usermap_;
	delete admininfo_;
}
