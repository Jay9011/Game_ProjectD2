#pragma once

#include "tinyxml2/tinyxml2.h"

/// <summary>
/// GameObject의 GUID 생성
/// </summary>
/// <returns>string GUID</returns>
string GenerateGUID();

/// <summary>
/// Game에서 사용하는 모든 객체의 기본 클래스
/// Reflection, Serialization 등을 지원
/// </summary>
class GameObject
{
protected:
	string guid;
	string name;
	list<string> tags;

public:
	GameObject(const string& guid);
	virtual ~GameObject();

public:
	const string& GetGUID() const { return guid; }
	void SetGUID(const string& guid) { this->guid = guid; }
	const string& GetName() const { return name; }
	void SetName(const string& name) { this->name = name; }
	void AddTag(const string& tag) { tags.push_back(tag); }
	void RemoveTag(const string& tag) { tags.remove(tag); }
	bool HasTag(const string& tag) const { return find(tags.begin(), tags.end(), tag) != tags.end(); }

	//////////////////////////////////////////////////////////////////////////
	/// Reflection
	//////////////////////////////////////////////////////////////////////////
public:
	virtual const char* ClassName() const { return "GameObject"; }

	//////////////////////////////////////////////////////////////////////////
	/// Serialization
	//////////////////////////////////////////////////////////////////////////
public:
    /// <summary>
    /// XML로 직렬화
    /// </summary>
    /// <param name="parentElement">상위 XML</param>
	virtual void Serialize(XmlElement* parentElement);
    /// <summary>
    /// 역직렬화
    /// </summary>
    /// <param name="objectElement"></param>
	virtual void Deserialize(XmlElement* objectElement);
};