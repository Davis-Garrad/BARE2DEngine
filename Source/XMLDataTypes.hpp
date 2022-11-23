#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <rapidxml/rapidxml.hpp>

namespace BARE2D {
enum class AttributeType
{
    STRING,
    UNSIGNED_INT,
    VECTOR_UNSIGNED_INT,
    INT,
    FLOAT,
    VECTOR_FLOAT,
    BOOL,
    VECTOR_BOOL,
    VEC2,
    VECTOR_VEC2,
    SCRIPT,
    TEXTURE
};

/**
 * @class AttributeBase
 * @brief The AttributeBase class only exists for some templating acrobatics reasons (as an abstract base class for
 * Attribute)
 */
class AttributeBase
{
   public:
    template <typename T> void setData(T data);

    template <typename T> T getData();

    template <typename T> T* getDataPointer();

    template <typename T> void swapDataPointer(T* newPtr);

    virtual ~AttributeBase()
    {}

    std::string name;
    AttributeType type;

    virtual std::string getDataString() = 0;

   protected:
    virtual void setDefaultData() = 0;
};

template <typename T> class Attribute : public AttributeBase
{
    friend class XMLData;

   public:
    Attribute()
    {}
    Attribute(std::string Name, AttributeType Type, T* data);
    ~Attribute()
    {}

    /**
     * @brief Sets the actual value of the data pointer, not the address.
     * @param data The data to set it to.
     */
    void setData(T data);

    /**
     * @brief Changes the old value of newPtr to that of this class' data, then changes this class' data pointer to
     * newPtr.
     * @param newPtr
     */
    void swapDataPointer(T* newPtr);

    /**
     * @return The data
     */
    T getData();
    /**
     * @return A pointer to the data.
     */
    T* getDataPointer();

    /**
     * @brief Creates a string for XML writing of the data.
     * @return A writable string.
     */
    virtual std::string getDataString() override;

   private:
    T* m_data = nullptr;

    /**
     * @brief Sets the data to its format's equivalent to 0.
     */
    virtual void setDefaultData() override;
};

/**
 * @class XMLData
 * @brief Holds all the very basic information for XML data. Designed to be a base class from which a user can derive
 * custom data formats.
 */
class XMLData
{
   public:
    XMLData();
    XMLData(std::string dataType, unsigned int ID);
    XMLData(std::vector<AttributeBase*> attributes);
    XMLData(std::unordered_map<std::string, AttributeBase*> attributes);
    ~XMLData()
    {}

    /**
     * @brief Reads the entire piece of data from a given XML node
     * @param node The node to interpret and read from
     */
    void read(rapidxml::xml_node<>* node);
    /**
     * @brief Writes the entire piece of data to a new node in the XML document
     * @param doc The document to write to.
     */
    void write(rapidxml::xml_document<>* doc);

    /**
     * @brief Finds an attribute by its name (eg. "name", "id")
     * @param name The name of the attribute
     * @return A copy of the data held by the attribute.
     */
    template <typename T> T getAttributeByName(std::string name);

    /**
     * @return Returns a copy of the entire attributes map. Useful for pseudo-copy operations.
     */
    std::unordered_map<std::string, AttributeBase*> getAttributes();

    std::string name;
    unsigned int id;
    std::string nodeName;

   protected:
    /**
     * @brief Constructs and adds an attribute to the data.
     * @param name The name of the attribute. "name" and "id" are already in use, please don't break things like that.
     * @param type The type of data. Eg. AttributeType::FLOAT is a float, AttributeType::VECTOR_FLOAT is a vector of
     * floats, etc.
     * @param data A pointer to the data that the attribute is linked to.
     */
    template <typename T> void addAttribute(std::string name, AttributeType type, T* data);
    /**
     * @brief Adds an attribute to the data
     * @param attr A pointer to the attribute to be added.
     */
    void addAttribute(AttributeBase* attr);

    /**
     * @brief Bulk adds attributes to the data.
     * @param attrs A vector of pointers to attributes to add.
     */
    void addAttributes(std::vector<AttributeBase*> attrs);

    std::unordered_map<std::string, AttributeBase*> m_attributes;
};
}  // namespace BARE2D

#include "XMLDataTypes.tcc"
