#include "FlxVirtualKeyboard.h"
#include "FlxG.h"

static const int SPACE = 1;
static const int CAP = 2;
static const int ENT = 3;
static const int BACK = 4;

static const int keyboardKeys[] = {
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', BACK,
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
    CAP, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ENT,
    'z', 'x', 'c', 'v', 'b', 'n', 'm',
    SPACE
};


FlxVirtualKeyboard::FlxVirtualKeyboard(float x, float y, const char *backgroundImg, const char *buttonImg,
                                    int buttonW, int buttonH, const char *buttonFont, int buttonFontSize,
                                    int buttonTextColor, float spacingX , float spacingY)
{
    capsLock = false;

    // add background
    FlxSprite *background = new FlxSprite(x, y, backgroundImg);
    background->isGUI = true;
    background->scrool = false;
    add(background);

    // add buttons
    int column = 0, row = 0;
    float currentX = x + (spacingX * 3.5), currentY = y + (spacingY * 2);

    for(unsigned int i = 0; i < sizeof(keyboardKeys) / sizeof(int); i++) {
        int currentKey = keyboardKeys[i];
        std::wstring text;

        if(currentKey == CAP) text = L"CAP";
        else if(currentKey == SPACE) text = L"_";
        else if(currentKey == ENT) text = L"ENT";
        else if(currentKey == BACK) text = L"BAC";
        else text += (wchar_t)currentKey;

        FlxButton *button = new FlxButton(currentX, currentY, buttonImg, buttonW, buttonH);
        button->setTextFormat(text.c_str(), buttonFont, buttonFontSize, buttonTextColor);
        button->onPressed = std::bind(&FlxVirtualKeyboard::pressedCallback, this, std::placeholders::_1);
        button->onReleased = std::bind(&FlxVirtualKeyboard::releasedCallback, this, std::placeholders::_1);
        add(button);

        currentX += buttonW + spacingX;
        column++;
        if(row == 0 && column == 11) {
            row = 1;
            column = 0;
            currentX = x + (spacingX * 5);
            currentY += spacingY * 3;
        }
        else if(row == 1 && column == 10) {
            row = 2;
            column = 0;
            currentX = x + (spacingX * 3.5);
            currentY += 3 * (spacingY);
        }
        else if(row == 2 && column == 11) {
            row = 3;
            column = 0;
            currentX = x + (spacingX * 10);
            currentY += 3 * (spacingY);
        }
        else if(row == 3 && column == 7) {
            column = 0;
            currentX = x + (spacingX * 19);
            currentY += 3 * (spacingY);
        }
    }
}


void FlxVirtualKeyboard::pressedCallback(FlxButton *button) {
    if(button->onText->text == L"ENT") {
        FlxG::key->simulateKeyDown(FlxKey::Enter);
    }
    else if(button->onText->text == L"CAP") {
        capsLock = !capsLock;

        for(unsigned int i = 1; i < members.size(); i++) {
            FlxButton *b = (FlxButton*)members[i];

            if(b->onText->text != L"ENT" &&  b->onText->text != L"CAP" &&
               b->onText->text != L"_" && b->onText->text != L"BAC")
            {
                if(capsLock) {
                    b->onText->text[0] = b->offText->text[0] = (wchar_t) std::toupper(b->onText->text[0]);
                }
                else {
                   b->onText->text[0] = b->offText->text[0] = (wchar_t) std::tolower(b->onText->text[0]);
                }
            }
        }
    }
    else if(button->onText->text == L"_") {
        FlxG::key->simulateKeyDown(FlxKey::Space);
    }
    else if(button->onText->text == L"BAC") {
        FlxG::key->simulateKeyDown(FlxKey::Back);
    }
    else {
        FlxG::key->simulateKeyDown((FlxKey::KeyCode) std::tolower(button->onText->text[0]));
    }
}


void FlxVirtualKeyboard::releasedCallback(FlxButton *button) {
    if(button->onText->text == L"ENT") {
        FlxG::key->simulateKeyUp(FlxKey::Enter);
    }
    else if(button->onText->text == L"CAP") {
    }
    else if(button->onText->text == L"_") {
        FlxG::key->simulateKeyUp(FlxKey::Space);
    }
    else if(button->onText->text == L"BAC") {
        FlxG::key->simulateKeyUp(FlxKey::Back);
    }
    else {
        FlxG::key->simulateKeyUp((FlxKey::KeyCode) std::tolower(button->onText->text[0]));
    }
}

