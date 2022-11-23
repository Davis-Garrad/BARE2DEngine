#include <stdio.h>

#include <App.hpp>
#include <Filesystem.hpp>
#include <Logger.hpp>
#include <XMLDataManager.hpp>
#include <XMLDataTypes.hpp>

#include <string>

class CustomDataType : public BARE2D::XMLData
{
   public:
    CustomDataType() : BARE2D::XMLData()
    {
	init();
    }
    CustomDataType(unsigned int ID, std::string Name) : BARE2D::XMLData()
    {
	init();
	id = ID;
	name = Name;
    }

    void init()
    {
	customFloat = new float(0.0f);
	customFloatVector = new std::vector<float>{};
	addAttribute("customDataFloat", BARE2D::AttributeType::FLOAT, customFloat);
	addAttribute("customDataFloatVector", BARE2D::AttributeType::VECTOR_FLOAT, customFloatVector);
	nodeName = "testDataType";
    }

    float* customFloat = nullptr;
    std::vector<float>* customFloatVector = nullptr;
};

int main(int argc, char** argv)
{
    BARE2D::App app;
    app.run();

    unsigned int dataID = 420;

    CustomDataType dataTest(dataID, "Some pointless name here");
    *dataTest.customFloat = 69.6969f;
    *dataTest.customFloatVector = std::vector<float>{1.0f, 1.0f, 2.0f, 3.0f, 5.0f, 8.0f, 13.0f};
    std::string tempString = std::to_string((*dataTest.customFloatVector)[0]);
    for(unsigned int i = 1; i < (*dataTest.customFloatVector).size(); i++)
	{
	    tempString += ", " + std::to_string((*dataTest.customFloatVector)[i]);
	}

    BARE2D::Logger::getInstance()->log("Contextual information: \nCustom float data to be manipulated: " +
                                       std::to_string(*dataTest.customFloat) + "\nCustom vector data: " + tempString);

    BARE2D::Logger::getInstance()->log("BEGIN WRITE OPERATION", true);

    BARE2D::XMLDataManager::addData(&dataTest);

    std::string writeDir = BARE2D::Filesystem::getWorkingDirectory() + "/Write";
    std::string readDir = BARE2D::Filesystem::getWorkingDirectory() + "/Read";

    BARE2D::XMLDataManager::saveXML(writeDir);

    BARE2D::Logger::getInstance()->log("FILE WRITTEN. CLEARING CACHE", true);

    BARE2D::XMLDataManager::clearCache();

    BARE2D::Logger::getInstance()->log("BEGIN READ/COPY OPERATION", true);

    BARE2D::XMLDataManager::addDataType<CustomDataType>();
    BARE2D::XMLDataManager::loadXML(writeDir);
    BARE2D::XMLDataManager::saveXML(readDir);

    BARE2D::Logger::getInstance()->log("FILE READ AND COPIED", true);

    CustomDataType t = BARE2D::XMLDataManager::getData<CustomDataType>("testDataType", dataID);
    float dataFloat = t.getAttributeByName<float>("customDataFloat");
    std::vector<float> dataVec = t.getAttributeByName<std::vector<float>>("customDataFloatVector");

    BARE2D::Logger::getInstance()->log("RESULTS:", true);

    BARE2D::Logger::getInstance()->log("Lone float: " + std::to_string(dataFloat));

    std::string vecFloatStr = std::to_string(dataVec[0]);

    for(unsigned int i = 1; i < dataVec.size(); i++)
	{
	    vecFloatStr += ", " + std::to_string(dataVec[i]);
	}

    BARE2D::Logger::getInstance()->log("Vector of floats: " + vecFloatStr);

    BARE2D::Logger::getInstance()->log("END", true);

    return 0;
}
