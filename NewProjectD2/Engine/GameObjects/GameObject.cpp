#include "pch.h"
#include "GameObject.h"

namespace Engine
{
    string GenerateGUID()
    {
        static int guid = 0;
        return to_string(guid++);
    }

    GameObject::GameObject(const string& guid = GenerateGUID())
	    : guid(guid), name("UnNamed"), tags()
    {
    }

    GameObject::~GameObject()
    {
    }

    void GameObject::Serialize(XmlElement* parentElement)
    {
	    XmlDocument* doc = parentElement->GetDocument();

	    XmlElement* objectElement = doc->NewElement("GameObject");
	    objectElement->SetAttribute("class", ClassName());
	    objectElement->SetAttribute("guid", guid.c_str());
	    objectElement->SetAttribute("name", name.c_str());

	    // 태그 직렬화
	    XmlElement* tagsElement = doc->NewElement("Tags");
	    for (const string& tag : tags)
	    {
		    XmlElement* tagElement = doc->NewElement("Tag");
		    tagElement->SetText(tag.c_str());
		    tagsElement->InsertEndChild(tagElement);
	    }

	    objectElement->InsertEndChild(tagsElement);

	    parentElement->InsertEndChild(objectElement);
    }

    void GameObject::Deserialize(XmlElement* objectElement)
    {
	    if (!objectElement) return;

	    guid = objectElement->Attribute("guid");
	    name = objectElement->Attribute("name");

	    // 태그 역직렬화
	    XmlElement* tagsElement = objectElement->FirstChildElement("Tags");
	    if (tagsElement)
	    {
		    for (XmlElement* tagElement = tagsElement->FirstChildElement("Tag");
			    tagElement != nullptr;
			    tagElement = tagElement->NextSiblingElement("Tag"))
		    {
			    const char* tag = tagElement->GetText();
			    tags.push_back(tag);
		    }
	    }
    }
}