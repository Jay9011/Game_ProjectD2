#pragma once

#include "tinyxml2/tinyxml2.h"

namespace Engine
{
    /**
     * GameObject의 GUID 생성
     *
     * @return GUID
     */
    string GenerateGUID();

    /**
     * Game에서 사용하는 모든 객체의 기본 클래스
     * Reflection, Serialization 등을 지원
     */
    class GameObject
    {
    public:
        GameObject(const string& guid);
        virtual ~GameObject();

    protected:
        /** Object 고유 식별자 */
        string guid;

        /** Object 이름 */
        string name;

        /** Object 태그 */
        list<string> tags;

    public:
        void AddTag(const string& tag) { tags.push_back(tag); }
        void RemoveTag(const string& tag) { tags.remove(tag); }
        bool HasTag(const string& tag) const { return find(tags.begin(), tags.end(), tag) != tags.end(); }

    //////////////////////////////////////////////////////////////////////////
    /// Reflection
    //////////////////////////////////////////////////////////////////////////
    public:
        /** 클래스 이름 반환 */
        virtual const char* ClassName() const { return "GameObject"; }

    //////////////////////////////////////////////////////////////////////////
    /// Serialization
    //////////////////////////////////////////////////////////////////////////
    public:
        /**
         * XML로 직렬화
         *
         * @param parentElement     상위 XML
         */
        virtual void Serialize(XmlElement* parentElement);
        /**
         * 역직렬화
         *
         * @param objectElement     Object XML
         */
        virtual void Deserialize(XmlElement* objectElement);

    //////////////////////////////////////////////////////////////////////////
    /// Getter & Setter
    //////////////////////////////////////////////////////////////////////////
    public:
        /** GUID 반환 */
        const string& GetGUID() const { return guid; }
        void SetGUID(const string& guid) { this->guid = guid; }

        const string& GetName() const { return name; }
        void SetName(const string& name) { this->name = name; }
    };
}