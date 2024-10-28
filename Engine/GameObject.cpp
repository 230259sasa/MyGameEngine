#include "GameObject.h"
#include"Direct3D.h"

GameObject::GameObject()
	:pParent_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
	:pParent_(parent),objectName_(name),isDead_(false)
{
	if (parent != nullptr) {
		this->transform_.pParent_ = &(parent->transform_);
	}
}

GameObject::~GameObject()
{
}

void GameObject::UpdateSub()
{
	Update();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {
		(*itr)->UpdateSub();
	}

	for (auto itr = childList_.begin(); itr != childList_.end();) {
		if ((*itr)->isDead_)
		{
			(*itr)->ReleaseSub();
			////(*itr)->Release();
			//delete (*itr);
			//(*itr) = nullptr;
			SAFE_DELETE(*itr);
			itr = childList_.erase(itr);
		}
		else {
			itr++;
		}
	}
}

void GameObject::DrawSub()
{
	Draw();
	for (auto itr : childList_) {
		itr->DrawSub();
	}
}

void GameObject::ReleaseSub()
{
	Release();
	for (auto itr : childList_) {
		itr->ReleaseSub();
	}
}

void GameObject::KillMe()
{
	isDead_ = true;
}

GameObject* GameObject::FindObject(std::string objName)
{
	/*GameObject* rootJob = GetRootJob();
	GameObject* res = rootJob->FindChildObject(objName);
	return res;*/
	return GetRootJob()->FindChildObject(objName);
}

GameObject* GameObject::GetRootJob()
{
	if (pParent_ == nullptr) {
		return this;
	}
	return pParent_->GetRootJob();
}

GameObject* GameObject::FindChildObject(std::string objName)
{
	if (this->objectName_ == objName) {
		return this;
	}
	else {
		for (auto itr : childList_) {
			GameObject* obj = itr->FindChildObject(objName);
			if (obj != nullptr);
			return obj;
		}
	}
	return nullptr;
}
