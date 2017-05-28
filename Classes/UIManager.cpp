#include "UIManager.h"
#include "cocos2d.h"

UIManager::UIManager()
{

}

UIManager::~UIManager()
{

}

Label* UIManager::GenerateText(const std::string labelname, const std::string text, const std::string filepath, const float size, const Vec2 pos)
{
    auto label = Label::createWithTTF(text, filepath, size);
    label->setPosition(Point(pos.x, pos.y));
    m_LabelMap.insert(m_LabelMap.end(), std::pair<std::string, Label*>(labelname, label));
    return label;
}

Label* UIManager::RemoveText(const std::string labelname)
{
    return m_LabelMap[labelname];
}

ui::Button* UIManager::GenerateButton(const std::string text, const std::string buttonfilepath, const std::string pressedfilepath, const float fontsize, const Vec2 pos)
{
    auto button = ui::Button::create(buttonfilepath, pressedfilepath);
    button->setTitleText(text);
    button->setTitleFontSize(fontsize);
    button->setPosition(Vec2(pos.x, pos.y));
    return button;
}